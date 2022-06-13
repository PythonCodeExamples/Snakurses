/* * * * * * * * * * * * * * * * * * *
 * Module for button representation  *
 * * * * * * * * * * * * * * * * * * */

#ifndef _BUTTON_H_SENTRY_
#define _BUTTON_H_SENTRY_

struct button {
    char *label;
    int id;
    int lsize; /* Label size */
    int x, y;
    char active; /* Y or N */
};

/* Allocaetes button on heap */
struct button*
create_button(
    const int x,
    const int y,
    const char *label,
    const char active
);

/* Free button from heap */
void delete_button(struct button *but);

/* Callback signature for button */
typedef void (*button_callback)(struct button *, void *);

#endif /*_BUTTON_H_SENTRY_*/