#include "apple.h"

#include <ncurses.h>
#include <stdlib.h>

#include "colors.h"

/* Some utilites for module realization */
static int
get_random_int(const double max_val)
{
    return (int)((max_val+1)*rand() / (RAND_MAX+1.0));
}

static
void change_apple_pos(struct apple *apl, const int maxx, const int maxy)
{
    apl->coords.x = get_random_int(maxx);
    apl->coords.y = get_random_int(maxy);
}
/* ==================================== */

struct apple *create_apple()
{
    struct apple *res;
    res = malloc(sizeof(struct apple));
    res->coords.x = 0;
    res->coords.y = 0;
    return res;
}

void delete_apple(struct apple *apl)
{
    free(apl);
}

void show_apple(struct apple *apl)
{
    attron(COLOR_PAIR(RED_PAIR) | A_BOLD);
    move(apl->coords.y, apl->coords.x);
    addch('A');
    attroff(COLOR_PAIR(RED_PAIR) | A_BOLD);
}

void hide_apple(struct apple *apl)
{
    move(apl->coords.y, apl->coords.x);
    addch(' ');
}

void move_apple(struct apple *apl, const int maxx, const int maxy)
{
    hide_apple(apl);
    change_apple_pos(apl, maxx, maxy);
    show_apple(apl);
}
