#include "_drawer.hpp"

void Drawer::addModel(ModelElem &modelElem, bool skipTextures)
{
    if (Drawer::m_LoadedModels.find(modelElem.path) != Drawer::m_LoadedModels.end())
    {
        Logger::logInfo("Model already exists in system, not reloading");
        modelElem.model = new Model(*Drawer::m_LoadedModels[modelElem.path]);
    }
    else
    {
        modelElem.model = new Model(modelElem.path, skipTextures);
        Drawer::m_LoadedModels[modelElem.path] = modelElem.model;
    }
    m_Models.push_back(modelElem);
}

void Drawer::setOnWindow(bool value)
{
    m_IsOnWindow = value;
}

void Drawer::addDirLight(DirLight &dirLight)
{
    m_DirLights.push_back(dirLight);
}

void Drawer::addPointLight(PointLight &pointLight)
{
    m_PointLights.push_back(pointLight);
}

void Drawer::addSpotLight(SpotLight &spotLight)
{
    m_SpotLights.push_back(spotLight);
}

void Drawer::lightControlsGui()
{
    std::string dir = "Add Directional Light";
    std::string point = "Add Point Light";
    std::string spot = "Add Spot Light";
    for (unsigned int i = 0; i < m_DirLights.size(); i++)
    {
        std::string o = "Directional Light (" + std::to_string(i) + ")";
        if (ImGui::TreeNode(o.c_str()))
        {
            std::string t = "Direction";
            std::string a = "Ambient";
            std::string d = "Diffuse";
            std::string s = "Specular";
            if (ImGui::TreeNode(t.c_str()))
            {
                ImGui::DragFloat("X", &m_DirLights[i].direction.x, 0.1);
                ImGui::DragFloat("Y", &m_DirLights[i].direction.y, 0.1);
                ImGui::DragFloat("Z", &m_DirLights[i].direction.z, 0.1);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(a.c_str()))
            {
                ImGui::DragFloat("R", &m_DirLights[i].ambient.x, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("G", &m_DirLights[i].ambient.y, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("B", &m_DirLights[i].ambient.z, 0.01, 0.0f, 1.0f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(d.c_str()))
            {
                ImGui::DragFloat("R", &m_DirLights[i].diffuse.x, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("G", &m_DirLights[i].diffuse.y, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("B", &m_DirLights[i].diffuse.z, 0.01, 0.0f, 1.0f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(s.c_str()))
            {
                ImGui::DragFloat("R", &m_DirLights[i].specular.x, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("G", &m_DirLights[i].specular.y, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("B", &m_DirLights[i].specular.z, 0.01, 0.0f, 1.0f);
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }
    for (unsigned int i = 0; i < m_PointLights.size(); i++)
    {
        std::string o = "Point Light (" + std::to_string(i) + ")";
        if (ImGui::TreeNode(o.c_str()))
        {
            std::string p = "Position";
            std::string a = "Ambient";
            std::string d = "Diffuse";
            std::string s = "Specular";
            std::string c = "Intensity";
            if (ImGui::TreeNode(p.c_str()))
            {
                ImGui::DragFloat("X", &m_PointLights[i].position.x, 0.1);
                ImGui::DragFloat("Y", &m_PointLights[i].position.y, 0.1);
                ImGui::DragFloat("Z", &m_PointLights[i].position.z, 0.1);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(a.c_str()))
            {
                ImGui::DragFloat("R", &m_PointLights[i].ambient.x, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("G", &m_PointLights[i].ambient.y, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("B", &m_PointLights[i].ambient.z, 0.01, 0.0f, 1.0f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(d.c_str()))
            {
                ImGui::DragFloat("R", &m_PointLights[i].diffuse.x, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("G", &m_PointLights[i].diffuse.y, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("B", &m_PointLights[i].diffuse.z, 0.01, 0.0f, 1.0f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(s.c_str()))
            {
                ImGui::DragFloat("R", &m_PointLights[i].specular.x, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("G", &m_PointLights[i].specular.y, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("B", &m_PointLights[i].specular.z, 0.01, 0.0f, 1.0f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(c.c_str()))
            {
                ImGui::DragFloat("Linear", &m_PointLights[i].strength, 0.01, 1.0f, 10.0f);
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }
    for (unsigned int i = 0; i < m_SpotLights.size(); i++)
    {
        std::string o = "Spot Light (" + std::to_string(i) + ")";
        if (ImGui::TreeNode(o.c_str()))
        {
            std::string p = "Position";
            std::string t = "Direction";
            std::string a = "Ambient";
            std::string d = "Diffuse";
            std::string s = "Specular";
            std::string c = "Intensity";
            std::string o = "Cutoff";
            if (ImGui::TreeNode(p.c_str()))
            {
                ImGui::DragFloat("X", &m_SpotLights[i].position.x, 0.1);
                ImGui::DragFloat("Y", &m_SpotLights[i].position.y, 0.1);
                ImGui::DragFloat("Z", &m_SpotLights[i].position.z, 0.1);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(t.c_str()))
            {
                ImGui::DragFloat("X", &m_SpotLights[i].direction.x, 0.1);
                ImGui::DragFloat("Y", &m_SpotLights[i].direction.y, 0.1);
                ImGui::DragFloat("Z", &m_SpotLights[i].direction.z, 0.1);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(a.c_str()))
            {
                ImGui::DragFloat("R", &m_SpotLights[i].ambient.x, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("G", &m_SpotLights[i].ambient.y, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("B", &m_SpotLights[i].ambient.z, 0.01, 0.0f, 1.0f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(d.c_str()))
            {
                ImGui::DragFloat("R", &m_SpotLights[i].diffuse.x, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("G", &m_SpotLights[i].diffuse.y, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("B", &m_SpotLights[i].diffuse.z, 0.01, 0.0f, 1.0f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(s.c_str()))
            {
                ImGui::DragFloat("R", &m_SpotLights[i].specular.x, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("G", &m_SpotLights[i].specular.y, 0.01, 0.0f, 1.0f);
                ImGui::DragFloat("B", &m_SpotLights[i].specular.z, 0.01, 0.0f, 1.0f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(c.c_str()))
            {
                ImGui::DragFloat("Linear", &m_SpotLights[i].strength, 0.01, 1.0f, 10.0f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(o.c_str()))
            {
                ImGui::DragFloat("Inner Cutoff", &m_SpotLights[i].innerCutOff, 0.01, 0.0f, 179.99f);
                ImGui::DragFloat("Outer Cutoff", &m_SpotLights[i].outerCutOff, 0.01, 0.01f, 180.0f);
                m_SpotLights[i].outerCutOff = std::max(m_SpotLights[i].outerCutOff, m_SpotLights[i].innerCutOff + 0.01f);
                ImGui::TreePop();
            }
            ImGui::Checkbox("Follow Camera", &m_SpotLights[i].follow);
            ImGui::TreePop();
        }
    }
    if (ImGui::Button(dir.c_str()))
    {
        DirLight _dirLight;
        addDirLight(_dirLight);
    }
    if (ImGui::Button(point.c_str()))
    {
        PointLight _pointLight;
        addPointLight(_pointLight);
    }
    if (ImGui::Button(spot.c_str()))
    {
        SpotLight _spotLight;
        addSpotLight(_spotLight);
    }
}

void Drawer::selectedTransformGui()
{
    std::string t = "Translation";
    std::string r = "Rotation";
    std::string g = "Rotation in Global Coordinates";
    std::string s = "Scale";
    if (ImGui::TreeNode(t.c_str()))
    {
        ImGui::DragFloat("X", &m_SelectedTrans.x, 0.1);
        ImGui::DragFloat("Y", &m_SelectedTrans.y, 0.1);
        ImGui::DragFloat("Z", &m_SelectedTrans.z, 0.1);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode(r.c_str()))
    {
        if (Mesh::getPickedColors().size() > 1)
            ImGui::BeginDisabled(true);
        ImGui::DragFloat("X", &m_SelectedRot.x, 0.1);
        ImGui::DragFloat("Y", &m_SelectedRot.y, 0.1);
        ImGui::DragFloat("Z", &m_SelectedRot.z, 0.1);
        if (Mesh::getPickedColors().size() > 1)
            ImGui::EndDisabled();
        ImGui::TreePop();
    }
    if (ImGui::TreeNode(g.c_str()))
    {
        ImGui::DragFloat("X", &m_SelectedGlobalRot.x, 0.1);
        ImGui::DragFloat("Y", &m_SelectedGlobalRot.y, 0.1);
        ImGui::DragFloat("Z", &m_SelectedGlobalRot.z, 0.1);
        ImGui::DragFloat("N", &m_ViewAngle, 0.1);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode(s.c_str()))
    {
        ImGui::DragFloat("X", &m_SelectedScale.x, 0.1, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        ImGui::DragFloat("Y", &m_SelectedScale.y, 0.1, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        ImGui::DragFloat("Z", &m_SelectedScale.z, 0.1, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        if (m_SelectedScale.x == 0.0f)
            m_SelectedScale.x = 0.00001f;
        if (m_SelectedScale.y == 0.0f)
            m_SelectedScale.y = 0.00001f;
        if (m_SelectedScale.z == 0.0f)
            m_SelectedScale.z = 0.00001f;
        ImGui::TreePop();
    }
}

void Drawer::resetSelectedTransform()
{
    m_SelectedTrans = glm::vec3(0.0f);
    m_SelectedRot = glm::vec3(0.0f);
    m_SelectedGlobalRot = glm::vec3(0.0f);
    m_SelectedScale = glm::vec3(1.0f);
    m_PrevSelectedTrans = glm::vec3(0.0f);
    m_PrevSelectedRot = glm::vec3(0.0f);
    m_PrevSelectedGlobalRot = glm::vec3(0.0f);
    m_PrevSelectedScale = glm::vec3(1.0f);
    m_ViewAngle = 0.0f;
    m_PrevViewAngle = 0.0f;
}

void Drawer::setSelectedTransform(glm::vec3 trans, glm::vec3 rot, glm::vec3 scale)
{
    m_SelectedTrans = m_PrevSelectedTrans = trans;
    m_SelectedRot = m_PrevSelectedRot = rot;
    m_SelectedScale = m_PrevSelectedScale = scale;
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

    m_Lights = new UniformBuffer(2156);
    m_Lights->bindBufferBase(0);

    m_MousePickingBuffer = new FrameBuffer();
    m_MousePickingBuffer->attachTexture(Screen::getScreenWidth(), Screen::getScreenHeight(), 31, 0);
    m_MousePickingBuffer->attachDepthBuffer(Screen::getScreenWidth(), Screen::getScreenHeight());
    m_MousePickingBuffer->validate();
    m_MousePickingBuffer->unbind();

    m_BorderShader = new Shader(
        std::vector<ShaderElem>(
            {ShaderElem("res/shaders/border/shader.vert", GL_VERTEX_SHADER),
             ShaderElem("res/shaders/border/shader.geom", GL_GEOMETRY_SHADER),
             ShaderElem("res/shaders/border/shader.frag", GL_FRAGMENT_SHADER)}));

    m_DefaultShader = new Shader(
        std::vector<ShaderElem>(
            {ShaderElem("res/shaders/default/shader.vert", GL_VERTEX_SHADER),
             ShaderElem("res/shaders/default/shader.geom", GL_GEOMETRY_SHADER),
             ShaderElem("res/shaders/default/shader.frag", GL_FRAGMENT_SHADER)}));

    m_MousePickingShader = new Shader(
        std::vector<ShaderElem>(
            {ShaderElem("res/shaders/mousePicking/shader.vert", GL_VERTEX_SHADER),
             ShaderElem("res/shaders/mousePicking/shader.frag", GL_FRAGMENT_SHADER)}));
}

void Drawer::render()
{
    Renderer::clearColor({0.2f, 0.2f, 0.2f, 1.0f});
    Renderer::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    for (unsigned int i = 0; i < m_Models.size(); i++)
    {
        m_Models[i].shader->use();
        m_Models[i].shader->setVec3f("cameraPos", Camera::getCameraPos());
        m_Models[i].shader->setFloat("time", glfwGetTime());
        m_Models[i].model->draw(*m_Models[i].shader, m_Models[i].mode);
    }
    for (auto &p : Mesh::getSelectedMeshes())
    {
        Renderer::stencilFunc(GL_ALWAYS, 1, 0xFF);
        Renderer::stencilMask(0xFF);

        p.first->updateTrans(m_SelectedTrans - m_PrevSelectedTrans);
        p.first->updateRot(m_SelectedRot - m_PrevSelectedRot);
        p.first->updateGlobalRot(m_SelectedGlobalRot - m_PrevSelectedGlobalRot);
        p.first->rotateAroundAxis(m_ViewAngle - m_PrevViewAngle, -1.0f * Camera::getCameraFront());
        p.first->updateScale(m_SelectedScale / m_PrevSelectedScale);
        if (!(ImGui::IsAnyItemActive() || ImGui::IsAnyItemFocused()))
            p.first->adjustAngles();
        p.first->draw(*p.second.first, p.second.second);

        Renderer::stencilFunc(GL_NOTEQUAL, 1, 0xFF);
        Renderer::stencilMask(0x00);
        Renderer::disable(GL_DEPTH_TEST);

        p.first->draw(*m_BorderShader, p.second.second);

        Renderer::stencilMask(0xFF);
        Renderer::stencilFunc(GL_ALWAYS, 1, 0xFF);
        Renderer::enable(GL_DEPTH_TEST);
    }
    m_PrevSelectedTrans = m_SelectedTrans;
    m_PrevSelectedRot = m_SelectedRot;
    m_PrevSelectedGlobalRot = m_SelectedGlobalRot;
    m_PrevSelectedScale = m_SelectedScale;
    m_PrevViewAngle = m_ViewAngle;
}

void Drawer::renderForMousePicking()
{
    m_MousePickingBuffer->bind();
    Renderer::stencilMask(0x00);
    Renderer::clearColor({0.0f, 0.0f, 0.0f, 1.0f});
    Renderer::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    for (unsigned int i = 0; i < m_Models.size(); i++)
    {
        m_Models[i].shader->use();
        m_Models[i].shader->setVec3f("cameraPos", Camera::getCameraPos());
        m_Models[i].shader->setFloat("time", glfwGetTime());
        m_Models[i].model->draw(*m_MousePickingShader, m_Models[i].mode, 0);
    }

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    glm::vec2 mousePos = {io.MousePos.x, io.MousePos.y};
    float pressed = io.MouseDownDuration[0];

    if (pressed > -1 && !m_IsOnWindow && !m_MouseLeftHeldDown)
    {
        unsigned char pixels[3];
        m_MouseLeftHeldDown = true;
        GLCall(glReadPixels((int)mousePos.x, Screen::getScreenHeight() - (int)mousePos.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels));
        int r = pixels[0], g = pixels[1], b = pixels[2];
        if (m_ShiftHeldDown)
        {
            if (Mesh::getColorMap().find(glm::vec3(r, g, b)) == Mesh::getColorMap().end() || !Mesh::getColorMap()[glm::vec3(r, g, b)]->selected())
                Mesh::addPickedColor(glm::vec3(r, g, b), false);
            else
                Mesh::removePickedColor(glm::vec3(r, g, b));
        }
        else
        {
            Mesh::addPickedColor(glm::vec3(r, g, b), true);
        }
    }
    else if (pressed == -1)
    {
        m_MouseLeftHeldDown = false;
    }

    if (!(ImGui::IsAnyItemActive() || ImGui::IsAnyItemFocused()))
        Drawer::resetSelectedTransform();

    if (Mesh::getPickedColors().size() == 1)
    {
        Mesh *curMesh = Mesh::getColorMap()[*Mesh::getPickedColors().begin()];
        setSelectedTransform(curMesh->getTrans(), curMesh->getRot(), curMesh->getScale());
    }
    Renderer::stencilMask(0xFF);
    m_MousePickingBuffer->unbind();
}

void Drawer::update(const unsigned int width, const unsigned int height)
{
    while (!m_Queue.empty())
    {
        ModelLoader loader = m_Queue.front();
        ModelElem modelElem = ModelElem(loader.modelPath, m_DefaultShader, loader.mode);
        Drawer::addModel(modelElem);
        m_Queue.pop();
    }

    glm::mat4 proj = glm::perspective(glm::radians(45.0f - Camera::getZoom() * 10.0f), (float)width / (float)height, 0.1f, 50000.0f);
    glm::mat4 view = Camera::getViewMatrix();
    m_Matrices->subData(0, sizeof(glm::mat4), glm::value_ptr(proj));
    m_Matrices->subData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));

    unsigned int dirLightCount = m_DirLights.size();
    unsigned int pointLightCount = m_PointLights.size();
    unsigned int spotLightCount = m_SpotLights.size();
    for (unsigned int i = 0; i < dirLightCount; i++)
        m_Lights->subData(64 * i, sizeof(DirLight), &m_DirLights[i]);
    for (unsigned int i = 0; i < pointLightCount; i++)
        m_Lights->subData(64 * 1 + 80 * i, sizeof(PointLight), &m_PointLights[i]);
    for (unsigned int i = 0; i < spotLightCount; i++)
    {
        if (m_SpotLights[i].follow)
        {
            m_SpotLights[i] = m_SpotLights[i].setPosition(Camera::getCameraPos());
            m_SpotLights[i] = m_SpotLights[i].setDirection(Camera::getCameraFront());
        }
        m_Lights->subData(64 * 1 + 80 * 20 + 96 * i, sizeof(SpotLight) - sizeof(bool), &m_SpotLights[i]);
    }
    m_Lights->subData(64 * 1 + 96 * 5 + 80 * 20, 4, &dirLightCount);
    m_Lights->subData(64 * 1 + 96 * 5 + 80 * 20 + 4 * 1, 4, &pointLightCount);
    m_Lights->subData(64 * 1 + 96 * 5 + 80 * 20 + 4 * 2, 4, &spotLightCount);
}

void Drawer::enqueue(const ModelLoader &loader)
{
    m_Queue.push(loader);
}

void Drawer::keyboardCallback(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
        m_ShiftHeldDown = true;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
        m_ShiftHeldDown = false;
}

bool Drawer::getOnWindow()
{
    return m_IsOnWindow;
}

std::unordered_map<std::string, Model *> Drawer::m_LoadedModels;
std::vector<ModelElem> Drawer::m_Models;
std::vector<DirLight> Drawer::m_DirLights;
std::vector<SpotLight> Drawer::m_SpotLights;
std::vector<PointLight> Drawer::m_PointLights;
std::queue<ModelLoader> Drawer::m_Queue;
UniformBuffer *Drawer::m_Matrices;
UniformBuffer *Drawer::m_Lights;
FrameBuffer *Drawer::m_MousePickingBuffer;
bool Drawer::m_IsOnWindow = false;
bool Drawer::m_MouseLeftHeldDown = false;
bool Drawer::m_ShiftHeldDown = false;
glm::vec3 Drawer::m_SelectedTrans(0.0f);
glm::vec3 Drawer::m_SelectedRot(0.0f);
glm::vec3 Drawer::m_SelectedGlobalRot(0.0f);
glm::vec3 Drawer::m_SelectedScale(1.0f);
float Drawer::m_ViewAngle(0.0f);
glm::vec3 Drawer::m_PrevSelectedTrans(0.0f);
glm::vec3 Drawer::m_PrevSelectedRot(0.0f);
glm::vec3 Drawer::m_PrevSelectedGlobalRot(0.0f);
glm::vec3 Drawer::m_PrevSelectedScale(1.0f);
float Drawer::m_PrevViewAngle(0.0f);
Shader *Drawer::m_BorderShader;
Shader *Drawer::m_DefaultShader;
Shader *Drawer::m_MousePickingShader;