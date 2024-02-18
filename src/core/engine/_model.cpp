#include "_model.hpp"

void Model::loadModel(const std::string &path, const bool skipTextures)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Logger::logWarn("ERROR::ASSIMP::{0}", importer.GetErrorString());
        return;
    }

    m_Directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene, skipTextures);
}

void Model::processNode(aiNode *node, const aiScene *scene, const bool skipTextures)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(processMesh(mesh, scene, skipTextures));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene, skipTextures);
}

Mesh *Model::processMesh(aiMesh *mesh, const aiScene *scene, const bool skipTextures)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture *> textures;
    std::vector<Image *> _images;
    std::vector<std::string> _paths;
    std::vector<std::string> _types;

    std::vector<std::thread> _threads;
    _threads.push_back(std::thread(&Model::loadVertices, mesh, std::ref(vertices)));
    _threads.push_back(std::thread(&Model::loadIndices, mesh, std::ref(indices)));

    if (mesh->mMaterialIndex >= 0 && !skipTextures)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        loadTextureImages(material, aiTextureType_DIFFUSE, "diffuse", _images, _paths, _types);
        loadTextureImages(material, aiTextureType_SPECULAR, "specular", _images, _paths, _types);
        loadTextureImages(material, aiTextureType_HEIGHT, "normal", _images, _paths, _types);

        for (Image *img : _images)
            _threads.push_back(std::thread(&Image::get, Texture::getLoadedImages()[img->path]));
    }

    float tt = glfwGetTime();
    for (std::thread &th : _threads)
        th.join();
    Logger::logInfo("Took {:05.5f} ms to load textures", (glfwGetTime() - tt) * 1000.0f);

    if (mesh->mMaterialIndex >= 0 && !skipTextures)
    {
        for (unsigned int i = 0; i < _paths.size(); i++)
        {
            if (Texture::getLoadedTextures().find(_paths[i]) != Texture::getLoadedTextures().end())
            {
                Logger::logInfo("Texture {0} already exists, not recreating, instead using the existing texture", _paths[i]);
                textures.push_back(Texture::getLoadedTextures()[_paths[i]]);
            }
            else
            {
                textures.push_back(new Texture(Texture::getLoadedImages()[_paths[i]], _types[i]));
                Texture::getLoadedTextures()[_paths[i]] = *textures.rbegin();
            }
        }
    }

    return new Mesh(vertices, indices, textures);
}

void Model::loadTextureImages(aiMaterial *mat, aiTextureType type, const std::string &typeName, std::vector<Image *> &images, std::vector<std::string> &paths, std::vector<std::string> &types)
{
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string filePath = m_Directory + "/" + str.C_Str();
        paths.push_back(filePath);
        types.push_back(typeName);
        if (Texture::getLoadedImages().find(filePath) == Texture::getLoadedImages().end())
        {
            if (typeName == "diffuse")
                images.push_back(Texture::loadImage(filePath, false, false));
            else
                images.push_back(Texture::loadImage(filePath, false));
            Texture::getLoadedImages()[filePath] = *images.rbegin();
            continue;
        }
        Logger::logInfo("Image {0} already loaded, not reloading, instead existing image", filePath);
    }
}

void Model::loadVertices(aiMesh *mesh, std::vector<Vertex> &vertices)
{
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D vec = mesh->mVertices[i];
        aiVector3D norm = mesh->mNormals[i];
        Vertex vertex = Vertex()
                            .setPos({vec.x, vec.y, vec.z})
                            .setNorm({norm.x, norm.y, norm.z});
        if (mesh->mTextureCoords[0])
            vertex = vertex.setTex({mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
        else
            vertex = vertex.setTex({0.0f, 0.0f});
        vertices.push_back(vertex);
    }
}

void Model::loadIndices(aiMesh *mesh, std::vector<unsigned int> &indices)
{
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
}

Model::Model(const std::string &path, const bool skipTextures)
{
    loadModel(path, skipTextures);
}

Model::Model(const Model &model)
{
    for (const Mesh *mesh : model.getMeshes())
        this->m_Meshes.push_back(new Mesh(*mesh));
}

Model::~Model()
{
    for (Mesh *mesh : m_Meshes)
        delete mesh;
}

void Model::draw(Shader &shader, unsigned int mode, unsigned int drawGui) const
{
    for (Mesh *mesh : m_Meshes)
    {
        if (!drawGui || !mesh->selected())
        {
            mesh->drawSelectButton(drawGui, false);
            Renderer::stencilMask(0x00);
            mesh->draw(shader, mode);
            if (drawGui && Mesh::getSelectedMeshes().find(mesh) != Mesh::getSelectedMeshes().end())
            {
                mesh->select(false);
                Mesh::getSelectedMeshes().erase(mesh);
            }
        }
        else
        {
            mesh->drawSelectButton(drawGui, true);
            Mesh::getSelectedMeshes()[mesh] = {&shader, mode};
            Mesh::getPickedColors().insert(mesh->getPickerColor());
        }
    }
}

const std::vector<Mesh *> Model::getMeshes() const
{
    return m_Meshes;
}
