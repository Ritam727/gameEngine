#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <_renderer.hpp>
#include <_vertex.hpp>
#include <_camera.hpp>
#include <_rotation.hpp>

class Cursor
{
private:
    std::vector<Vertex> m_Vertices;
    Shader *m_Shader;
    VertexArray *m_Array;
    VertexBuffer *m_Buffer;
    VertexLayout *m_Layout;

public:
    Cursor();
    ~Cursor();

    void draw(float screenWidth, float screenHeight) const;
};

#endif