#include "stdafx.h"
#include "Player.h"


Player::Player(int gridPosX, int gridPosZ, int gridDir)
    : attackLenght_(60),
    blockLenght_(120),
    animLenght_(180) {

    gridPos_[0] = gridPosZ;
    gridPos_[1] = gridPosX;
    gridDir_ = gridDir;

    float x = gridPos_[1] * GRID + GRID / 2;
    float z = gridPos_[0] * GRID + GRID / 2;
    pos_.set(x, 1.0f, z);
    dir_.set(1.0f, 0.0f, 0.0f);

    weapon_ = new Weapon(1.0, "Hands");
    isAttacking_ = false;
    isBlocking_ = false;
    damage_ = weapon_->damage_;
    health_ = 10.0f;

    animationFrame_ = 0;
}


Player::~Player(){
    delete weapon_;
}

void Player::render(){
    glPushMatrix();
    glTranslatef(pos_.getX(), pos_.getY(), pos_.getZ());
    glTranslatef(0.0f, -0.06f, 0.0f);
    glScalef(0.08f, 0.08f, 0.08f);
    glCallList(animation_[animationFrame_]);
    glPopMatrix();
}

void Player::loadAnimation(){
    ObjectAnimated::loadAnimation(animation_, "Resources/Weapons/Hands/handsAttack", 60);
    ObjectAnimated::loadAnimation(animation_, "Resources/Weapons/Hands/handsBlock", 120);
}

void Player::attack(){
    isAttacking_ = true;
    if (getForwardSymbol() == 'e'){
        for (auto enemy : scene.enemies){
            if (enemy->gridPos_[0] == getForwardZ() &&
                enemy->gridPos_[1] == getForwardX()){
                enemy->takeDamage(damage_);
                if (enemy->isDead()){
                    enemy->changeIsAttacking();
                    enemy->animationFrame_ = enemy->attackLenght_;
                }
            }
        }
    }
}

void Player::interact(){
    if (getForwardSymbol() == 'c'){
        for (int i = 0; i < scene.chests.size(); ++i){
            if (scene.chests[i]->gridPos_[0] == scene.player->getForwardZ() &&
                scene.chests[i]->gridPos_[1] == scene.player->getForwardX()){
                scene.chests[i]->changeIsOpen();
            }
        }
    }
}