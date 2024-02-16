#include "_basicMaterial.hpp"

BasicMaterial::BasicMaterial()
    : diffuse({0.8f, 0.2f, 0.2f}), specular(0.5f), emission(0.0f), shininess(32.0f)
{
}

BasicMaterial::~BasicMaterial()
{
}
