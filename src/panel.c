#include "panel.h"

#include <stdlib.h>
#include <stdarg.h>

#include "button_list.h"
#include "button_callbacks.h"

struct panel *create_panel(struct button *btn, ...)
{
    struct panel *res;
    struct button *tmp;
    int i;
    va_list vl;

    res = malloc(sizeof(struct panel));
    res->blist = create_button_list();
    res->active_button_idx = 0;

    add_button_to_list(res->blist, btn);
    va_start(vl, btn);
    i = 0;
    while ((tmp = va_arg(vl, struct button *)) != NULL) {
        if (tmp->active == 'Y')
            res->active_button_idx = tmp->id;
        add_button_to_list(res->blist, tmp);
        i++;
    }
    res->max_button_idx = i;
    va_end(vl);

    return res;
}

void delete_panel(struct panel *pnl)
{
    delete_button_list(pnl->blist);
    free(pnl);
}

void set_button_coord_by_index(struct panel *pnl, const int btn_idx, const int x, const int y)
{
    struct set_coords_user_data ud;
    ud.idx = btn_idx;
    ud.x = x;
    ud.y = y;
    for_buttons(pnl->blist, &set_coords_button, (void*)&ud);
}

void draw_panel(struct panel *pnl)
{
    for_buttons(pnl->blist, &draw_button, NULL);
}

void hide_panel(struct panel *pnl)
{
    for_buttons(pnl->blist, &hide_button, NULL);
}

void increase_active_button_index(struct panel *pnl)
{
    if (pnl->active_button_idx == pnl->max_button_idx)
        pnl->active_button_idx = 0;
    else
        (pnl->active_button_idx)++;
    set_active_button_by_index(pnl, pnl->active_button_idx);
}

void decrease_active_button_index(struct panel *pnl)
{

    if (pnl->active_button_idx == 0)
        pnl->active_button_idx = pnl->max_button_idx;
    else
        (pnl->active_button_idx)--;
    set_active_button_by_index(pnl, pnl->active_button_idx);
}

void set_active_button_by_index(struct panel *pnl, int idx)
{
    for_buttons(pnl->blist, &deactivate_button, NULL);
    for_buttons(pnl->blist, &activate_button, (int*)&idx);
}
