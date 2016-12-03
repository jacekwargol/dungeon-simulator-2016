#pragma once

class Wall;

class WallCube : public Object{
public:
    WallCube() = default;
    WallCube(float gridPosX, float gridPosZ) { gridPos_[0] = gridPosZ; gridPos_[1] = gridPosX; }
    ~WallCube();

    void initialize();
    void render();

    int getGridX() { return gridPos_[1]; }
    int getGridZ() { return gridPos_[0]; }

private:
    float gridPos_[2];
    Wall* front, *left, *back, *right;
};