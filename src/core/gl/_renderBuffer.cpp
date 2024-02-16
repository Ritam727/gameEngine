#include "_renderBuffer.hpp"

RenderBuffer::RenderBuffer()
    : m_Type(0)
{
    GLCall(glGenRenderbuffers(1, &m_ID));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_ID));
}

RenderBuffer::~RenderBuffer()
{
    GLCall(glDeleteRenderbuffers(1, &m_ID));
}

void RenderBuffer::createBufferStorage(const unsigned int type, const unsigned int width, const unsigned int height)
{
    m_Type = type;
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, m_Type, width, height));
}

void RenderBuffer::adjustDimensions(const unsigned int width, const unsigned int height)
{
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, m_Type, width, height));
}

const unsigned int &RenderBuffer::getID() const
{
    return m_ID;
}
