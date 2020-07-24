#include "buffer.hpp"

Buffer::Buffer(){
    glGenBuffers( 1,&(this->buffer_));
}

Buffer::~Buffer(){
    if(this->deallocFunc_ != NULL){
        this->deallocFunc_(this->data_);
    }
    glDeleteBuffers(1,&(this->buffer_));
}

void Buffer::bind(){
    glBindBuffer(this->target_,this->buffer_);
}
void Buffer::unbind(){
    glBindBuffer(this->target_,0);
}

void Buffer::initData(){
    glBufferData(this->target_,this->size_,this->data_,this->usage_);
}

//TODO:check last parameter
void Buffer::bindToVertexAttr(){
    //Enable vertex position
    glEnableVertexAttribArray( this->location_ );

    //Set vertex data
    glBindBuffer( this->target_, this->buffer_ );
    glVertexAttribPointer( this->location_, this->frameSize_, this->type_, this->normailized_, this->stride_ * this->typeSize_, NULL );
}


//TODO:check last parameter
void Buffer::drawElements(){
    glDrawElements(this->mode_,this->frameSize_,this->type_,NULL);
}

GLuint Buffer::findLocation(Program &program,std::string attrName){
    return glGetAttribLocation(program.getProgram(),attrName.c_str());
}