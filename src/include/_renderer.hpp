#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <_debug.hpp>
#include <_shader.hpp>
#include <_vertexArray.hpp>
#include <_indexBuffer.hpp>
#include <_dirLight.hpp>
#include <_spotLight.hpp>
#include <_pointLight.hpp>
#include <_uniformBuffer.hpp>
#include <_camera.hpp>
#include <_screen.hpp>

#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

class Renderer
{
private:
    Renderer() = delete;
    Renderer(const Renderer &renderer) = delete;

public:
    static void clearColor(glm::vec4 clearColor);
    static void clear(unsigned int bits);
    static void drawElem(const VertexArray &array, const Shader &shader, const IndexBuffer &index, glm::mat4 &model);
    static void drawArr(const VertexArray &array, const Shader &shader, glm::mat4 &model);

    static void clearDepth();
    
    static void enable(unsigned int feature);
    static void disable(unsigned int feature);
    static void blendFunc(unsigned int source, unsigned int target);
    static void depthMask(unsigned int value);
    static void stencilFunc(unsigned int func, int ref, unsigned int mask);
    static void stencilOp(unsigned int st, unsigned int dp, unsigned int stdp);
    static void stencilMask(unsigned int val);
    static void frontFace(unsigned int val);

    static void viewportCallback(GLFWwindow *window, int width, int height);
    static void adjustViewport(const unsigned int st, const unsigned int en, const unsigned int width, const unsigned int height);
};

#endif