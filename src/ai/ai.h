#ifndef AI_H
#define AI_H

#include "../util/util.h"

struct AI 
{
    u32 ID;
};

typedef struct AI AI;

void AI_init();
u32 AI_choose_direction();

#endif