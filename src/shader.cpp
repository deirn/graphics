#include "config.h"
#include "shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "paths.h"

Shader::Shader(int type, const char *fileName) :
    type(type),
    id(glCreateShader(type)) {
#if CONFIG_DEBUG_SHADER
    std::cout << "[DEBUG::SHADER::CREATED] " << id << std::endl;
#endif

    std::string path = "shader/";
    path += fileName;

    std::ifstream sourceFile(getResourcePath(path.c_str()));
    std::string source((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

    const char *cSource = source.c_str();
    glShaderSource(id, 1, &cSource, nullptr);

    sourceFile.close();

    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

Shader::~Shader() {
    glDeleteShader(id);

#if CONFIG_DEBUG_SHADER
    std::cout << "[DEBUG::SHADER::DELETED] " << id << std::endl;
#endif
}

unsigned int Shader::getId() const {
    return id;
}

ShaderProgram::ShaderProgram() :
    id(glCreateProgram()) {
}

unsigned int ShaderProgram::getId() const {
    return id;
}

void ShaderProgram::attach(Shader &shader) const {
    glAttachShader(id, shader.getId());
}

bool ShaderProgram::link() const {
    int success;
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        return false;
    }

    return true;
}

void ShaderProgram::use() const {
    glUseProgram(id);
}

void ShaderProgram::uniform4f(const char *name, float v0, float v1, float v2, float v3) const {
    int location = glGetUniformLocation(id, name);
    glUniform4f(location, v0, v1, v2, v3);
}
