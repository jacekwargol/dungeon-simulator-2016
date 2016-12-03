#include "stdafx.h"
#include "Map.h"


Map::Map(int size, std::string mapName)
    : size_(size),  mapName_(mapName){
    map_ = new char*[size_];
    for (int i = 0; i < size_; ++i){
        map_[i] = new char[size_];
    }
}

Map::~Map(){
    for (int i = 0; i < size_; ++i){
        delete[] map_[i];
    }
    delete[] map_;
}

void Map::load(){
    std::ifstream map(mapName_);

    std::string line;
    int i = 0;
    while (getline(map, line)){
        for (int j = 0; j < line.length(); ++j){
            if (line[j] == '#'){
                map_[i][j] = 'w';
            }
            else if(line[j] == '.' || line[j] == ' '){
                map_[i][j] = '.';
            }
            else{
                break;
            }
        }
        ++i;
    }
}

void Map::print(){
    for (int i = 0; i < size_; ++i){
        for (int j = 0; j < size_; ++j){
            if (map_[i][j] == ';'){
                break;
            }
            std::cout << map_[i][j];
        }
        std::cout << std::endl;
    }
}

void Map::rotate(std::string direction){
    char** tmpMatrix;
    tmpMatrix = new char*[size_];
    for (int i = 0; i < size_; ++i){
        tmpMatrix[i] = new char[size_];
    }
    for (int i = 0; i < size_; ++i){
        for (int j = 0; j < size_; ++j){
            tmpMatrix[i][j] = map_[i][j];
        }
    }

    if (direction == "left"){
        for (int i = 0; i < size_; ++i){
            for (int j = 0; j < size_; ++j){
                map_[i][j] = tmpMatrix[size_ - j - 1][i];
            }
        }
    }
    else if (direction == "right"){
        for (int i = 0; i < size_; ++i){
            for (int j = 0; j < size_; ++j){
                map_[i][j] = tmpMatrix[j][size_ - i - 1];
            }
        }
    }
}

bool Map::isValid(int posZ, int posX){
    return map_[posZ][posX] == '.';
}

bool Map::isValid(int posZ, int velZ, int posX, int velX){
    //int z = (velZ == 0 ? 0 : (int)velZ);
    //int x = (velX == 0 ? 0 : (int)velX);

    return map_[posZ + velZ][posX + velX] == '.';
}