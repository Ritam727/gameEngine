#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <gl/_texture.hpp>

#include <vector>
#include <memory>

struct Material
{
    unsigned int diffuse[1];
    unsigned int specular[1];
    unsigned int emission[1];
    unsigned int normal[1];

    float shininess;

    unsigned int diffuseCount;
    unsigned int specularCount;
    unsigned int emissionCount;
    unsigned int normalCount;

    Material(const std::vector<std::string> &textures);
    ~Material();
};

#endif