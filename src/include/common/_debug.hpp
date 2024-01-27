#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "_logger.hpp"

#include <glad/glad.h>
#include <iostream>
#include <stb_image/stb_image.h>


#if defined ENVIRONMENT_DEBUG
#if defined PLATFORM_LINUX
#include <signal.h>
#define dbg raise(SIGTRAP)
#elif defined PLATFORM_WINDOWS
#define dbg __debugbreak()
#else
#error "UNSUPPORTED PLATFORM"
#endif
#else
#define dbg
#endif

#define ASSERT(x) if (!(x)) dbg;
#define GLCall(x)   GLClearError();\
                    x;\
                    ASSERT(GLLogCall(__FILE__, #x, __LINE__))

void GLClearError();
bool GLLogCall(const char *file, const char *function, int line);

#endif