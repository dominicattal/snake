#ifndef GAME_H
#define GAME_H

#include "../gfx/shader.h"
#include "../gfx/vao.h"
#include "../gfx/vbo.h"
#include "../util/util.h"

#define MAP_WIDTH 21
#define MAP_HEIGHT 21
#define NUM_TILES (MAP_WIDTH * MAP_HEIGHT)

typedef struct Node {
    u32 idx;
    struct Node* next;
} Node;

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
    u8 snake_direction;
    u8 query_direction;
    u32 snake_length;
    Node* snake_head;
    Node* snake_tail;
    bool playing;
    FILE* log;
    char* file_name;
    char mode;
    u32 food_idx;
    u32 argc;
    char** argv;
};

typedef struct Game Game;

void game_query_direction(u8 direction);

void game_init(u32 argc, char** argv);
void game_setup();
void game_update();
void game_render();
void game_exit();

#endif