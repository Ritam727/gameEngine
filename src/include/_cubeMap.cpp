#include "_cubeMap.hpp"

CubeMap::CubeMap(std::string &name, std::vector<std::string> &faces)
{
    GLCall(glGenTextures(1, &m_ID));
    GLCall(glActiveTexture(GL_TEXTURE31));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID));

    std::vector<Image *> _images;
    for (unsigned int i = 0; i < faces.size(); i++)
        _images.push_back(Texture::loadImage(faces[i], false));

    float tt = glfwGetTime();
    std::vector<std::thread> _threads;
    for (Image *img : _images)
        _threads.push_back(std::thread(&Image::get, img));
    for (std::thread &th : _threads)
        th.join();
    Logger::logInfo("Took {:05.5f} ms to load textures", (glfwGetTime() - tt) * 1000.0f);

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        if (_images[i]->data)
        {
            GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, _images[i]->format, _images[i]->width, _images[i]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, _images[i]->data));
            _images[i]->free();
        }
        else
        {
            Logger::logWarn("Couldn't load cubemap texture: {0}", faces[i]);
        }
    }
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
}

CubeMap::~CubeMap()
{
    GLCall(glDeleteTextures(1, &m_ID));
}

void CubeMap::bind()
{
    GLCall(glActiveTexture(GL_TEXTURE31));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID));
}
