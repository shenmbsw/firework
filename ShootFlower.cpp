//
// Created by shenshen on 6/28/21.
//

#include "ShootFlower.h"
#include "random"

int Shoot::resetShoot(int max_height_, int x_, int y_, int state){
    this->x = x_;
    this->y = y_;
    this->max_height = max_height_;
    this->t_start = std::chrono::high_resolution_clock::now();
    this->t_now = std::chrono::high_resolution_clock::now();
    this->dt = std::chrono::milliseconds(5);
    if(state >= 5){
        this->shoot_color = (int)random() % 5;
    } else {
        this->shoot_color = state;
    }
    this->show = true;
    return 1;
}

int Shoot::get_show_x() const{
    return this->x - ONE_SHOOT_WID / 2;
}

int Shoot::get_show_y() const{
    return this->y - ONE_SHOOT_HIG / 2;
}

Flower::Flower(int max_r_, int center_x_, int center_y_) {
    this->cent_x = center_x_;
    this->cent_y = center_y_;
    this->max_r = max_r_;
    this->dt = std::chrono::milliseconds(5);
}

int Flower::resetFlower(int x_, int y_) {
    this->x = x_;
    this->y = y_;
    this->cur_r = 0;
    this->t_start = std::chrono::high_resolution_clock::now();
    this->t_now = std::chrono::high_resolution_clock::now();
    this->flower_type = static_cast<int>(random() % 13);
    this->show = true;
    return 1;
}

int Flower::get_show_x() const{
    return this->x - ONE_FLOWER_WID / 2;
}

int Flower::get_show_y() const{
    return this->y - ONE_FLOWER_HIG / 2;
}
