#pragma once

class string;

void onRender();
void onReshape(int, int);
void onKeyPress(unsigned char, int, int);
void onKeyDown(unsigned char, int, int);
void onKeyUp(unsigned char, int, int);
void onMouseMove(int, int);
void onTimer(int);
void onButtonPress(int button, int button_state, int x, int y);
GLuint loadTexture(char* file, int magFilter, int minFilter);
GLuint LoadObj(std::string fileName);

struct vec3 {
    float x, y, z;
};

struct SFace {
    int v[3];
    int n[3];
    int t[3];
};

//struct Node{
//    Node(int posZ, int posX){
//        id_ = scene.map->getSize() * posZ + posX;
//        parent_ = NULL;
//        pos_[0] = posZ;
//        pos_[1] = posX;
//    }
//    Node(int posZ, int posX, Node* parent){
//        id_ = scene.map->getSize() * posZ + posX;
//        parent_ = parent;
//        pos_[0] = posZ;
//        pos_[1] = posX;
//        isOpen_ = true;
//    }
//
//    int id_;
//    bool isOpen_;
//    std::array < int, 2 > pos_;
//    int distFromStart_, distFromGoal_;
//    Node* parent_;
//
//    int getScore() { return distFromStart_ + distFromGoal_; }
//    int getDist(Node goal) { return (abs(goal.pos_[0] - pos_[0]) + abs(goal.pos_[1] + pos_[1])); }
//    Node& operator=(Node other);
//    bool operator==(Node other) { return pos_[0] == other.pos_[0] && pos_[1] == other.pos_[1]; }
//    
//};