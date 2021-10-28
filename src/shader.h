#include <unordered_map>

class Shader {
public:
    unsigned int id;
    bool compile(unsigned int progId);

protected:
    Shader(int type, const char *source);

private:
    bool compiled = false;
};

class ShaderProgram {
public:
    ShaderProgram();

    Shader createShader(int type, const char *source);

    Shader getShader(int type);

    bool link();

    void use() const;

private:
    unsigned int id;
    std::unordered_map<int, Shader> shaders = {};
};
