#ifndef SPOT_LIGHT_HPP
#define SPOT_LIGHT_HPP

#include <glm/glm.hpp>

struct SpotLight
{
    glm::vec4 position;
    glm::vec4 direction;

    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;

    float strength;

    float innerCutOff;
    float outerCutOff;

    bool follow;

    SpotLight();

    SpotLight setPosition(const glm::vec3 &position);
    SpotLight setDirection(const glm::vec3 &direction);

    SpotLight setAmbient(const glm::vec3 &ambient);
    SpotLight setDiffuse(const glm::vec3 &diffuse);
    SpotLight setSpecular(const glm::vec3 &specular);

    SpotLight setStrength(const float &strength);

    SpotLight setInnerCutOff(const float &innerCutOff);
    SpotLight setOuterCutOff(const float &outerCutOff);
};

#endif