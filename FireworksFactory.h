//
// Created by shenshen on 6/28/21.
//

#ifndef UNTITLED_FireworksFactory_H
#define UNTITLED_FireworksFactory_H

#include "vector"
#include "ShootFlower.h"
#include "opencv4/opencv2/opencv.hpp"
#include "thread"
#include "array"
#define WND_WIDTH  1900
#define WND_HEIGHT 1000


class FireworksFactory {
public:
    std::vector<Shoot> shoots;
    std::vector<Flower> flowers;
    cv::Mat *pMem;
    cv::Mat *pMem_ori;
    int state = 0;
    std::chrono::high_resolution_clock::time_point last_shoot_generate_time;

    FireworksFactory();
    ~FireworksFactory();

    int getCurrentState(std::chrono::high_resolution_clock::time_point &t1);
    int generateCurrentImage();
    int generateCurrentColor(std::vector<int>& curr_color);


private:
    cv::Mat shoot_m;
    cv::Mat flower_m;
    const int total_fire_shoot_num = 13;
};


#endif //UNTITLED_FireworksFactory_H
