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
        // review performance loss https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
        std::fstream shaderFile;
        shaderFile.open("./shaders/vshader.shader");
        std::stringstream vshaderSource;
        vshaderSource<<shaderFile.rdbuf();
        shaderFile.close();
        shaderFile.clear();

        shaderFile.open("./shaders/fshader.shader");
        std::stringstream fshaderSource;
        fshaderSource<<shaderFile.rdbuf();
        shaderFile.close();
        shaderFile.clear();
        Renderer renderer(
            vshaderSource.str(),
            fshaderSource.str()
        );
    });
    app.startApplication();
    return 0;
}
