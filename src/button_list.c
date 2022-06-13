#include "button_list.h"

#include <stdlib.h>

/* Function for module realization */
static void
clear_button_list(struct button_list *blist)
{
    while(blist->first)
        remove_button_from_list(blist);
}
/* ========================== */

struct button_list *create_button_list()
{
    struct button_list *res;
    res = malloc(sizeof(struct button_list));
    res->first = NULL;
    res->length = 0;
    return res;
}

void delete_button_list(struct button_list *blist)
{
    clear_button_list(blist);
    free(blist);
}

void add_button_to_list(struct button_list *blist, struct button *btn)
{
    struct button_list_item *tmp;
    tmp = malloc(sizeof(struct button_list_item));
    tmp->btn = btn;
    tmp->next = blist->first;
    blist->first = tmp;
    (blist->length)++;
}

void remove_button_from_list(struct button_list *blist)
{
    struct button_list_item *tmp;
    tmp = blist->first;
    blist->first = blist->first->next;
    delete_button(tmp->btn);
    free(tmp);
    (blist->length)--;
}

void for_buttons_recursion(struct button_list_item *first, button_callback callback, void *user_data)
{
    if (!first)
        return;
    for_buttons_recursion(first->next, callback, user_data);
    callback(first->btn, user_data);
}

void for_buttons(struct button_list *blist, button_callback callback, void *user_data)
{
    for_buttons_recursion(blist->first, callback, user_data);
}