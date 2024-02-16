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

    float constant;
    float linear;
    float quadratic;

    float innerCutOff;
    float outerCutOff;

    bool follow;

    SpotLight();

    SpotLight setPosition(const glm::vec3 &position);
    SpotLight setDirection(const glm::vec3 &direction);

    SpotLight setAmbient(const glm::vec3 &ambient);
    SpotLight setDiffuse(const glm::vec3 &diffuse);
    SpotLight setSpecular(const glm::vec3 &specular);

    SpotLight setConstant(const float &constant);
    SpotLight setLinear(const float &linear);
    SpotLight setQuadratic(const float &quadratic);

    SpotLight setInnerCutOff(const float &innerCutOff);
    SpotLight setOuterCutOff(const float &outerCutOff);
};

#endif