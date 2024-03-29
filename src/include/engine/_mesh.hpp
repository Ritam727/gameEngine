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
    size_t operator()(const glm::vec3 &v) const
    {
        unsigned int r = v.r;
        unsigned int g = v.g;
        unsigned int b = v.b;
        std::hash<unsigned int> h;
        return h(r | (g >> 8) | (b >> 16));
    }
};

class Drawer;

class Mesh
{
private:
    VertexArray m_Array;
    VertexBuffer m_Buffer;
    VertexLayout m_Layout;
    IndexBuffer m_Index;

    glm::vec3 m_Trans;
    glm::vec3 m_Scale;
    glm::vec3 m_Rot;
    glm::mat4 m_TransMat;
    glm::mat4 m_RotMat;
    glm::mat4 m_ScaleMat;
    glm::vec3 m_X;
    glm::vec3 m_Y;
    glm::vec3 m_Z;
    glm::vec3 m_PickerColor;
    glm::vec3 m_Centre;

    std::vector<std::string> m_Textures;

    Material *m_Material;
    BasicMaterial *m_BasicMaterial;

    unsigned int m_ID;
    bool m_Selected;

    static unsigned int m_Count;
    static std::unordered_set<glm::vec3, Vec3Hash> m_PickedColors;
    static std::unordered_map<Mesh *, std::pair<Shader *, unsigned int>> m_MeshShaderMode;
    static std::unordered_map<glm::vec3, Mesh *, Vec3Hash> m_ColorMap;
    static glm::vec3 m_SelectionCentre;

public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture *> &textures);
    Mesh(const Mesh &mesh);
    ~Mesh();

    const glm::vec3 getTrans();
    const glm::vec3 getRot();
    const glm::vec3 getScale();
    const glm::mat4 getModelMatrix();
    const glm::mat4 getTranslationMatrix();
    const glm::vec3 getPickerColor();
    const glm::vec3 getCentre() const;
    const unsigned int getID() const;
    const VertexArray &getArray() const;
    const VertexBuffer &getBuffer() const;
    const VertexLayout &getLayout() const;
    const IndexBuffer &getIndex() const;
    const std::vector<std::string> getTextures() const;
    const Material *getMaterial() const;
    const BasicMaterial *getBasicMaterial() const;
    const bool selected() const;

    static std::unordered_map<Mesh *, std::pair<Shader *, unsigned int>> &getSelectedMeshes();
    static std::unordered_set<glm::vec3, Vec3Hash> &getPickedColors();
    static std::unordered_map<glm::vec3, Mesh *, Vec3Hash> &getColorMap();

    void activateTextures();
    void useShader(const Shader &shader);
    void drawSelectButton(unsigned int drawGui = 1, bool expand = false);
    void draw(const Shader &shader, unsigned int mode = 0);
    void addTexture(const std::string &texture, const std::string &type);
    void setMaterial(const Shader &shader);
    void setBasicMaterial(const Shader &shader);
    void select(const bool &select);
    void adjustAngles();

    static void addPickedColor(const glm::vec3 color, const bool clear);
    static void removePickedColor(const glm::vec3 color);

    void updateTrans(const glm::vec3 delta);
    void rotateAroundAxis(const float angle, const glm::vec3 axis);
    void updateRot(const glm::vec3 delta);
    void updateGlobalRot(const glm::vec3 delta);
    void updateScale(const glm::vec3 delta);
};

#endif