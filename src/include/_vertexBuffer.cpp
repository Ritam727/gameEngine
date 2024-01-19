#include "_vertexBuffer.hpp"

VertexBuffer::VertexBuffer(unsigned int count, unsigned int sizeElem, const void *data)
    : m_Count(count), m_SizeElem(sizeElem)
{
    GLCall(glGenBuffers(1, &m_ID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeElem, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_ID));
}

void VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

unsigned int VertexBuffer::getCount() const
{
    return m_Count;
}
