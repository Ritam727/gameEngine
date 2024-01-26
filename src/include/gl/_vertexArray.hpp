#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <gl/_vertexBuffer.hpp>
#include <gl/_vertexLayout.hpp>

class VertexArray
{
private:
    unsigned int m_ID;
    unsigned int m_Count;

public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void addBuffer(const VertexBuffer &buffer, const VertexLayout &layout);

    unsigned int getCount() const;
    unsigned int getID() const;
};

#endif