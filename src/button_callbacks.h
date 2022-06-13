/* * * * * * * * * * * * * * * * * * * * * * * *
 * Module describes some callbacks for button. *
 * Callbacks are declared in button.h file     *
 * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _BUTTON_CALLBACKS_H_SENTRY_
#define _BUTTON_CALLBACKS_H_SENTRY_

#include "button.h"

struct set_coords_user_data {
    int idx, x, y;
};

/* Draws button on surface */
void draw_button(struct button *but, void *user_data);
/* Hide button from surface */
void hide_button(struct button *but, void *user_data);

/* Changes button coordinates */
void set_coords_button(struct button *but, void *user_data);

/* --- BUTTON HOVERING --- */
/* Sets button to passive statement (no lighting) */
void deactivate_button(struct button *but, void *user_data);
/* Sets button to active statement */
void activate_button(struct button *but, void *user_data);

#endif /*_BUTTON_CALLBACKS_H_SENTRY_*/