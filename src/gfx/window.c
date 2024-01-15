#include "window.h"

GLFWwindow* window;

void window_init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "Snake", NULL, NULL);

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    // glEnable(GL_CULL_FACE); 
    // glCullFace(GL_FRONT); 

    game_init();
}

void window_loop()
{
    while (!glfwWindowShouldClose(window))
    {
        process_input();
        game_render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    window_exit();
}

void window_exit()
{
    glfwTerminate();
    game_exit();
}

void process_input()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    /*
    if (glfwGetKey(window.handle, GLFW_KEY_W) == GLFW_PRESS)
        moving.z += 1;
    if (glfwGetKey(window.handle, GLFW_KEY_S) == GLFW_PRESS)
        moving.z -= 1;
    if (glfwGetKey(window.handle, GLFW_KEY_A) == GLFW_PRESS)
        moving.x -= 1;
    if (glfwGetKey(window.handle, GLFW_KEY_D) == GLFW_PRESS)
        moving.x += 1;
    */
}

void framebuffer_size_callback(GLFWwindow* window, s32 width, s32 height)
{

}

void mouse_button_callback(GLFWwindow* window, s32 button, s32 actions, s32 mods)
{

}

void mouse_callback(GLFWwindow* window, f64 xpos, f64 ypos)
{

}
