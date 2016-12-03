#pragma once

class Vector3;
class Scene; 

class Object{
public:
    int gridPos_[2];
    int gridDir_;
    Vector3 pos_;
    Vector3 dir_;
    char symbol_;

    virtual void render() = 0;
    virtual void initialize() = 0;
    char getForwardSymbol();
    int getForwardX();
    int getForwardZ();


};

