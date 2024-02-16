#include "_frameBuffer.hpp"

FrameBuffer::FrameBuffer()
    : m_TextureSlot(0)
{
    GLCall(glGenFramebuffers(1, &m_ID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
    GLCall(glReadBuffer(GL_NONE));
}

FrameBuffer::~FrameBuffer()
{
    GLCall(glDeleteFramebuffers(1, &m_ID));
    delete m_Texture;
    delete m_RenderBuffer;
}

void FrameBuffer::attachTexture(const unsigned int width, const unsigned int height, const unsigned int slot, const unsigned int attachment)
{
    m_TextureSlot = slot;
    m_Attachment = attachment;
    m_Texture = new Texture(width, height, GL_RGB, GL_FLOAT, GL_RGB);
    m_Texture->bind(slot);
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_Attachment, GL_TEXTURE_2D, m_Texture->getID(), 0));
}

void FrameBuffer::attachDepthBuffer(const unsigned int width, const unsigned int height)
{
    m_RenderBuffer = new RenderBuffer();
    m_RenderBuffer->createBufferStorage(GL_DEPTH24_STENCIL8, width, height);
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer->getID()));
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
    GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0 + m_Attachment));
    GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT0 + m_Attachment));
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

RenderBuffer *FrameBuffer::getRenderBuffer()
{
    return m_RenderBuffer;
}
