#pragma once

#include <unordered_map>

class Buffer {
public:
    int type;
    unsigned int id{};

    void bind() const;

    void unbind() const;

    void setData(int dataType, unsigned int size, void *data) const;

protected:
    explicit Buffer(int type);
};

class VertexArray {
public:
    VertexArray();

    Buffer createBuffer(int type);

    Buffer getBuffer(int type);

    void bind() const;

    void unbind() const;

private:
    unsigned int id{};
    std::unordered_map<int, Buffer> buffers = {};
};
