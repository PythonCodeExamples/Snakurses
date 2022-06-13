#include "deque.h"

#include <stdlib.h>
#include <stdio.h>

/* Utilities for module realization*/
static void delete_node_callback(struct deque_node *node, void *user_data)
{
    if (user_data)
        return;
    free(node);
}

static void
for_every_node_recursion(
    struct deque_node *first,
    node_callback callback,
    void *user_data)
{
    if (!first)
        return;
    for_every_node_recursion(first->next, callback, user_data);
    callback(first, user_data);
}
/* =============================== */

struct deque *create_deque()
{
    struct deque *res;
    res = malloc(sizeof(struct deque));
    res->first = NULL;
    res->last = NULL;
    res->length = 0;
    return res;
}

void delete_deque(struct deque *deq)
{
    if (!deq)
        return;
    for_every_node(deq, &delete_node_callback, NULL);
    free(deq);
}

void deque_push_front(struct deque *deq, const int x, const int y)
{
    struct deque_node *tmp;
    if (!deq)
        return;
    tmp = malloc(sizeof(struct deque_node));
    tmp->coords.x = x;
    tmp->coords.y = y;
    tmp->prev = NULL;
    tmp->next = deq->first;

    if (!deq->first)
        deq->last = tmp;
    else
        deq->first->prev = tmp;
    deq->first = tmp;
    (deq->length)++;
}

void deque_push_back(struct deque *deq, const int x, const int y)
{
    struct deque_node *tmp;
    if (!deq)
        return;
    tmp = malloc(sizeof(struct deque_node));
    tmp->coords.x = x;
    tmp->coords.y = y;
    tmp->next = NULL;
    tmp->prev = deq->last;

    if (!deq->first)
        deq->first = tmp;
    else
        deq->last->next = tmp;
    deq->last = tmp;
    (deq->length)++;
}

void deque_pop_front(struct deque *deq, int *x, int *y)
{
    struct deque_node *tmp;

    if (!deq || !deq->first)
        return;

    tmp = deq->first;
    *x = deq->first->coords.x;
    *y = deq->first->coords.y;

    deq->first = deq->first->next;
    if (deq->first)
        deq->first->prev = NULL;
    else
        deq->last = NULL;

    free(tmp);
    (deq->length)--;
}

void deque_pop_back(struct deque *deq, int *x, int *y)
{
    struct deque_node *tmp;

    if (!deq || !deq->first)
        return;

    tmp = deq->last;
    *x = deq->last->coords.x;
    *y = deq->last->coords.y;

    deq->last = deq->last->prev;
    if (deq->last)
        deq->last->next = NULL;
    else
        deq->first = NULL;

    free(tmp);
    (deq->length)--;
}

void for_every_node(struct deque *deq, node_callback callback, void *user_data)
{
    for_every_node_recursion(deq->first, callback, user_data);
}

