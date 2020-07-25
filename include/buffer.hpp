#ifndef __BUFFER__
#define __BUFFER__
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <iostream>

#include "program.hpp"

typedef void (*DeallocFunc)(void *);

class Buffer
{
private:
    GLuint location_;
    GLuint buffer_;
    GLenum target_;
    GLsizeiptr size_;
    void *data_ = NULL;
    GLenum usage_;
    GLsizei typeSize_;
    GLenum type_;
    GLboolean normailized_ = GL_FALSE;
    GLsizei stride_;
    GLint frameSize_;
    GLenum mode_;

    DeallocFunc deallocFunc_ = NULL;
    bool shouldBeDeallocated_ = false;
public:
    Buffer();
    ~Buffer();

    ///requires target
    void bind();
    ///requires target
    void unbind();

    /**  requires buffer be bound, target, size, data, usage */
    void initData();

    /**  
    *   requires buffer be bound and data inited, 
    *   target, buffer,location, frameSize, type, normailized,stride,typeSize 
    */
    void bindToVertexAttr();
    /**  
    *   requires buffer be bound and data inited, 
    *   mode,frameSize,type
    */
    void drawElements();

    /** requires location */
    void enableVertexAttr();


    //GETTERS-----------------------------------------------------------
    
    ///can be obtained with findlocation
    GLuint location() { return this->location_; };
    ///is setted when buffer is created and destroy when buffer is deleted
    GLuint buffer() { return this->buffer_; };
    /// target example: GL_ARRAY_BUFFER
    GLenum target() { return this->target_; };
    ///size of the data
    GLsizeiptr size() { return this->size_; };
    /// the data pointer
    void *data() { return this->data_; };
    /// usage example: GL_STATIC_DRAW
    GLenum usage() { return this->usage_; };
    /// the type of data example GL_FLOAT
    GLenum type() { return this->type_; };
    /// the size of the type
    GLsizei typeSize() { return this->typeSize_; };
    /*** 
     * the space between one value and the other. 
     * example:if its one after the other it seems
     * to be framesize * typesize
    */
    GLsizei stride() { return this->stride_; };
    /// dont really no what this is, default is false
    GLboolean normailized() { return this->normailized_; };
    /// the size of one unit. example: in a 2d point its 2
    GLint frameSize() { return this->frameSize_; };
    /// the draw elements mode example:GL_TRIANGLE_FAN
    GLenum mode(){return this->mode_;};
    /*** 
     * the functions used for deallocating the data
     * if null, data is not deallocated. default is null
    */
    DeallocFunc deallocFunc(){return this->deallocFunc_;};
    /**
     * this is used for the renderer to know if this buffer
     * should be deallocated after finishing or the caller
     * deallocates it himself
    */
    bool shouldBeDeallocated(){return this->shouldBeDeallocated_;};
    
    //UTILITY------------------------------------------------------------
    
    /// requires program be bound
    static GLuint findLocation(Program &program, std::string attrName);

    //SETTERS------------------------------------------------------------
    ///can be obtained with findlocation
    void location(GLuint location) { this->location_ = location; };
    /// target example: GL_ARRAY_BUFFER
    void target(GLenum target) { this->target_ = target; };
    ///size of the data
    void size(GLsizeiptr size) { this->size_ = size; };
    /// the data pointer
    void data(void *data) { this->data_ = data; };
    /// usage example: GL_STATIC_DRAW
    void usage(GLenum usage) { this->usage_ = usage; };
    /// the type of data example GL_FLOAT
    void type(GLenum type) { this->type_ = type; };
    /// the size of the type
    void typeSize(long typeSize) { this->typeSize_ = typeSize; };
    /*** 
     * the space between one value and the other. 
     * example:if its one after the other it seems
     * to be framesize * typesize
    */
    void stride(GLsizei stride) { this->stride_ = stride; };
    /// dont really no what this is, default is false
    void normailized(GLboolean normailized) { this->normailized_ = normailized; };
    /// the size of one unit. example: in a 2d point its 2
    void frameSize(GLint frameSize) { this->frameSize_ = frameSize; };
    /// the draw elements mode example:GL_TRIANGLE_FAN
    void mode(GLenum mode){this->mode_ = mode;};
    /*** 
     * the functions used for deallocating the data
     * if null, data is not deallocated. default is null
    */
    void deallocFunc(DeallocFunc deallocFunc){this->deallocFunc_ = deallocFunc;};
    /**
     * this is used for the renderer to know if this buffer
     * should be deallocated after finishing or the caller
     * deallocates it himself
    */
    void shouldBeDeallocated(bool shouldBeDeallocated){this->shouldBeDeallocated_ = shouldBeDeallocated;};
};

#endif