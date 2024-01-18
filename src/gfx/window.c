#include "window.h"

Window window;

void window_init(u32 argc, char** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window.handle = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "Snake", NULL, NULL);

    glfwMakeContextCurrent(window.handle);

    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

    game_init(argc, argv);
}

void window_loop(u32 argc, char** argv)
{
    while (!glfwWindowShouldClose(window.handle))
    {
        process_input(argc, argv);
        game_update();
        game_render();
        glfwSwapBuffers(window.handle);
        glfwPollEvents();
    }
    window_exit();
}

void window_exit(u32 argc, char** argv)
{
    glfwTerminate();
    game_exit();
}

void process_input(u32 argc, char** argv)
{
    if (glfwGetKey(window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.handle, true);
    if (argc == 1)
    {
        if (glfwGetKey(window.handle, GLFW_KEY_W) == GLFW_PRESS)
            game_query_direction(2);
        if (glfwGetKey(window.handle, GLFW_KEY_S) == GLFW_PRESS)
            game_query_direction(0);
        if (glfwGetKey(window.handle, GLFW_KEY_A) == GLFW_PRESS)
            game_query_direction(3);
        if (glfwGetKey(window.handle, GLFW_KEY_D) == GLFW_PRESS)
            game_query_direction(1);
    }
    if (glfwGetKey(window.handle, GLFW_KEY_R) == GLFW_PRESS)
        game_init(argc, argv);
}



