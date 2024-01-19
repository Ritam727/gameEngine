#include "_cursor.hpp"

Cursor::Cursor()
    : m_Vertices({
        Vertex().setPos({ -0.01f, -0.01f, -1.0f }).setCol({ 0.8f, 0.1f, 0.3f }),
        Vertex().setPos({  0.01f, -0.01f, -1.0f }).setCol({ 0.8f, 0.1f, 0.3f }),
        Vertex().setPos({   0.0f,  0.01f, -1.0f }).setCol({ 0.8f, 0.1f, 0.3f })
    })
{
    m_Shader = new Shader(std::vector<ShaderElem>({
        ShaderElem("res/shaders/cursor.vs", GL_VERTEX_SHADER),
        ShaderElem("res/shaders/cursor.fs", GL_FRAGMENT_SHADER)
    }));
    m_Array = new VertexArray();
    m_Buffer = new VertexBuffer(m_Vertices.size(), sizeof(Vertex), m_Vertices.data());
    m_Layout = new VertexLayout(Vertex::getVertexLayout());
    m_Array->addBuffer(*m_Buffer, *m_Layout);
}

Cursor::~Cursor()
{
    delete m_Shader;
    delete m_Array;
    delete m_Buffer;
    delete m_Layout;
}

void Cursor::draw(float screenWidth, float screenHeight) const
{
    glm::mat4 model = glm::rotation(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3({ 0.0f, 0.1f, 1.0f }));
    model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
    glm::mat4 proj = glm::perspective(glm::radians(Camera::getFOV()), (float) screenWidth / (float) screenHeight, 0.1f, 100.0f);
    glm::mat4 view(1.0f);
    Renderer::drawArr(*m_Array, *m_Shader, model);
}
