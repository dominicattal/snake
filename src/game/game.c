#include "game.h"

Game game;

static void print_map()
{
    for (int i = 0; i < NUM_TILES; i++)
    {
        printf("%d", game.map[i]);
        if (i % MAP_WIDTH == MAP_WIDTH - 1)
            printf("\n");
    }
}

static void init_vertex_data()
{
    game.map = calloc(NUM_TILES, sizeof(u8));
    game.vertices = calloc(5 * 4 * NUM_TILES, sizeof(f32));
    game.indices = calloc(6 * NUM_TILES, sizeof(u32));
}

static void init_map()
{
    for (int i = 0; i < MAP_WIDTH; i++)
        game.map[i] = game.map[MAP_WIDTH * (MAP_HEIGHT - 1) + i] = 1;

    for (int i = 0; i < MAP_HEIGHT; i++)
        game.map[MAP_WIDTH * i] = game.map[MAP_WIDTH * i + MAP_WIDTH - 1] = 1;
}

static void init_snake()
{
    game.snake_length = 1;
    game.snake_direction = 4;
    game.query_direction = 4;
    int snake_head_idx = (MAP_HEIGHT / 2) * (MAP_WIDTH) + MAP_WIDTH / 2;
    game.map[snake_head_idx] = 2;
    game.snake_head = game.snake_tail = malloc(sizeof(Node));
    game.snake_head->idx = snake_head_idx;
    game.snake_head->next = NULL;
}

static void init_game_gfx()
{
    game.shader = shader_init("src/shaders/vertex.sl", "src/shaders/fragment.sl");
    shader_use(game.shader);

    game.vao = vao_init();
    game.vbo = vbo_init(GL_ARRAY_BUFFER);
    game.ebo = vbo_init(GL_ELEMENT_ARRAY_BUFFER);
}

static void update_vertex_data()
{
    for (int tile_idx = 0; tile_idx < NUM_TILES; tile_idx++)
    {
        // indices
        game.indices[6 * tile_idx    ] = 4 * tile_idx + 1;
        game.indices[6 * tile_idx + 1] = 4 * tile_idx + 3;
        game.indices[6 * tile_idx + 2] = 4 * tile_idx;
        game.indices[6 * tile_idx + 3] = 4 * tile_idx + 3;
        game.indices[6 * tile_idx + 4] = 4 * tile_idx + 2;
        game.indices[6 * tile_idx + 5] = 4 * tile_idx;

        // vertices
        int row = tile_idx / MAP_WIDTH, col = tile_idx % MAP_WIDTH; 
        int top_left_vertex_idx, top_right_vertex_idx, bottom_left_vertex_idx, bottom_right_vertex_idx;
        top_left_vertex_idx     = 5 * 4 * tile_idx;
        top_right_vertex_idx    = 5 * 4 * tile_idx + 5;
        bottom_left_vertex_idx  = 5 * 4 * tile_idx + 10;
        bottom_right_vertex_idx = 5 * 4 * tile_idx + 15;

        // coordinates
        game.vertices[top_left_vertex_idx    ]     = (f32)(col    ) / MAP_WIDTH * 2 - 1;
        game.vertices[top_left_vertex_idx + 1]     = - ((f32)(row    ) / MAP_WIDTH * 2 - 1);
        game.vertices[top_right_vertex_idx    ]    = (f32)(col + 1) / MAP_WIDTH * 2 - 1;
        game.vertices[top_right_vertex_idx + 1]    = - ((f32)(row    ) / MAP_WIDTH * 2 - 1);
        game.vertices[bottom_left_vertex_idx    ]  = (f32)(col    ) / MAP_WIDTH * 2 - 1;
        game.vertices[bottom_left_vertex_idx + 1]  = - ((f32)(row + 1) / MAP_WIDTH * 2 - 1);        
        game.vertices[bottom_right_vertex_idx    ] = (f32)(col + 1) / MAP_WIDTH * 2 - 1;
        game.vertices[bottom_right_vertex_idx + 1] = - ((f32)(row + 1) / MAP_WIDTH * 2 - 1);
        
        // color
        Color tile_color;
        switch (game.map[tile_idx])
        {
            case 1:
                tile_color.r = 0.6;
                tile_color.g = 0.3;
                tile_color.b = 0.2;
                break;
            case 2:
                tile_color.r = 0;
                tile_color.g = 0.3;
                tile_color.b = 0.6;
                break;
            case 3:
                tile_color.r = 0.7;
                tile_color.g = 0.7;
                tile_color.b = 0;
                break;
            default:
                tile_color.r = 0.5;
                tile_color.g = 0.5;
                tile_color.b = 0.5;
        }
        game.vertices[top_left_vertex_idx + 2]     = tile_color.r;
        game.vertices[top_left_vertex_idx + 3]     = tile_color.g;
        game.vertices[top_left_vertex_idx + 4]     = tile_color.b;
        game.vertices[top_right_vertex_idx + 2]    = tile_color.r;
        game.vertices[top_right_vertex_idx + 3]    = tile_color.g;
        game.vertices[top_right_vertex_idx + 4]    = tile_color.b;
        game.vertices[bottom_left_vertex_idx + 2]  = tile_color.r;
        game.vertices[bottom_left_vertex_idx + 3]  = tile_color.g;
        game.vertices[bottom_left_vertex_idx + 4]  = tile_color.b;
        game.vertices[bottom_right_vertex_idx + 2] = tile_color.r;
        game.vertices[bottom_right_vertex_idx + 3] = tile_color.g;
        game.vertices[bottom_right_vertex_idx + 4] = tile_color.b;
    }

    vao_bind(game.vao);
    vbo_bind(game.vbo);
    vbo_buffer(game.vbo, 20 * NUM_TILES * sizeof(f32), game.vertices);
    vbo_bind(game.ebo);
    vbo_buffer(game.ebo, 6 * NUM_TILES * sizeof(u32), game.indices);
    vao_attr(0, 2, 5 * sizeof(f32), (void*)0);
    vao_attr(1, 3, 5 * sizeof(f32), (void*)(2 * sizeof(f32)));
}

static void set_snake_direction()
{
    if (game.query_direction == 4)
        return;
    if (game.snake_direction == 0 && game.query_direction != 2)
        game.snake_direction = game.query_direction;
    if (game.snake_direction == 1 && game.query_direction != 3)
        game.snake_direction = game.query_direction;
    if (game.snake_direction == 2 && game.query_direction != 0)
        game.snake_direction = game.query_direction;
    if (game.snake_direction == 3 && game.query_direction != 1)
        game.snake_direction = game.query_direction;
    if (game.snake_direction == 4)
        game.snake_direction = game.query_direction;
    game.query_direction = 4;
}

static void create_food()
{
    if (game.mode == 'w')
    {
        u32 food_idx = rand_range(NUM_TILES);
        while (game.map[food_idx] != 0)
            food_idx = rand_range(NUM_TILES);
        game.food_idx = food_idx;
    }
    game.map[game.food_idx] = 3;
}

static bool snake_started_moving()
{
    return game.snake_direction != 4;
}

static void update_map()
{
    Node* new_snake_head = malloc(sizeof(Node));
    u32 new_snake_head_idx = game.snake_head->idx;
    switch (game.snake_direction)
    {
        case 0:
            new_snake_head_idx += MAP_WIDTH;
            break;
        case 1:
            new_snake_head_idx += 1;
            break;
        case 2:
            new_snake_head_idx -= MAP_WIDTH;
            break;
        case 3:
            new_snake_head_idx -= 1;
            break;
    }
    assert(new_snake_head_idx >= 0 && new_snake_head_idx < NUM_TILES);
    
    switch (game.map[new_snake_head_idx])
    {
        case 0:
            // empty space
            new_snake_head->idx = new_snake_head_idx;
            new_snake_head->next = NULL;
            game.snake_head->next = new_snake_head;
            game.snake_head = new_snake_head;
            game.map[new_snake_head_idx] = 2;
            game.map[game.snake_tail->idx] = 0;
            free(game.snake_tail);
            Node* new_snake_tail = game.snake_tail->next;
            game.snake_tail = new_snake_tail;
            break;
        case 3:
            // food
            new_snake_head->idx = new_snake_head_idx;
            new_snake_head->next = NULL;
            game.snake_head->next = new_snake_head;
            game.snake_head = new_snake_head;
            game.snake_length++;
            game.map[new_snake_head_idx] = 2;
            if (game.mode == 'w')
                create_food();
            break;
        default:
            // hits wall or snake
            game.playing = false;
    }
}

static void get_next_line()
{
    char c = '0';
    char line[10];
    u32 idx = 0;
    c = fgetc(game.log);
    if (c == EOF)
    {
        game.playing = false;
        return;
    }
    while (c != '\n')
    {
        line[idx++] = c;
        c = fgetc(game.log);
    }
    char* output;
    u32 dir = strtol(&line[0], &output, 10);
    game.food_idx = strtol(&line[2], &output, 10);
    game_query_direction(dir);
    create_food();
}

void game_query_direction(u8 direction)
{
    game.query_direction = direction;
}

void game_init(u32 argc, char** argv) 
{   
    game.game_speed = 0.1; 
    game.last_move = glfwGetTime();
    game.playing = true;

    rand_init();
    init_vertex_data();
    init_map();
    init_snake();
    init_game_gfx();

    if (argc == 1)
    {
        game.log = fopen("logs/log.txt", "w");
        game.mode = 'w';
        create_food();
    }
    else 
    {
        game.log = fopen("logs/log.txt", "r");
        game.mode = 'r';
        get_next_line();
    }

    update_vertex_data();
}

void game_update()
{
    if (game.playing && glfwGetTime() > game.last_move + game.game_speed)
    {
        if (game.mode == 'w')
            fprintf(game.log, "%d %d\n", game.query_direction, game.food_idx);
        else
            get_next_line();
        set_snake_direction();
        game.last_move = glfwGetTime();
        if (!snake_started_moving())
            return;
        update_map();
        update_vertex_data();
    }
}

void game_render()
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
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
    fclose(game.log);
}