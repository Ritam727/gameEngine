#include "_camera.hpp"

glm::vec3 &Camera::getCameraPos()
{
    return m_CameraPos;
}

glm::vec3 Camera::getCameraFront()
{
    return m_CameraFront;
}

glm::vec3 Camera::getCameraUp()
{
    return m_CameraUp;
}

glm::vec3 Camera::getCameraForward()
{
    return m_CameraFoward;
}

glm::vec3 Camera::getCameraRight()
{
    return m_CameraRight;
}

float &Camera::getZoom()
{
    return m_Zoom;
}

float &Camera::getPitch()
{
    return m_Pitch;
}

float &Camera::getYaw()
{
    return m_Yaw;
}

void Camera::setCameraPos(const glm::vec3 pos)
{
    m_CameraPos = pos;
}

void Camera::setCameraFront(const glm::vec3 front)
{
    m_CameraFront = glm::normalize(front);
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(m_CameraFront, worldUp));
    setCameraUp(glm::cross(right, m_CameraFront));
    setCameraRight(right);
    glm::vec3 forward = glm::cross(worldUp, right);
    setCameraFoward(forward);
}

void Camera::setCameraUp(const glm::vec3 up)
{
    m_CameraUp = glm::normalize(up);
}

void Camera::setCameraFoward(const glm::vec3 forward)
{
    m_CameraFoward = glm::normalize(forward);
}

void Camera::setCameraRight(const glm::vec3 right)
{
    m_CameraRight = glm::normalize(right);
}

void Camera::updateCameraPos(const glm::vec3 diff)
{
    glm::vec3 pos = m_CameraPos + diff;
    setCameraPos(pos);
}

void Camera::updateCameraFront(const glm::vec3 diff)
{
    glm::vec3 front = m_CameraFront + diff;
    setCameraFront(front);
}

void Camera::updateCameraUp(const glm::vec3 diff)
{
    glm::vec3 up = m_CameraUp + diff;
    setCameraUp(up);
}

void Camera::drawCameraControlsGui()
{
    if (ImGui::TreeNode("Translation"))
    {
        ImGui::SliderFloat("X", &getCameraPos().x, std::min(getCameraPos().x, -10.0f), std::max(getCameraPos().x, 10.0f));
        ImGui::SliderFloat("Y", &getCameraPos().y, std::min(getCameraPos().y, -10.0f), std::max(getCameraPos().y, 10.0f));
        ImGui::SliderFloat("Z", &getCameraPos().z, std::min(getCameraPos().z, -10.0f), std::max(getCameraPos().z, 10.0f));
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Rotation"))
    {
        ImGui::SliderFloat("X", &getYaw(), std::min(getYaw(), -360.0f), std::max(getYaw(), 360.0f));
        ImGui::SliderFloat("Y", &getPitch(), std::min(getPitch(), -360.0f), std::max(getPitch(), 360.0f));
        ImGui::TreePop();
    }
    ImGui::SliderFloat("Camera Zoom", &getZoom(), -2.0f, 2.0f);
}

void Camera::revertCameraY()
{
    m_Yaw -= 180.0f;
    updateDirection();
}

void Camera::updateDirection()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(getYaw() - 90.0f)) * cos(glm::radians(getPitch()));
    direction.y = sin(glm::radians(getPitch()));
    direction.z = sin(glm::radians(getYaw() - 90.0f)) * cos(glm::radians(getPitch()));
    setCameraFront(glm::normalize(direction));
}

void Camera::invertCameraY()
{
    m_Yaw += 180.0f;
    updateDirection();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(getCameraPos(), getCameraFront() + getCameraPos(), getCameraUp());
}

glm::vec3 Camera::m_CameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 Camera::m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Camera::m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Camera::m_CameraFoward = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Camera::m_CameraRight = glm::vec3(1.0f, 0.0f, 0.0f);

float Camera::m_LastX = 400.0f;
float Camera::m_LastY = 300.0f;
float Camera::m_Sensitivity = 0.1f;
float Camera::m_Yaw = 0.0f;
float Camera::m_Pitch = 0.0f;
float Camera::m_Zoom = 0.0f;

int Camera::m_FPSCamera = 0.0f;

bool Camera::m_FirstMouse = true;
bool Camera::m_KeyHeldDown = false;