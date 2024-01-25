#include "_drawer.hpp"

void Drawer::addModel(ModelElem &modelElem, unsigned int priority, bool skipTextures)
{
    if (Drawer::getLoadedModels().find(modelElem.path) != Drawer::getLoadedModels().end())
    {
        Logger::logInfo("Model already exists in system, not reloading");
        modelElem.model = Drawer::getLoadedModels()[modelElem.path];
    }
    else
    {
        modelElem.model = new Model(modelElem.path, skipTextures);
        Drawer::getLoadedModels()[modelElem.path] = modelElem.model;
    }
    m_Models[priority].push_back(modelElem);
}

void Drawer::addMesh(Mesh *mesh, Shader *shader, unsigned int mode, unsigned int priority, const glm::vec3 &trans, const glm::vec3 &rot, const glm::vec3 &scale)
{
    m_Meshes[priority].push_back(MeshElem(mesh, shader, mode).setTranslation(trans).setRotation(rot).setScale(scale));
}

void Drawer::setOnWindow(bool value)
{
    m_IsOnWindow = value;
}

void Drawer::clearMeshes()
{
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < m_Meshes[i].size(); j++)
        {
            delete m_Meshes[i][j].mesh;
            if (m_Meshes[i][j].shader)
                delete m_Meshes[i][j].shader;
        }
    }
}

void Drawer::clearModels()
{
    for (auto &model : m_LoadedModels)
        delete model.second;
}

void Drawer::clearUniformBuffers()
{
    delete m_Matrices;
    delete m_Lights;
}

void Drawer::init()
{
    m_Matrices = new UniformBuffer(2 * sizeof(glm::mat4));
    m_Matrices->bindBufferBase(1);

    m_Lights = new UniformBuffer(2506);
    m_Lights->bindBufferBase(0);
}

void Drawer::render()
{
    for (int i = 2; i >= 0; i--)
    {
        for (unsigned int j = 0; j < m_Models[i].size(); j++)
        {
            m_Models[i][j].shader->use();
            m_Models[i][j].shader->setVec3f("cameraPos", Camera::getCameraPos());
            m_Models[i][j].shader->setFloat("time", glfwGetTime());
            m_Models[i][j].model->draw(*m_Models[i][j].shader, m_Models[i][j].mode);
        }
        for (unsigned int j = 0; j < m_Meshes[i].size(); j++)
        {
            m_Meshes[i][j].shader->use();
            m_Meshes[i][j].shader->setVec3f("cameraPos", Camera::getCameraPos());
            m_Meshes[i][j].shader->setFloat("time", glfwGetTime());
            m_Meshes[i][j].mesh->drawSelectButton();
            m_Meshes[i][j].mesh->draw(*m_Meshes[i][j].shader, m_Meshes[i][j].mode);
        }
    }
    if (Mesh::getSelectedMesh() != NULL)
    {
        Renderer::stencilFunc(GL_ALWAYS, 1, 0xFF);
        Renderer::stencilMask(0xFF);
        Mesh *curMesh = Mesh::getSelectedMesh();
        curMesh->draw(*Mesh::getSelectedMeshShader(), Mesh::getSelectedMeshMode());

        Renderer::stencilFunc(GL_NOTEQUAL, 1, 0xFF);
        Renderer::stencilMask(0x00);
        Renderer::disable(GL_DEPTH_TEST);

        std::vector<ShaderElem> shaderElems({
            ShaderElem("res/shaders/border/shader.vert", GL_VERTEX_SHADER),
            ShaderElem("res/shaders/border/shader.geom", GL_GEOMETRY_SHADER),
            ShaderElem("res/shaders/border/shader.frag", GL_FRAGMENT_SHADER),
        });
        Shader shader_(shaderElems);

        glm::vec3 _scale = Mesh::getSelectedMesh()->getScale();
        Mesh::getSelectedMesh()->setScale(_scale * 1.01f);
        Mesh::getSelectedMesh()->draw(shader_, Mesh::getSelectedMeshMode());
        Mesh::getSelectedMesh()->setScale(_scale);

        Renderer::stencilMask(0xFF);
        Renderer::stencilFunc(GL_ALWAYS, 1, 0xFF);
        Renderer::enable(GL_DEPTH_TEST);
    }
}

void Drawer::renderForMousePicking(bool onWindow)
{
    std::vector<ShaderElem> shaderElems({ShaderElem("res/shaders/mousePicking/shader.vert", GL_VERTEX_SHADER),
                                         ShaderElem("res/shaders/mousePicking/shader.frag", GL_FRAGMENT_SHADER)});
    Shader mousePicking(shaderElems);
    for (int i = 2; i >= 0; i--)
    {
        for (unsigned int j = 0; j < m_Models[i].size(); j++)
        {
            m_Models[i][j].shader->use();
            m_Models[i][j].shader->setVec3f("cameraPos", Camera::getCameraPos());
            m_Models[i][j].shader->setFloat("time", glfwGetTime());
            m_Models[i][j].model->draw(mousePicking, m_Models[i][j].mode, 0);
        }
        for (unsigned int j = 0; j < m_Meshes[i].size(); j++)
        {
            m_Meshes[i][j].shader->use();
            m_Meshes[i][j].shader->setVec3f("cameraPos", Camera::getCameraPos());
            m_Meshes[i][j].shader->setFloat("time", glfwGetTime());
            m_Meshes[i][j].mesh->drawSelectButton(0);
            m_Meshes[i][j].mesh->draw(mousePicking, m_Meshes[i][j].mode);
        }
    }
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    glm::vec2 mousePos = {io.MousePos.x, io.MousePos.y};
    float pressed = io.MouseDownDuration[0];
    if (pressed > -1 && !onWindow)
    {
        unsigned char pixels[3];
        GLCall(glReadPixels((int)mousePos.x, Screen::getScreenHeight() - (int)mousePos.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels));
        int r = pixels[0], g = pixels[1], b = pixels[2];
        Mesh::setCurPickedColor(glm::vec3(r, g, b));
    }
}

void Drawer::update(const unsigned int width, const unsigned int height, const std::vector<DirLight> &dirLights, const std::vector<PointLight> &pointLights, const std::vector<SpotLight> &spotLights)
{
    while (!m_Queue.empty())
    {
        ModelLoader loader = m_Queue.front();
        std::vector<ShaderElem> shaderElems({ShaderElem("res/shaders/default/shader.vert", GL_VERTEX_SHADER),
                                             ShaderElem("res/shaders/default/shader.geom", GL_GEOMETRY_SHADER),
                                             ShaderElem("res/shaders/default/shader.frag", GL_FRAGMENT_SHADER)});
        Shader *shader = new Shader(shaderElems);
        ModelElem modelElem = ModelElem(loader.modelPath, shader, loader.mode);
        Drawer::addModel(modelElem, loader.priority);
        m_Queue.pop();
    }

    glm::mat4 proj = glm::perspective(glm::radians(45.0f - Camera::getZoom() * 10.0f), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 view = Camera::getViewMatrix();
    m_Matrices->subData(0, sizeof(glm::mat4), glm::value_ptr(proj));
    m_Matrices->subData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));

    unsigned int dirLightCount = dirLights.size();
    unsigned int pointLightCount = pointLights.size();
    unsigned int spotLightCount = spotLights.size();
    for (unsigned int i = 0; i < dirLightCount; i++)
        m_Lights->subData(64 * i, sizeof(DirLight), &dirLights[i]);
    for (unsigned int i = 0; i < pointLightCount; i++)
        m_Lights->subData(64 * 1 + 80 * i, sizeof(PointLight), &pointLights[i]);
    for (unsigned int i = 0; i < spotLightCount; i++)
        m_Lights->subData(64 * 1 + 80 * 20 + 112 * i, sizeof(SpotLight), &spotLights[i]);
    m_Lights->subData(64 * 1 + 112 * 5 + 80 * 20, 4, &dirLightCount);
    m_Lights->subData(64 * 1 + 112 * 5 + 80 * 20 + 4 * 1, 4, &pointLightCount);
    m_Lights->subData(64 * 1 + 112 * 5 + 80 * 20 + 4 * 2, 4, &spotLightCount);
}

void Drawer::enqueue(const ModelLoader &loader)
{
    m_Queue.push(loader);
}

std::unordered_map<std::string, Model *> &Drawer::getLoadedModels()
{
    return m_LoadedModels;
}

bool Drawer::getOnWindow()
{
    return m_IsOnWindow;
}

std::unordered_map<std::string, Model *> Drawer::m_LoadedModels;
std::vector<std::vector<ModelElem>> Drawer::m_Models(3, std::vector<ModelElem>());
std::vector<std::vector<MeshElem>> Drawer::m_Meshes(3, std::vector<MeshElem>());
std::vector<DirLight> Drawer::m_DirLights;
std::vector<SpotLight> Drawer::m_SpotLights;
std::vector<PointLight> Drawer::m_PointLights;
std::queue<ModelLoader> Drawer::m_Queue;
UniformBuffer *Drawer::m_Matrices;
UniformBuffer *Drawer::m_Lights;
bool Drawer::m_IsOnWindow = false;