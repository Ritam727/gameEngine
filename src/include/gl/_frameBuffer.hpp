#ifndef FRAME_BUFFER_HPP
#define FRAME_BUFFER_HPP

#include "_renderBuffer.hpp"
#include "_texture.hpp"

class FrameBuffer
{
private:
    unsigned int m_ID;
    unsigned int m_TextureSlot;
    unsigned int m_DepthSlot;
    Texture *m_Texture;
    RenderBuffer *m_RenderBuffer;

public:
    FrameBuffer();
    ~FrameBuffer();

    void attachTexture(const unsigned int width, const unsigned int height, const unsigned int slot);
    void attachDepthBuffer(const unsigned int width, const unsigned int height, const unsigned int slot);
    void validate() const;
    void bind() const;
    void unbind() const;

    Texture *getTexture();
    RenderBuffer *getRenderBuffer();
};

#endif