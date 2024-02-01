#ifndef UNIFORM_BUFFER_HPP
#define UNIFORM_BUFFER_HPP

#include "_debug.hpp"

class UniformBuffer
{
private:
    unsigned int m_ID;

public:
    UniformBuffer(unsigned int size);
    ~UniformBuffer();

    void bind() const;
    void unbind() const;
    void subData(unsigned int offset, unsigned int size, const void *data) const;
    void bindBufferBase(unsigned int index);
};

#endif