#ifndef MODEL_HPP
#define MODEL_HPP

#include <_mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <unordered_map>
#include <thread>
#include <future>
#include <mutex>

class Model
{
private:
    std::vector<Mesh*> m_Meshes;
    std::string m_Directory;

    void loadModel(const std::string &path, const bool skipTextures);
    void processNode(aiNode *node, const aiScene *scene, const bool skipTextures);
    Mesh *processMesh(aiMesh *mesh, const aiScene *scene, const bool skipTextures);
    static void loadVertices(aiMesh *mesh, std::vector<Vertex> &vertices);
    static void loadIndices(aiMesh *mesh, std::vector<unsigned int> &indices);
    void loadTextureImages(aiMaterial *mat, aiTextureType type, const std::string &typeName, std::vector<Image*> &images, std::vector<std::string> &paths, std::vector<std::string> &types);

public:
    Model(const std::string &path, const bool skipTextures = false);
    Model(const Mesh &mesh);
    ~Model();

    void draw(Shader &shader, unsigned int mode = 0) const;
};

#endif