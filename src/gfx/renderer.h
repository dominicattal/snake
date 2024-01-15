#ifndef RENDERER_H
#define RENDERER_H

#include "gfx.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "../game/game.h"

void renderer_init();
void renderer_render();
void renderer_exit();

#endif