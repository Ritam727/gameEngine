#include "_mesh.hpp"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture *> &textures)
    : m_Buffer(VertexBuffer(vertices.size(), sizeof(Vertex), vertices.data())), m_Array(VertexArray()),
      m_Index(IndexBuffer(indices.size(), indices.data())), m_Layout(Vertex::getVertexLayout()), m_Trans({0.0f, 0.0f, 0.0f}),
      m_Rot({0.0f, 0.0f, 0.0f}), m_Scale({1.0f, 1.0f, 1.0f}), m_Material(NULL), m_BasicMaterial(NULL), m_ID(m_Count),
      m_PrevRot({0.0f, 0.0f, 0.0f}), m_RotMat(1.0f), m_X({1.0f, 0.0f, 0.0f}), m_Y({0.0f, 1.0f, 0.0f}), m_Z({0.0f, 0.0f, 1.0f}),
      m_GlobalRot({0.0f, 0.0f, 0.0f}), m_PrevGlobalRot({0.0f, 0.0f, 0.0f})
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

const unsigned int Mesh::getID() const
{
    return m_ID;
}

Mesh *Mesh::getSelectedMesh()
{
    return m_CurMesh;
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
        shader.setMaterial("material", *m_Material);
    shader.setBasicMaterial("basicMaterial", *m_BasicMaterial);
}

void Mesh::drawSelectButton()
{
    std::string o = "Object (" + std::to_string(m_ID) + ")";
    if (ImGui::TreeNode(o.c_str()))
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
    float X, Y, Z;
    glm::extractEulerAngleXYZ(m_RotMat, X, Y, Z);
    ImGui::Text("Actual angles : %.10g, %.10g, %.10g", glm::degrees(X), glm::degrees(Y), glm::degrees(Z));
    if (ImGui::TreeNode(t.c_str()))
    {
        ImGui::SliderFloat("X", &this->m_Trans.x, std::min(this->m_Trans.x, -20.0f), std::max(this->m_Trans.x, 20.0f));
        ImGui::SliderFloat("Y", &this->m_Trans.y, std::min(this->m_Trans.y, -20.0f), std::max(this->m_Trans.y, 20.0f));
        ImGui::SliderFloat("Z", &this->m_Trans.z, std::min(this->m_Trans.z, -20.0f), std::max(this->m_Trans.z, 20.0f));
        ImGui::TreePop();
    }
    if (ImGui::TreeNode(g.c_str()))
    {
        ImGui::SliderFloat("X", &this->m_GlobalRot.x, std::min(this->m_GlobalRot.x, -360.0f), std::max(this->m_GlobalRot.x, 360.0f));
        ImGui::SliderFloat("Y", &this->m_GlobalRot.y, std::min(this->m_GlobalRot.y, -360.0f), std::max(this->m_GlobalRot.y, 360.0f));
        ImGui::SliderFloat("Z", &this->m_GlobalRot.z, std::min(this->m_GlobalRot.z, -360.0f), std::max(this->m_GlobalRot.z, 360.0f));
        ImGui::TreePop();
    }
    if (ImGui::TreeNode(r.c_str()))
    {
        ImGui::SliderFloat("X", &this->m_Rot.x, std::min(this->m_Rot.x, -360.0f), std::max(this->m_Rot.x, 360.0f));
        ImGui::SliderFloat("Y", &this->m_Rot.y, std::min(this->m_Rot.y, -360.0f), std::max(this->m_Rot.y, 360.0f));
        ImGui::SliderFloat("Z", &this->m_Rot.z, std::min(this->m_Rot.z, -360.0f), std::max(this->m_Rot.z, 360.0f));
        ImGui::TreePop();
    }
    if (ImGui::TreeNode(s.c_str()))
    {
        ImGui::SliderFloat("X", &this->m_Scale.x, std::min(this->m_Scale.x, 0.0f), std::max(this->m_Scale.x, 20.0f));
        ImGui::SliderFloat("Y", &this->m_Scale.y, std::min(this->m_Scale.y, 0.0f), std::max(this->m_Scale.y, 20.0f));
        ImGui::SliderFloat("Z", &this->m_Scale.z, std::min(this->m_Scale.z, 0.0f), std::max(this->m_Scale.z, 20.0f));
        ImGui::TreePop();
    }
    if (ImGui::Button(b.c_str()))
        this->selectMesh();
    if (ImGui::Button(u.c_str()))
        deselectMesh();
}

void Mesh::draw(const Shader &shader, unsigned int mode)
{
    this->useShader(shader);
    glm::mat4 model = this->getModelMatrix();
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

void Mesh::deselectMesh()
{
    m_CurMesh = NULL;
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
    m_PrevGlobalRot += _delta;
}

unsigned int Mesh::m_Count = 0;
Mesh *Mesh::m_CurMesh = NULL;