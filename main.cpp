#include "ControlArray.hpp"
#include <ncurses.h>
#include <stack>
#include <stdlib.h>
#include <string>

using namespace std;

#define SQ_HEIGHT 5
#define SQ_WIDTH 12
#define NUM_ROW 4
#define NUM_COL 4

void create_board(void);
void destroy_board(void);
void display_value(ControlArray *CA);

WINDOW *BOARD[16];

int main(int argc, char **argv) {
    int key;

    initscr();
    noecho();
    curs_set(FALSE);

    /* Assert window */

    if ((LINES < 24) || (COLS < 80)) {
        endwin();
        puts("Your terminal needs to be at least 80x24");
        exit(2);
    }

    /* Assert color and Set_color_pair */

    if (has_colors() == FALSE) {
        puts("Terminal does not support colors!");
        endwin();
        return 1;
    } else {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_CYAN, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_BLUE, COLOR_BLACK);
        init_pair(7, COLOR_YELLOW, COLOR_BLACK);

        init_pair(8, COLOR_CYAN, COLOR_BLUE);
        init_pair(9, COLOR_GREEN, COLOR_BLUE);
        init_pair(10, COLOR_MAGENTA, COLOR_BLUE);
        init_pair(11, COLOR_RED, COLOR_BLUE);
        init_pair(12, COLOR_WHITE, COLOR_BLUE);

        init_pair(13, COLOR_YELLOW, COLOR_WHITE);
        init_pair(14, COLOR_BLUE, COLOR_WHITE);
        init_pair(15, COLOR_GREEN, COLOR_WHITE);
        init_pair(16, COLOR_RED, COLOR_WHITE);
        init_pair(17, COLOR_BLACK, COLOR_WHITE);
    }

    clear();

    /* Print game name */
    mvprintw(0, 0, "#######   #######      ###    #######");
    mvprintw(1, 0, "##   ##   #    ##     # ##    #    ##");
    mvprintw(2, 0, "    ###   #    ##    #  ##    #######");
    mvprintw(3, 0, "   ###    #    ##   #   ##    #   ###");
    mvprintw(4, 0, " ##       #    ##   #######   #    ##");
    mvprintw(5, 0, "#######   #######       ##    #######");
    refresh();

    /* initialize array */
    ControlArray CA;
    CA.create_random();

    /* initialize Stack */
    stack<int> values_log;
    stack<int> scores_log;

    /* Print block */
    display_value(&CA);

    /* Print score */
    WINDOW *score_board = newwin(3, 20, 2 + 5, 33);
    box(score_board, 0, 0);
    mvwprintw(score_board, 1, 2, "score");
    mvwprintw(score_board, 1, 10, "%9d", CA.get_score());
    wrefresh(score_board);

    /* Print term */
    WINDOW *term_board = newwin(3, 20, 2 + 5, 5);
    box(term_board, 0, 0);
    mvwprintw(term_board, 1, 2, "term");
    mvwprintw(term_board, 1, 10, "%9d", CA.get_term());
    wrefresh(term_board);

    /* initialize array for checking change*/
    int compare_arr_1[NUM_ROW][NUM_COL] = {};
    int compare_arr_2[NUM_ROW][NUM_COL] = {};

    /*initailize variable for score*/
    int score = 0;

    while (1) {
        key = getch();

        /* Moving Page */

        // Save state before moving
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                compare_arr_1[row][col] = CA.at(row, col);
            }
        }
        score = CA.get_score();

        switch (key) {
        case 'w':
            CA.move_block_up();
            break;
        case 's':
            CA.move_block_down();
            break;
        case 'a':
            CA.move_block_left();
            break;
        case 'd':
            CA.move_block_right();
            break;

        case 'b': // undo
            if (CA.get_term() == 1)
                break;

            for (int row = NUM_ROW - 1; row >= 0; row--) {
                for (int col = NUM_COL - 1; col >= 0; col--) {
                    CA.set_arr2d_compoent(row, col, values_log.top());
                    values_log.pop();
                }
            }

            CA.set_score(scores_log.top());
            scores_log.pop();
            CA.decrease_term();

            break;

        default:
            break;
        }

        if ((key == 'q') || (key == 'Q'))
            break;

        /* Checking Page */

        // Save state after moving
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                compare_arr_2[row][col] = CA.at(row, col);
            }
        }

        if (key == 'b') {
        }
        // if (compare_arr_1 == compare_arr_2), do not move
        else if (!CA.is_possible_moving(compare_arr_1, compare_arr_2)) {
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    CA.set_arr2d_compoent(row, col, compare_arr_1[row][col]);
                }
            }
        }
        // if (compare_arr_1 == compare_arr_2), do move
        else {

            // Update stack
            for (int row = 0; row < NUM_ROW; row++) {
                for (int col = 0; col < NUM_COL; col++) {
                    values_log.push(compare_arr_1[row][col]);
                }
            }
            scores_log.push(score);
            // create new block
            CA.create_random();
            // go next term
            CA.increase_term();
        }

        /* Displaying Page */

        // Update value board
        display_value(&CA);

        // Update score board
        mvwprintw(score_board, 1, 2, "score");
        mvwprintw(score_board, 1, 10, "%9d", CA.get_score());
        wrefresh(score_board);

        // Update term board
        mvwprintw(term_board, 1, 2, "term");
        mvwprintw(term_board, 1, 10, "%9d", CA.get_term());
        wrefresh(term_board);
    };

    clear();
    mvprintw(0, 0,
             "#######   #######   #######   #######   #######   #######   "
             "#######   #######");
    mvprintw(1, 0,
             "#######   #######   #######   #######   #######   #######   "
             "#######   #######");
    mvprintw(2, 0,
             "#######   #######   #######   #######   #######   #######   "
             "#######   #######");
    mvprintw(3, 0,
             "#######   #######   #######   #######   #######   #######   "
             "#######   #######");
    mvprintw(4, 0,
             "#######   #######   #######   #######   #######   #######   "
             "#######   #######");
    mvprintw(5, 0,
             "#######   #######   #######   #######   #######   #######   "
             "#######   #######");
    mvprintw(7, 0, "Your score is : %9d", CA.get_score());
    mvprintw(8, 0, "(Press 'q' to exit.)");
    refresh();

    while (1) {
        key = getch();
        if ((key == 'q') || (key == 'Q'))
            break;
    }

    /* when done, free up the board, and exit */
    destroy_board();

    endwin();
    exit(0);
}

void display_value(ControlArray *CA) {
    int num_value;
    int num_color_pair;

    int tmp;

    for (int row = 0; row < NUM_ROW; row++) {
        for (int col = 0; col < NUM_COL; col++) {
            wclear(BOARD[row * NUM_COL + col]);
            create_board();

            num_value = CA->at(row, col);

            num_color_pair = 1;

            for (int tmp = 1; tmp < num_value; tmp *= 2)
                num_color_pair++;

            mvwprintw(BOARD[row * NUM_COL + col], SQ_HEIGHT / 2, SQ_WIDTH / 4,
                      "%5d", num_value);
            wbkgd(BOARD[row * NUM_COL + col], COLOR_PAIR(num_color_pair));
            wrefresh(BOARD[row * NUM_COL + col]);
        }
    }
}

void create_board(void) {
    int i;
    int starty, startx;

    starty = 10;
    for (i = 0; i < NUM_COL; i++) {
        startx = 5 + i * SQ_WIDTH;
        BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty, startx);
    }

    starty += SQ_HEIGHT;
    for (i = NUM_COL; i < NUM_COL * 2; i++) {
        startx = 5 + (i % 4) * SQ_WIDTH;
        BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty, startx);
    }

    starty += SQ_HEIGHT;
    for (i = NUM_COL * 2; i < NUM_COL * 3; i++) {
        startx = 5 + (i % 4) * SQ_WIDTH;
        BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty, startx);
    }

    starty += SQ_HEIGHT;
    for (i = NUM_COL * 3; i < NUM_COL * 4; i++) {
        startx = 5 + (i % 4) * SQ_WIDTH;
        BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty, startx);
    }

    /* put border on each window and refresh */

    for (i = 0; i < 30; i++) {
        box(BOARD[i], 0, 0);
        // wrefresh(BOARD[i]);
    }
}

void destroy_board(void) {
    int i;

    /* erase every box and delete each window */

    for (i = 0; i < 30; i++) {
        wborder(BOARD[i], ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wrefresh(BOARD[i]);
        delwin(BOARD[i]);
    }
}
