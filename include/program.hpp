#ifndef __PROGRAM__
#define __PROGRAM__
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <iostream>

class Program
{
private:
    GLuint program = 0;

    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);
public:
    Program(std::string vshaderSource, std::string fshaderSource);
    void bind();
    void unbind();
    //requires program be bound
    GLuint getAttributeLocation(std::string attr);
    GLuint getProgram();
    ~Program();
};

#endif