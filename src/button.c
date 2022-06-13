#include "button.h"

#include <string.h>
#include <stdlib.h>

static int auto_btn_id = 0;

struct button*
create_button(const int x, const int y, const char *label, const char active)
{
    struct button *res;
    res = malloc(sizeof(struct button));
    res->label = strdup(label);
    res->lsize = strlen(label);
    res->x = x;
    res->y = y;
    res->active = active;
    res->id = auto_btn_id;
    auto_btn_id++;
    return res;
}

void delete_button(struct button *but)
{
    free(but->label);
    free(but);
}

