#include "program.hpp"

Program::Program(std::string vshaderSource, std::string fshaderSource){
        if(this->program != 0){
        glDeleteProgram(this->program);
        this->program = 0;
    }

    this->program = glCreateProgram();

    //Create vertex shader
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    //Set vertex source
    const char *vshaderSourcecstr = vshaderSource.c_str();
    glShaderSource(vshader, 1, &vshaderSourcecstr, NULL);
    //Compile vertex source
    glCompileShader(vshader);

    //Check vertex shader for errors
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &vShaderCompiled);
    if (vShaderCompiled != GL_TRUE)
    {
        //TODO: output compile error
        printf("Unable to compile vertex shader %d!\n", vshader);
        this->printShaderLog(vshader);
        glDeleteShader(vshader);
        return;
    }
    //Attach vertex shader to program
    glAttachShader(this->program, vshader);

    //Create fragment shader
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

    //Set fragment source
    const char *fShaderSourcecstr = fshaderSource.c_str();
    glShaderSource(fshader, 1, &fShaderSourcecstr, NULL);

    //Compile fragment source
    glCompileShader(fshader);

    //Check fragment shader for errors
    GLint fShaderCompiled = GL_FALSE;
    glGetShaderiv(fshader, GL_COMPILE_STATUS, &fShaderCompiled);
    if (fShaderCompiled != GL_TRUE)
    {
        //TODO: output compile error
        printf("Unable to compile fragment shader %d!\n", fshader);
        this->printShaderLog(fshader);
        glDeleteShader(vshader);
        glDeleteShader(fshader);
        return;
    }

    //Attach fragment shader to program
    glAttachShader(this->program, fshader);

    //Link program
    glLinkProgram(this->program);

    //Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(this->program, GL_LINK_STATUS, &programSuccess);

    if (programSuccess != GL_TRUE)
    {
        //TODO: output link error
        printf("Error linking program %d!\n", this->program);
        this->printProgramLog(this->program);
        glDeleteShader(vshader);
        glDeleteShader(fshader);
        glDeleteProgram(this->program);
        this->program = 0;
        return;
    }

    glDeleteShader(vshader);
    glDeleteShader(fshader);
}

Program::~Program(){
    glDeleteProgram(this->program);
}

void Program::printShaderLog( GLuint shader )
{
    //Make sure name is shader
    if( glIsShader( shader ) )
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

        //Allocate string
        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a shader\n", shader );
    }
}


void Program::printProgramLog( GLuint program )
{
    //Make sure name is shader
    if( glIsProgram( program ) )
    {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

        //Allocate string
        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a program\n", program );
    }
}

void Program::bind(){
    glUseProgram(this->program);
}

void Program::unbind(){
    glUseProgram(0);
}

GLuint Program::getProgram(){
    return this->program;
}

GLuint Program::getAttributeLocation(std::string attrName){
    return glGetAttribLocation(this->program,attrName.c_str());
}