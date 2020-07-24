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
#include "program.hpp"
#include "buffer.hpp"

class Renderer
{
private:
    Program *program = NULL;
    std::vector<Buffer*> buffers;
public:
    
    //GETTERS--------------------------------------------
    Program* getProgram(){return this->program;};

    void appendBuffer(Buffer *buffer){this->buffers.push_back(buffer);};

    /* TODO:add a render function */
    void render(){
        
    };
    
    
    Renderer(std::string vshaderSource, std::string fshaderSource);
    ~Renderer();

};

#endif