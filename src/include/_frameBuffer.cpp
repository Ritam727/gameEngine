#include "_frameBuffer.hpp"

FrameBuffer::FrameBuffer()
    : m_TextureSlot(0), m_DepthSlot(0)
{
    GLCall(glGenFramebuffers(1, &m_ID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
    GLCall(glReadBuffer(GL_NONE));
}

FrameBuffer::~FrameBuffer()
{
    GLCall(glDeleteFramebuffers(1, &m_ID));
    delete m_Texture;
    delete m_DepthBuffer;
}

void FrameBuffer::attachTexture(const unsigned int slot)
{
    m_TextureSlot = slot;
    m_Texture = new Texture();
    m_Texture->bind(slot);
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->getID(), 0));
    GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT0));
}

void FrameBuffer::attachDepthBuffer(const unsigned int slot)
{
    m_DepthSlot = slot;
    m_DepthBuffer = new Texture(GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_COMPONENT);
    m_DepthBuffer->bind(slot);
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthBuffer->getID(), 0));
}

void FrameBuffer::adjustDimensions(const unsigned int width, const unsigned int height)
{
}

void FrameBuffer::forwardBuffers(const unsigned int width, const unsigned int height)
{
    m_Texture->bind(m_TextureSlot);
}

void FrameBuffer::validate() const
{
    GLCall(unsigned int _ret = glCheckFramebufferStatus(GL_FRAMEBUFFER));
    if (_ret != GL_FRAMEBUFFER_COMPLETE)
        Logger::logWarn("ERROR::FRAMEBUFFER::FrameBuffer is not complete::{0}", _ret);
}

void FrameBuffer::bind() const
{
    GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ID));
    GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID));
    GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0));
    GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT0));
}

void FrameBuffer::unbind() const
{
    GLCall(glReadBuffer(GL_NONE));
    GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
    GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));

}

Texture *FrameBuffer::getTexture()
{
    return m_Texture;
}

Texture *FrameBuffer::getDepthBuffer()
{
    return m_DepthBuffer;
}
