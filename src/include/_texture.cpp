#include "_texture.hpp"

Texture::Texture()
{
    GLCall(glGenTextures(1, &m_ID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    this->adjustDimensions();
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::Texture(Image *image, const std::string &type)
    : m_Type(type), m_Slot(0), m_File(image->path)
{
    GLCall(glGenTextures(1, &m_ID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));

    this->attachData(image);
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_ID));
}

void Texture::bind(unsigned int slot)
{
    m_Slot = slot;
    GLCall(glBindTextureUnit(slot, m_ID));
}

Image *Texture::loadImage(const std::string &path, const bool flip)
{
    stbi_set_flip_vertically_on_load(flip);
    return new Image(path);
}

void Texture::attachData(Image *image)
{
    GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, image->format, image->width, image->height, 0, image->format, GL_UNSIGNED_BYTE, image->data));
    image->free();
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
}

void Texture::adjustDimensions()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Screen::getScreenWidth(), Screen::getScreenHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
}

const unsigned int &Texture::getSlot() const
{
    return m_Slot;
}

const std::string &Texture::getFile() const
{
    return m_File;
}

const std::string &Texture::getType() const
{
    return m_Type;
}

const unsigned int &Texture::getID() const
{
    return m_ID;
}

std::unordered_map<std::string, Image *> &Texture::getLoadedImages()
{
    return m_LoadedImages;
}

std::unordered_map<std::string, Texture *> &Texture::getLoadedTextures()
{
    return m_LoadedTextures;
}

void Texture::clearTextures()
{
    for (auto &tex : m_LoadedTextures)
        delete tex.second;
    for (auto &img : m_LoadedImages)
        delete img.second;
}

std::unordered_map<std::string, Image *> Texture::m_LoadedImages;
std::unordered_map<std::string, Texture *> Texture::m_LoadedTextures;