#pragma once

class Wall;

class FloorAndCeiling : public Object{
public:
    FloorAndCeiling() = default;
    FloorAndCeiling(float gridPosX, float gridPosZ) { gridPos_[0] = gridPosZ; gridPos_[1] = gridPosX; }
    ~FloorAndCeiling() {}

    void initialize();
    void render();

    int getGridX() { return gridPos_[1]; }
    int getGridZ() { return gridPos_[0]; }
private:
    float gridPos_[2];
    Wall* floor, *ceiling;
};

