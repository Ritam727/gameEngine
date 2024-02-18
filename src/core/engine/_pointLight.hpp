#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include <glm/glm.hpp>

struct PointLight
{
    glm::vec4 position;

    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;

    float strength;

    PointLight();

    PointLight setPosition(const glm::vec3 &position);

    PointLight setAmbient(const glm::vec3 &ambient);
    PointLight setDiffuse(const glm::vec3 &diffuse);
    PointLight setSpecular(const glm::vec3 &specular);

    PointLight setStrength(const float &strength);
};

#endif