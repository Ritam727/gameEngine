#ifndef HELPER_CPP
#define HELPER_CPP

#include <_vertex.hpp>

#include <set>
#include <vector>
#include <glm/glm.hpp>

struct Vec2Sort
{
    inline bool operator()(const glm::vec2 &v1, const glm::vec2 &v2) const
    {
        if (v1.x < v2.x) return true;
        if (v1.x == v2.x) return (v1.y < v2.y);
        return false;
    }
};

class Helper
{
public:
    static std::set<glm::vec2, Vec2Sort> getConvexHull(const std::vector<glm::vec2> &vertices);
};

#endif