#include "_shader.hpp"

unsigned int Shader::compileShader(const char *filePath, unsigned int type)
{
    std::string shaderData;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    try
    {
        shaderFile.open(filePath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        shaderData = shaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        Logger::logError("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ {0}", filePath);
    }

    const char *data = shaderData.c_str();

    unsigned int shaderID = glCreateShader(type);
    GLCall(glShaderSource(shaderID, 1, &data, NULL));
    GLCall(glCompileShader(shaderID));

    int success;
    char infoLog[512];
    GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success));
    if (success != GL_TRUE)
    {
        GLCall(glGetShaderInfoLog(shaderID, 512, NULL, infoLog));
        std::string typeString;
        if (type == GL_VERTEX_SHADER)
        {
            typeString = "VERTEX";
        }
        else if (type == GL_GEOMETRY_SHADER)
        {
            typeString = "GEOMETRY";
        }
        else if (type == GL_FRAGMENT_SHADER)
        {
            typeString = "FRAGMENT";
        }
        Logger::logError("ERROR::SHADER::{0}::COMPILATION FAILED", typeString);
        Logger::logError(infoLog);
    }

    return shaderID;
}

int Shader::getUniformLocation(const std::string &name) const
{
    GLCall(int location = glGetUniformLocation(m_ID, name.c_str()));
    return location;
}

Shader::Shader(std::vector<ShaderElem> shaderElems)
{
    GLCall(m_ID = glCreateProgram());

    std::vector<unsigned int> _shaders;

    for (ShaderElem &shaderElem : shaderElems)
    {
        unsigned int _shader = compileShader(shaderElem.path.c_str(), shaderElem.type);
        _shaders.push_back(_shader);
        GLCall(glAttachShader(m_ID, _shader));
    }
    GLCall(glLinkProgram(m_ID));

    int success;
    char infoLog[512];
    GLCall(glGetProgramiv(m_ID, GL_LINK_STATUS, &success));
    if (success != GL_TRUE)
    {
        GLCall(glGetProgramInfoLog(m_ID, 512, NULL, infoLog));
        Logger::logError("ERROR::PROGRAM::LINKING FAILED");
        Logger::logError(infoLog);
    }

    for (unsigned int _shader : _shaders)
    {
        GLCall(glDeleteShader(_shader));
    }
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_ID));
}

void Shader::use() const
{
    GLCall(glUseProgram(m_ID));
}

void Shader::setBool(const std::string &name, bool value) const
{
    GLCall(glUniform1i(getUniformLocation(name), (int)value));
}

void Shader::setInt(const std::string &name, int value) const
{
    GLCall(glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value));
}

void Shader::setFloat(const std::string &name, float value) const
{
    GLCall(glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value));
}

void Shader::setMat4f(const std::string &name, const glm::mat4 &trans) const
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(trans)));
}

void Shader::setVec2i(const std::string &name, const int *value) const
{
    GLCall(glUniform1iv(getUniformLocation(name), 2, value));
}

void Shader::setVec3f(const std::string &name, const glm::vec3 &value) const
{
    GLCall(glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value)));
}

void Shader::setVec4f(const std::string &name, const glm::vec4 &value) const
{
    GLCall(glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value)));
}

void Shader::setSpotLight(const std::string &name, const SpotLight &light) const
{
    this->setVec3f(name + ".position", light.position);
    this->setVec3f(name + ".direction", light.direction);
    this->setVec3f(name + ".ambient", light.ambient);
    this->setVec3f(name + ".diffuse", light.diffuse);
    this->setVec3f(name + ".specular", light.specular);
    this->setFloat(name + ".constant", light.constant);
    this->setFloat(name + ".linear", light.linear);
    this->setFloat(name + ".quadratic", light.quadratic);
    this->setFloat(name + ".innerCutOff", light.innerCutOff);
    this->setFloat(name + ".outerCutOff", light.outerCutOff);
}

void Shader::setDirLight(const std::string &name, const DirLight &light) const
{
    this->setVec3f(name + ".direction", light.direction);
    this->setVec3f(name + ".ambient", light.ambient);
    this->setVec3f(name + ".diffuse", light.diffuse);
    this->setVec3f(name + ".specular", light.specular);
}

void Shader::setPointLight(const std::string &name, const PointLight &light) const
{
    this->setVec3f(name + ".position", light.position);
    this->setVec3f(name + ".ambient", light.ambient);
    this->setVec3f(name + ".diffuse", light.diffuse);
    this->setVec3f(name + ".specular", light.specular);
    this->setFloat(name + ".constant", light.constant);
    this->setFloat(name + ".linear", light.linear);
    this->setFloat(name + ".quadratic", light.quadratic);
}

void Shader::setPointLights(const std::string &name, std::vector<PointLight> &lights) const
{
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        this->setPointLight(name + "[" + std::to_string(i) + "]", lights[i]);
    }
}

void Shader::setMaterial(const std::string &name, Material &material) const
{
    for (unsigned int i = 0; i < material.diffuseCount; i++)
    {
        this->setInt(name + ".diffuse[" + std::to_string(i) + "]", material.diffuse[i]);
    }
    for (unsigned int i = 0; i < material.specularCount; i++)
    {
        this->setInt(name + ".specular[" + std::to_string(i) + "]", material.specular[i]);
    }
    for (unsigned int i = 0; i < material.emissionCount; i++)
    {
        this->setInt(name + ".emission[" + std::to_string(i) + "]", material.emission[i]);
    }
    for (unsigned int i = 0; i < material.normalCount; i++)
        this->setInt(name + ".normal[" + std::to_string(i) + "]", material.normal[i]);
    this->setInt(name + ".diffuseCount", material.diffuseCount);
    this->setInt(name + ".specularCount", material.specularCount);
    this->setInt(name + ".emissionCount", material.emissionCount);
    this->setInt(name + ".normalCount", material.normalCount);
    this->setFloat(name + ".shininess", 32.0f);
}

void Shader::setBasicMaterial(const std::string &name, BasicMaterial &material) const
{
    this->setVec3f(name + ".diffuse", material.diffuse);
    this->setVec3f(name + ".specular", material.specular);
    this->setVec3f(name + ".emission", material.emission);
    this->setFloat(name + ".shininess", material.shininess);
}
