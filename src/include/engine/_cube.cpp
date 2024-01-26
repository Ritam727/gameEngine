#include "_cube.hpp"

Cube::Cube()
    : Mesh(std::vector<Vertex>({
        Vertex().setPos({ -1.0f, -1.0f, -1.0f }).setNorm({ 0.0f, 0.0f, -1.0f }).setTex({ 0.0f, 0.0f }),
        Vertex().setPos({ -1.0f,  1.0f, -1.0f }).setNorm({ 0.0f, 0.0f, -1.0f }).setTex({ 0.0f, 1.0f }),
        Vertex().setPos({  1.0f,  1.0f, -1.0f }).setNorm({ 0.0f, 0.0f, -1.0f }).setTex({ 1.0f, 1.0f }),
        Vertex().setPos({  1.0f, -1.0f, -1.0f }).setNorm({ 0.0f, 0.0f, -1.0f }).setTex({ 1.0f, 0.0f }),

        Vertex().setPos({ -1.0f, -1.0f, -1.0f }).setNorm({ -1.0f, 0.0f, 0.0f }).setTex({ 0.0f, 0.0f }),
        Vertex().setPos({ -1.0f, -1.0f,  1.0f }).setNorm({ -1.0f, 0.0f, 0.0f }).setTex({ 0.0f, 1.0f }),
        Vertex().setPos({ -1.0f,  1.0f,  1.0f }).setNorm({ -1.0f, 0.0f, 0.0f }).setTex({ 1.0f, 1.0f }),
        Vertex().setPos({ -1.0f,  1.0f, -1.0f }).setNorm({ -1.0f, 0.0f, 0.0f }).setTex({ 1.0f, 0.0f }),

        Vertex().setPos({  1.0f, -1.0f, -1.0f }).setNorm({ 1.0f, 0.0f, 0.0f }).setTex({ 0.0f, 0.0f }),
        Vertex().setPos({  1.0f,  1.0f, -1.0f }).setNorm({ 1.0f, 0.0f, 0.0f }).setTex({ 1.0f, 0.0f }),
        Vertex().setPos({  1.0f,  1.0f,  1.0f }).setNorm({ 1.0f, 0.0f, 0.0f }).setTex({ 1.0f, 1.0f }),
        Vertex().setPos({  1.0f, -1.0f,  1.0f }).setNorm({ 1.0f, 0.0f, 0.0f }).setTex({ 0.0f, 1.0f }),

        Vertex().setPos({ -1.0f, -1.0f,  1.0f }).setNorm({ 0.0f, 0.0f, 1.0f }).setTex({ 0.0f, 0.0f }),
        Vertex().setPos({  1.0f, -1.0f,  1.0f }).setNorm({ 0.0f, 0.0f, 1.0f }).setTex({ 1.0f, 0.0f }),
        Vertex().setPos({  1.0f,  1.0f,  1.0f }).setNorm({ 0.0f, 0.0f, 1.0f }).setTex({ 1.0f, 1.0f }),
        Vertex().setPos({ -1.0f,  1.0f,  1.0f }).setNorm({ 0.0f, 0.0f, 1.0f }).setTex({ 0.0f, 1.0f }),

        Vertex().setPos({ -1.0f,  1.0f, -1.0f }).setNorm({ 0.0f, 1.0f, 0.0f }).setTex({ 0.0f, 0.0f }),
        Vertex().setPos({ -1.0f,  1.0f,  1.0f }).setNorm({ 0.0f, 1.0f, 0.0f }).setTex({ 1.0f, 0.0f }),
        Vertex().setPos({  1.0f,  1.0f,  1.0f }).setNorm({ 0.0f, 1.0f, 0.0f }).setTex({ 1.0f, 1.0f }),
        Vertex().setPos({  1.0f,  1.0f, -1.0f }).setNorm({ 0.0f, 1.0f, 0.0f }).setTex({ 0.0f, 1.0f }),

        Vertex().setPos({ -1.0f, -1.0f, -1.0f }).setNorm({ 0.0f, -1.0f, 0.0f }).setTex({ 0.0f, 0.0f }),
        Vertex().setPos({  1.0f, -1.0f, -1.0f }).setNorm({ 0.0f, -1.0f, 0.0f }).setTex({ 0.0f, 1.0f }),
        Vertex().setPos({  1.0f, -1.0f,  1.0f }).setNorm({ 0.0f, -1.0f, 0.0f }).setTex({ 1.0f, 1.0f }),
        Vertex().setPos({ -1.0f, -1.0f,  1.0f }).setNorm({ 0.0f, -1.0f, 0.0f }).setTex({ 1.0f, 0.0f }),
    }), std::vector<unsigned int>({
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    }), std::vector<Texture*>())
{
}

Cube::~Cube()
{
}
