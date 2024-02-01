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
#include <unordered_set>

struct Vec3Hash
{
    size_t operator() (const glm::vec3 &v) const
    {
        unsigned int r = v.r;
        unsigned int g = v.g;
        unsigned int b = v.b;
        std::hash<unsigned int> h;
        return h(r | (g >> 8) | (b >> 16));
    }
};

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
    glm::mat4 m_RotMat;
    glm::vec3 m_X;
    glm::vec3 m_Y;
    glm::vec3 m_Z;
    glm::vec3 m_GlobalRot;
    glm::vec3 m_PrevGlobalRot;
    glm::vec3 m_PickerColor;
    glm::vec3 m_Centre;
    
    std::vector<std::string> m_Textures;

    Material *m_Material;
    BasicMaterial *m_BasicMaterial;

    unsigned int m_ID;

    static unsigned int m_Count;
    static std::unordered_set<glm::vec3, Vec3Hash> m_PickedColors;
    static std::unordered_map<Mesh*, std::pair<Shader*, unsigned int>> m_MeshShaderMode;

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
    
    static std::unordered_map<Mesh*, std::pair<Shader*, unsigned int>> &getSelectedMeshes();
    static std::unordered_set<glm::vec3, Vec3Hash> &getPickedColors();

    void activateTextures();
    void useShader(const Shader &shader);
    void drawSelectButton(unsigned int drawGui = 1, bool expand = false);
    void drawTransformGui();
    void draw(const Shader &shader, unsigned int mode = 0);
    void addTexture(const std::string &texture, const std::string &type);
    void setMaterial(const Shader &shader);
    void setBasicMaterial(const Shader &shader);
    
    static void addPickedColor(const glm::vec3 color, const bool clear);

    void setTrans(const glm::vec3 trans);
    void setRot(const glm::vec3 rot);
    void setScale(const glm::vec3 scale);
    void updateRot(const glm::vec3 rot);
    void updateGlobalRot(const glm::vec3 rot);
};

#endif