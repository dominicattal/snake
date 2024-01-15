#include "game.h"

u8* map;
f32* vertices;
u32* indices;

void game_init() 
{   
    map = calloc((MAP_WIDTH + 2) * (MAP_HEIGHT + 2), sizeof(u8));
    map[16] = 1;
    for (int i = 0; i < (MAP_WIDTH + 2) * (MAP_HEIGHT + 2); i++)
    {
        printf("%d", map[i]);
    }
}

void game_render()
{

}

void game_exit()
{
    free(map);
}