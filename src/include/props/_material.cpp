#include "_material.hpp"

Material::Material(const std::vector<std::string> &textures)
    : diffuseCount(0), specularCount(0), emissionCount(0), normalCount(0), shininess(32.0f)
{
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        if (Texture::getLoadedTextures()[textures[i]]->getType() == "diffuse")
        {
            this->diffuse[this->diffuseCount++] = Texture::getLoadedTextures()[textures[i]]->getSlot();
        }
        else if (Texture::getLoadedTextures()[textures[i]]->getType() == "specular")
        {
            this->specular[this->specularCount++] = Texture::getLoadedTextures()[textures[i]]->getSlot();
        }
        else if (Texture::getLoadedTextures()[textures[i]]->getType() == "emission")
        {
            this->emission[this->emissionCount++] = Texture::getLoadedTextures()[textures[i]]->getSlot();
        }
        else if(Texture::getLoadedTextures()[textures[i]]->getType() == "normal")
        {
            this->normal[this->normalCount++] = Texture::getLoadedTextures()[textures[i]]->getSlot();
        }
    }
}

Material::~Material()
{
}
