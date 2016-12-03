#include "stdafx.h"
//#include "AStar.h"
//
//std::vector<std::array<int, 2>> AStar::findPath(int startZ, int startX, int goalZ, int goalX){
//    std::priority_queue<Node> nodes;
//    Node* current;
//    Node* neighbour;
//    Node* start = new Node(startZ, startX);
//    start->distFromStart_ = 0;
//    start->updateDist(goalZ, goalX);
//    start->updateScore();
//
//    nodes.push(*start);
//    openedList_.push_back(start);
//
//    while (!nodes.empty()){
//        current = &nodes.top();
//        nodes.pop();
//        for (int i = 0; i < openedList_.size(); ++i){
//            if (current == openedList_[i]){
//                openedList_.erase(openedList_.begin() + i);
//                break;
//            }
//        }
//        closedList_.push_back(current);
//    }
//}
//
//AStar::Node& AStar::Node::operator=(Node other){
//    parent_ = other.parent_;
//    pos_ = other.pos_;
//    isOpen_ = other.isOpen_;
//    distFromGoal_ = other.distFromGoal_;
//    distFromStart_ = other.distFromStart_;
//
//    return *this;
//}
//
////AStar::AStar(){
////    isInitialized_ = false;
////    isGoalFound_ = false;
////}
////
////
////AStar::~AStar(){}
////
////void AStar::findPath(int startPosZ, int startPosX, int goalPosZ, int goalPosX){
////    if (!isInitialized_){
////        for (auto node : openList_){
////            delete node;
////        }
////        openList_.clear();
////        for (auto node : closedList_){
////            delete node;
////        }
////        closedList_.clear();
////        path_.clear();
////
////        Node start(startPosZ, startPosX);
////        Node goal(goalPosZ, goalPosX);
////
////        isInitialized_ = true;
////        setStartAndGoal(start, goal);
////    }
////
////    continuePath();
////}
////
////void AStar::setStartAndGoal(Node start, Node goal){
////    start_ = new Node(start.pos_[0], start.pos_[1]);
////    goal_ = new Node(goal.pos_[0], goal.pos_[1]);
////
////    start_->distFromStart_ = 0;
////    start_->distFromGoal_ = start_->getDist(goal);
////
////    openList_.push_back(start_);
////}
////
////Node* AStar::getNextNode(){
////    int bestScore = start_->getDist(*goal_);
////    Node* nextNode = NULL;
////    int nodeId = -1;
////
////    int i = 0;
////    for (auto node : openList_){
////        if (node->getScore() < bestScore){
////            bestScore = node->getScore();
////            nodeId = i;
////        }
////        ++i;
////    }
////    if (nodeId > -1){
////        nextNode = openList_[nodeId];
////        closedList_.push_back(nextNode);
////        openList_.erase(openList_.begin() + nodeId);
////    }
////
////    return nextNode;
////}
////
////void AStar::pathOpened(int z, int x, int newCost, Node* parent){
////    Node* newChild = new Node(z, x, parent);
////    
////    for (auto node : closedList_){
////        if (newChild == node){
////            delete newChild;
////            return;
////        }
////    }
////
////    newChild->distFromStart_ = newCost;
////    newChild->distFromGoal_ = parent->getDist(*goal_);
////
////    for (auto node : openList_){
////        int newScore = newChild->distFromStart_ + newCost + node->distFromGoal_;
////
////        if (node->getScore() > newScore){
////            node->distFromStart_ = newChild->distFromStart_ + newCost;
////            node->parent_ = newChild;
////        }
////
////        else{
////            delete newChild;
////            return;
////        }
////    }
////
////    openList_.push_back(newChild);
////}
////
////void AStar::continuePath(){
////    if (openList_.empty()){
////        return;
////    }
////
////    std::priority_queue<Node> nodes[2];
////    static int index;
////    static Node* current; // = getNextNode();
////    static Node* neighbourNode;
////
////    static Node* start;
////    start = new Node()
////    if (current->id_ == goal_->id_){
////        goal_->parent_ = current->parent_;
////        Node* getPath;
////
////        for (getPath = goal_; getPath != NULL; getPath = getPath->parent_){
////            path_.push_back({ { getPath->pos_[0], getPath->pos_[1] } });
////        }
////
////        isGoalFound_ = true;
////        return;
////    }
////    else{
////        // Test left node
////        pathOpened(current->pos_[0] - 1, current->pos_[1], current->distFromStart_ + 1, current);
////        // Test right node
////        pathOpened(current->pos_[0] + 1, current->pos_[1], current->distFromStart_ + 1, current);
////        // Test forward node
////        pathOpened(current->pos_[0], current->pos_[1] - 1, current->distFromStart_ + 1, current);
////        // Test back node
////        pathOpened(current->pos_[0], current->pos_[1] + 1, current->distFromStart_ + 1, current);
////
////        for (int i = 0; i < openList_.size(); ++i){
////            if (current->id_ == openList_[i]->id_){
////                openList_.erase(openList_.begin() + i);
////            }
////        }
////    }
////}
////
////std::array<int, 2> AStar::nextPathPos(){
////    int i = 1;
////    std::array<int, 2> nextPos;
////    nextPos = path_[path_.size() - i];
////
////    //std::array<int, 2> dist = nextPos - pos_;
////
////    return nextPos;
////}
//
