#include "_vertex.hpp"

Vertex::Vertex()
    : pos(0.0f), col(1.0f), tex(0.0f), norm(1.0f)
{
}

Vertex Vertex::setPos(const glm::vec3 _pos)
{
    this->pos = _pos;
    return *this;
}

Vertex Vertex::setCol(const glm::vec3 _col)
{
    this->col = _col;
    return *this;
}

Vertex Vertex::setTex(const glm::vec2 _tex)
{
    this->tex = _tex;
    return *this;
}

Vertex Vertex::setNorm(const glm::vec3 _norm)
{
    this->norm = _norm;
    return *this;
}

VertexLayout Vertex::getVertexLayout()
{
    VertexLayout _layout;
    _layout.push<float>(3);
    _layout.push<float>(3);
    _layout.push<float>(3);
    _layout.push<float>(2);
    return _layout;
}
