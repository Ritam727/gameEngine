#ifndef RENDER_BUFFER_HPP
#define RENDER_BUFFER_HPP

#include <common/_debug.hpp>

class RenderBuffer
{
private:
    unsigned int m_ID;
    unsigned int m_Type;

public:
    RenderBuffer();
    ~RenderBuffer();

    void createBufferStorage(const unsigned int type, const unsigned int width, const unsigned int height);
    void adjustDimensions(const unsigned int width, const unsigned int height);

    const unsigned int& getID() const;
};

#endif