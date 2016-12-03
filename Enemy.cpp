#include "stdafx.h"
#include "Enemy.h"

bool Enemy::isLoaded_ = false;
Texture* Enemy::texture_ = NULL;

Enemy::Enemy(int gridPosX, int gridPosZ, int gridDir, float velX, float velZ)
    : attackLenght_(150), blockLenght_(0), dyingLenght_(300), animLenght_(450),
    velX_(velX), velZ_(velZ) {
    gridPos_[0] = gridPosZ;
    gridPos_[1] = gridPosX;
    gridDir_ = gridDir;
    scene.map->map_[gridPosZ][gridPosX] = 'e';
    float x = gridPos_[1] * GRID + GRID / 2;
    float z = gridPos_[0] * GRID + GRID / 2;
    pos_.set(x, 1.0f, z);

    health_ = 5.0f;
    damage_ = 1.0f;

    animationFrame_ = 0;
    attackDelay_ = 0;
    moveDelay_ = 0;
}

Enemy::~Enemy(){}

void Enemy::initialize(){
    ObjectAnimated::loadAnimation(animation_, "Resources/Enemies/Andrzej/andrzejAttack", attackLenght_);
    ObjectAnimated::loadAnimation(animation_, "Resources/Enemies/Andrzej/andrzejDying", dyingLenght_);

    if (isLoaded_){
        return;
    }
    isLoaded_ = true;

    texture_ = new Texture("Resources/andrzej.bmp");
    texture_->load();
}

void Enemy::render(){
    glPushMatrix();
    float mAmb[] = { 0.545f, 0.49f, 0.4823f };
    float mSpe[] = { 0.5f, 0.5f, 0.4f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mAmb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mSpe);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_->getId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTranslatef(pos_.getX(), 0.0f, pos_.getZ());
    glRotatef(90.0 * (gridDir_ + 1), 0.0f, 1.0f, 0.0f);
    glScalef(0.11f, 0.11f, 0.11f);
    glCallList(animation_[animationFrame_]);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

bool Enemy::isPlayerForward(int dir){
    switch (dir){
    case 0:
        for (int i = 1; i < 50; ++i){
            if (scene.map->map_[gridPos_[0]][gridPos_[1] + i] == '@'){
                return true;
            }
            else if (scene.map->map_[gridPos_[0]][gridPos_[1] + i] == 'w'){
                return false;
            }
        }
    case 1:
        for (int i = 1; i < 50; ++i){
            if (scene.map->map_[gridPos_[0] - i][gridPos_[1]] == '@'){
                return true;
            }
            else if (scene.map->map_[gridPos_[0] - i][gridPos_[1]] == 'w'){
                return false;
            }
        }
    case 2:
        for (int i = 1; i < 50; ++i){
            if (scene.map->map_[gridPos_[0]][gridPos_[1] - i] == '@'){
                return true;
            }
            else if (scene.map->map_[gridPos_[0]][gridPos_[1] - i] == 'w'){
                return false;
            }
        }
    case 3:
        for (int i = 1; i < 50; ++i){
            if (scene.map->map_[gridPos_[0] + i][gridPos_[1]] == '@'){
                return true;
            }
            else if (scene.map->map_[gridPos_[0] + i][gridPos_[1]] == 'w'){
                return false;
            }
        }
    }
    return false;
}

bool Enemy::isNeighbour(){
    if (scene.map->map_[gridPos_[0]][gridPos_[1] - 1] == '@' ||
        scene.map->map_[gridPos_[0]][gridPos_[1] + 1] == '@' ||
        scene.map->map_[gridPos_[0] + 1][gridPos_[1]] == '@' ||
        scene.map->map_[gridPos_[0] - 1][gridPos_[1]] == '@'){

        return true;
    }
    return false;
}
void Enemy::move(Player *player){
    rotate();
    int dz = player->gridPos_[0] - gridPos_[0];
    int dx = player->gridPos_[1] - gridPos_[1];
    switch (gridDir_){
    case 0:
        if (dz != 0){
            dz /= abs(dz);
            if (scene.map->isValid(gridPos_[0] + dz, gridPos_[1])){
                scene.map->map_[gridPos_[0]][gridPos_[1]] = '.';
                gridPos_[0] += dz;
                pos_.setZ(pos_.getZ() + dz * GRID);
                scene.map->map_[gridPos_[0]][gridPos_[1]] = 'e';
            }
        }
        else{
            dx /= abs(dx);
            if (scene.map->isValid(gridPos_[0], gridPos_[1] + dx)){
                scene.map->map_[gridPos_[0]][gridPos_[1]] = '.';
                gridPos_[1] += dx;
                pos_.setX(pos_.getX() + dx * GRID);
                scene.map->map_[gridPos_[0]][gridPos_[1]] = 'e';
            }
        }
        break;
    case 1:
        if (dx != 0){
            dx /= abs(dx);
            if (scene.map->isValid(gridPos_[0], gridPos_[1] + dx)){
                scene.map->map_[gridPos_[0]][gridPos_[1]] = '.';
                gridPos_[1] += dx;
                pos_.setX(pos_.getX() + dx * GRID);
                scene.map->map_[gridPos_[0]][gridPos_[1]] = 'e';
            }
        }
        else{
            dz /= abs(dz);
            if (scene.map->isValid(gridPos_[0] + dz, gridPos_[1])){
                scene.map->map_[gridPos_[0]][gridPos_[1]] = '.';
                gridPos_[0] += dz;
                pos_.setZ(pos_.getZ() + dz * GRID);
                scene.map->map_[gridPos_[0]][gridPos_[1]] = 'e';
            }
        }
        break;
    case 2:
        if (dz != 0){
            dz /= abs(dz);
            if (scene.map->isValid(gridPos_[0] + dz, gridPos_[1])){
                scene.map->map_[gridPos_[0]][gridPos_[1]] = '.';
                gridPos_[0] += dz;
                pos_.setZ(pos_.getZ() + dz * GRID);
                scene.map->map_[gridPos_[0]][gridPos_[1]] = 'e';
            }
        }
        else{
            dx /= abs(dx);
            if (scene.map->isValid(gridPos_[0], gridPos_[1] + dx)){
                scene.map->map_[gridPos_[0]][gridPos_[1]] = '.';
                gridPos_[1] += dx;
                pos_.setX(pos_.getX() + dx * GRID);
                scene.map->map_[gridPos_[0]][gridPos_[1]] = 'e';
            }
        }
        break;
    case 3:
        if (dx != 0){
            dx /= abs(dx);
            if (scene.map->isValid(gridPos_[0], gridPos_[1] + dx)){
                scene.map->map_[gridPos_[0]][gridPos_[1]] = '.';
                gridPos_[1] += dx;
                pos_.setX(pos_.getX() + dx * GRID);
                scene.map->map_[gridPos_[0]][gridPos_[1]] = 'e';
            }
        }
        else{
            dz /= abs(dz);
            if (scene.map->isValid(gridPos_[0] + dz, gridPos_[1])){
                scene.map->map_[gridPos_[0]][gridPos_[1]] = '.';
                gridPos_[0] += dz;
                pos_.setZ(pos_.getZ() + dz * GRID);
                scene.map->map_[gridPos_[0]][gridPos_[1]] = 'e';
            }
        }
    }
}
void Enemy::rotate(){
    for (int i = 0; i < 4; ++i){
        if (isPlayerForward(i)){
            gridDir_ = i;
            return;
        }
    }
}

void Enemy::attack(){
    if (attackDelay_ == 0){
        isAttacking_ = true;
    }
}
