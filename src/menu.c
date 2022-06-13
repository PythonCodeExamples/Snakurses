#include "menu.h"

#include <ncurses.h>
#include <string.h>

#include "panel.h"
#include "button.h"
#include "colors.h"

/* === BUTTON LABLES === */
static const char *blabel1 = "PLAY";
static const char *blabel2 = "QUIT";

/* === GAME LABLES ===== */
static const char *change_button_controls = "Change button: arrows";
static const char *press_button_controls = "Press button: Enter";
static const char *exit_controls = "Exit game: ESC";
static const char *game_banner[] = {
"  _________              __\n",
" /   _____/ ____ _____  |  | __ ____ \n",
" \\_____  \\ /    \\\\__  \\ |  |/ // __ \\\n",
" /        \\   |  \\/ __ \\|    <\\  ___/\n",
"/_______  /___|  (____  /__|_ \\\\___  >\n",
"        \\/     \\/     \\/     \\/    \\/", NULL};

enum {
    key_enter = 10,
    key_escape = 27
};

static void draw_banner(const int x, int y)
{
    const char **gbcopy;
    attrset(COLOR_PAIR(RED_PAIR) | A_BOLD);
    for (gbcopy = game_banner; *gbcopy; y++, gbcopy++) {
        move(y, x);
        addstr(*gbcopy);
    }
    attroff(COLOR_PAIR(RED_PAIR) | A_BOLD);
}


static void draw_controls(const int x, const int y)
{
    draw_banner(
        (x-strlen(game_banner[3]))/2,
        0);
    move(y-2, 0);
    addstr(change_button_controls);
    move(y-1, 0);
    addstr(press_button_controls);
    move(y, 0);
    addstr(exit_controls);
}

static void center_button(struct panel *pnl, const int x, const int y)
{
    set_button_coord_by_index(pnl, 0, (x-strlen(blabel1))/2, y/2-1);
    set_button_coord_by_index(pnl, 1, (x-strlen(blabel2))/2, y/2+1);
}

static void handle_resize(struct panel *pnl, int x, int y)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    x = col-1; y = row-1;
    center_button(pnl, x, y);
    hide_panel(pnl);
    erase();
    draw_controls(x, y);
}

enum MENU_RET_CODES run_menu(int *maxx, int *maxy)
{
    /* INITIALIZATION */
    struct panel *pnl;
    struct button *btn1, *btn2;
    int k;
    btn1 = create_button(0, 0, blabel1, 'Y');
    btn2 = create_button(0, 0, blabel2, 'N');
    pnl = create_panel(btn1, btn2, NULL);
    center_button(pnl, *maxx, *maxy);

    /* FIRST DRAWING */
    draw_controls(*maxx, *maxy);
    draw_panel(pnl);
    refresh();

    /* KEY HANDLING CYCLE */
    while ((k = getch()) != key_escape) {
        switch (k) {
        case KEY_UP:
            decrease_active_button_index(pnl);
            break;
        case KEY_DOWN:
            increase_active_button_index(pnl);
            break;
        case KEY_RESIZE:
            handle_resize(pnl, *maxx, *maxy);
            break;
        case key_enter:
            k = pnl->active_button_idx;
            delete_panel(pnl);
            return k;
        }
        draw_panel(pnl);
        refresh();
    }
    delete_panel(pnl);
    return CODE_EXIT;
}
