#include "stdafx.h"
#include "Scene.h"


Scene::Scene(){
}


Scene::~Scene(){
    if (map){
        delete map;
    }
    if (player){
        delete player;
    }
    if (enemies.size() > 0){
        for (int i = 0; i < enemies.size(); ++i){
            delete enemies[i];
        }
        enemies.clear();
    }
    if (environment.size() > 0){
        for (int i = 0; i < chests.size(); ++i){
            delete environment[i];
        }
        environment.clear();
    }
    if (chests.size() > 0){
        for (int i = 0; i < chests.size(); ++i){
            delete chests[i];
        }
        chests.clear();
    }
}

void Scene::addChest(int gridPosZ, int gridPosX, int gridDir){
    map->map_[gridPosZ][gridPosX] = 'c';
    chests.push_back(new Chest(gridPosZ, gridPosX, gridDir));
}

void Scene::initialize(){
    map = new Map(256, "Maps/dun1.txt");
    map->load();
    // =  new std::vector<Object*>();
    //floorAndCeiling = new std::vector<FloorAndCeiling*>();

#pragma region Walls
    float x = GRID / 2, z = GRID / 2;

    for (int i = 0; i < map->getSize(); ++i){
        for (int j = 0; j < map->getSize(); ++j){
            if ((*map)(i, j) == 'w'){
                WallCube* wall = new WallCube(x, z);
                wall->initialize();
                environment.push_back(wall);

                x += GRID;
            }
            else if ((*map)(i, j) == '.'){
                FloorAndCeiling* fac = new FloorAndCeiling(x, z);
                fac->initialize();
               environment.push_back(fac);
                x += GRID;              
            }
            else{
                x = GRID / 2;
                z += GRID;
                break;
            }
        }
    }
#pragma endregion

    player = new Player(1, 1, 0);
    map->map_[1][1] = '@';
}

void Scene::initializeChests(){
    for (int i = 0; i < chests.size(); ++i){
        chests[i]->initialize();
    }
}