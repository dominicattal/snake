#include "renderer.h"

void renderer_init()
{
    game_init();
}

void renderer_render()
{
    game_update();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
}

void renderer_exit()
{
    game_exit();
}