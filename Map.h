#pragma once

class Map{
public:
    char** map_;

    Map(int size, std::string mapName);
    ~Map();

    void load();
    void print();
    void rotate(std::string direction);

    bool isValid(int posZ, int posX);
    bool isValid(int posZ, int velZ, int posX, int velX);

    int getSize() { return size_; }

    char operator()(int i, int j) { return map_[i][j]; }
private:
    int size_;
    std::string mapName_;
};

