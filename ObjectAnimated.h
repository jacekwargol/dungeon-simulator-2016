#pragma once

class Object;

class ObjectAnimated : public Object{
public:
    void loadAnimation(std::vector<GLuint>& frames, std::string name, int nFrames);
    std::vector<GLuint> animation_;
    int animationFrame_;
};

