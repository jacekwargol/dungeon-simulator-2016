#include "stdafx.h"
#include "ObjectAnimated.h"

void ObjectAnimated::loadAnimation(std::vector<GLuint>& frames, std::string name, int nFrames){
    for (int i = 0; i < nFrames; ++i){
        std::string s;
        s = std::string(6 - std::to_string(i).length(), '0') + std::to_string(i);
        s = name + "_" + s + ".obj";
        frames.push_back(LoadObj(s));
    }
}

//void loadAnimation(std::vector<std::string>& frames, int firstFrame, std::string name, int nFrames){
//    for (int i = 0; i < nFrames; ++i){
//        std::string s;
//        s = std::string(6 - std::to_string(i).length(), '0') + std::to_string(i);
//        s = name + "_" + s + ".obj";
//        frames.push_back(s);
//    }
//}