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
#include <imgui/imgui.h>

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
    glm::vec3 m_PrevRot;
    glm::vec3 m_Scale;
    glm::mat4 m_RotMat;
    glm::vec3 m_X;
    glm::vec3 m_Y;
    glm::vec3 m_Z;
    glm::vec3 m_GlobalRot;
    glm::vec3 m_PrevGlobalRot;
    
    std::vector<std::string> m_Textures;

    Material *m_Material;
    BasicMaterial *m_BasicMaterial;

    static unsigned int m_Count;
    unsigned int m_ID;

    static Mesh *m_CurMesh;

public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture*> &textures);
    ~Mesh();

    const glm::mat4 getModelMatrix();
    const unsigned int getID() const;
    static Mesh *getSelectedMesh();

    void activateTextures();
    void useShader(const Shader &shader);
    void drawSelectButton();
    void drawTransformGui();
    void draw(const Shader &shader, unsigned int mode = 0);
    void addTexture(const std::string &texture, const std::string &type);
    void selectMesh();
    static void deselectMesh();

    void setTrans(const glm::vec3 trans);
    void setRot(const glm::vec3 rot);
    void setScale(const glm::vec3 scale);
    void updateRot();
    void updateGlobalRot();
};

#endif