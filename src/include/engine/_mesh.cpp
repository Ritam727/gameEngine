#include "_mesh.hpp"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture *> &textures)
    : m_Buffer(VertexBuffer(vertices.size(), sizeof(Vertex), vertices.data())), m_Array(VertexArray()),
      m_Index(IndexBuffer(indices.size(), indices.data())), m_Layout(Vertex::getVertexLayout()), m_Trans({0.0f, 0.0f, 0.0f}),
      m_Scale({1.0f, 1.0f, 1.0f}), m_Material(NULL), m_BasicMaterial(NULL), m_ID(m_Count), m_Selected(false), m_Centre(0.0f),
      m_RotMat(1.0f), m_X({1.0f, 0.0f, 0.0f}), m_Y({0.0f, 1.0f, 0.0f}), m_Z({0.0f, 0.0f, 1.0f}), m_Rot(0.0f), m_GlobalRot(0.0f),
      m_TransMat(1.0f), m_ScaleMat(1.0f)
{
    m_Array.addBuffer(m_Buffer, m_Layout);
    for (Texture *texture : textures)
    {
        m_Textures.push_back(texture->getFile());
        Texture::getLoadedTextures()[texture->getFile()] = texture;
    }
    this->activateTextures();
    m_Material = new Material(m_Textures);
    m_BasicMaterial = new BasicMaterial();
    m_Count++;
    m_PickerColor = glm::vec3(m_Count % 256, (m_Count / 256) % 256, ((m_Count / 256) / 256) % 256);
    for (const Vertex &vertex : vertices)
        m_Centre += vertex.pos;
    m_Centre = (1.0f / (float)vertices.size()) * m_Centre;
    m_ColorMap[m_PickerColor] = this;
}

Mesh::Mesh(const Mesh &mesh)
    : m_Buffer(0, sizeof(Vertex), NULL), m_Index(0, NULL), m_Trans(0.0f),
      m_Scale(1.0f), m_RotMat(1.0f), m_X(1.0f, 0.0f, 0.0f), m_Y(0.0f, 1.0f, 0.0f),
      m_Z(0.0f, 0.0f, 1.0f), m_Selected(false)
{
    this->m_Array = mesh.getArray();
    this->m_Buffer = mesh.getBuffer();
    this->m_Layout = mesh.getLayout();
    this->m_Index = mesh.getIndex();
    this->m_Textures = mesh.getTextures();
    if (mesh.getMaterial() == NULL)
        this->m_Material = NULL;
    else
        this->m_Material = new Material(*mesh.getMaterial());
    this->m_BasicMaterial = new BasicMaterial(*mesh.getBasicMaterial());
    this->m_ID = m_Count++;
    this->m_PickerColor = glm::vec3(m_Count % 256, (m_Count / 256) % 256, ((m_Count / 256) / 256) % 256);
    m_ColorMap[this->m_PickerColor] = this;
}

Mesh::~Mesh()
{
    delete m_BasicMaterial;
    delete m_Material;
}

const glm::vec3 Mesh::getTrans()
{
    return m_Trans;
}

const glm::vec3 Mesh::getRot()
{
    return m_Rot;
}

const glm::vec3 Mesh::getGlobalRot()
{
    return m_GlobalRot;
}

const glm::vec3 Mesh::getScale()
{
    return m_Scale;
}

const glm::mat4 Mesh::getModelMatrix()
{
    return m_TransMat * m_RotMat * m_ScaleMat;
}

const glm::vec3 Mesh::getPickerColor()
{
    return m_PickerColor;
}

const unsigned int Mesh::getID() const
{
    return m_ID;
}

const VertexArray &Mesh::getArray() const
{
    return m_Array;
}

const VertexBuffer &Mesh::getBuffer() const
{
    return m_Buffer;
}

const VertexLayout &Mesh::getLayout() const
{
    return m_Layout;
}

const IndexBuffer &Mesh::getIndex() const
{
    return m_Index;
}

const std::vector<std::string> Mesh::getTextures() const
{
    return m_Textures;
}

const Material *Mesh::getMaterial() const
{
    return m_Material;
}

const BasicMaterial *Mesh::getBasicMaterial() const
{
    return m_BasicMaterial;
}

const bool Mesh::selected() const
{
    return m_Selected;
}

void Mesh::activateTextures()
{
    for (unsigned int i = 0; i < m_Textures.size(); i++)
        Texture::getLoadedTextures()[m_Textures[i]]->bind(i);
}

void Mesh::useShader(const Shader &shader)
{
    shader.use();
    this->activateTextures();
    this->setMaterial(shader);
    this->setBasicMaterial(shader);
    shader.setVec3f("centre", m_Centre);
}

void Mesh::drawSelectButton(unsigned int drawGui, bool expand)
{
    if (!drawGui)
        return;
    std::string o = "Object (" + std::to_string(m_ID) + ")##" + std::to_string(drawGui);
    ImGui::Checkbox(o.c_str(), &this->m_Selected);
    if (this->m_Selected)
        addPickedColor(this->m_PickerColor, false);
    else
        removePickedColor(this->m_PickerColor);
}

void Mesh::draw(const Shader &shader, unsigned int mode)
{
    this->useShader(shader);
    glm::mat4 model = this->getModelMatrix();
    glm::vec3 pickerColor = 1.0f / 255.0f * m_PickerColor;
    shader.setVec3f("u_Color", pickerColor);
    if (mode)
        Renderer::drawElem(m_Array, shader, m_Index, model);
    else
        Renderer::drawArr(m_Array, shader, model);
}

void Mesh::addTexture(const std::string &texture, const std::string &type)
{
    m_Textures.push_back(texture);
    if (Texture::getLoadedTextures().find(texture) == Texture::getLoadedTextures().end())
    {
        if (Texture::getLoadedImages().find(texture) == Texture::getLoadedImages().end())
        {
            Image *img = Texture::loadImage(texture);
            Texture::getLoadedImages()[texture] = img;
            img->get();
        }
        Texture::getLoadedTextures()[texture] = new Texture(Texture::getLoadedImages()[texture], type);
    }
    if (m_Material)
        delete m_Material;
    m_Material = new Material(m_Textures);
}

void Mesh::setMaterial(const Shader &shader)
{
    for (unsigned int i = 0; i < this->m_Material->diffuseCount; i++)
    {
        shader.setInt("material.diffuse[" + std::to_string(i) + "]", this->m_Material->diffuse[i]);
    }
    for (unsigned int i = 0; i < this->m_Material->specularCount; i++)
    {
        shader.setInt("material.specular[" + std::to_string(i) + "]", this->m_Material->specular[i]);
    }
    for (unsigned int i = 0; i < this->m_Material->emissionCount; i++)
    {
        shader.setInt("material.emission[" + std::to_string(i) + "]", this->m_Material->emission[i]);
    }
    for (unsigned int i = 0; i < this->m_Material->normalCount; i++)
        shader.setInt("material.normal[" + std::to_string(i) + "]", this->m_Material->normal[i]);
    shader.setInt("material.diffuseCount", this->m_Material->diffuseCount);
    shader.setInt("material.specularCount", this->m_Material->specularCount);
    shader.setInt("material.emissionCount", this->m_Material->emissionCount);
    shader.setInt("material.normalCount", this->m_Material->normalCount);
    shader.setFloat("material.shininess", this->m_Material->shininess);
}

void Mesh::setBasicMaterial(const Shader &shader)
{
    shader.setVec3f("basicMaterial.diffuse", this->m_BasicMaterial->diffuse);
    shader.setVec3f("basicMaterial.specular", this->m_BasicMaterial->specular);
    shader.setVec3f("basicMaterial.emission", this->m_BasicMaterial->emission);
    shader.setFloat("basicMaterial.shininess", this->m_BasicMaterial->shininess);
}

void Mesh::select(const bool &select)
{
    this->m_Selected = select;
}

void Mesh::adjustAngles()
{
    float X, Y, Z;
    glm::extractEulerAngleXYZ(this->m_RotMat, X, Y, Z);
    this->m_Rot = glm::degrees(glm::vec3(X, Y, Z));
    this->m_RotMat = glm::mat4(1.0f);
    this->m_RotMat = glm::rotation(this->m_RotMat, glm::vec3(X, 0.0f, 0.0f));
    this->m_RotMat = glm::rotation(this->m_RotMat, glm::vec3(0.0f, Y, 0.0f));
    this->m_RotMat = glm::rotation(this->m_RotMat, glm::vec3(0.0f, 0.0f, Z));
    this->m_X = glm::rotation(glm::vec3(1.0f, 0.0f, 0.0f), -1.0f * glm::vec3(X, Y, Z));
    this->m_Y = glm::rotation(glm::vec3(0.0f, 1.0f, 0.0f), -1.0f * glm::vec3(X, Y, Z));
    this->m_Z = glm::rotation(glm::vec3(0.0f, 0.0f, 1.0f), -1.0f * glm::vec3(X, Y, Z));
}

void Mesh::updateTrans(const glm::vec3 delta)
{
    this->m_TransMat = glm::translate(this->m_TransMat, delta);
    this->m_Trans += delta;
}

void Mesh::rotateAroundAxis(const float angle, const glm::vec3 axis)
{
    glm::vec3 _axis = glm::rotation(axis, -1.0f * glm::radians(this->m_Rot));
    glm::quat _q = glm::angleAxis(glm::radians(angle), _axis);
    this->m_RotMat = glm::translate(this->m_RotMat, this->m_Centre);
    this->m_RotMat = glm::rotation(this->m_RotMat, glm::radians(angle), _axis);
    this->m_RotMat = glm::translate(this->m_RotMat, -1.0f * this->m_Centre);
    if (angle > 0.0f)
        adjustAngles();

}

void Mesh::updateRot(const glm::vec3 delta)
{
    glm::quat _q = glm::quat(glm::radians(delta));
    this->m_RotMat = glm::translate(this->m_RotMat, this->m_Centre);
    this->m_RotMat = glm::rotation(this->m_RotMat, glm::radians(delta));
    this->m_RotMat = glm::translate(this->m_RotMat, -1.0f * this->m_Centre);
    if (glm::length(delta) > 0)
        adjustAngles();
}

void Mesh::updateGlobalRot(const glm::vec3 delta)
{
    glm::quat _q;
    this->m_RotMat = glm::translate(this->m_RotMat, this->m_Centre);
    if (delta.x != 0)
    {
        _q = glm::angleAxis(glm::radians(delta.x), m_X);
        this->m_RotMat = glm::rotation(this->m_RotMat, glm::radians(delta.x), m_X);
    }
    if (delta.y != 0)
    {
        _q = glm::angleAxis(glm::radians(delta.y), m_Y);
        this->m_RotMat = glm::rotation(this->m_RotMat, glm::radians(delta.y), m_Y);
    }
    if (delta.z != 0)
    {
        _q = glm::angleAxis(glm::radians(delta.z), m_Z);
        this->m_RotMat = glm::rotation(this->m_RotMat, glm::radians(delta.z), m_Z);
    }
    this->m_RotMat = glm::translate(this->m_RotMat, -1.0f * this->m_Centre);
    if (glm::length(delta) > 0)
        adjustAngles();
    this->m_GlobalRot += delta;
}

void Mesh::updateScale(const glm::vec3 delta)
{
    this->m_ScaleMat = glm::translate(this->m_ScaleMat, this->m_Centre);
    this->m_ScaleMat = glm::scale(this->m_ScaleMat, delta);
    this->m_ScaleMat = glm::translate(this->m_ScaleMat, -1.0f * this->m_Centre);
    this->m_Scale *= delta;
}

void Mesh::addPickedColor(const glm::vec3 color, const bool clear)
{
    if (!clear)
    {
        if (color.r == 0 && color.g == 0 && color.b == 0)
            return;
        m_PickedColors.insert(color);
        m_ColorMap[color]->select(true);
    }
    else
    {
        for (const glm::vec3 color_ : m_PickedColors)
            m_ColorMap[color_]->select(false);
        m_PickedColors.clear();
        if (color.r == 0 && color.g == 0 && color.b == 0)
            return;
        m_PickedColors.insert(color);
        m_ColorMap[color]->select(true);
    }
}

void Mesh::removePickedColor(const glm::vec3 color)
{
    if (m_PickedColors.find(color) != m_PickedColors.end())
        m_PickedColors.erase(color);
    m_ColorMap[color]->select(false);
}

std::unordered_map<Mesh *, std::pair<Shader *, unsigned int>> &Mesh::getSelectedMeshes()
{
    return m_MeshShaderMode;
}

std::unordered_set<glm::vec3, Vec3Hash> &Mesh::getPickedColors()
{
    return m_PickedColors;
}

std::unordered_map<glm::vec3, Mesh *, Vec3Hash> &Mesh::getColorMap()
{
    return m_ColorMap;
}

unsigned int Mesh::m_Count = 0;
std::unordered_set<glm::vec3, Vec3Hash> Mesh::m_PickedColors;
std::unordered_map<Mesh *, std::pair<Shader *, unsigned int>> Mesh::m_MeshShaderMode;
std::unordered_map<glm::vec3, Mesh *, Vec3Hash> Mesh::m_ColorMap;