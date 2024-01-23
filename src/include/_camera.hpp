#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>

#include <iostream>

class Camera
{
private:
    static glm::vec3 m_CameraPos;
    static glm::vec3 m_CameraFront;
    static glm::vec3 m_CameraUp;
    static glm::vec3 m_CameraFoward;
    static glm::vec3 m_CameraRight;

    static float m_LastX;
    static float m_LastY;
    static float m_Yaw;
    static float m_Pitch;
    static float m_Sensitivity;
    static float m_Zoom;

    static int m_FPSCamera;

    static bool m_FirstMouse;
    static bool m_KeyHeldDown;

    Camera() = delete;
    Camera(const Camera &camera) = delete;

public:
    static void init();
    
    static glm::vec3 &getCameraPos();
    static glm::vec3 getCameraFront();
    static glm::vec3 getCameraUp();
    static glm::vec3 getCameraForward();
    static glm::vec3 getCameraRight();

    static float &getZoom();
    static float &getPitch();
    static float &getYaw();

    static void setCameraPos(const glm::vec3 pos);
    static void setCameraFront(const glm::vec3 front);
    static void setCameraUp(const glm::vec3 up);
    static void setCameraFoward(const glm::vec3 forward);
    static void setCameraRight(const glm::vec3 right);

    static void updateCameraPos(const glm::vec3 diff);
    static void updateCameraFront(const glm::vec3 diff);
    static void updateCameraUp(const glm::vec3 diff);

    static void drawCameraControlsGui();

    static void invertCameraY();
    static void revertCameraY();
    static void updateDirection();

    static glm::mat4 getViewMatrix();
};

#endif