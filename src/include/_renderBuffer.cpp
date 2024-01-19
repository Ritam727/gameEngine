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

void RenderBuffer::createBufferStorage(const unsigned int type)
{
    m_Type = type;
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, type, Screen::getScreenWidth(), Screen::getScreenHeight()));
}

void RenderBuffer::adjustDimensions()
{
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, m_Type, Screen::getScreenWidth(), Screen::getScreenHeight()));
}

const unsigned int &RenderBuffer::getID() const
{
    return m_ID;
}
