#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <_texture.hpp>

#include <vector>
#include <memory>

struct Material
{
    unsigned int diffuse[8];
    unsigned int specular[8];
    unsigned int emission[8];
    unsigned int normal[8];

    float shininess;

    unsigned int diffuseCount;
    unsigned int specularCount;
    unsigned int emissionCount;
    unsigned int normalCount;

    Material(const std::vector<std::string> &textures);
    ~Material();
};

#endif