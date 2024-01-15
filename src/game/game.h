#ifndef GAME_H
#define GAME_H

#include "../gfx/shader.h"
#include "../gfx/vao.h"
#include "../gfx/vbo.h"
#include "../util/util.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

void game_init();
void game_render();
void game_exit();

#endif