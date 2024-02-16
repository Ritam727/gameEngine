#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

#include "_debug.hpp"

class IndexBuffer
{
private:
    unsigned int m_ID;
    unsigned int m_Count;

public:
    IndexBuffer(unsigned int count, const void *data, unsigned int mode = GL_STATIC_DRAW);
    ~IndexBuffer();

    void bind() const;
    unsigned int getCount() const;
};

#endif