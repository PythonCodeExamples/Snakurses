/* * * * * * * * * * * * * * * * * *
 * Module for apple representation *
 * * * * * * * * * * * * * * * * * */

#ifndef _SNAKE_H_SENTRY_
#define _SNAKE_H_SENTRY_

#include "deque.h"

enum dirs {
    DIR_NEUTRAL = 0,
    DIR_UP      = 1,
    DIR_DOWN    =-1,
    DIR_LEFT    = 2,
    DIR_RIGHT   =-2
};

struct snake {
    struct deque *deq;
    enum dirs dir;
    int length;
};

struct snake *create_snake(const int x, const int y);
void delete_snake(struct snake *snk);

void show_snake(struct snake *snk);
void hide_snake(struct snake *snk);
void move_snake(struct snake *snk, const int maxx, const int maxy);
void grow_snake(struct snake *snk);

void change_dir_snake(struct snake *snk, const enum dirs snkdir);
int is_collided_snake(struct snake *snk, const int x, const int y);
void check_self_collision(struct snake *snk);

#endif /*_SNAKE_H_SENTRY_*/
