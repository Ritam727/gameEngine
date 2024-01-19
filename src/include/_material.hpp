#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <_texture.hpp>

#include <vector>
#include <memory>

struct Material
{
    unsigned int diffuse[32];
    unsigned int specular[32];
    unsigned int emission[32];
    unsigned int normal[32];

    float shininess;

    unsigned int diffuseCount;
    unsigned int specularCount;
    unsigned int emissionCount;
    unsigned int normalCount;

    Material(const std::vector<std::string> &textures);
    ~Material();
};

#endif