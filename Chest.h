#pragma once

class Object;

class Chest : public Object{
public:
    Chest(int gridPosZ, int gridPosX, int gridDir);
    ~Chest();

    void changeIsOpen() { isOpen_ = !isOpen_; }

    void add(int gridPosZ, int gridPosX);
    void initialize();
    void render();

private:
    float angle_;
    float animSpeed_;
    bool isOpen_;
    GLuint displayListId_[2];
};