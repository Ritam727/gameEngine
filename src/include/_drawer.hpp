#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <_model.hpp>
#include <_camera.hpp>
#include <_screen.hpp>

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
    unsigned int priority;

    ModelLoader(const std::string &path, const unsigned int mode, const unsigned int priority)
    {
        this->modelPath = path;
        this->mode = mode;
        this->priority = priority;
    }
};

class Drawer
{
private:
    static std::vector<std::vector<ModelElem>> m_Models;
    static std::vector<std::vector<MeshElem>> m_Meshes;
    static std::vector<DirLight> m_DirLights;
    static std::vector<SpotLight> m_SpotLights;
    static std::vector<PointLight> m_PointLights;
    static std::queue<ModelLoader> m_Queue;
    static UniformBuffer *m_Matrices;
    static UniformBuffer *m_Lights;
    static std::unordered_map<std::string, Model*> m_LoadedModels;
    static bool m_IsOnWindow;

public:
    static void init();
    static void render();
    static void renderForMousePicking(bool onWindow);
    static void update(const unsigned int width, const unsigned int height, const std::vector<DirLight> &dirLights, const std::vector<PointLight> &pointLights, const std::vector<SpotLight> &spotLights);
    static void enqueue(const ModelLoader &loader);

    static void addModel(ModelElem &modelElem, unsigned int priority, bool skipTextures = false);
    static void addMesh(Mesh *mesh, Shader *shader, unsigned int mode, unsigned int priority, const glm::vec3 &trans, const glm::vec3 &rot, const glm::vec3 &scale);
    static void setOnWindow(bool value);

    static void clearMeshes();
    static void clearModels();
    static void clearUniformBuffers();

    static std::unordered_map<std::string, Model*> &getLoadedModels();
    static bool getOnWindow();
};

#endif