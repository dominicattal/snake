#ifndef WINDOW_H
#define WINDOW_H

#include "gfx.h"
#include "../game/game.h"

#define DEFAULT_WINDOW_WIDTH 300
#define DEFAULT_WINDOW_HEIGHT 300

struct Window 
{
    GLFWwindow* handle;
    f32 dt, last_frame;
};

typedef struct Window Window;

void window_init();
void window_loop();
void window_exit();

void update_delta_time();
void process_input();
void framebuffer_size_callback(GLFWwindow* window, s32 width, s32 height);
void mouse_button_callback(GLFWwindow* window, s32 button, s32 actions, s32 mods);
void mouse_callback(GLFWwindow* window, f64 xpos, f64 ypos);

#endif 