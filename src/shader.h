#pragma once

#include <unordered_map>

class Shader {
public:
    const int type;

private:
    unsigned int id;

public:
    Shader(int type, const char *fileName);

    ~Shader();

    unsigned int getId() const;
};

class ShaderProgram {
private:
    unsigned int id;

public:
    ShaderProgram();

    unsigned int getId() const;

    void attach(Shader &shader) const;

    bool link() const;

    void use() const;

    void uniform4f(const char *name, float v0, float v1, float v2, float v3) const;
};
