#include "_camera.hpp"

void Camera::init()
{
    m_CameraFront = glm::normalize(m_CameraFront);
}

glm::vec3 Camera::getCameraPos()
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

float Camera::getZoom()
{
    return m_Zoom;
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
    glm::vec3 forward = glm::cross(worldUp, right);
}

void Camera::setCameraUp(const glm::vec3 up)
{
    m_CameraUp = glm::normalize(up);
}

void Camera::drawCameraControlsGui()
{
    if (ImGui::TreeNode("Translation"))
    {
        ImGui::DragFloat("X", &m_CameraPos.x, 0.1);
        ImGui::DragFloat("Y", &m_CameraPos.y, 0.1);
        ImGui::DragFloat("Z", &m_CameraPos.z, 0.1);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Rotation"))
    {
        ImGui::DragFloat("X", &m_Yaw, 0.1);
        ImGui::DragFloat("Y", &m_Pitch, 0.1);
        ImGui::TreePop();
    }
    ImGui::DragFloat("Camera Zoom", &m_Zoom, 0.1, -3.0f, 3.0f);
    updateDirection();
}

void Camera::updateDirection()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw - 90.0f)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw - 90.0f)) * cos(glm::radians(m_Pitch));
    setCameraFront(glm::normalize(direction));
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(getCameraPos(), getCameraFront() + getCameraPos(), getCameraUp());
}

glm::vec3 Camera::m_CameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
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