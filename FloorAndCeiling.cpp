#include "stdafx.h"
#include "FloorAndCeiling.h"


void FloorAndCeiling::render(){
    floor->render();
    ceiling->render();
}

void FloorAndCeiling::initialize(){
    Vector3 F0(gridPos_[1] - GRID / 2, 0.0f, gridPos_[0] - GRID / 2);
    Vector3 F1(gridPos_[1] - GRID / 2, 0.0f, gridPos_[0] + GRID / 2);
    Vector3 F2(gridPos_[1] + GRID / 2, 0.0f, gridPos_[0] + GRID / 2);
    Vector3 F3(gridPos_[1] + GRID / 2, 0.0f, gridPos_[0] - GRID / 2);
    floor = new Wall(F0, F1, F2, F3);
    floor->initialize();


    Vector3 C0(gridPos_[1] - GRID / 2, 2.0f, gridPos_[0] - GRID / 2);
    Vector3 C1(gridPos_[1] + GRID / 2, 2.0f, gridPos_[0] - GRID / 2);
    Vector3 C2(gridPos_[1] + GRID / 2, 2.0f, gridPos_[0] + GRID / 2);
    Vector3 C3(gridPos_[1] - GRID / 2, 2.0f, gridPos_[0] + GRID / 2);
    ceiling = new Wall(C0, C1, C2, C3);
    ceiling->initialize();
}
