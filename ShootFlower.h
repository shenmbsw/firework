//
// Created by shenshen on 6/28/21.
//

#ifndef UNTITLED_SHOOTFLOWER_H
#define UNTITLED_SHOOTFLOWER_H

#include "chrono"

#define ONE_SHOOT_WID 20
#define ONE_SHOOT_HIG 50
#define ONE_FLOWER_WID 240
#define ONE_FLOWER_HIG 240

enum ShootColor {
    GREEN = 0,
    ORANGE = 1,
    BLUE = 2,
    PURPLE = 3,
    YELLOW = 4,
};

class Shoot {
public:
    int x{}, y{}; // y bigger, shoot lower

    int max_height{};
    bool show = false;
    bool is_bright = false;
    int shoot_color{};
    std::chrono::high_resolution_clock::time_point t_start, t_now;
    std::chrono::high_resolution_clock::duration dt{}; // time duration for one process
    Shoot() = default;
    int resetShoot(int max_height, int x, int y, int state=0);
    int get_show_x() const;
    int get_show_y() const;

};

class Flower {
public:
    int x{}, y{}; // y bigger, shoot lower

    int cur_r{};
    int cent_x, cent_y;
    int max_r;
    bool show = false;
    int flower_type{};
    std::chrono::high_resolution_clock::time_point t_start, t_now;
    std::chrono::high_resolution_clock::duration dt{};
    Flower(int max_r_, int center_x_, int center_y_);
    int resetFlower(int x, int y);
    int get_show_x() const;
    int get_show_y() const;
};

#endif //UNTITLED_SHOOTFLOWER_H
