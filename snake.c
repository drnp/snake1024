/**
 * Terminal based <SNAKE> game
 * Just an easter egg for 10.24
 *
 * by Dr.NP <np@bsgroup.org>
 */

#include "snake.h"

struct snake_scene scene;
WINDOW *ground = NULL;
WINDOW *score = NULL;
int ground_arr[GROUND_HEIGHT][GROUND_WIDTH];
int direction = DIR_UP;
int eggs = 0;
struct snake_section new_head;
struct snake god;
int speed_map[10] = {1000000, 500000, 300000, 200000, 120000, 80000, 70000, 60000, 50000, 40000};

// Splash box
void snake_welcome()
{
    // Don't ask me how you write this array ...
    // I am programmer who like SCRIPT!
    int font_tbl[14][58] = {
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}
    };

    // Blue splash
    WINDOW *welcome_box = newwin(24, 70, scene.win_height / 2 - 12, scene.win_width / 2 - 35);
    wbkgd(welcome_box, COLOR_PAIR(2));
    wattron(welcome_box, COLOR_PAIR(2));
    box(welcome_box, 0, 0);
    int line, idx;
    wattron(welcome_box, A_BOLD);
    for (line = 0; line < 14; line ++)
    {
        for (idx = 0; idx < 58; idx ++)
        {
            if (font_tbl[line][idx])
            {
                mvwaddch(welcome_box, 2 + line, 6 + idx, ACS_CKBOARD);
            }
        }
    }

    wattroff(welcome_box, COLOR_PAIR(2));
    wattron(welcome_box, COLOR_PAIR(3));
    mvwaddstr(welcome_box, 19, 23, "By Dr.NP <np@bsgroup.org>");
    wattroff(welcome_box, COLOR_PAIR(3));
    wattron(welcome_box, COLOR_PAIR(4));
    mvwaddstr(welcome_box, 21, 21, "Press any key to continue ...");
    wattroff(welcome_box, COLOR_PAIR(4));
    wattroff(welcome_box, A_BOLD);
    wrefresh(welcome_box);

    getch();
    wclear(welcome_box);
    wbkgd(welcome_box, COLOR_PAIR(1));
    wrefresh(welcome_box);
    delwin(welcome_box);

    return;
}

void snake_failed()
{
    WINDOW *failed_box = newwin(16, 60, scene.win_height / 2 - 8, scene.win_width / 2 - 30);
    wbkgd(failed_box, COLOR_PAIR(2));
    wattron(failed_box, COLOR_PAIR(2));
    box(failed_box, 0, 0);
    wattroff(failed_box, COLOR_PAIR(2));
    wattron(failed_box, A_BOLD);
    wattron(failed_box, COLOR_PAIR(4));
    mvwaddstr(failed_box, 7, 22, "Our snake DIE!!!");
    wattroff(failed_box, COLOR_PAIR(4));
    wattron(failed_box, COLOR_PAIR(3));
    mvwaddstr(failed_box, 10, 18, "Press any key to quit ...");
    wattroff(failed_box, COLOR_PAIR(3));
    wattroff(failed_box, A_BOLD);
    wrefresh(failed_box);

    getch();
    wclear(failed_box);
    wbkgd(failed_box, COLOR_PAIR(1));
    wrefresh(failed_box);
    delwin(failed_box);

    return;
}

void snake_easter()
{
    int heart_tbl[22][46] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int font_1_tbl[12][9] = {
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0}
    };

    int font_0_tbl[12][9] = {
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0}
    };

    int font_2_tbl[12][9] = {
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0}
    };

    int font_4_tbl[12][9] = {
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0}
    };

    int x, y;
    clear();
    attron(A_BOLD);
    attron(COLOR_PAIR(6));
    for (y = 0; y < 22; y ++)
    {
        for (x = 0; x < 46; x ++)
        {
            if (heart_tbl[y][x])
            {
                mvaddch(y + 10, x * 2 + 14, ACS_CKBOARD);
                mvaddch(y + 10, x * 2 + 15, ACS_CKBOARD);
            }
        }
    }

    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(1));
    for (y = 0; y < 12; y ++)
    {
        for (x = 0; x < 9; x ++)
        {
            if (font_1_tbl[y][x])
            {
                mvaddch(y + 24, x * 2 + 60, ACS_CKBOARD);
                mvaddch(y + 24, x * 2 + 61, ACS_CKBOARD);
            }
        }
    }

    for (y = 0; y < 12; y ++)
    {
        for (x = 0; x < 9; x ++)
        {
            if (font_0_tbl[y][x])
            {
                mvaddch(y + 24, x * 2 + 80, ACS_CKBOARD);
                mvaddch(y + 24, x * 2 + 81, ACS_CKBOARD);
            }
        }
    }

    for (y = 0; y < 12; y ++)
    {
        for (x = 0; x < 9; x ++)
        {
            if (font_2_tbl[y][x])
            {
                mvaddch(y + 24, x * 2 + 100, ACS_CKBOARD);
                mvaddch(y + 24, x * 2 + 101, ACS_CKBOARD);
            }
        }
    }

    for (y = 0; y < 12; y ++)
    {
        for (x = 0; x < 9; x ++)
        {
            if (font_4_tbl[y][x])
            {
                mvaddch(y + 24, x * 2 + 120, ACS_CKBOARD);
                mvaddch(y + 24, x * 2 + 121, ACS_CKBOARD);
            }
        }
    }

    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(7));
    mvaddstr(3, 2, "We are programmers, we are code MONKEYS");
    mvaddstr(4, 2, "We love console, we love terminal, we love IDEs, we love data, and, we also love BUGS");
    mvaddstr(5, 45, "So we ...");
    attroff(COLOR_PAIR(7));
    attroff(A_BOLD);

    refresh();

    getch();

    return;
}

// Two window : Playground & Score
void snake_main_scene()
{
    ground = newwin(38, 74, 3, 3);
    wbkgd(ground, COLOR_PAIR(1));
    wattron(ground, COLOR_PAIR(5));
    box(ground, 0, 0);
    wattroff(ground, COLOR_PAIR(5));
    wrefresh(ground);
    
    score = newwin(38, 40, 3, 80);
    wbkgd(score, COLOR_PAIR(1));
    wattron(score, COLOR_PAIR(1));
    box(score, 0, 0);
    wattroff(score, COLOR_PAIR(1));
    wattron(score, COLOR_PAIR(8));
    mvwaddch(score, 16, 4, ACS_CKBOARD);
    mvwaddch(score, 16, 5, ACS_CKBOARD);
    wattroff(score, COLOR_PAIR(8));
    wattron(score, COLOR_PAIR(9));
    mvwaddch(score, 18, 4, ACS_CKBOARD);
    mvwaddch(score, 18, 5, ACS_CKBOARD);
    wattroff(score, COLOR_PAIR(9));
    wattron(score, COLOR_PAIR(7));
    mvwaddch(score, 20, 4, ACS_CKBOARD);
    mvwaddch(score, 20, 5, ACS_CKBOARD);
    wattroff(score, COLOR_PAIR(7));
    wattron(score, COLOR_PAIR(10));
    mvwaddch(score, 22, 4, ACS_CKBOARD);
    mvwaddch(score, 22, 5, ACS_CKBOARD);
    wattroff(score, COLOR_PAIR(10));
    wattron(score, COLOR_PAIR(6));
    mvwaddch(score, 24, 4, ACS_CKBOARD);
    mvwaddch(score, 24, 5, ACS_CKBOARD);
    wattroff(score, COLOR_PAIR(6));
    wattron(score, A_BOLD);
    wattron(score, COLOR_PAIR(1));
    mvwaddstr(score, 16, 7, "-> Snake HEAD");
    mvwaddstr(score, 18, 7, "-> Snake BODY");
    mvwaddstr(score, 20, 7, "-> Egg, Eat ME!");
    mvwaddstr(score, 22, 7, "-> Pillow, Waaaaaool!");
    mvwaddstr(score, 24, 7, "-> Wall, PAINFUL");
    mvwaddstr(score, 27, 3, "Current length    :");
    mvwaddstr(score, 29, 3, "Current direction :");
    mvwaddstr(score, 31, 3, "Speed             :");
    wattroff(score, COLOR_PAIR(1));
    wattron(score, COLOR_PAIR(8));
    mvwaddstr(score, 5, 10, "Score : ");
    wattroff(score, COLOR_PAIR(8));
    wattroff(score, A_BOLD);
    wrefresh(score);

    int x, y;
    // Clear ground
    for (y = 0; y < GROUND_HEIGHT; y ++)
    {
        for (x = 0; x < GROUND_WIDTH; x ++)
        {
            ground_arr[y][x] = SNAKE_NULL;
        }
    }

    return;
}

// Display informations
void output_length()
{
    wattron(score, A_BOLD);
    wattron(score, COLOR_PAIR(7));
    mvwprintw(score, 27, 25, "%d    ", god.length);
    wattroff(score, COLOR_PAIR(7));
    wattroff(score, A_BOLD);
    wrefresh(score);

    return;
}

void output_direction()
{
    wattron(score, A_BOLD);
    wattron(score, COLOR_PAIR(10));
    switch (direction)
    {
        case DIR_UP : 
            mvwaddstr(score, 29, 25, "UP   ");
            break;
        case DIR_DOWN : 
            mvwaddstr(score, 29, 25, "DOWN ");
            break;
        case DIR_LEFT : 
            mvwaddstr(score, 29, 25, "LEFT ");
            break;
        case DIR_RIGHT : 
            mvwaddstr(score, 29, 25, "RIGHT");
            break;
        default :
            break;
    }

    wattroff(score, COLOR_PAIR(10));
    wattroff(score, A_BOLD);
    wrefresh(score);

    return;
}

void output_speed()
{
    wattron(score, A_BOLD);
    wattron(score, COLOR_PAIR(9));
    mvwprintw(score, 31, 25, "%d    ", scene.speed);
    wattroff(score, COLOR_PAIR(9));
    wattroff(score, A_BOLD);
    wrefresh(score);

    return;
}

void output_score()
{
    wattron(score, A_BOLD);
    wattron(score, A_BLINK);
    wattron(score, COLOR_PAIR(1));
    mvwprintw(score, 5, 20, "%d     ", god.score);
    wattroff(score, COLOR_PAIR(1));
    wattroff(score, A_BLINK);
    wattroff(score, A_BOLD);
    wrefresh(score);

    return;
}

// Put <god> to ground array
void draw_snake()
{
    int x, y;
    for (y = 0; y < GROUND_HEIGHT; y ++)
    {
        for (x = 0; x < GROUND_WIDTH; x ++)
        {
            // Let's clean god up
            if (SNAKE_HEAD == ground_arr[y][x] ||
                SNAKE_BODY == ground_arr[y][x] ||
                SNAKE_TAIL == ground_arr[y][x])
            {
                ground_arr[y][x] = SNAKE_NULL;
            }
        }
    }

    struct snake_section *section = god.head;
    while (section)
    {
        ground_arr[section->y][section->x] = section->type;
        section = section->next;
    }

    return;
}

// Output ground
void refresh_ground()
{
    int x, y;
    wattron(ground, A_BOLD);
    for (y = 0; y < GROUND_HEIGHT; y ++)
    {
        for (x = 0; x < GROUND_WIDTH; x ++)
        {
            switch (ground_arr[y][x])
            {
                case SNAKE_NULL : 
                    mvwaddch(ground, y + 1, x * 2 + 1, ' ');
                    mvwaddch(ground, y + 1, x * 2 + 2, ' ');
                    break;
                case SNAKE_WALL : 
                    wattron(ground, COLOR_PAIR(6));
                    mvwaddch(ground, y + 1, x * 2 + 1, ACS_CKBOARD);
                    mvwaddch(ground, y + 1, x * 2 + 2, ACS_CKBOARD);
                    wattroff(ground, COLOR_PAIR(6));
                    break;
                case SNAKE_EGG : 
                    wattron(ground, COLOR_PAIR(7));
                    mvwaddch(ground, y + 1, x * 2 + 1, ACS_CKBOARD);
                    mvwaddch(ground, y + 1, x * 2 + 2, ACS_CKBOARD);
                    wattroff(ground, COLOR_PAIR(7));
                    break;
                case SNAKE_HEAD : 
                    wattron(ground, COLOR_PAIR(8));
                    mvwaddch(ground, y + 1, x * 2 + 1, ACS_CKBOARD);
                    mvwaddch(ground, y + 1, x * 2 + 2, ACS_CKBOARD);
                    wattroff(ground, COLOR_PAIR(8));
                    break;
                case SNAKE_BODY : 
                case SNAKE_TAIL : 
                    wattron(ground, COLOR_PAIR(9));
                    mvwaddch(ground, y + 1, x * 2 + 1, ACS_CKBOARD);
                    mvwaddch(ground, y + 1, x * 2 + 2, ACS_CKBOARD);
                    wattroff(ground, COLOR_PAIR(9));
                    break;
                case SNAKE_PILLOW : 
                    wattron(ground, COLOR_PAIR(10));
                    mvwaddch(ground, y + 1, x * 2 + 1, ACS_CKBOARD);
                    mvwaddch(ground, y + 1, x * 2 + 2, ACS_CKBOARD);
                    wattroff(ground, COLOR_PAIR(10));
                    break;
            }
        }
    }

    wattroff(ground, A_BOLD);
    wrefresh(ground);

    return;
}

void snake_new()
{
    // Draw small snake <~~~
    int i;
    struct snake_section *section = NULL, *s_prev = NULL;
    god.head = NULL;
    god.tail = NULL;
    god.alive = 1;
    god.score = 0;
    god.length = SNAKE_INIT_LENGTH;
    for (i = 0; i < SNAKE_INIT_LENGTH; i ++)
    {
        section = calloc(1, sizeof(struct snake_section));
        section->y = GROUND_HEIGHT / 2 + i;
        section->x = GROUND_WIDTH / 2;
        section->type = SNAKE_BODY;
        if (0 == i)
        {
            section->type = SNAKE_HEAD;
            god.head = section;
        }

        if ((SNAKE_INIT_LENGTH - 1) == i)
        {
            section->type = SNAKE_TAIL;
            god.tail = section;
        }

        section->prev = s_prev;
        if (s_prev)
        {
            s_prev->next = section;
        }

        s_prev = section;
    }

    direction = DIR_UP;

    return;
}

// Put eggs in playground
void place_eggs(int count)
{
    int i, y, x;
    srandom((unsigned int) time(NULL));
    for (i = 0; i < count; i ++)
    {
        while (TRUE)
        {
            y = random() % GROUND_HEIGHT;
            x = random() % GROUND_WIDTH;
            if (SNAKE_NULL == ground_arr[y][x])
            {
                // Place an egg
                ground_arr[y][x] = SNAKE_EGG;
                break;
            }
        }
    }

    return;
}

void snake_step()
{
    switch (direction)
    {
        case DIR_UP :
            new_head.y = god.head->y - 1;
            new_head.x = god.head->x;
            break;
        case DIR_DOWN :
            new_head.y = god.head->y + 1;
            new_head.x = god.head->x;
            break;
        case DIR_LEFT :
            new_head.y = god.head->y;
            new_head.x = god.head->x - 1;
            break;
        case DIR_RIGHT :
            new_head.y = god.head->y;
            new_head.x = god.head->x + 1;
            break;
        default :
            // Ahhya?
            break;
    }

    return;
}

void * snake_timer(void *arg)
{
    while (god.alive)
    {
        usleep(scene.interval);
        snake_step();

        // Whether god die?
        if (new_head.y < 0 ||
            new_head.x < 0 ||
            new_head.y >= GROUND_HEIGHT ||
            new_head.x >= GROUND_WIDTH)
        {
            // Out of ground
            wattron(score, A_BOLD);
            wattron(score, COLOR_PAIR(6));
            mvwprintw(score, 33, 7, "Snake walk out of ground!!!  ");
            wattroff(score, COLOR_PAIR(6));
            wattroff(score, A_BOLD);
            wrefresh(score);
            god.alive = 0;
            break;
        }

        if (SNAKE_HEAD == ground_arr[new_head.y][new_head.x] ||
            SNAKE_BODY == ground_arr[new_head.y][new_head.x] ||
            SNAKE_TAIL == ground_arr[new_head.y][new_head.x] ||
            SNAKE_WALL == ground_arr[new_head.y][new_head.x])
        {
            // Hit Hit Hit & Booooooooom!
            wattron(score, A_BOLD);
            wattron(score, COLOR_PAIR(6));
            mvwprintw(score, 33, 7, "Snake hit herself!!!         ");
            wattroff(score, COLOR_PAIR(6));
            wattroff(score, A_BOLD);
            wrefresh(score);
            god.alive = 0;
            break;
        }


        struct snake_section *new_section = calloc(1, sizeof(struct snake_section));
        new_section->y = new_head.y;
        new_section->x = new_head.x;
        new_section->type = SNAKE_HEAD;
        new_section->next = god.head;
        new_section->prev = NULL;
        god.head->prev = new_section;
        god.head->type = SNAKE_BODY;
        god.head = new_section;

        // Eat an egg?
        if (SNAKE_EGG == ground_arr[new_head.y][new_head.x])
        {
            god.score ++;
            god.length ++;
            eggs --;
            if (god.score >= EASTER_EGGS)
            {
                // Waaaahhh
                wattron(score, A_BOLD);
                wattron(score, COLOR_PAIR(9));
                mvwprintw(score, 33, 7, "Easter egg here!!!           ");
                wattroff(score, COLOR_PAIR(9));
                wattroff(score, A_BOLD);
                wrefresh(score);
                god.alive = 2;
                break;
            }
        }
        else if (god.tail && god.tail->prev)
        {
            god.tail->prev->type = SNAKE_TAIL;
            god.tail->prev->next = NULL;
            new_section = god.tail;
            god.tail = god.tail->prev;
            free(new_section);
        }

        // Eat a pillow

        // Place an egg
        if (0 >= eggs)
        {
            place_eggs(scene.eggs_place);
            eggs = scene.eggs_place;
        }

        draw_snake();
        refresh_ground();
        output_length();
        output_speed();
        output_score();
    }

    return NULL;
}

// Keyboard event
void snake_play()
{
    int ch;
    pthread_attr_t attr;
    pthread_t timer_thread;
    pthread_attr_init(&attr);
    // Make timer to another OS thread
    pthread_create(&timer_thread, &attr, snake_timer, NULL);
    output_direction();
    output_score();
    while (ch = getch())
    {
        if ('\033' == ch)
        {
            // Bye
            god.alive = 3;
        }

        if (1 != god.alive)
        {
            break;
        }

        switch (ch)
        {
            case 's' : 
            case 'S' : 
            case KEY_DOWN :
                if (DIR_UP != direction)
                {
                    direction = DIR_DOWN;
                }

                break;
            case 'w' : 
            case 'W' : 
            case KEY_UP :
                if (DIR_DOWN != direction)
                {
                    direction = DIR_UP;
                }

                break;
            case 'a' : 
            case 'A' : 
            case KEY_LEFT :
                if (DIR_RIGHT != direction)
                {
                    direction = DIR_LEFT;
                }

                break;
            case 'd' : 
            case 'D' : 
            case KEY_RIGHT :
                if (DIR_LEFT != direction)
                {
                    direction = DIR_RIGHT;
                }

                break;
            default : 
                break;
        }

        output_direction();
    }

    return;
}

// Portal
int main(int argc, char *argv[])
{
    memset(&scene, 0, sizeof(struct snake_scene));
    int c, speed, eggs_place;
    scene.speed = DEFAULT_SNAKE_SPEED;
    scene.interval = speed_map[scene.speed];
    scene.eggs_place = DEFAULT_EGGS_PLACE;
    while (-1 != (c = getopt(argc, argv, "e:s:h")))
    {
        switch (c)
        {
            case 'h' :
                // Display help topic
                printf(" <KEY-UP / w> <KEY-DOWN / s> <KEY-LEFT / a> <KEY-RIGHT / d> for snake direction\n");
                printf(" <KEY-ESC> to quit directly\n");
                printf("-s : Snake speed [0 - 9], default value is %d\n", DEFAULT_SNAKE_SPEED);
                printf("-e : Number of eggs placed each time, default value is %d\n", DEFAULT_EGGS_PLACE);
                printf("-h : Print this topic\n\n");
                exit(0);

                break;
            case 's' :
                speed = atoi(optarg);
                if (speed > 9 || speed < 0)
                {
                    speed = DEFAULT_SNAKE_SPEED;
                }

                scene.interval = speed_map[speed];
                scene.speed = speed;
        
                break;
            case 'e' :
                eggs_place = atoi(optarg);
                if (eggs_place > 0 && eggs_place < EASTER_EGGS)
                {
                    scene.eggs_place = eggs_place;
                }

                break;
            default :
                break;
        }
    }

    initscr();
    // Check color support (VT-100 only support 8 colors)
    if (FALSE == has_colors())
    {
        endwin();
        printf("Your terminal does not support color\n\n");
        exit(-1);
    }

    // Check window size
    getmaxyx(stdscr, scene.win_height, scene.win_width);
    if (scene.win_height < GROUND_HEIGHT + 6 || 
        scene.win_width < GROUND_WIDTH + 50)
    {
        endwin();
        printf("Terminal window too small\n\n");
        exit -1;
    }

    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(-1);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLUE);
    init_pair(3, COLOR_YELLOW, COLOR_BLUE);
    init_pair(4, COLOR_RED, COLOR_BLUE);
    init_pair(5, COLOR_MAGENTA, COLOR_BLUE);

    // Wall
    init_pair(6, COLOR_RED, COLOR_BLACK);

    // Egg
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);

    // Head
    init_pair(8, COLOR_BLUE, COLOR_BLACK);

    // Body & tail
    init_pair(9, COLOR_CYAN, COLOR_BLACK);

    // Pillow
    init_pair(10, COLOR_GREEN, COLOR_BLACK);

    // Draw base box
    bkgd(COLOR_PAIR(1));
    attron(COLOR_PAIR(1));
    box(stdscr, 0, 0);
    attroff(COLOR_PAIR(1));
    refresh();

    snake_welcome();
    snake_main_scene();
    snake_new();
    draw_snake();
    refresh_ground();
    snake_play();
    if (0 == god.alive)
    {
        snake_failed();
    }
    else if (2 == god.alive)
    {
        snake_easter();
    }

    curs_set(TRUE);
    echo();
    endwin();

    return 0;
}
