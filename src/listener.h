#include <glad/glad.h>
#include <GLFW/glfw3.h>

void onSetFramebufferSize(GLFWwindow *window, int w, int h) {
    glViewport(0, 0, w, h);
}

void onInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}