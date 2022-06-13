#include "snake.h"

#include <ncurses.h>
#include <stdlib.h>

#include "deque.h"
#include "colors.h"

enum { start_length = 3 };

struct snake *create_snake(const int x, const int y)
{
    int i;
    struct snake *res;

    res = malloc(sizeof(struct snake));
    res->deq = create_deque();
    res->dir = DIR_NEUTRAL;
    res->length = start_length;

    for (i = 0; i < start_length; i++)
        deque_push_front(res->deq, x, y);

    return res;
}

void delete_snake(struct snake *snk)
{
    delete_deque(snk->deq);
    free(snk);
}

static void
show_node_callback(struct deque_node *node, void *user_data)
{
    if (user_data)
        return;
    move(node->coords.y, node->coords.x);
    addch('*');
}

void show_snake(struct snake *snk)
{
    attron(COLOR_PAIR(GREEN_PAIR) | A_BOLD);
    for_every_node(snk->deq, &show_node_callback, NULL);
    attroff(COLOR_PAIR(GREEN_PAIR) | A_BOLD);
}

static void
hide_node_callback(struct deque_node *node, void *user_data)
{
    if (user_data)
        return;
    move(node->coords.y, node->coords.x);
    addch(' ');
}

void hide_snake(struct snake *snk)
{
    for_every_node(snk->deq, &hide_node_callback, NULL);
}

static void
check_coord(int *coord, const int maxval)
{
    if (*coord < 0)
        *coord = maxval;
    else if (*coord > maxval)
        *coord = 0;
}

static void
do_move(struct snake *snk,
        const int xd, const int yd,
        const int maxx, const int maxy)
{
    int x, y;
    deque_pop_back(snk->deq, &x, &y);
    x = snk->deq->first->coords.x + xd;
    y = snk->deq->first->coords.y + yd;
    check_coord(&x, maxx);
    check_coord(&y, maxy);
    deque_push_front(snk->deq, x, y);
}

void move_snake(struct snake *snk, const int maxx, const int maxy)
{
    hide_snake(snk);

    switch (snk->dir) {
    case DIR_UP:
        do_move(snk, 0, -1, maxx, maxy);
        break;
    case DIR_DOWN:
        do_move(snk, 0, 1, maxx, maxy);
        break;
    case DIR_LEFT:
        do_move(snk, -1, 0, maxx, maxy);
        break;
    case DIR_RIGHT:
        do_move(snk, 1, 0, maxx, maxy);
        break;
    case DIR_NEUTRAL:
        break;
    }
    if (snk->deq->length > 4)
        check_self_collision(snk);
    show_snake(snk);
}

void check_self_collision(struct snake *snk)
{
    struct deque_node *dn;   
    int x, y;

    for (dn = snk->deq->first->next; dn; dn = dn->next)
        if (is_collided_snake(snk, dn->coords.x, dn->coords.y)) {
            while (dn != snk->deq->last)
                deque_pop_back(snk->deq, &x, &y);
        }
}

void change_dir_snake(struct snake *snk, const enum dirs snkdir)
{
    if (snk->dir != -snkdir)
        snk->dir = snkdir;
}

int is_collided_snake(struct snake *snk, const int x, const int y)
{
    return snk->deq->first->coords.x == x && snk->deq->first->coords.y == y;
}

void grow_snake(struct snake *snk)
{
    deque_push_back(snk->deq, 0, 0);
}
