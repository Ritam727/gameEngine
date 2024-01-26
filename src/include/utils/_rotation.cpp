#include "_rotation.hpp"

glm::mat4 glm::rotation(glm::vec3 angles)
{
    glm::quat _rot = glm::quat(angles);
    glm::mat4 _mat = glm::mat4_cast(_rot);
    return _mat;
}

glm::mat4 glm::rotation(const glm::mat4 &mat, const float &angle, glm::vec3 axis)
{
    glm::quat _rot = glm::angleAxis(angle, glm::normalize(axis));
    glm::mat4 _mat = glm::mat4_cast(_rot);
    return mat * _mat;
}

glm::mat4 glm::rotation(const glm::mat4 &mat, glm::vec3 angles)
{
    glm::quat _rot = glm::normalize(glm::quat(angles));
    glm::mat4 _mat = glm::mat4_cast(_rot);
    return mat * _mat;
}
