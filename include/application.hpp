#ifndef __APPLICATION__
#define __APPLICATION__
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <iostream>
#include <vector>
#include "renderer.hpp"

#define FPS 1

class Application
{
private:
    void (*handleEvent)(SDL_Event *,Application*) = NULL;
    void (*startedCallback)(Application*) = NULL;
    void (*mainLoopCallback)(Application*) = NULL;
    std::string title;
    std::vector<Renderer> renderVector;



    //render application
    void render();
public:
    //if true application is closed
    bool quit = false;
    
    //application entrypoint
    void startApplication();

    //function called after window initialized
    void setStartedCallback(void (*startedCallback)(Application*)){this->startedCallback = startedCallback;};
    //function called every loop
    void setMainLoopCallback(void (*mainLoopCallback)(Application*)){this->mainLoopCallback = mainLoopCallback;};


    //renderers function
    int appendRenderer(Renderer renderer){this->renderVector.push_back(renderer);return this->renderVector.size()-1;};

    //some simple setters
    void setHandleEvent(void (*eventHandler)(SDL_Event *,Application*)){this->handleEvent = eventHandler;};
    void setTitle(const std::string title){this->title = title;};
    

    ~Application(){
        this->renderVector.clear();
    }
};

#endif