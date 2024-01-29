#include "_mesh.hpp"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture *> &textures)
    : m_Buffer(VertexBuffer(vertices.size(), sizeof(Vertex), vertices.data())), m_Array(VertexArray()),
      m_Index(IndexBuffer(indices.size(), indices.data())), m_Layout(Vertex::getVertexLayout()), m_Trans({0.0f, 0.0f, 0.0f}),
      m_Rot({0.0f, 0.0f, 0.0f}), m_Scale({1.0f, 1.0f, 1.0f}), m_Material(NULL), m_BasicMaterial(NULL), m_ID(m_Count),
      m_PrevRot({0.0f, 0.0f, 0.0f}), m_RotMat(1.0f), m_X({1.0f, 0.0f, 0.0f}), m_Y({0.0f, 1.0f, 0.0f}), m_Z({0.0f, 0.0f, 1.0f}),
      m_GlobalRot({0.0f, 0.0f, 0.0f}), m_PrevGlobalRot({0.0f, 0.0f, 0.0f}), m_Centre(0.0f)
{
    m_Array.addBuffer(m_Buffer, m_Layout);
    for (Texture *texture : textures)
    {
        m_Textures.push_back(texture->getFile());
        Texture::getLoadedTextures()[texture->getFile()] = texture;
    }
    this->activateTextures();
    if (m_Textures.size() > 0)
        m_Material = new Material(m_Textures);
    m_BasicMaterial = new BasicMaterial();
    m_Count++;
    m_PickerColor = glm::vec3(m_Count % 256, (m_Count / 256) % 256, ((m_Count / 256) / 256) % 256);
    for (const Vertex &vertex : vertices)
        m_Centre += vertex.pos;
    m_Centre = (1.0f / (float) vertices.size()) * m_Centre;
}

Mesh::Mesh(const Mesh &mesh)
    : m_Buffer(0, sizeof(Vertex), NULL), m_Index(0, NULL), m_Trans(0.0f),
    m_Scale(1.0f), m_Rot(0.0f), m_PrevRot(0.0f), m_GlobalRot(0.0f), m_PrevGlobalRot(0.0f),
    m_RotMat(1.0f), m_X(1.0f, 0.0f, 0.0f), m_Y(0.0f, 1.0f, 0.0f), m_Z(0.0f, 0.0f, 1.0f)
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
    // this->m_Vertices = mesh.getVertices();
    this->m_ID = m_Count++;
    this->m_PickerColor = glm::vec3(m_Count % 256, (m_Count / 256) % 256, ((m_Count / 256) / 256) % 256);
}

Mesh::~Mesh()
{
    delete m_BasicMaterial;
    delete m_Material;
}

const glm::mat4 Mesh::getModelMatrix()
{
    updateRot();
    updateGlobalRot();
    glm::mat4 _trans = glm::translate(glm::mat4(1.0f), this->m_Trans);
    glm::mat4 _scale = glm::scale(glm::mat4(1.0f), this->m_Scale);
    return _trans * m_RotMat * _scale;
}

const glm::vec3 Mesh::getPickerColor()
{
    return m_PickerColor;
}

const glm::vec3 Mesh::getTrans()
{
    return m_Trans;
}

const glm::vec3 Mesh::getRot()
{
    return m_Rot;
}

const glm::vec3 Mesh::getScale()
{
    return m_Scale;
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

Mesh *Mesh::getSelectedMesh()
{
    return m_CurMesh;
}

Shader *Mesh::getSelectedMeshShader()
{
    return m_CurMeshShader;
}

unsigned int Mesh::getSelectedMeshMode()
{
    return m_CurMeshMode;
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
    if (m_Material)
        this->setMaterial(shader);
    this->setBasicMaterial(shader);
    shader.setVec3f("centre", m_Centre);
}

void Mesh::drawSelectButton(unsigned int drawGui)
{
    if (!drawGui)
        return;
    std::string o = "Object (" + std::to_string(m_ID) + ")##" + std::to_string(drawGui);
    unsigned int treeNodeFlag = 0;
    if (m_CurMesh == this)
        treeNodeFlag |= ImGuiTreeNodeFlags_DefaultOpen;
    if (ImGui::TreeNodeEx(o.c_str(), treeNodeFlag))
    {
        this->drawTransformGui();
        ImGui::TreePop();
    }
}

void Mesh::drawTransformGui()
{
    std::string t = "Translation##" + std::to_string(m_ID);
    std::string r = "Rotation##" + std::to_string(m_ID);
    std::string g = "Global Rotation##" + std::to_string(m_ID);
    std::string s = "Scale##" + std::to_string(m_ID);
    std::string b = "Select Mesh##" + std::to_string(m_ID);
    std::string u = "Unselect Mesh##" + std::to_string(m_ID);

    ImGui::Text("Object (%d)", m_ID);
    if (ImGui::TreeNode(t.c_str()))
    {
        ImGui::DragFloat("X", &m_Trans.x, 0.1);
        ImGui::DragFloat("Y", &m_Trans.y, 0.1);
        ImGui::DragFloat("Z", &m_Trans.z, 0.1);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode(g.c_str()))
    {
        ImGui::DragFloat("X", &m_GlobalRot.x, 0.1);
        ImGui::DragFloat("Y", &m_GlobalRot.y, 0.1);
        ImGui::DragFloat("Z", &m_GlobalRot.z, 0.1);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode(r.c_str()))
    {
        ImGui::DragFloat("X", &m_Rot.x, 0.1);
        ImGui::DragFloat("Y", &m_Rot.y, 0.1);
        ImGui::DragFloat("Z", &m_Rot.z, 0.1);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode(s.c_str()))
    {
        ImGui::DragFloat("X", &m_Scale.x, 0.1);
        ImGui::DragFloat("Y", &m_Scale.y, 0.1);
        ImGui::DragFloat("Z", &m_Scale.z, 0.1);
        ImGui::TreePop();
    }
    if (ImGui::Button(b.c_str()))
        Mesh::setCurPickedColor(this->m_PickerColor);
    if (ImGui::Button(u.c_str()))
        deselectMesh();
}

void Mesh::update()
{
    if (m_PickerColor == m_CurrentPickedColor)
    {
        this->selectMesh();
    }
    else if (m_CurrentPickedColor == glm::vec3(0))
    {
        this->deselectMesh();
    }
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

void Mesh::selectMesh()
{
    m_CurMesh = this;
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

void Mesh::deselectMesh()
{
    m_CurMesh = NULL;
    m_CurMeshShader = NULL;
    m_CurMeshMode = -1;
}

void Mesh::setCurMeshMode(unsigned int mode)
{
    m_CurMeshMode = mode;
}

void Mesh::setCurPickedColor(glm::vec3 color)
{
    m_CurrentPickedColor = color;
}

void Mesh::setCurMeshShader(Shader *shader)
{
    m_CurMeshShader = shader;
}

void Mesh::setTrans(const glm::vec3 trans)
{
    m_Trans = trans;
}

void Mesh::setRot(const glm::vec3 rot)
{
    m_Rot = rot;
}

void Mesh::setScale(const glm::vec3 scale)
{
    m_Scale = scale;
}

void Mesh::updateRot()
{
    glm::vec3 _delta = m_Rot - m_PrevRot;
    glm::quat _q = glm::quat(glm::radians(_delta));
    m_X = glm::rotate(glm::inverse(_q), m_X);
    m_Y = glm::rotate(glm::inverse(_q), m_Y);
    m_Z = glm::rotate(glm::inverse(_q), m_Z);
    m_RotMat = glm::rotation(m_RotMat, glm::radians(_delta));
    m_PrevRot += _delta;
}

void Mesh::updateGlobalRot()
{
    glm::vec3 _delta = m_GlobalRot - m_PrevGlobalRot;
    glm::quat _q;
    if (_delta.x != 0)
    {
        _q = glm::angleAxis(glm::radians(_delta.x), m_X);
        m_Y = glm::rotate(glm::inverse(_q), m_Y);
        m_Z = glm::rotate(glm::inverse(_q), m_Z);
        m_RotMat = glm::rotation(m_RotMat, glm::radians(_delta.x), m_X);
    }
    if (_delta.y != 0)
    {
        _q = glm::angleAxis(glm::radians(_delta.y), m_Y);
        m_X = glm::rotate(glm::inverse(_q), m_X);
        m_Z = glm::rotate(glm::inverse(_q), m_Z);
        m_RotMat = glm::rotation(m_RotMat, glm::radians(_delta.y), m_Y);
    }
    if (_delta.z != 0)
    {
        _q = glm::angleAxis(glm::radians(_delta.z), m_Z);
        m_Y = glm::rotate(glm::inverse(_q), m_Y);
        m_X = glm::rotate(glm::inverse(_q), m_X);
        m_RotMat = glm::rotation(m_RotMat, glm::radians(_delta.z), m_Z);
    }
    if (glm::length(_delta) > 0)
    {
        float X, Y, Z;
        glm::extractEulerAngleXYZ(m_RotMat, X, Y, Z);
        m_PrevRot = glm::degrees(glm::vec3(X, Y, Z));
        m_Rot = glm::degrees(glm::vec3(X, Y, Z));
    }
    m_PrevGlobalRot += _delta;
}

unsigned int Mesh::m_Count = 0;
Mesh *Mesh::m_CurMesh = NULL;
Shader *Mesh::m_CurMeshShader = NULL;
unsigned int Mesh::m_CurMeshMode = -1;
glm::vec3 Mesh::m_CurrentPickedColor = glm::vec3(0);