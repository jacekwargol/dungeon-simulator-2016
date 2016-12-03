//#pragma once
//
//class AStar{
//public:
//    AStar();
//    ~AStar();
//
//    std::vector<std::array<int, 2>> findPath(int startZ, int startX, int goalZ, int goalX);
//
//private:  
//    struct Node{
//        Node(int posZ, int posX){
//            parent_ = NULL;
//            pos_[0] = posZ;
//            pos_[1] = posX;
//        }
//        Node(int posZ, int posX, Node* parent){
//            parent_ = parent;
//            pos_[0] = posZ;
//            pos_[1] = posX;
//            isOpen_ = true;
//        }
//
//        bool isOpen_;
//        std::array < int, 2 > pos_;
//        int distFromStart_, distFromGoal_;
//        int score_;
//        Node* parent_;
//
//        void updateScore() { score_ = distFromStart_ + distFromGoal_; }
//        void updateDist(int goalZ, int goalX) { distFromGoal_ = (abs(goalZ - pos_[0]) + abs(goalX + pos_[1])); }
//        int getDist(Node goal) { return (abs(goal.pos_[0] - pos_[0]) + abs(goal.pos_[1] + pos_[1])); }
//        Node& operator=(Node other);
//        bool operator==(Node other) { return pos_[0] == other.pos_[0] && pos_[1] == other.pos_[1]; }
//
//    };
//
//    std::vector<Node*> openedList_;
//    std::vector<Node*> closedList_;
//
//    /*std::vector<std::array<int, 2>> path_;
//
//    void findPath(int startPosZ, int startPosX, int goalPosZ, int goalPosX);
//    std::array<int, 2> nextPathPos();
//    void clearOpenList() { openList_.clear(); }
//    void clearClosedList() { closedList_.clear(); }
//    void clearPath() { path_.clear(); }
//
//private:
//    void setStartAndGoal(Node start, Node goal);
//    Node* getNextNode();
//    void continuePath();
//    void pathOpened(int z, int x, int newCost, Node* parent);
//
//    Node* start_;
//    Node* goal_;
//    std::vector<Node*> openList_;
//    std::vector<Node*> closedList_;
//    bool isInitialized_;
//    bool isGoalFound_;
//    */
//};
//
