#ifndef MESH_HPP
#define MESH_HPP

#include "_vertex.hpp"

#include <gl/_vertexArray.hpp>
#include <gl/_vertexBuffer.hpp>
#include <gl/_indexBuffer.hpp>
#include <gl/_texture.hpp>
#include <gl/_shader.hpp>
#include <gl/_renderer.hpp>
#include <utils/_rotation.hpp>
#include <common/_camera.hpp>
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
    glm::vec3 m_PickerColor;
    
    std::vector<std::string> m_Textures;

    Material *m_Material;
    BasicMaterial *m_BasicMaterial;

    unsigned int m_ID;

    static unsigned int m_Count;
    static Mesh *m_CurMesh;
    static Shader *m_CurMeshShader;
    static unsigned int m_CurMeshMode;
    static glm::vec3 m_CurrentPickedColor;

public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture*> &textures);
    Mesh(const Mesh &mesh);
    ~Mesh();

    const glm::mat4 getModelMatrix();
    const glm::vec3 getPickerColor();
    const glm::vec3 getTrans();
    const glm::vec3 getRot();
    const glm::vec3 getScale();
    const unsigned int getID() const;
    const VertexArray &getArray() const;
    const VertexBuffer &getBuffer() const;
    const VertexLayout &getLayout() const;
    const IndexBuffer &getIndex() const;
    const std::vector<std::string> getTextures() const;
    const Material *getMaterial() const;
    const BasicMaterial *getBasicMaterial() const;
    
    static Mesh *getSelectedMesh();
    static Shader *getSelectedMeshShader();
    static unsigned int getSelectedMeshMode();

    void activateTextures();
    void useShader(const Shader &shader);
    void drawSelectButton(unsigned int drawGui = 1);
    void drawTransformGui();
    void update();
    void draw(const Shader &shader, unsigned int mode = 0);
    void addTexture(const std::string &texture, const std::string &type);
    void selectMesh();
    void setMaterial(const Shader &shader);
    void setBasicMaterial(const Shader &shader);
    static void deselectMesh();
    static void setCurMeshShader(Shader *shader);
    static void setCurMeshMode(unsigned int mode);
    static void setCurPickedColor(glm::vec3 color);

    void setTrans(const glm::vec3 trans);
    void setRot(const glm::vec3 rot);
    void setScale(const glm::vec3 scale);
    void updateRot();
    void updateGlobalRot();
};

#endif