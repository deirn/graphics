#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "listener.h"
#include "buffer.h"
#include "shader.h"

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main() {\n"
                                 "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                 "}";

const char *fragmentShaderSource0 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main() {\n"
                                    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}";

const char *fragmentShaderSource1 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main() {\n"
                                    "    FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
                                    "}";

float vertices0[] = {
    -0.5f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    -0.25f, 0.5f, 0.0f
};

float vertices1[] = {
    0.0f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.25f, 0.5f, 0.0f
};

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

    auto vao0 = VertexArray();
    auto vbo0 = vao0.createBuffer(GL_ARRAY_BUFFER);
    vbo0.setData(GL_STATIC_DRAW, sizeof(vertices0), vertices0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    vao0.unbind();

    auto vao1 = VertexArray();
    auto vbo1 = vao1.createBuffer(GL_ARRAY_BUFFER);
    vbo1.setData(GL_STATIC_DRAW, sizeof(vertices1), vertices1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    vao1.unbind();

    auto shader0 = ShaderProgram();
    shader0.createShader(GL_VERTEX_SHADER, vertexShaderSource);
    shader0.createShader(GL_FRAGMENT_SHADER, fragmentShaderSource0);
    shader0.link();

    auto shader1 = ShaderProgram();
    shader1.createShader(GL_VERTEX_SHADER, vertexShaderSource);
    shader1.createShader(GL_FRAGMENT_SHADER, fragmentShaderSource1);
    shader1.link();

    while (!glfwWindowShouldClose(window)) {
        onInput(window);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader0.use();
        vao0.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        shader1.use();
        vao1.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // free the memory
    glfwTerminate();
    return 0;
}
