#include "stdafx.h"
#include "Texture.h"

Texture::Texture(char* fileName){
    isLoaded_ = false;
    fileName_ = fileName;
    magFilter_ = GL_LINEAR;
    minFilter_ = GL_LINEAR;
}


Texture::~Texture(){
}

bool Texture::load(){
    Bitmap* tex = new Bitmap();
    if (!tex->loadBMP(fileName_)){
        std::cout << " ERROR: Cannot read texture file " << fileName_ << std::endl;
        return false;
    }

    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter_);

    if (minFilter_ == GL_LINEAR_MIPMAP_LINEAR || minFilter_ == GL_LINEAR_MIPMAP_NEAREST){
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex->width, tex->height, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
    }
    else{
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
    }

    delete tex;

    isLoaded_ = true;

    return true;
}

GLuint Texture::getId(){
    if (!isLoaded_){
        load();
    }
    return id_;
}