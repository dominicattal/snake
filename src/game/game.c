#include "game.h"

Game game;

void game_init() 
{   
    game.map = calloc(NUM_TILES, sizeof(u8));
    game.map[0] = 1;

    game.vertices = calloc(5 * NUM_VERTICES, sizeof(f32));
    game.indices = calloc(6 * NUM_TILES, sizeof(u32));

    for (int vertex_idx = 0; vertex_idx < NUM_VERTICES; vertex_idx++)
    {
        game.vertices[5 * vertex_idx]     = (f32)(vertex_idx / (MAP_WIDTH + 1)) / MAP_WIDTH * 2 - 1; // row
        game.vertices[5 * vertex_idx + 1] = (f32)(vertex_idx % (MAP_WIDTH + 1)) / MAP_WIDTH * 2 - 1; // col
        game.vertices[5 * vertex_idx + 2] = 0.6;
        game.vertices[5 * vertex_idx + 3] = 0.3;
        game.vertices[5 * vertex_idx + 4] = 0.2;
    }

    for (int tile_idx = 0; tile_idx < NUM_TILES; tile_idx++)
    {
        int row = tile_idx / MAP_WIDTH, col = tile_idx % MAP_WIDTH; 
        int top_left_vertex_idx, top_right_vertex_idx, bottom_left_vertex_idx, bottom_right_vertex_idx;
        top_left_vertex_idx = row * (MAP_WIDTH + 1) + col;
        top_right_vertex_idx = row * (MAP_WIDTH + 1) + col + 1;
        bottom_left_vertex_idx = (row + 1) * (MAP_WIDTH + 1) + col;
        bottom_right_vertex_idx = (row + 1) * (MAP_WIDTH + 1) + col + 1;
        game.indices[6 * tile_idx    ] = top_right_vertex_idx;
        game.indices[6 * tile_idx + 1] = bottom_right_vertex_idx;
        game.indices[6 * tile_idx + 2] = top_left_vertex_idx;
        game.indices[6 * tile_idx + 3] = bottom_right_vertex_idx;
        game.indices[6 * tile_idx + 4] = bottom_left_vertex_idx;
        game.indices[6 * tile_idx + 5] = top_left_vertex_idx;
    }

    for (int i = 0; i < 5*NUM_VERTICES; i++)
    {
        printf("%f\t", game.vertices[i]);
        if (i % 5 == 4)
            printf("\n");
    }

    game.shader = shader_init("src/shaders/vertex.sl", "src/shaders/fragment.sl");
    shader_use(game.shader);

    game.vao = vao_init();
    game.vbo = vbo_init(GL_ARRAY_BUFFER);
    game.ebo = vbo_init(GL_ELEMENT_ARRAY_BUFFER);
    vao_bind(game.vao);
    vbo_bind(game.vbo);
    vbo_buffer(game.vbo, 5 * NUM_VERTICES * sizeof(f32), game.vertices);
    vbo_bind(game.ebo);
    vbo_buffer(game.ebo, 6 * NUM_TILES * sizeof(u32), game.indices);
    vao_attr(0, 2, 5 * sizeof(f32), (void*)0);
    vao_attr(1, 3, 5 * sizeof(f32), (void*)(2 * sizeof(f32)));
}

void game_render()
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
    vao_bind(game.vao);
    glDrawElements(GL_TRIANGLES, 6 * NUM_TILES, GL_UNSIGNED_INT, 0);
}

void game_exit()
{
    free(game.map);
    free(game.vertices);
    free(game.indices);
    shader_destroy(game.shader);
    vao_destroy(game.vao);
    vbo_destroy(game.vbo);
    vbo_destroy(game.ebo);
}