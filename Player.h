#pragma once

class Player : public Character{
private:
    class Weapon{
    public:
        Weapon(float damage, std::string type) : damage_(damage), type_(type) {}
        float damage_;
        std::string type_;
    };
public:

    Player(int gridPosX, int gridPosZ, int gridDir);
    ~Player();

    const int getAttackLenght() { return attackLenght_; }
    const int getBlockLenght() { return blockLenght_; }

    void loadAnimation();
    void render();
    virtual void initialize() {};
    
    void interact();
    void attack();
  
protected:
    const int animLenght_;
    const int attackLenght_, blockLenght_;
    Weapon* weapon_;
};

