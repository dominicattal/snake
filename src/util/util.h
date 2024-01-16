#ifndef UTIL_H
#define UTIL_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <glad.h>

typedef GLboolean s2;
typedef GLbyte    s8;
typedef GLubyte   u8;
typedef GLshort   s16;
typedef GLushort  u16;
typedef GLint     s32;
typedef GLuint    u32;
typedef GLint64   s64;
typedef GLuint64  u64; 

typedef GLhalf    f16;
typedef GLfloat   f32;
typedef GLdouble  f64;

typedef struct Color {
    f32 r, g, b;
} Color;

typedef struct Queue {
    u32 val;
    struct Queue* next;
} Queue;

#endif