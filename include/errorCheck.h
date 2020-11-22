#pragma once
#ifndef _ERRORCHECK_H_
#define  _ERRORCHECK_H_
#include"defines.h"
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x)  GLClearError();\
  x;\
  ASSERT(GLLogCall(#x,__FILE__,__LINE__))
inline void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);

}
inline bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        cout << "OpenGL error " << function << " " << file << ":" << line;
        return false;
    }
    return true;

}

#endif //!_ERRORCHECK_H_