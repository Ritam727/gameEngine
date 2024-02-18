#include "_spotLight.hpp"

SpotLight::SpotLight()
    : position(0.0f), direction(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f)),
      ambient(0.2f), diffuse(0.5f), specular(1.0f),
      innerCutOff(12.5), outerCutOff(17.5),
      follow(false), strength(1.0f)
{
}

SpotLight SpotLight::setPosition(const glm::vec3 &position)
{
    this->position = glm::vec4(position, 0.0f);
    return *this;
}

SpotLight SpotLight::setDirection(const glm::vec3 &direction)
{
    this->direction = glm::vec4(direction, 0.0f);
    return *this;
}

SpotLight SpotLight::setAmbient(const glm::vec3 &ambient)
{
    this->ambient = glm::vec4(ambient, 0.0f);
    return *this;
}

SpotLight SpotLight::setDiffuse(const glm::vec3 &diffuse)
{
    this->diffuse = glm::vec4(diffuse, 0.0f);
    return *this;
}

SpotLight SpotLight::setSpecular(const glm::vec3 &specular)
{
    this->specular = glm::vec4(specular, 0.0f);
    return *this;
}

SpotLight SpotLight::setStrength(const float &strength)
{
    this->strength = strength;
    return *this;
}

SpotLight SpotLight::setInnerCutOff(const float &innerCutOff)
{
    this->innerCutOff = innerCutOff;
    return *this;
}

SpotLight SpotLight::setOuterCutOff(const float &outerCutOff)
{
    this->outerCutOff = outerCutOff;
    return *this;
}
