#pragma once

class Texture{
public:
    Texture(char* fileName);
    ~Texture();

    bool load();
    GLuint getId();

private:
    bool isLoaded_;
    int magFilter_, minFilter_;
    char* fileName_;
    GLuint id_;
};

