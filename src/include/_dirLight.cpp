#include "_dirLight.hpp"

DirLight::DirLight()
    : direction(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)),
      ambient(0.2f), diffuse(0.5f), specular(1.0f)
{
}

DirLight DirLight::setDirection(const glm::vec3 &direction)
{
    this->direction = glm::vec4(direction, 0.0f);
    return *this;
}

DirLight DirLight::setAmbient(const glm::vec3 &ambient)
{
    this->ambient = glm::vec4(ambient, 0.0f);
    return *this;
}

DirLight DirLight::setDiffuse(const glm::vec3 &diffuse)
{
    this->diffuse = glm::vec4(diffuse, 0.0f);
    return *this;
}

DirLight DirLight::setSpecular(const glm::vec3 &specular)
{
    this->specular = glm::vec4(specular, 0.0f);
    return *this;
}
