#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace glm
{
    glm::mat4 rotation(glm::vec3 angles);
    glm::mat4 rotation(const glm::mat4 &mat, const float &angle, glm::vec3 axis);
    glm::mat4 rotation(const glm::mat4 &mat, glm::vec3 angles);
    glm::vec3 rotation(const glm::vec3 &vec, glm::vec3 angles);
}