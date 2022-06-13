#include "game_cycle.h"

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "snake.h"
#include "apple.h"

static void handle_resize(struct apple *apl, int *x, int *y)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    *x = col-1; *y = row-1;
    if (apl->coords.x > *x)
        apl->coords.x = *x;
    if (apl->coords.y > *y)
        apl->coords.y = *y;
    erase();
}

static void show_score(struct snake *snk)
{
    move(0,0);
    addstr("         ");
    move(0,0);
    printw("SCORE: %d", snk->deq->length-3);
}

void run_game(int *maxx, int *maxy)
{
    int x, y, key;
    struct snake *snk;
    struct apple *apl;
    srand(time(NULL));
    timeout(100);
    getmaxyx(stdscr, y, x);
    *maxx = x-1; *maxy = y-1;
    x = (*maxx)/2; y = (*maxy)/2;
    snk = create_snake(x, y);
    apl = create_apple();

    show_snake(snk);
    move_apple(apl, *maxx, *maxy);
    refresh();

    while ((key = getch()) != 27) {
        switch (key) {
        case KEY_UP:
            change_dir_snake(snk, DIR_UP);
            break;
        case KEY_DOWN:
            change_dir_snake(snk, DIR_DOWN);
            break;
        case KEY_RIGHT:
            change_dir_snake(snk, DIR_RIGHT);
            break;
        case KEY_LEFT:
            change_dir_snake(snk, DIR_LEFT);
            break;
        case KEY_RESIZE:
            handle_resize(apl, maxx, maxy);
            break;
        case ERR:
            break;
        }
        show_score(snk);
        move_snake(snk, *maxx, *maxy);
        if (is_collided_snake(snk, apl->coords.x, apl->coords.y)) {
            move_apple(apl, *maxx, *maxy);
            grow_snake(snk);
        }
        show_apple(apl);
        refresh();
    }
    delete_apple(apl);
    delete_snake(snk);
}
