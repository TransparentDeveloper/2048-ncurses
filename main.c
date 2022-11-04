#include <ncurses.h>

int main(int argc, char const *argv[]) {
    WINDOW *window;

    initscr();

    if (has_colors() == FALSE) {
        puts("Terminal does not support colors!");
        endwin();
        return 1;
    } else {
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_WHITE);
    }

    refresh();

    window = newwin(18, 80, 0, 0);

    wbkgd(window, COLOR_PAIR(1));

    wprintw(window, "Hello!");

    wrefresh(window);

    getch();
    endwin();
    return 0;
}
