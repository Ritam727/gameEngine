#include "_camera.hpp"

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

glm::vec3 Camera::getCameraForward()
{
    return m_CameraFoward;
}

glm::vec3 Camera::getCameraRight()
{
    return m_CameraRight;
}

float Camera::getFOV()
{
    return m_FOV;
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

void Camera::revertCameraY()
{
    m_Yaw -= 180.0f;
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    setCameraFront(glm::normalize(direction));
}

void Camera::invertCameraY()
{
    m_Yaw += 180.0f;
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    setCameraFront(glm::normalize(direction));
}

void Camera::keyboardCallback(GLFWwindow *window, const float deltaTime)
{
    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        updateCameraPos(cameraSpeed * ((float) m_FPSCamera * getCameraForward() + (float) (1 - m_FPSCamera) * getCameraFront()));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        updateCameraPos(-cameraSpeed * ((float) m_FPSCamera * getCameraForward() + (float) (1 - m_FPSCamera) * getCameraFront()));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        updateCameraPos(-cameraSpeed * ((float) m_FPSCamera * getCameraRight() + (float) (1 - m_FPSCamera) * glm::normalize(glm::cross(m_CameraFront, m_CameraUp))));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        updateCameraPos(cameraSpeed * ((float) m_FPSCamera * getCameraRight() + (float) (1 - m_FPSCamera) * glm::normalize(glm::cross(m_CameraFront, m_CameraUp))));
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !m_KeyHeldDown)
        m_FPSCamera = 1 - m_FPSCamera, m_KeyHeldDown = true;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
        m_KeyHeldDown = false;
}

void Camera::mouseCallback(GLFWwindow *window, double xPos, double yPos)
{
    if (m_FirstMouse)
    {
        m_LastX = xPos;
        m_LastY = yPos;
        m_FirstMouse = false;
    }

    float xOffset = xPos - m_LastX;
    float yOffset = yPos - m_LastY;
    m_LastX = xPos;
    m_LastY = yPos;

    xOffset *= m_Sensitivity;
    yOffset *= m_Sensitivity;

    m_Yaw += xOffset;
    m_Pitch = std::min(std::max(m_Pitch - yOffset, -89.0f), 89.0f);

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    setCameraFront(glm::normalize(direction));
}

void Camera::scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
    m_FOV = std::min(std::max(m_FOV - (float) yOffset, 1.0f), 45.0f);
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(getCameraPos(), getCameraFront() + getCameraPos(), getCameraUp());
}

glm::vec3 Camera::m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 Camera::m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Camera::m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Camera::m_CameraFoward = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Camera::m_CameraRight = glm::vec3(1.0f, 0.0f, 0.0f);

float Camera::m_LastX = 400.0f;
float Camera::m_LastY = 300.0f;
float Camera::m_Sensitivity = 0.1f;
float Camera::m_Yaw = -90.0f;
float Camera::m_Pitch = 0.0f;
float Camera::m_FOV = 45.0f;

int Camera::m_FPSCamera = 0.0f;

bool Camera::m_FirstMouse = true;
bool Camera::m_KeyHeldDown = false;