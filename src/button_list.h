/* * * * * * * * * * * * * * * * *
 * Module declares button list   *
 * realization for panel module  *
 * * * * * * * * * * * * * * * * */

#ifndef _BUTTON_LIST_H_SENTRY_
#define _BUTTON_LIST_H_SENTRY_

#include "button.h"
#include "button_callbacks.h"

struct button_list_item {
    struct button *btn;
    struct button_list_item *next;
};

struct button_list {
    struct button_list_item *first;
    int length;
};


/* Allocates button_list on heap */
struct button_list *create_button_list();
/* Free button_list from heap */
void delete_button_list(struct button_list *blist);

/* Inserts button to button_list as first element */
void add_button_to_list(struct button_list *blist, struct button *btn);
/* Removes first button from button_list */
void remove_button_from_list(struct button_list *blist);

/* ---FUNCTION FOR CALLBACK USAGE--- */
/* Declares recursive calls for button_list_item */
void for_buttons_recursion(
    struct button_list_item *first,
    button_callback callback, // button_callback declared in button.h 
    void *user_data
);
/* Calls callback for every button in blist */
void for_buttons(
    struct button_list *blist,
    button_callback callback,
    void *user_data
);

#endif /*_BUTTON_LIST_H_SENTRY_*/