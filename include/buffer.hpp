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

    void bind();
    void unbind();

    /*  requires buffer be bound, target, size, data, usage */
    void initData();

    /*  
        requires buffer be bound and data inited, 
        target, buffer,location, frameSize, type, normailized,stride,typeSize 
    */
    void bindToVertexAttr();
    /*  
        requires buffer be bound and data inited, 
        mode,frameSize,type
    */
    void drawElements();

    /* requires location */
    void enableVertexAttr();


    //GETTERS-----------------------------------------------------------
    GLuint location() { return this->location_; };
    GLuint buffer() { return this->buffer_; };
    GLenum target() { return this->target_; };
    GLsizeiptr size() { return this->size_; };
    void *data() { return this->data_; };
    GLenum usage() { return this->usage_; };
    GLenum type() { return this->type_; };
    GLsizei typeSize() { return this->typeSize_; };
    GLsizei stride() { return this->stride_; };
    GLboolean normailized() { return this->normailized_; };
    GLint frameSize() { return this->frameSize_; };
    GLenum mode(){return this->mode_;};
    DeallocFunc deallocFunc(){return this->deallocFunc_;};
    bool shouldBeDeallocated(){return this->shouldBeDeallocated_;};
    
    //UTILITY------------------------------------------------------------
    /* requires program be bound */
    static GLuint findLocation(Program &program, std::string attrName);

    //SETTERS------------------------------------------------------------
    void location(GLuint location) { this->location_ = location; };
    void target(GLenum target) { this->target_ = target; };
    void size(GLsizeiptr size) { this->size_ = size; };
    void data(void *data) { this->data_ = data; };
    void usage(GLenum usage) { this->usage_ = usage; };
    void type(GLenum type) { this->type_ = type; };
    void typeSize(long typeSize) { this->typeSize_ = typeSize; };
    void stride(GLsizei stride) { this->stride_ = stride; };
    void normailized(GLboolean normailized) { this->normailized_ = normailized; };
    void frameSize(GLint frameSize) { this->frameSize_ = frameSize; };
    void mode(GLenum mode){this->mode_ = mode;};
    void deallocFunc(DeallocFunc deallocFunc){this->deallocFunc_ = deallocFunc;};
    void shouldBeDeallocated(bool shouldBeDeallocated){this->shouldBeDeallocated_ = shouldBeDeallocated;};
};

#endif