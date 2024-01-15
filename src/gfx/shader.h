#ifndef SHADER_H
#define SHADER_H

#include "gfx.h"

struct Shader
{
    u32 ID;
};

typedef struct Shader Shader;

Shader shader_init(char* vs_path, char* fs_path);
void shader_use(Shader shader);
void shader_destroy(Shader shader);

#endif