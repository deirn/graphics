#include "shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "paths.h"

class ShaderImpl : public Shader {
public:
    ShaderImpl(int type, const char *source) :
        Shader(type, source) {};
};

Shader::Shader(int type, const char *source) :
    id(glCreateShader(type)) {
    glShaderSource(id, 1, &source, nullptr);
}

bool Shader::compile() {
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

Shader ShaderProgram::createShader(int type, const char *fileName) {
    std::string path = "shader/";
    path += fileName;

    std::ifstream sourceFile(getResourcePath(path.c_str()));
    std::string source((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

    auto shader = ShaderImpl(type, source.c_str());
    shaders.insert({type, shader});

    sourceFile.close();
    return shader;
}

Shader ShaderProgram::getShader(int type) {
    return shaders.at(type);
}

bool ShaderProgram::link() {
    for (const auto &pair: shaders) {
        auto shader = pair.second;
        if (!shader.compile()) {
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
