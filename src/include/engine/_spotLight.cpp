#include "_spotLight.hpp"

SpotLight::SpotLight()
    : position(0.0f), direction(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)),
      ambient(0.2f), diffuse(0.5f), specular(1.0f),
      constant(1.0f), linear(0.0f), quadratic(0.0f),
      innerCutOff(cos(glm::radians(12.5f))), outerCutOff(cos(glm::radians(17.5f)))
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

SpotLight SpotLight::setConstant(const float &constant)
{
    this->constant = constant;
    return *this;
}

SpotLight SpotLight::setLinear(const float &linear)
{
    this->linear = linear;
    return *this;
}

SpotLight SpotLight::setQuadratic(const float &quadratic)
{
    this->quadratic = quadratic;
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
