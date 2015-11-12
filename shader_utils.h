#ifndef _SHADER_UTILS_H_
#define _SHADER_UTILS_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
GLuint createProgram(char const* vshader_filename, char const* fshader_filename);
#endif
