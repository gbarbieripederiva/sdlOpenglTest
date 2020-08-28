#include "renderer.hpp"

/*
json schema:{
    //if it starts with debuff its add as de draw elements buffer
    "nameOfAttribute or debuff": {
    "data": [],
    //optional default is this
    //possibilities, GL_ELEMENT_ARRAY_BUFFER and GL_ARRAY_BUFFER
    "target":"GL_ARRAY_BUFFER",
    "framesize": uint,
    //optional default is this
    //possible types are GL_UNSIGNED_INT and GL_FLOAT
    "type":"GL_FLOAT",
    "stride":uint,
    //optional default is this
    //possibilities, GL_STATIC_DRAW and GL_DYNAMIC_DRAW
    "usage":"GL_STATIC_DRAW"
  }
}

*/

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

void Renderer::readDataJson(std::string path){
    //TODO:validate json

    //open json and parse it
    rapidjson::Document json;
    {
        std::stringstream jsonSS;
        std::fstream jsonFile;
        jsonFile.open("./assets/data.json",std::ios::in);
        jsonSS << jsonFile.rdbuf();
        jsonFile.close();
        jsonFile.clear();
        json.Parse(jsonSS.str().c_str());
    }

    for(rapidjson::Value::ConstMemberIterator itr = json.MemberBegin();itr != json.MemberEnd(); itr++){
        GLenum target;
        GLenum type;
        size_t framesize = itr->value["framesize"].GetUint();
        const rapidjson::Value &data = itr->value["data"];
        size_t size = data.Size();
        size_t typesize;
        GLenum usage;
        if(itr->value.HasMember("type") && std::string(itr->value["type"].GetString()) == "GL_UNSIGNED_INT"){
            type = GL_UNSIGNED_INT;
        }else{
            type = GL_FLOAT;
        }
        if(itr->value.HasMember("target") && std::string(itr->value["target"].GetString()) == "GL_ELEMENT_ARRAY_BUFFER"){
            target = GL_ELEMENT_ARRAY_BUFFER;
        }else{
            target = GL_ARRAY_BUFFER;
        }
        if(itr->value.HasMember("usage") && std::string(itr->value["usage"].GetString()) == "GL_DYNAMIC_DRAW"){
            usage = GL_DYNAMIC_DRAW;
        }else{
            usage = GL_STATIC_DRAW;
        }

        Buffer *buff = new Buffer();
        if(GL_UNSIGNED_INT == type){
            GLuint *dataArr = new GLuint[size];
            for(int i = 0; i < size; i++){
                dataArr[i] = (GLuint)(data[i].GetFloat());
            }
            typesize = sizeof(GLuint);
            buff->data(dataArr);
            buff->size(size*typesize);
            buff->typeSize(typesize);
            buff->deallocFunc([](void *data){
                delete []((GLuint *)data);
            });
        }else{
            GLfloat *dataArr = new GLfloat[size];
            for(int i = 0; i < size; i++){
                dataArr[i] = (GLfloat)(data[i].GetFloat());
            }
            typesize = sizeof(GLfloat);
            buff->data(dataArr);
            buff->size(size*typesize);
            buff->typeSize(typesize);
            buff->deallocFunc([](void *data){
                delete []((GLfloat *)data);
            });
        }
        buff->target(target);
        buff->frameSize(framesize);
        buff->type(type);
        buff->usage(usage);
        
        buff->shouldBeDeallocated(true);

        if(std::string(itr->name.GetString()).substr(0,6) == "deBuff"){
            if(itr->value.HasMember("mode") && std::string(itr->value["mode"].GetString()) == "GL_TRIANGLE_STRIP"){
                buff->mode(GL_TRIANGLE_STRIP);
            }else{
                buff->mode(GL_TRIANGLE_FAN);
            }
            buff->bind();
            buff->initData();
            this->appendDEBuffer(buff);
        }else{
            buff->stride(typesize * itr->value["stride"].GetUint());
            buff->location(Buffer::findLocation(*(this->getProgram()),itr->name.GetString()));
            buff->bind();
            buff->initData();
            buff->bindToVertexAttr();
            this->appendVBuffer(buff);
        }
    }
}
