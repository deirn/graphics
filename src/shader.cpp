#include "shader.h"
#include <glad/glad.h>
#include <iostream>
#include <algorithm>

class ShaderImpl : public Shader {
public:
    ShaderImpl(int type, const char *source) :
        Shader(type, source) {};
};

Shader::Shader(int type, const char *source) :
    id(glCreateShader(type)) {
    glShaderSource(id, 1, &source, nullptr);
}

bool Shader::compile(unsigned int progId) {
    if (compiled) {
        std::cout << "ERROR::SHADER::ALREADY_COMPILED\n";
        return true;
    }

    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    compiled = true;
    return true;
}

ShaderProgram::ShaderProgram() :
    id(glCreateProgram()) {}

Shader ShaderProgram::createShader(int type, const char *source) {
    auto shader = ShaderImpl(type, source);
    shaders.insert({type, shader});
    return shader;
}

Shader ShaderProgram::getShader(int type) {
    return shaders.at(type);
}

bool ShaderProgram::link() {
    for (const auto &pair: shaders) {
        auto shader = pair.second;
        if (!shader.compile(id)) {
            return false;
        }

        glAttachShader(id, shader.id);
    }

    int success;
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        return false;
    }

    for (const auto &pair: shaders) {
        glDeleteShader(pair.second.id);
    }

    return true;
}

void ShaderProgram::use() const {
    glUseProgram(id);
}
