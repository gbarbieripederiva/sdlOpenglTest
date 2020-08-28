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
#include <fstream>
#include <sstream>
#include "program.hpp"
#include "buffer.hpp"

// https://github.com/Tencent/rapidjson
#include <rapidjson/document.h>

class Renderer
{
private:
    Program *program = NULL;
    std::vector<Buffer*> vbuffers;
    std::vector<Buffer*> debuffers;
public:
    
    //GETTERS--------------------------------------------
    Program* getProgram(){return this->program;};

    void appendVBuffer(Buffer *vbuffer){this->vbuffers.push_back(vbuffer);};
    void appendDEBuffer(Buffer *debuffer){this->debuffers.push_back(debuffer);};

    void readDataJson(std::string path);

    void render(){
        program->bind();
        for (auto vb : vbuffers)
        {
            vb->bind();
            vb->enableVertexAttr();
        }
        for(auto deb:debuffers){
            deb->bind();
            deb->drawElements();
        }
        program->unbind();
    };
    Renderer(std::string vshaderSource, std::string fshaderSource);
    Renderer(std::string vshaderSource, std::string fshaderSource,bool isFile);
    ~Renderer();

};

#endif