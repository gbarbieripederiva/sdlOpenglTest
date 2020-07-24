#ifndef __RENDERER__
#define __RENDERER__

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <iostream>
#include <vector>

class Renderer
{
private:
    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);

public:
    GLuint program = 0;
    std::vector<GLuint> buffers; 
    void (* renderFunction)(Renderer *);
    
    Renderer(std::string vshaderSource, std::string fshaderSource);
    ~Renderer();

    void render(){this->renderFunction(this);};
};

#endif