#pragma once

class Texture; 

class Enemy : public Character{
    friend class Player;

public:
    int velX_, velZ_;
    int attackDelay_;
    int moveDelay_;
    Vector3 vertices_[4];
    Vector3 normal_;
    std::vector<std::array<int, 2>> path_;
    Enemy(int gridPosX, int gridPosZ, int gridDir, float velZ, float velX);
    ~Enemy();

    const int getAnimLenght() { return animLenght_; }
    const int getAttackLenght() { return attackLenght_; }
    const int getBlockLenght() { return blockLenght_; }

    //void loadAnimation();
    void initialize();
    void render();

    bool isPlayerForward(int dir);
    bool isNeighbour();
    void move(Player *player);
    void rotate();
    void attack();

private:
    GLuint displayListId_;
    static bool isLoaded_;
    static Texture* texture_;
    const int animLenght_;
    const int attackLenght_, blockLenght_, dyingLenght_;
};

