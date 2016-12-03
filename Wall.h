#pragma once

class Texture;

class Wall : public Object{
public:
    Wall();
    Wall(Vector3 a, Vector3 b, Vector3 c, Vector3 d);
    Wall(Vector3 a, Vector3 b, Vector3 c, Vector3 d, char *textureName);
    ~Wall();

    void initialize();
    void render();

    Vector3 vertices_[4];
    Vector3 normal_;

private:
    GLuint displayListId_;
    static bool isLoaded_;
    static Texture* wallTexture_;
};

