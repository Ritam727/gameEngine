#ifndef DIR_LIGHT_HPP
#define DIR_LIGHT_HPP

#include <glm/glm.hpp>

struct DirLight
{
    glm::vec4 direction;

    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;

    DirLight();

    DirLight setDirection(const glm::vec3 &direction);
    
    DirLight setAmbient(const glm::vec3 &ambient);
    DirLight setDiffuse(const glm::vec3 &diffuse);
    DirLight setSpecular(const glm::vec3 &specular);
};

#endif