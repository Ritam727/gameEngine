#ifndef VERTEX_LAYOUT_HPP
#define VERTEX_LAYOUT_HPP

#include <common/_debug.hpp>

#include <vector>

struct VertexLayoutElement
{
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int getSizeOfElement(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT : return sizeof(GLfloat);
            case GL_INT : return sizeof(GLint);
        }
        return 0;
    }
};

class VertexLayout
{
private:
    unsigned int m_Stride;
    std::vector<VertexLayoutElement> m_Elements;

public:
    VertexLayout()
        : m_Stride(0), m_Elements(std::vector<VertexLayoutElement>()) {}
    ~VertexLayout() {}

    unsigned int getStride() const
    {
        return m_Stride;
    }

    std::vector<VertexLayoutElement> getElements() const
    {
        return m_Elements;
    }

    template<typename T>
    void push(unsigned int count)
    {
        static_assert(true);
    }
};

template<>
inline void VertexLayout::push<float>(unsigned int count)
{
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count * VertexLayoutElement::getSizeOfElement(GL_FLOAT);
}

template<>
inline void VertexLayout::push<int>(unsigned int count)
{
    m_Elements.push_back({ GL_INT, count, GL_FALSE });
    m_Stride += count * VertexLayoutElement::getSizeOfElement(GL_INT);
}

#endif