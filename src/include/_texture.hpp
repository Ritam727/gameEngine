#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <_debug.hpp>
#include <_screen.hpp>

#include <string>
#include <iostream>
#include <unordered_map>

struct Image
{
    int width;
    int height;
    int channels;
    unsigned int format;
    std::string path;

    unsigned char *data;

    Image(const std::string &path)
    {
        this->data = NULL;
        this->path = path;
        this->format = GL_RGB;
    }

    void get()
    {
        this->data = stbi_load(this->path.c_str(), &this->width, &this->height, &this->channels, 0);
        if (this->channels == 1)
            this->format = GL_RED;
        if (this->channels == 4)
            this->format = GL_RGBA;
    }

    void free()
    {
        stbi_image_free(this->data);
        this->data = NULL;
    }

    ~Image()
    {
        if (this->data) this->free();
    }
};

class Texture
{
private:
    unsigned int m_ID;
    unsigned int m_Slot;
    std::string m_Type;
    std::string m_File;
    static std::unordered_map<std::string, Image*> m_LoadedImages;
    static std::unordered_map<std::string, Texture*> m_LoadedTextures;

public:
    Texture();
    Texture(Image *image, const std::string &type);
    ~Texture();

    void bind(unsigned int slot);
    static Image *loadImage(const std::string &path, const bool flip = true);
    void attachData(Image *image);
    void adjustDimensions();

    const unsigned int& getSlot() const;
    const std::string &getFile() const;
    const std::string& getType() const;
    const unsigned int& getID() const;

    static std::unordered_map<std::string, Image*> &getLoadedImages();
    static std::unordered_map<std::string, Texture*> &getLoadedTextures();

    static void clearTextures();
};

#endif