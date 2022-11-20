#include "contrlArray.cpp"
#include <ncurses.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define SQ_HEIGHT 5
#define SQ_WIDTH 12
#define NUM_ROW 4
#define NUM_COL 4

void create_board(void);
void destroy_board(void);
void display_value(blockLog *block);

WINDOW *BOARD[16];

int main(int argc, char **argv) {
    int key;

    /* initialize curses */

    initscr();
    noecho();
    curs_set(FALSE);

    if ((LINES < 24) || (COLS < 80)) {
        endwin();
        puts("Your terminal needs to be at least 80x24");
        exit(2);
    }

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

        init_pair(9, COLOR_CYAN, COLOR_BLUE);
        init_pair(10, COLOR_GREEN, COLOR_BLUE);
        init_pair(11, COLOR_MAGENTA, COLOR_BLUE);
        init_pair(12, COLOR_RED, COLOR_BLUE);
        init_pair(13, COLOR_WHITE, COLOR_BLUE);
        init_pair(8, COLOR_YELLOW, COLOR_BLUE);

        init_pair(14, COLOR_BLUE, COLOR_WHITE);
        init_pair(15, COLOR_GREEN, COLOR_WHITE);
        init_pair(16, COLOR_RED, COLOR_WHITE);
    }

    /* print welcome text */
    clear();

    mvprintw(0, 0, "2048");
    refresh();

    /* create value */
    blockLog block;
    block.term = 0;
    block.state = {0};
    create_random(&block);
    display_value(&block);
    // create_board();
    /* */

    while (1) {
        key = getch();
        switch (key) {

        case 'w':
            move_block_up(&block);
            create_random(&block);
            display_value(&block);
            break;
        case 's':
            move_block_down(&block);
            create_random(&block);
            display_value(&block);
            break;
        case 'a':
            move_block_left(&block);
            create_random(&block);
            display_value(&block);
            break;
        case 'd':
            move_block_right(&block);
            create_random(&block);
            display_value(&block);
            break;
        }

        if ((key == 'q') || (key == 'Q'))
            break;
    };

    /* when done, free up the board, and exit */
    destroy_board();

    endwin();
    exit(0);
}

void display_value(blockLog *block) {
    int num_value;
    int num_color_pair;

    int tmp;

    for (int row = 0; row < NUM_ROW; row++) {
        for (int col = 0; col < NUM_COL; col++) {
            wclear(BOARD[row * NUM_COL + col]);
            create_board();

            num_value = ((block->state).at(row)).at(col);

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

    starty = 5;
    for (i = 0; i < NUM_COL; i++) {
        startx = 10 + i * SQ_WIDTH;
        BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty, startx);
    }

    starty += SQ_HEIGHT;
    for (i = NUM_COL; i < NUM_COL * 2; i++) {
        startx = 10 + (i % 4) * SQ_WIDTH;
        BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty, startx);
    }

    starty += SQ_HEIGHT;
    for (i = NUM_COL * 2; i < NUM_COL * 3; i++) {
        startx = 10 + (i % 4) * SQ_WIDTH;
        BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty, startx);
    }

    starty += SQ_HEIGHT;
    for (i = NUM_COL * 3; i < NUM_COL * 4; i++) {
        startx = 10 + (i % 4) * SQ_WIDTH;
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

// int timer() {
//     int row = 10, col = 10;
//     initscr();
//     noecho();
//     curs_set(FALSE);

//     keypad(stdscr, TRUE);
//     addch(ACS_ULCORNER);
//     while (1) {
//         int input = getch();
//         clear();
//         switch (input) {
//         case KEY_UP:
//             mvprintw(row += 3, col, "[ A ]");
//             continue;
//         case KEY_DOWN:
//             mvprintw(row -= 3, col, "[ A ]");
//             continue;
//         case KEY_LEFT:
//             mvprintw(row, col -= 5, "[ A ]");
//             continue;
//         case KEY_RIGHT:
//             mvprintw(row, col += 5, "[ A ]");
//             continue;
//         }
//         if (input == 'q')
//             break;
//     }
//     endwin();
//     return 0;
// }
