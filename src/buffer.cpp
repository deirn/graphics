#include <glad/glad.h>
#include <iostream>
#include "buffer.h"

class BufferImpl : public Buffer {
public:
    explicit BufferImpl(int type) : Buffer(type) {}
};

Buffer::Buffer(int type) : type(type) {
    glGenBuffers(1, &id);
}

void Buffer::bind() const {
    glBindBuffer(type, id);
}

void Buffer::unbind() const {
    glBindBuffer(type, 0);
}

void Buffer::setData(int dataType, unsigned int size, void *data) const {
    glBufferData(type, size, data, dataType);
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
    bind();
}

void VertexArray::bind() const {
    glBindVertexArray(id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

Buffer VertexArray::createBuffer(int type) {
    auto buffer = BufferImpl(type);
    buffer.bind();
    buffers.insert({buffer.type, buffer});
    return buffer;
}

Buffer VertexArray::getBuffer(int type) {
    return buffers.at(type);
}
