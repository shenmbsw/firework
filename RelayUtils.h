//
// Created by ais on 7/2/21.
//

#ifndef FIREWORK_RELAYUTILS_H
#define FIREWORK_RELAYUTILS_H

extern "C" {
// add your #include statements here
#include "libusbrelay.h"
}
#include "array"
#include "thread"

//enum ShootColor {
//    GREEN = 0,
//    ORANGE = 1,
//    BLUE = 2,
//    PURPLE = 3,
//    YELLOW = 4,
//};
const std::array<int,5> color2switch = {1,7,6,8,4};

void lightUpShoot(int color);

void initRelayOperator();

void doLightUp(int color);




#endif //FIREWORK_RELAYUTILS_H
