#include "renderer.hpp"

Renderer::Renderer(std::string vshaderSource, std::string fshaderSource)
{
    this->program = new Program(vshaderSource,fshaderSource);
}

Renderer::~Renderer()
{
    delete this->program;
    for(auto a:this->vbuffers){
        if(a->shouldBeDeallocated()){
            delete a;
        }
    }
    for(auto a:this->debuffers){
        if (a->shouldBeDeallocated())
        {
            delete a;
        }
    }
}


