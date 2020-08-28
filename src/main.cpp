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

// https://github.com/Tencent/rapidjson
#include <rapidjson/document.h>

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
        Renderer *renderer = new Renderer(
            "./assets/vshader.shader",
            "./assets/fshader.shader",
            true
        );
        renderer->readDataJson("./assets/data.json");
        
        glClearColor(0.0f,0.0f,0.0f,1.0f);

        app->appendRenderer(renderer);
    });
    app.startApplication();
    return 0;
}
