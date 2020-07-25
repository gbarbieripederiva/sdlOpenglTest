#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "application.hpp"
#include "renderer.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


void eventHandler(SDL_Event &e, Application &app)
{
    switch (e.type)
    {
    case SDL_QUIT:
        app.quit = true;
        break;
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case 'q':
            app.quit = true;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    

    Application app;
    app.setTitle("Hello world");
    app.setHandleEvent((void (*)(SDL_Event *, Application *))eventHandler);
    app.setStartedCallback([](Application *app){
        
        //create Renderer
        std::fstream shaderFile;
        shaderFile.open("./shaders/vshader.shader");
        std::stringstream vshaderSource;
        // review performance loss https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
        vshaderSource<<shaderFile.rdbuf();
        shaderFile.close();
        shaderFile.clear();

        shaderFile.open("./shaders/fshader.shader");
        std::stringstream fshaderSource;
        fshaderSource<<shaderFile.rdbuf();
        shaderFile.close();
        shaderFile.clear();
        Renderer *renderer = new Renderer(
            vshaderSource.str(),
            fshaderSource.str()
        );

        //create vertex data buffer
        GLfloat *vdata = new GLfloat[8];
        vdata[0]= -0.5f;vdata[1]= -0.5f;
        vdata[2]=  0.5f;vdata[3]= -0.5f;
        vdata[4]=  0.5f;vdata[5]=  0.5f;
        vdata[6]= -0.5f;vdata[7]=  0.5f;
        Buffer *vbuff = new Buffer();
        vbuff->data(vdata);
        vbuff->target(GL_ARRAY_BUFFER);
        vbuff->location(Buffer::findLocation(*(renderer->getProgram()),"my_vpos"));
        vbuff->frameSize(2);
        vbuff->type(GL_FLOAT);
        vbuff->stride(2*sizeof(GLfloat));
        vbuff->size(8*sizeof(GLfloat));
        vbuff->usage(GL_STATIC_DRAW);
        vbuff->typeSize(sizeof(GLfloat));
        vbuff->shouldBeDeallocated(true);
        vbuff->deallocFunc([](void *data){
            delete []((GLfloat *)data);
        });
        vbuff->bind();
        vbuff->initData();
        vbuff->bindToVertexAttr();
        renderer->appendVBuffer(vbuff);

        //create vertex data buffer
        GLfloat *cdata = new GLfloat[16];
        cdata[0]=   1.0f;cdata[1]=   1.0f;cdata[2]=   1.0f;cdata[3]=   1.0f;
        cdata[4]=   1.0f;cdata[5]=   0.0f;cdata[6]=   0.0f;cdata[7]=   1.0f;
        cdata[8]=   0.0f;cdata[9]=   1.0f;cdata[10]=  0.0f;cdata[11]=  1.0f;
        cdata[12]=  0.0f;cdata[13]=  0.0f;cdata[14]=  1.0f;cdata[15]=  1.0f;
        Buffer *cbuff = new Buffer();
        cbuff->data(cdata);
        cbuff->target(GL_ARRAY_BUFFER);
        cbuff->location(Buffer::findLocation(*(renderer->getProgram()),"my_vcolor"));
        cbuff->frameSize(2);
        cbuff->type(GL_FLOAT);
        cbuff->stride(4*sizeof(GLfloat));
        cbuff->size(16*sizeof(GLfloat));
        cbuff->usage(GL_STATIC_DRAW);
        cbuff->typeSize(sizeof(GLfloat));
        cbuff->shouldBeDeallocated(true);
        cbuff->deallocFunc([](void *data){
            delete []((GLfloat *)data);
        });
        cbuff->bind();
        cbuff->initData();
        cbuff->bindToVertexAttr();
        renderer->appendVBuffer(cbuff);

        //create index data buffer
        Buffer *ibuff = new Buffer();
        GLuint *idata = new GLuint[4];
        idata[0] = 0;idata[1] =  1;
        idata[2] = 2;idata[3] = 3;
        ibuff->target(GL_ELEMENT_ARRAY_BUFFER);
        ibuff->data(idata);
        ibuff->mode(GL_TRIANGLE_FAN);
        ibuff->frameSize(4);
        ibuff->type(GL_UNSIGNED_INT);
        ibuff->size(4*sizeof(GLuint));
        ibuff->usage(GL_STATIC_DRAW);
        ibuff->shouldBeDeallocated(true);
        ibuff->deallocFunc([](void *data){
            delete []((GLuint *)data);
        });
        ibuff->bind();
        ibuff->initData();
        renderer->appendDEBuffer(ibuff);
        
        glClearColor(0.0f,0.0f,0.0f,1.0f);

        app->appendRenderer(renderer);
    });
    app.startApplication();
    return 0;
}
