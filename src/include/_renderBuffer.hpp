#ifndef RENDER_BUFFER_HPP
#define RENDER_BUFFER_HPP

#include <_debug.hpp>
#include <_renderer.hpp>
#include <_screen.hpp>

class RenderBuffer
{
private:
    unsigned int m_ID;
    unsigned int m_Type;

public:
    RenderBuffer();
    ~RenderBuffer();

    void createBufferStorage(const unsigned int type);
    void adjustDimensions(const unsigned int width, const unsigned int height);

    const unsigned int& getID() const;
};

#endif