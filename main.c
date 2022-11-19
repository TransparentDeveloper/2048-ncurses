/* senet.c */

#include <ncurses.h>
#include <stdlib.h>

#define SQ_HEIGHT 5
#define SQ_WIDTH 12
#define NUM_ROW 4
#define NUM_COL 4

void create_board(void);
void destroy_board(void);

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

    /* print welcome text */
    clear();

    mvprintw(0, 0, "2048");
    refresh();

    /* draw board */
    create_board();

    do {
        key = getch();
    } while ((key != 'q') && (key != 'Q'));

    /* when done, free up the board, and exit */
    destroy_board();

    endwin();
    exit(0);
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
        wrefresh(BOARD[i]);
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
