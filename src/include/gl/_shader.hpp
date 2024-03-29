#ifndef SHADER_HPP
#define SHADER_HPP

#include "_debug.hpp"
#include <props/_material.hpp>
#include <props/_basicMaterial.hpp>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderElem
{
    std::string path;
    unsigned int type;

    ShaderElem(const std::string &path, const unsigned int type)
    {
        this->path = path;
        this->type = type;
    }
};

class Shader
{
private:
    unsigned int m_ID;

    unsigned int compileShader(const char *filePath, unsigned int type);
    int getUniformLocation(const std::string &name) const;

public:
    Shader(std::vector<ShaderElem> shaderElems);
    ~Shader();

    void use() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4f(const std::string &name, const glm::mat4 &trans) const;
    void setVec2i(const std::string &name, const int *value) const;
    void setVec3f(const std::string &name, const glm::vec3 &value) const;
    void setVec4f(const std::string &name, const glm::vec4 &value) const;
};

#endif