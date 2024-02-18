#include "_pointLight.hpp"

PointLight::PointLight()
    : position(0.0f), ambient(0.2f), diffuse(0.5f), specular(1.0f), strength(1.0f)
{
}

PointLight PointLight::setPosition(const glm::vec3 &position)
{
    this->position = glm::vec4(position, 0.0f);
    return *this;
}

PointLight PointLight::setAmbient(const glm::vec3 &ambient)
{
    this->ambient = glm::vec4(ambient, 0.0f);
    return *this;
}

PointLight PointLight::setDiffuse(const glm::vec3 &diffuse)
{
    this->diffuse = glm::vec4(diffuse, 0.0f);
    return *this;
}

PointLight PointLight::setSpecular(const glm::vec3 &specular)
{
    this->specular = glm::vec4(specular, 0.0f);
    return *this;
}

PointLight PointLight::setStrength(const float &strength)
{
    this->strength = strength;
    return *this;
}
