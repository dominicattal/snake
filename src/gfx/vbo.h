#ifndef VBO_H
#define VBO_H

#include "gfx.h"

struct VBO
{
    u32 ID;
    GLenum type;
};

typedef struct VBO VBO;

VBO vbo_init();
void vbo_bind(VBO vbo);
void vbo_buffer(VBO vbo, u32 size, void* data);
void vbo_destroy(VBO vbo);

#endif