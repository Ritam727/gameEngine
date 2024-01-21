#include "_mesh.hpp"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture*> &textures)
    : m_Buffer(VertexBuffer(vertices.size(), sizeof(Vertex), vertices.data())),
      m_Array(VertexArray()), m_Index(IndexBuffer(indices.size(), indices.data())),
      m_Layout(Vertex::getVertexLayout()), m_Trans({ 0.0f, 0.0f, 0.0f }), m_Rot({ 0.0f, 0.0f, 0.0f }), m_Scale({ 1.0f, 1.0f, 1.0f }),
      m_Material(NULL), m_BasicMaterial(NULL), m_ID(m_Count)
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

const glm::mat4 Mesh::getModelMatrix() const
{
    glm::mat4 _model(1.0f);
    _model = glm::translate(_model, this->m_Trans);
    _model = glm::rotation(_model, { glm::radians(this->m_Rot.x), glm::radians(this->m_Rot.y), glm::radians(this->m_Rot.z) });
    _model = glm::scale(_model, this->m_Scale);
    return _model;
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
    std::string s = "Scale##" + std::to_string(m_ID);
    std::string b = "Select Mesh##" + std::to_string(m_ID);
    std::string u = "Unselect Mesh##" + std::to_string(m_ID);

    ImGui::Text("Object (%d)", m_ID);
    if (ImGui::TreeNode(t.c_str()))
    {
        ImGui::SliderFloat("X", &this->m_Trans.x, std::min(this->m_Trans.x, -20.0f), std::max(this->m_Trans.x, 20.0f));
        ImGui::SliderFloat("Y", &this->m_Trans.y, std::min(this->m_Trans.y, -20.0f), std::max(this->m_Trans.y, 20.0f));
        ImGui::SliderFloat("Z", &this->m_Trans.z, std::min(this->m_Trans.z, -20.0f), std::max(this->m_Trans.z, 20.0f));
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

unsigned int Mesh::m_Count = 0;
Mesh *Mesh::m_CurMesh = NULL;