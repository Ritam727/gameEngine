#include "_helper.hpp"

std::set<glm::vec2, Vec2Sort> Helper::getConvexHull(const std::vector<glm::vec2> &_vertices)
{
    std::vector<glm::vec2> hull;
    if (_vertices.size() > 1)
    {
        for (unsigned int rIt = 0; rIt < _vertices.size();)
        {
            if (hull.size() < 2)
            {
                hull.push_back(_vertices[rIt]);
                rIt++;
                continue;
            }
            glm::vec3 p = glm::vec3(hull[hull.size() - 2], 0.0f);
            glm::vec3 q = glm::vec3(hull[hull.size() - 1], 0.0f);
            glm::vec3 r = glm::vec3(_vertices[rIt], 0.0f);
            glm::vec3 _cross = glm::cross(r - q, q - p);
            if (_cross.z > 0)
            {
                hull.push_back(r);
                rIt++;
            }
            else
            {
                hull.pop_back();
            }
        }
        for (int rIt = _vertices.size() - 1; rIt >= 0;)
        {
            if (hull.size() < 2)
            {
                hull.push_back(_vertices[rIt]);
                rIt--;
                continue;
            }
            glm::vec3 p = glm::vec3(hull[hull.size() - 2], 0.0f);
            glm::vec3 q = glm::vec3(hull[hull.size() - 1], 0.0f);
            glm::vec3 r = glm::vec3(_vertices[rIt], 0.0f);
            glm::vec3 _cross = glm::cross(r - q, q - p);
            if (_cross.z >= 0)
            {
                hull.push_back(r);
                rIt--;
            }
            else
            {
                hull.pop_back();
            }
        }
    }
    std::set<glm::vec2, Vec2Sort> _hull(hull.begin(), hull.end());
    return _hull;
}