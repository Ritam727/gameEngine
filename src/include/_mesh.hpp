#ifndef MESH_HPP
#define MESH_HPP

#include <_vertexArray.hpp>
#include <_vertexBuffer.hpp>
#include <_indexBuffer.hpp>
#include <_texture.hpp>
#include <_vertex.hpp>
#include <_shader.hpp>
#include <_renderer.hpp>
#include <_rotation.hpp>
#include <_camera.hpp>

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

class Mesh
{
private:
    VertexArray m_Array;
    VertexBuffer m_Buffer;
    VertexLayout m_Layout;
    IndexBuffer m_Index;
    
    glm::vec3 m_Trans;
    glm::vec3 m_Rot;
    glm::vec3 m_Scale;
    
    std::vector<std::string> m_Textures;

    Material *m_Material;
    BasicMaterial *m_BasicMaterial;

public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture*> &textures);
    ~Mesh();

    const glm::mat4 getModelMatrix() const;

    void activateTextures();
    void useShader(const Shader &shader);
    void draw(const Shader &shader, unsigned int mode = 0);
    void addTexture(const std::string &texture, const std::string &type);

    void setTrans(const glm::vec3 trans);
    void setRot(const glm::vec3 rot);
    void setScale(const glm::vec3 scale);
};

#endif