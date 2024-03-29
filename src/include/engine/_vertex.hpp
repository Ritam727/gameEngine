#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>

#include <gl/_vertexLayout.hpp>

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 col;
    glm::vec3 norm;
    glm::vec2 tex;
    glm::mat4 model;

    Vertex();

    Vertex setPos(const glm::vec3 _pos);
    Vertex setCol(const glm::vec3 _col);
    Vertex setTex(const glm::vec2 _tex);
    Vertex setNorm(const glm::vec3 _norm);
    Vertex setModel(const glm::mat4 _model);

    static VertexLayout getVertexLayout();
};

#endif