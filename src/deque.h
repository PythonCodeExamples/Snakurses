/* * * * * * * * * * * * * * * * * * * * *
 * Module implements double-ended-queue  *
 * for coordinate type                   *
 * * * * * * * * * * * * * * * * * * * * */

#ifndef _DEQ_SENTRY_
#define _DEQ_SENTRY_

struct deque_node {
    struct {int x; int y;} coords;
    struct deque_node *next, *prev;
};


struct deque {
    struct deque_node *first, *last;
    int length;
};

/* Allocates deque on heap*/
struct deque *create_deque();
/* Free deque from heap */
void delete_deque(struct deque *deq);

/* --- ELEMENT INSERTIONS --- */
/* Insert element in the begining of deque */
void deque_push_front(struct deque *deq, const int x, const int y);
/* Insert element in the end of deque */
void deque_push_back(struct deque *deq, const int x, const int y);

/* --- ELEMENT REMOVES --- */
/* Remove element from the end of deque */
void deque_pop_front(struct deque *deq, int *x, int *y);
/* Remove element from the begininig of deque */
void deque_pop_back(struct deque *deq, int *x, int *y);

/* --- CALLBACK UTILITIES --- */
/* Callback signature */
typedef void (*node_callback)(struct deque_node *deq, void *user_data);
/* Calls callback for every node */
void for_every_node(
    struct deque *deq,
    node_callback callback,
    void *user_data
);

#endif /* _DEQ_SENTRY_ */
