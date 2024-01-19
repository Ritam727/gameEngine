#ifndef BASIC_MATERIAL_HPP
#define BASIC_MATERIAL_HPP

#include <glm/glm.hpp>

struct BasicMaterial
{
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emission;

    float shininess;

    BasicMaterial();
    ~BasicMaterial();
};

#endif