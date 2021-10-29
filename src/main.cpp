#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "listener.h"
#include "buffer.h"
#include "shader.h"
#include "paths.h"

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

int main([[maybe_unused]] int argc, char **argv) {
    setProcName(argv[0]);

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

    auto mainVert = new Shader(GL_VERTEX_SHADER, "main.vert");

    auto orangeShader = ShaderProgram();
    {
        auto orangeFrag = Shader(GL_FRAGMENT_SHADER, "orange.frag");
        orangeShader.attach(*mainVert);
        orangeShader.attach(orangeFrag);
        orangeShader.link();
    }

    auto vertexColorShader = ShaderProgram();
    {
        auto colorVert = Shader(GL_VERTEX_SHADER, "color.vert");
        auto colorFrag = Shader(GL_FRAGMENT_SHADER, "color.frag");
        vertexColorShader.attach(colorVert);
        vertexColorShader.attach(colorFrag);
        vertexColorShader.link();
    }

    auto uniformShader = ShaderProgram();
    {
        auto uniformFrag = Shader(GL_FRAGMENT_SHADER, "uniform.frag");
        uniformShader.attach(*mainVert);
        uniformShader.attach(uniformFrag);
        uniformShader.link();
    }

    delete mainVert;

    while (!glfwWindowShouldClose(window)) {
        onInput(window);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        orangeShader.use();
        vao0.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        auto time = (float) glfwGetTime();
        float green = (sin(time) / 2.0f) + 0.5f;
        uniformShader.use();
        uniformShader.uniform4f("ourColor", 0.0f, green, 0.0f, 1.0f);
        vao1.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // free the memory
    glfwTerminate();
    return 0;
}
