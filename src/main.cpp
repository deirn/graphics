#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "listener.h"
#include "render.h"

int main() {
    // initialize glfw
    glfwInit();

    // tell glfw to use opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // tell glfw to use opengl core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // load gl via glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, onSetFramebufferSize);

    int width, height;
    while (!glfwWindowShouldClose(window)) {
        onInput(window);

        glfwGetWindowSize(window, &width, &height);
        render(window, width, height);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // free the memory
    glfwTerminate();
    return 0;
}
