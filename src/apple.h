/* * * * * * * * * * * * * * * * * *
 * Module for apple representation *
 * * * * * * * * * * * * * * * * * */

#ifndef _APPLE_H_SENTRY_
#define _APPLE_H_SENTRY_

struct apple {
    struct { int x, y; } coords;
};

/* Allocates struct apple on heap */
struct apple *create_apple();
/* Free allocated memory on heap */
void delete_apple(struct apple *apl);

/* Draws apple on surface */
void show_apple(struct apple *apl);
/* Hides apple from surface */
void hide_apple(struct apple *apl);

/* Hides apple, changes
 * coordinates and draw it on */
void move_apple(
    struct apple *apl,
    const int maxx,
    const int maxy
    );

#endif /*_APPLE_H_SENTRY_*/
