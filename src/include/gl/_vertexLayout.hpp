#ifndef VERTEX_LAYOUT_HPP
#define VERTEX_LAYOUT_HPP

#include "_debug.hpp"

#include <glm/glm.hpp>

#include <vector>

struct VertexLayoutElement
{
    unsigned int type;
    unsigned int count;
    unsigned int normalized;
    unsigned int interval;

    static unsigned int getSizeOfElement(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return sizeof(GLfloat);
        case GL_INT:
            return sizeof(GLint);
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

    template <typename T>
    void push(unsigned int count, unsigned int interval = 0)
    {
        static_assert(true);
    }
};

template <>
inline void VertexLayout::push<float>(unsigned int count, unsigned int interval)
{
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE, interval});
    m_Stride += count * VertexLayoutElement::getSizeOfElement(GL_FLOAT);
}

template <>
inline void VertexLayout::push<int>(unsigned int count, unsigned int interval)
{
    m_Elements.push_back({GL_INT, count, GL_FALSE, interval});
    m_Stride += count * VertexLayoutElement::getSizeOfElement(GL_INT);
}

template <>
inline void VertexLayout::push<glm::vec4>(unsigned int count, unsigned int interval)
{
    for (unsigned int i = 0; i < count; i++)
        this->push<float>(4, interval);
}

template <>
inline void VertexLayout::push<glm::mat4>(unsigned int count, unsigned int interval)
{
    for (unsigned int i = 0; i < count; i++)
        this->push<glm::vec4>(4, interval);
}

#endif