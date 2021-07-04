//
// Created by ais on 7/2/21.
//

#include "RelayUtils.h"

//enum ShootColor {
//    GREEN = 0,
//    ORANGE = 1,
//    BLUE = 2,
//    PURPLE = 3,
//    YELLOW = 4,
//};

void lightUpShoot(int color){
    enumerate_relay_boards("aaa", 0, 1);
    operate_relay("6QMBS", color2switch[color], CMD_ON, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    operate_relay("6QMBS", color2switch[color], CMD_OFF, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void initRelayOperator() {
    for (int i = 0; i < 5; i++) {
        lightUpShoot(i);
    }
}


