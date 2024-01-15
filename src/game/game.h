#ifndef GAME_H
#define GAME_H

#include "../gfx/shader.h"
#include "../gfx/vao.h"
#include "../gfx/vbo.h"
#include "../util/util.h"

#define MAP_WIDTH 5
#define MAP_HEIGHT 5
#define NUM_TILES (MAP_WIDTH * MAP_HEIGHT)
#define NUM_VERTICES ((MAP_WIDTH + 1) * (MAP_HEIGHT + 1))

struct Game
{
    u8* map;
    f32* vertices;
    u32* indices;
    Shader shader;
    VAO vao;
    VBO vbo, ebo;
};

typedef struct Game Game;

void game_init();
void game_render();
void game_exit();

#endif