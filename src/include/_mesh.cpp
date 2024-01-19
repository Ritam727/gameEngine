#include "_mesh.hpp"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture*> &textures)
    : m_Buffer(VertexBuffer(vertices.size(), sizeof(Vertex), vertices.data())),
      m_Array(VertexArray()), m_Index(IndexBuffer(indices.size(), indices.data())),
      m_Layout(Vertex::getVertexLayout()), m_Trans({ 0.0f, 0.0f, 0.0f }), m_Rot({ 0.0f, 0.0f, 0.0f }), m_Scale({ 1.0f, 1.0f, 1.0f }),
      m_Material(NULL), m_BasicMaterial(NULL)
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
    _model = glm::rotation(_model, this->m_Rot);
    _model = glm::scale(_model, this->m_Scale);
    return _model;
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
