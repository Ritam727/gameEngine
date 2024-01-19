#ifndef FRAME_BUFFER_HPP
#define FRAME_BUFFER_HPP

#include <_renderBuffer.hpp>
#include <_texture.hpp>

class FrameBuffer
{
private:
    unsigned int m_ID;
    Texture *m_Texture;
    RenderBuffer *m_RenderBuffer;

public:
    FrameBuffer();
    ~FrameBuffer();

    void attachTexture(const unsigned int slot);
    void attachRenderBuffer(const unsigned int type, const unsigned int renderBufferType);
    void forwardBuffers();
    void validate() const;
    void bind() const;
    void unbind() const;

    Texture *getTexture();
    RenderBuffer *getRenderBuffer();
};

#endif