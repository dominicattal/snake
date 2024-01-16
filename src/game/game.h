#ifndef GAME_H
#define GAME_H

#include "../gfx/shader.h"
#include "../gfx/vao.h"
#include "../gfx/vbo.h"
#include "../util/util.h"

#define MAP_WIDTH 11
#define MAP_HEIGHT 11
#define NUM_TILES (MAP_WIDTH * MAP_HEIGHT)

struct Game
{
    u8* map;
    f32* vertices;
    u32* indices;
    Shader shader;
    VAO vao;
    VBO vbo, ebo;
    f32 game_speed;
    f32 last_move;
    Queue* snake_head;
    Queue* snake_tail;
};

typedef struct Game Game;

void game_init();
void game_update();
void game_render();
void game_exit();

#endif