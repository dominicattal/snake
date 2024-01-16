#include "random.h"

void rand_init()
{
    srand(time(NULL));
}

u32 rand_range(u32 range)
{
    return rand() % range;
}