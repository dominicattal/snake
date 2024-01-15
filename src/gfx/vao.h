#ifndef VAO_H
#define VAO_H

#include "gfx.h"

struct VAO
{
    u32 ID;
};

typedef struct VAO VAO;

VAO vao_init();
void vao_bind(VAO vao);
void vao_attr(u8 index, u8 count, u32 size, void* offset);
void vao_destroy(VAO vao);

#endif