#pragma once

class Map;
class Player;
class Enemy;
class Wall;
class WallCube;
class Chest;
class FloorAndCeiling;

class Scene{
    friend class Object;
public:
    Map* map;
    Player* player;
    std::vector<Object*> environment;
    std::vector<Enemy*> enemies;
    //std::vector<WallCube*>* walls;
    //std::vector<FloorAndCeiling*>* floorAndCeiling;
    std::vector<Chest*> chests;

    Scene();
    ~Scene();

    void addChest(int gridPosZ, int gridPosX, int gridDir);
    void initialize();
    void Scene::initializeChests();
};

extern Scene scene;