#ifndef DRAWER_HPP
#define DRAWER_HPP

#include "_model.hpp"

#include <common/_camera.hpp>
#include <common/_screen.hpp>
#include <engine/_dirLight.hpp>
#include <engine/_spotLight.hpp>
#include <engine/_pointLight.hpp>
#include <utils/_helper.hpp>
#include <gl/_uniformBuffer.hpp>
#include <gl/_frameBuffer.hpp>

#include <queue>

struct ModelElem
{
    std::string path;
    Model *model;
    Shader *shader;
    unsigned int mode;

    glm::vec3 trans;
    glm::vec3 rot;
    glm::vec3 scale;

    ModelElem(std::string &path, Shader *shader, unsigned int mode)
        : trans(0.0f), rot(0.0f), scale(1.0f)
    {
        this->path = path;
        this->shader = shader;
        this->mode = mode;
    }

    ModelElem setTranslation(const glm::vec3 &trans)
    {
        this->trans = trans;
        return *this;
    }

    ModelElem setRotation(const glm::vec3 &rot)
    {
        this->rot = rot;
        return *this;
    }

    ModelElem setScale(const glm::vec3 &scale)
    {
        this->scale = scale;
        return *this;
    }
};

struct MeshElem
{
    Mesh *mesh;
    Shader *shader;
    unsigned int mode;

    glm::vec3 trans;
    glm::vec3 rot;
    glm::vec3 scale;

    MeshElem(Mesh *mesh, Shader *shader, unsigned int mode)
    {
        this->mesh = mesh;
        this->shader = shader;
        this->mode = mode;
    }

    MeshElem setTranslation(const glm::vec3 &trans)
    {
        this->trans = trans;
        return *this;
    }

    MeshElem setRotation(const glm::vec3 &rot)
    {
        this->rot = rot;
        return *this;
    }

    MeshElem setScale(const glm::vec3 &scale)
    {
        this->scale = scale;
        return *this;
    }
};

struct ModelLoader
{
    std::string modelPath;
    unsigned int mode;

    ModelLoader(const std::string &path, const unsigned int mode)
    {
        this->modelPath = path;
        this->mode = mode;
    }
};

class Drawer
{
private:
    static std::vector<ModelElem> m_Models;
    static std::vector<DirLight> m_DirLights;
    static std::vector<SpotLight> m_SpotLights;
    static std::vector<PointLight> m_PointLights;
    static std::queue<ModelLoader> m_Queue;
    static UniformBuffer *m_Matrices;
    static UniformBuffer *m_Lights;
    static FrameBuffer *m_MousePickingBuffer;
    static std::unordered_map<std::string, Model*> m_LoadedModels;
    static bool m_IsOnWindow;
    static bool m_MouseLeftHeldDown;
    static bool m_ShiftHeldDown;
    static glm::vec3 m_SelectedTrans;
    static glm::vec3 m_SelectedRot;
    static glm::vec3 m_SelectedGlobalRot;
    static glm::vec3 m_SelectedScale;
    static glm::vec3 m_PrevSelectedTrans;
    static glm::vec3 m_PrevSelectedRot;
    static glm::vec3 m_PrevSelectedGlobalRot;
    static glm::vec3 m_PrevSelectedScale;
    static Shader *m_BorderShader;
    static Shader *m_DefaultShader;
    static Shader *m_MousePickingShader;

public:
    static void init();
    static void render();
    static void renderForMousePicking();
    static void update(const unsigned int width, const unsigned int height);
    static void enqueue(const ModelLoader &loader);
    static void keyboardCallback(GLFWwindow *window, float deltaTime);

    static void addModel(ModelElem &modelElem, bool skipTextures = false);
    static void setOnWindow(bool value);
    static void addDirLight(DirLight &dirLight);
    static void addPointLight(PointLight &pointLight);
    static void addSpotLight(SpotLight &spotLight);
    static void lightControlsGui();
    static void selectedTransformGui();
    static void resetSelectedTransform();
    static void setSelectedTransform(glm::vec3 trans, glm::vec3 rot, glm::vec3 globalRot, glm::vec3 scale);

    static void clearModels();
    static void clearUniformBuffers();
    
    static bool getOnWindow();
};

#endif