#include "vbo.h"

VBO vbo_init(GLenum type)
{
    VBO vbo;
    glGenBuffers(1, &vbo.ID);
    vbo.type = type;
    return vbo;
}

void vbo_bind(VBO vbo)
{
    glBindBuffer(vbo.type, vbo.ID);
}

void vbo_buffer(VBO vbo, u32 size, void* data)
{
    glBufferData(vbo.type, size, data, GL_STATIC_DRAW);
}

void vbo_destroy(VBO vbo)
{
    glDeleteBuffers(1, &vbo.ID);
}