#ifndef MODEL_HPP
#define MODEL_HPP

#include "_mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <unordered_set>
#include <unordered_map>
#include <thread>
#include <future>
#include <mutex>

struct Vec3Hash
{
    size_t operator() (const glm::vec3 &v) const
    {
        unsigned int r = v.r;
        unsigned int g = v.g;
        unsigned int b = v.b;
        std::hash<unsigned int> h;
        return h(r | (g >> 8) | (b >> 16));
    }
};

class Model
{
private:
    std::unordered_set<Mesh*> m_Meshes;
    std::string m_Directory;

    static std::unordered_set<glm::vec3, Vec3Hash> m_PickedColors;
    static std::unordered_map<Mesh*, std::pair<Shader*, unsigned int>> m_MeshShaderMode;

    void loadModel(const std::string &path, const bool skipTextures);
    void processNode(aiNode *node, const aiScene *scene, const bool skipTextures);
    Mesh *processMesh(aiMesh *mesh, const aiScene *scene, const bool skipTextures);
    static void loadVertices(aiMesh *mesh, std::vector<Vertex> &vertices);
    static void loadIndices(aiMesh *mesh, std::vector<unsigned int> &indices);
    void loadTextureImages(aiMaterial *mat, aiTextureType type, const std::string &typeName, std::vector<Image*> &images, std::vector<std::string> &paths, std::vector<std::string> &types);

public:
    Model(const std::string &path, const bool skipTextures = false);
    Model(const Mesh &mesh);
    Model(const Model &model);
    ~Model();

    void draw(Shader &shader, unsigned int mode = 0, unsigned int drawGui = 1) const;

    const std::unordered_set<Mesh*> getMeshes() const;
    
    static void addPickedColor(const glm::vec3 color, const bool clear);
    static std::unordered_map<Mesh*, std::pair<Shader*, unsigned int>> getSelectedMeshes();
};

#endif