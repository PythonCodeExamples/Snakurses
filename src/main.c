#include <ncurses.h>
#include <unistd.h>

#include "menu.h"
#include "game_cycle.h"
#include "colors.h"

enum {
    key_escape = 27,
    delay_duration = 100
};

void init_ncurses(int *maxx, int *maxy)
{
    /* INIT NCURSES */
    int row, col;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, 1);
    curs_set(0);
    getmaxyx(stdscr, row, col);
    *maxx = col-1; *maxy = row-1;

    /* INIT COLORS */
    if (has_colors())
        start_color();
    init_pair(RED_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(CYAN_PAIR, COLOR_CYAN, COLOR_BLACK);
    init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);
}

int main()
{
    int maxx, maxy;
    init_ncurses(&maxx, &maxy);
    switch (run_menu(&maxx, &maxy)) {
    case CODE_PLAY:
        erase();
        run_game(&maxx, &maxy);
    case CODE_EXIT:
        break;
    }
    endwin();
    return 0;
}
