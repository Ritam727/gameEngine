#include "_renderer.hpp"

void Renderer::clearColor(glm::vec4 clearColor)
{
    GLCall(glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a));
}

void Renderer::clear(unsigned int bits)
{
    GLCall(glClear(bits));
}

void Renderer::drawElem(const VertexArray &array, const Shader &shader, const IndexBuffer &index, glm::mat4 &model)
{
    array.bind();
    index.bind();

    shader.use();
    shader.setMat4f("model", model);

    GLCall(glDrawElements(GL_TRIANGLES, index.getCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::drawArr(const VertexArray &array, const Shader &shader, glm::mat4 &model)
{
    array.bind();

    shader.use();
    shader.setMat4f("model", model);

    GLCall(glDrawArrays(GL_TRIANGLES, 0, array.getCount()));
}

void Renderer::clearDepth()
{
    GLCall(glClearDepth(1.0f));
}

void Renderer::enable(unsigned int feature)
{
    GLCall(glEnable(feature));
}

void Renderer::disable(unsigned int feature)
{
    GLCall(glDisable(feature));
}

void Renderer::blendFunc(unsigned int source, unsigned int target)
{
    GLCall(glBlendFunc(source, target));
}

void Renderer::depthMask(unsigned int value)
{
    GLCall(glDepthMask(value));
}

void Renderer::stencilFunc(unsigned int func, int ref, unsigned int mask)
{
    GLCall(glStencilFunc(func, ref, mask));
}

void Renderer::stencilOp(unsigned int st, unsigned int dp, unsigned int stdp)
{
    GLCall(glStencilOp(st, dp, stdp));
}

void Renderer::stencilMask(unsigned int val)
{
    GLCall(glStencilMask(val));
}

void Renderer::frontFace(unsigned int val)
{
    GLCall(glFrontFace(val));
}

void Renderer::viewportCallback(GLFWwindow *window, int width, int height)
{
    GLCall(glViewport(0, 0, width, height));
}

void Renderer::adjustViewport(const unsigned int st, const unsigned int en, const unsigned int width, const unsigned int height)
{
    GLCall(glViewport(st, en, width, height));
}
