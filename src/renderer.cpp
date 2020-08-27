#include "renderer.hpp"

Renderer::Renderer(std::string vshaderSource, std::string fshaderSource)
{
    this->program = new Program(vshaderSource,fshaderSource);
}

Renderer::Renderer(std::string vshaderSource, std::string fshaderSource,bool isFile)
{
    if(!isFile){
        this->program = new Program(vshaderSource,fshaderSource);
    }else{
        // create a file stream
        std::fstream shaderFile;

        //open vertex shader file, read it and store it in a string stream
        shaderFile.open(vshaderSource);
        std::stringstream vshaderSourceStream;
        // review performance loss https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
        vshaderSourceStream<<shaderFile.rdbuf();

        //close file and clear it
        shaderFile.close();
        shaderFile.clear();

        //open fragment shader file, read it and store it in a string stream
        shaderFile.open(fshaderSource);
        std::stringstream fshaderSourceStream;
        fshaderSourceStream<<shaderFile.rdbuf();

        //close file and clear it
        shaderFile.close();
        shaderFile.clear();

        //create a program with the read files
        this->program = new Program(vshaderSourceStream.str(),fshaderSourceStream.str());
    }
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


