#include "stdafx.h"
#include "Object.h"

char Object::getForwardSymbol(){
  switch (gridDir_){
    case 0:
        return scene.map->map_[gridPos_[0]][gridPos_[1] + 1];
        break;
    case 1:
        return scene.map->map_[gridPos_[0] + 1][gridPos_[1]];
        break;
    case 2:
        return scene.map->map_[gridPos_[0]][gridPos_[1] - 1];
        break;
    case 3:
        return scene.map->map_[gridPos_[0] - 1][gridPos_[1]];
    }
    return 'a';
}

int Object::getForwardX(){
    switch (gridDir_){
    case 0:
        return gridPos_[1] + 1;
        break;
    case 1:
        return gridPos_[1];
        break;
    case 2:
        return gridPos_[1] - 1;
        break;
    case 3:
        return gridPos_[1];
    }
}
int Object::getForwardZ(){
    switch (gridDir_){
    case 0:
        return gridPos_[0];
        break;
    case 1:
        return gridPos_[0] + 1;
        break;
    case 2:
        return gridPos_[0];
        break;
    case 3:
        return gridPos_[0] - 1;
    }
}