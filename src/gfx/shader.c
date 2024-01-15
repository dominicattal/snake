#include "shader.h"

static const char* _read_file(char* path)
{
    FILE* ptr;
    char* content;
    ptr = fopen(path, "rb");
    fseek(ptr, 0, SEEK_END);
    s32 len = ftell(ptr);
    assert(len > 0);
    fseek(ptr, 0, SEEK_SET);
    content = calloc(1, len);
    assert(content != NULL);
    fread(content, 1, len, ptr);
    assert(strlen(content) > 0);
    fclose(ptr);
    return content;
}

static unsigned int _compile(char* s_path, GLenum type)
{
    u32 shader;
    const char* shader_code;
    shader = glCreateShader(type);
    shader_code = _read_file(s_path);
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);

    //debug
    char info_log[512];
    s32 success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        printf(info_log);
        exit(1);
    }

    return shader;
}

Shader shader_init(char* vs_path, char* fs_path)
{
    Shader self;
    unsigned int vertex, fragment;
    self.ID = glCreateProgram();
    vertex   = _compile(vs_path, GL_VERTEX_SHADER);
    fragment = _compile(fs_path, GL_FRAGMENT_SHADER);
    glAttachShader(self.ID, vertex);
    glAttachShader(self.ID, fragment);
    glLinkProgram(self.ID);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    //debug
    char info_log[512];
    s32 success;
    glGetProgramiv(self.ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(self.ID, 512, NULL, info_log);
        printf(info_log);
        exit(1);
    }

    return self;
}

void shader_use(Shader shader)
{
    glUseProgram(shader.ID);
}
