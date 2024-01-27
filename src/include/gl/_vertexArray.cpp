#include "_vertexArray.hpp"

VertexArray::VertexArray()
    : m_Count(0)
{
    GLCall(glGenVertexArrays(1, &m_ID));
    GLCall(glBindVertexArray(m_ID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_ID));
}

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(m_ID));
}

void VertexArray::addBuffer(const VertexBuffer &buffer, const VertexLayout &layout)
{
    this->bind();
    buffer.bind();
    m_Count = buffer.getCount();
    std::vector<VertexLayoutElement> elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.getStride(), (const void *) (std::size_t) offset));
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribDivisor(i, elements[i].interval));
        offset += elements[i].count * VertexLayoutElement::getSizeOfElement(elements[i].type);
    }
}

unsigned int VertexArray::getCount() const
{
    return m_Count;
}

unsigned int VertexArray::getID() const
{
    return m_ID;
}
