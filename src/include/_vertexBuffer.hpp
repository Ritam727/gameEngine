#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <_debug.hpp>

class VertexBuffer
{
private:
    unsigned int m_ID;
    unsigned int m_Count;
    unsigned int m_SizeElem;

public:
    VertexBuffer(unsigned int count, unsigned int sizeElem, const void *data);
    ~VertexBuffer();

    void bind() const;
    unsigned int getCount() const;
};

#endif