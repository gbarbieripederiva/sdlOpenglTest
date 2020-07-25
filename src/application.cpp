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


    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_ES );
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
    #ifdef __APPLICATION_DEBUG__
        std::cout << "opengl version:" << glGetString(GL_VERSION) << std::endl;
        //code from https://www.khronos.org/opengl/wiki/OpenGL_Error
        glEnable              ( GL_DEBUG_OUTPUT );
        glDebugMessageCallback(
            []( GLenum source,
                        GLenum type,
                        GLuint id,
                        GLenum severity,
                        GLsizei length,
                        const GLchar* message,
                        const void* userParam )
        {
        fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
                    type, severity, message );
        }, 0 );
    #endif
    
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
            glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            this->render();
            SDL_GL_SwapWindow(window);
            ticks = SDL_GetTicks();
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
        r->render();
    }
}