#ifndef CUBE_MAP_HPP
#define CUBE_MAP_HPP

#include <_renderer.hpp>
#include <_debug.hpp>
#include <_screen.hpp>
#include <_texture.hpp>
#include <_logger.hpp>

#include <vector>
#include <string>
#include <thread>

class CubeMap
{
private:
    unsigned int m_ID;

    static std::unordered_map<std::string, CubeMap*> m_CubeMaps;

public:
    CubeMap(std::string &name, std::vector<std::string> &faces);
    ~CubeMap();

    void bind();
};

#endif