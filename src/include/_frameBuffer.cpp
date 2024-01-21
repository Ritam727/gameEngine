#include "_frameBuffer.hpp"

FrameBuffer::FrameBuffer()
    : m_TextureSlot(0)
{
    GLCall(glGenFramebuffers(1, &m_ID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
}

FrameBuffer::~FrameBuffer()
{
    GLCall(glDeleteFramebuffers(1, &m_ID));
    delete m_Texture;
    delete m_RenderBuffer;
}

void FrameBuffer::attachTexture(const unsigned int slot)
{
    this->bind();
    m_TextureSlot = slot;
    m_Texture = new Texture();
    m_Texture->bind(slot);
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, m_Texture->getID(), 0));
    this->unbind();
}

void FrameBuffer::attachRenderBuffer(const unsigned int type, const unsigned int renderBufferType)
{
    this->bind();
    m_RenderBuffer = new RenderBuffer();
    m_RenderBuffer->createBufferStorage(renderBufferType);
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, type, GL_RENDERBUFFER, m_RenderBuffer->getID()));
    this->unbind();
}

void FrameBuffer::adjustDimensions(const unsigned int width, const unsigned int height)
{
    m_RenderBuffer->adjustDimensions(width, height);
}

void FrameBuffer::forwardBuffers(const unsigned int width, const unsigned int height)
{
    m_Texture->adjustDimensions(width, height);
    m_Texture->bind(m_TextureSlot);
    m_RenderBuffer->adjustDimensions(width, height);
}

void FrameBuffer::validate() const
{
    this->bind();
    GLCall(unsigned int _ret = glCheckFramebufferStatus(GL_FRAMEBUFFER));
    if (_ret != GL_FRAMEBUFFER_COMPLETE)
        Logger::logWarn("ERROR::FRAMEBUFFER::FrameBuffer is not complete");
    this->unbind();
}

void FrameBuffer::bind() const
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
}

void FrameBuffer::unbind() const
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

Texture *FrameBuffer::getTexture()
{
    return m_Texture;
}

RenderBuffer *FrameBuffer::getRenderBuffer()
{
    return m_RenderBuffer;
}
