#include "stdafx.h"
#include "WallCube.h"


WallCube::~WallCube(){
}

void WallCube::render(){
    front->render();
    left->render();
    back->render();
    right->render();
}

void WallCube::initialize(){

    Vector3 vF0(gridPos_[1] - GRID / 2, 2.0, gridPos_[0] + GRID / 2);
    Vector3 vF1(gridPos_[1] - GRID / 2, 0.0, gridPos_[0] + GRID / 2);
    Vector3 vF2(gridPos_[1] + GRID / 2, 0.0, gridPos_[0] + GRID / 2);
    Vector3 vF3(gridPos_[1] + GRID / 2, 2.0, gridPos_[0] + GRID / 2);
    front = new Wall(vF0, vF1, vF2, vF3);
    front->initialize();

    Vector3 vR0(gridPos_[1] + GRID / 2, 2.0, gridPos_[0] + GRID / 2);
    Vector3 vR1(gridPos_[1] + GRID / 2, 0.0, gridPos_[0] + GRID / 2);
    Vector3 vR2(gridPos_[1] + GRID / 2, 0.0, gridPos_[0] - GRID / 2);
    Vector3 vR3(gridPos_[1] + GRID / 2, 2.0, gridPos_[0] - GRID / 2);
    right = new Wall(vR0, vR1, vR2, vR3);
    right->initialize();

    Vector3 vB0(gridPos_[1] - GRID / 2, 2.0, gridPos_[0] - GRID / 2);
    Vector3 vB1(gridPos_[1] + GRID / 2, 2.0, gridPos_[0] - GRID / 2);
    Vector3 vB2(gridPos_[1] + GRID / 2, 0.0, gridPos_[0] - GRID / 2);
    Vector3 vB3(gridPos_[1] - GRID / 2, 0.0, gridPos_[0] - GRID / 2);
    back = new Wall(vB0, vB1, vB2, vB3);
    back->initialize();

    Vector3 vL0(gridPos_[1] - GRID / 2, 2.0, gridPos_[0] - GRID / 2);
    Vector3 vL1(gridPos_[1] - GRID / 2, 0.0, gridPos_[0] - GRID / 2);
    Vector3 vL2(gridPos_[1] - GRID / 2, 0.0, gridPos_[0] + GRID / 2);
    Vector3 vL3(gridPos_[1] - GRID / 2, 2.0, gridPos_[0] + GRID / 2);
    left = new Wall(vL0, vL1, vL2, vL3);
    left->initialize();
}