#include "_uniformBuffer.hpp"

UniformBuffer::UniformBuffer(unsigned int size)
{
    GLCall(glGenBuffers(1, &m_ID));
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_ID));
    GLCall(glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW));
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

UniformBuffer::~UniformBuffer()
{
    GLCall(glDeleteBuffers(1, &m_ID));
}

void UniformBuffer::bind() const
{
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_ID));
}

void UniformBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void UniformBuffer::subData(unsigned int offset, unsigned int size, const void *data) const
{
    this->bind();
    GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data));
    this->unbind();
}

void UniformBuffer::bindBufferBase(unsigned int index)
{
    this->bind();
    GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, index, m_ID));
    this->unbind();
}
