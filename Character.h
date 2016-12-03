#pragma once

class Character : public ObjectAnimated{
public:
    void changeIsAttacking() { isAttacking_ = !isAttacking_; }
    void changeIsBlocking() { isBlocking_ = !isBlocking_; }
    bool getIsAttacking() { return isAttacking_; }
    bool getIsBlocking() { return isBlocking_; }
    float getHealth() { return health_; }
    float getDamage() { return damage_; }

    void setSpeed(float speed) { speed_ = speed; }
    void takeDamage(float damage) {
        if (isBlocking_){
            damage * 0.1;
        }
        health_ -= damage;
    }
    bool isDead() { return health_ <= 0.0; }

protected:
    float damage_, health_, speed_;

    bool isAttacking_;
    bool isBlocking_;
};

