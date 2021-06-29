//
// Created by shenshen on 6/28/21.
//

#ifndef UNTITLED_FIREWORKSFRACTORY_H
#define UNTITLED_FIREWORKSFRACTORY_H

#include "vector"
#include "ShootFlower.h"
#include "cv.hpp"
#define WND_WIDTH  800
#define WND_HEIGHT 800


class FireworksFractory {
public:
    std::vector<Shoot> shoots;
    std::vector<Flower> flowers;
    cv::Mat *pMem;
    cv::Mat *pMem_ori;
    std::chrono::high_resolution_clock::time_point last_shoot_generate_time;

    FireworksFractory();
    ~FireworksFractory();

    int getCurrentState(std::chrono::high_resolution_clock::time_point &t1);
    int generateCurrentImage();

private:
    cv::Mat shoot_m;
    cv::Mat flower_m;
    const int total_fire_shoot_num = 5;
};


#endif //UNTITLED_FIREWORKSFRACTORY_H
