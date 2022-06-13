#include "button_callbacks.h"

#include <ncurses.h>

#include "button.h"
#include "colors.h"

void draw_button(struct button *but, void *user_data)
{
    if (user_data)
        return;
    move(but->y, but->x);
    if (but->active == 'Y')
        attrset(COLOR_PAIR(CYAN_PAIR) | A_UNDERLINE);
    addstr(but->label);
    attroff(COLOR_PAIR(CYAN_PAIR) | A_UNDERLINE);
}

void hide_button(struct button *but, void *user_data)
{
    int i;
    if (user_data)
        return;
    move(but->y, but->x);
    for (i = 0; i < but->lsize; i++)
        addch(' ');
}

void set_coords_button(struct button *but, void *user_data)
{
    struct set_coords_user_data *ud = user_data;
    if (ud->idx == but->id) {
        but->x = ud->x;
        but->y = ud->y;
    }
}

void deactivate_button(struct button *but, void *user_data)
{
    if (user_data)
        return;
    if (but->active == 'Y')
        but->active = 'N';
}

void activate_button(struct button *but, void *user_data)
{
    if (but->id == *(int*)user_data)
        but->active = 'Y';
}
