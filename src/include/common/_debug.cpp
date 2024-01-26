#include "_debug.hpp"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool GLLogCall(const char *file, const char *function, int line)
{
    bool value = true;
    while (GLenum error = glGetError())
    {
        Logger::logError("[OpenGL Error] ({0}) in file {1}, at function {2}, on line {3}", error, file, function, line);
        value = false;
    }
    return value;
}