#ifndef WINDOW_H
#define WINDOW_H

#include "gfx.h"
#include "../game/game.h"

#define DEFAULT_WINDOW_WIDTH 300
#define DEFAULT_WINDOW_HEIGHT 300

struct Window 
{
    GLFWwindow* handle;
};

typedef struct Window Window;

void window_init(u32 argc, char** argv);
void window_loop();
void window_exit();

void process_input();

#endif 