#include "application.hpp"


void Application::startApplication(){
    // init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
        printf("error initializing SDL: %s\n", SDL_GetError());
        return;
    }
    const int windowWidth=640,windowHeight=480;
    //create a window
    SDL_Window* window = SDL_CreateWindow(this->title.c_str(), 
                                       SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 
                                       windowWidth, windowHeight, 
                                       SDL_WINDOW_OPENGL);

    SDL_GLContext glCtx = SDL_GL_CreateContext(window);
    if(glCtx == NULL){
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
        return;
    }
    //Initialize GLEW
    glewExperimental = GL_TRUE; 
    GLenum glewError = glewInit();
    if( glewError != GLEW_OK )
    {
        printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
        return;
    }

    //Oficially started application
    if(this->startedCallback!=NULL){
        this->startedCallback(this);
    }

    // poll events and pass to handler
    SDL_Event e;
    Uint32 ticks = SDL_GetTicks();
    while(!this->quit){
        if (SDL_PollEvent(&e))
        {
            this->handleEvent(&e,this);
        }
        if(SDL_GetTicks()> ticks + (1/FPS)*1000){
            this->render();
            SDL_GL_SwapWindow(window);
        }
        if(this->mainLoopCallback != NULL){
            this->mainLoopCallback(this);
        }
    }


    //close sdl
    SDL_GL_DeleteContext(glCtx);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::render(){
    for(auto r:this->renderVector){
        r.render();
    }
}