#include "renderer.hpp"

Renderer::Renderer(std::string vshaderSource, std::string fshaderSource)
{
    this->program = new Program(vshaderSource,fshaderSource);
}

Renderer::~Renderer()
{
    delete this->program;
}


