/**
 * BS.Snake header file
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include <ncurses.h>

#define GROUND_HEIGHT                   36
#define GROUND_WIDTH                    36
#define DEFAULT_SNAKE_SPEED             3
#define DEFAULT_EGGS_PLACE              1

#define DIR_UP                          0
#define DIR_DOWN                        1
#define DIR_LEFT                        2
#define DIR_RIGHT                       3

#define EASTER_EGGS                     16

#define SNAKE_NULL                      0
#define SNAKE_WALL                      1
#define SNAKE_EGG                       2
#define SNAKE_HEAD                      5
#define SNAKE_BODY                      6
#define SNAKE_TAIL                      7
#define SNAKE_PILLOW                    10

#define SNAKE_INIT_LENGTH               4

struct snake_scene
{
    int                 win_width;
    int                 win_height;
    int                 interval;
    int                 speed;
    int                 eggs_place;
};

// A snake is just a double-link -_-!
struct snake_section
{
    int                 x;
    int                 y;
    int                 type;
    struct snake_section
                        *next;
    struct snake_section
                        *prev;
};

struct snake
{
    struct snake_section
                        *head;
    struct snake_section
                        *tail;
    int                 alive;
    int                 score;
    int                 length;
};
