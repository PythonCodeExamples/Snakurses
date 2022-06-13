/* * * * * * * * * * * * * * * * * * * * * *
 * Module for button panel representation  *
 * * * * * * * * * * * * * * * * * * * * * */

#ifndef _PANEL_H_SENTRY_
#define _PANEL_H_SENTRY_

#include "button.h"

struct panel {
    struct button_list *blist;
    int active_button_idx;
    int max_button_idx;
};

/* Allocates panel on heap.
 * Accepts variadic number of button. (not less than 1)
 * Last pointer must be NULL.
 * * * * * * * * * * * * * * * * * * * * * * */
struct panel *create_panel(struct button *btn, ...);
/* Free panel from heap */
void delete_panel(struct panel *pnl);

/* Gets button from panel by id
 * and sets coordinates to x and y*/
void set_button_coord_by_index(
    struct panel *pnl,
    const int btn_idx,
    const int x, const int y
);

/* Draws panel on surface */
void draw_panel(struct panel *pnl);
/* Hide panel from surface */
void hide_panel(struct panel *pnl);

/* Sets active button as passive,
 * sets next button by index as active */
void increase_active_button_index(struct panel *pnl);
/* Reversing increase_active_button_index */
void decrease_active_button_index(struct panel *pnl);
/* Gets button from panel by id
 * and sets the button as acrive */
void set_active_button_by_index(struct panel *pnl, int idx);

#endif /*_PANEL_H_SENTRY_*/