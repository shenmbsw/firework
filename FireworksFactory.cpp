//
// Created by shenshen on 6/28/21.
//

#include "FireworksFactory.h"
#include "RelayUtils.h"
#include "iostream"
#include "thread"

using namespace std::chrono;

int randint(int low, int hei){
    return (int)(low + random()%(hei - low));
}

void put_flower_on_image(cv::Mat &pic, cv::Mat &flower_m, const Flower &flower) {
    if(flower.get_show_x() > WND_WIDTH - ONE_FLOWER_WID || flower.get_show_x() < 0 || flower.get_show_y() > WND_HEIGHT - ONE_FLOWER_HIG || flower.get_show_x() < 0) return;
    cv::Mat roiImage = pic(cv::Rect(flower.get_show_x(), flower.get_show_y(), ONE_FLOWER_WID, ONE_FLOWER_HIG));
    int current_flower_idx = ONE_FLOWER_WID * flower.flower_type;
    cv::Mat flowerRoi = flower_m(cv::Rect(current_flower_idx, 0, ONE_FLOWER_WID, ONE_FLOWER_HIG));
    cv::Mat roiMask = cv::Mat(cv::Size(ONE_FLOWER_WID, ONE_FLOWER_HIG), CV_8UC1, cv::Scalar(0));
    double a = 0.0;
    while (a < 2 * M_PI) {
        int x1 = (int) (flower.cent_x + flower.cur_r * cos(a));
        int y1 = (int) (flower.cent_y + flower.cur_r * sin(a));
        if (x1 > 0 && x1 < ONE_FLOWER_WID && y1 > 0 && y1 < ONE_FLOWER_HIG) {
//            std::cout << "cent x: " << x1 << ", cent y: " << y1 << " r : " << flower.cur_r << std::endl;
            roiMask.at<uchar>(x1, y1) = 255;
        }
        a += 0.01;
    }
    flowerRoi.copyTo(roiImage, roiMask);

}


void pepper(cv::Mat &image, int n) {
    int i, j;
    for (int k = 0; k < n; k++) {
        i = randint(0, image.cols - 1);
        j = randint(0, image.rows);
        image.at<uchar>(j, i) = 255;
        image.at<uchar>(j, i + 1) = 255;
    }
}

void clear_flower_on_image(cv::Mat &pic, cv::Mat &pic_ori, const Flower &flower) {
    if(flower.get_show_x() > WND_WIDTH - ONE_FLOWER_WID || flower.get_show_x() < 0 || flower.get_show_y() > WND_HEIGHT - ONE_FLOWER_HIG || flower.get_show_x() < 0) return;
    cv::Mat roiSrc = pic_ori(cv::Rect(flower.get_show_x(), flower.get_show_y(), ONE_FLOWER_WID, ONE_FLOWER_HIG));
    cv::Mat roiDst = pic(cv::Rect(flower.get_show_x(), flower.get_show_y(), ONE_FLOWER_WID, ONE_FLOWER_HIG));
    cv::Mat roiMask = cv::Mat(cv::Size(ONE_FLOWER_WID, ONE_FLOWER_HIG), CV_8UC1, cv::Scalar(0));
    pepper(roiMask, 1000);
    roiSrc.copyTo(roiDst, roiMask);
}

void eliminate_flower_on_image(cv::Mat &pic, cv::Mat &pic_ori, const Flower &flower) {
    cv::Mat roiSrc = pic_ori(cv::Rect(flower.get_show_x(), flower.get_show_y(), ONE_FLOWER_WID, ONE_FLOWER_HIG));
    cv::Mat roiDst = pic(cv::Rect(flower.get_show_x(), flower.get_show_y(), ONE_FLOWER_WID, ONE_FLOWER_HIG));
    roiSrc.copyTo(roiDst);
}

void put_shoot_on_image(cv::Mat &pic, cv::Mat &shoot_m, const Shoot &shoot) {
//    std::cout << shoot.get_show_x() << ", " << shoot.get_show_y() << std::endl;
    if(shoot.get_show_x() > WND_WIDTH - ONE_SHOOT_WID || shoot.get_show_x() < 0 || shoot.get_show_y() > WND_HEIGHT - ONE_SHOOT_HIG || shoot.get_show_x() < 0) return;
    cv::Mat roiImage = pic(cv::Rect(shoot.get_show_x(), shoot.get_show_y(), ONE_SHOOT_WID, ONE_SHOOT_HIG));
    int current_shoot_idx = shoot.is_bright ? ONE_SHOOT_WID * shoot.shoot_color : ONE_SHOOT_WID *
                                                                                  (shoot.shoot_color + 5);
    cv::Mat shootRoi = shoot_m(cv::Rect(current_shoot_idx, 0, ONE_SHOOT_WID, ONE_SHOOT_HIG));
//    shootRoi.copyTo(roiImage);
    cv::bitwise_or(shootRoi,roiImage, roiImage);

}

void clear_shoot_on_image(cv::Mat &pic, cv::Mat &pic_ori, const Shoot &shoot) {
    cv::Mat roiSrc = pic_ori(cv::Rect(shoot.get_show_x(), shoot.get_show_y(), ONE_SHOOT_WID, ONE_SHOOT_HIG));
    cv::Mat roiDst = pic(cv::Rect(shoot.get_show_x(), shoot.get_show_y(), ONE_SHOOT_WID, ONE_SHOOT_HIG));
    roiSrc.copyTo(roiDst);
}


FireworksFactory::FireworksFactory() {
    initRelayOperator();
    pMem = new cv::Mat(cv::Size(WND_WIDTH, WND_HEIGHT), CV_8UC3, cv::Scalar(0, 0, 0));
    pMem_ori = new cv::Mat(cv::Size(WND_WIDTH, WND_HEIGHT), CV_8UC3, cv::Scalar(0, 0, 0));
    shoot_m = cv::imread("./data/shoot.jpg");
    flower_m = cv::imread("./data/flower.jpg");

    int radius[13] = {80, 90, 100, 105, 113, 150, 122, 98, 100, 78, 92, 120, 133};
//    int center_x[13] = {120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110};
//    int center_y[13] = {120, 120, 85, 118, 120, 105, 103, 110, 110, 120, 120, 104, 85};

    for (int i = 0; i < total_fire_shoot_num; i++) {
        shoots.emplace_back();
        flowers.emplace_back(radius[i], ONE_FLOWER_WID/2, ONE_FLOWER_HIG/2);
    }
    last_shoot_generate_time = high_resolution_clock::now();

}

FireworksFactory::~FireworksFactory() {
    delete pMem;
    delete pMem_ori;
}

int FireworksFactory::getCurrentState(high_resolution_clock::time_point &current_frame_start_time) {
    if (current_frame_start_time - last_shoot_generate_time > milliseconds(1000))   //100ms产生一个烟花弹
    {
        state = randint(0,9);
        int n = randint(0,19);
        if (n < total_fire_shoot_num && !shoots[n].show && !flowers[n].show) {
//            if(thread_arr[n]!= nullptr){
//                delete thread_arr
//            }
            int max_height = randint(ONE_FLOWER_HIG, WND_HEIGHT/2-ONE_FLOWER_HIG);
            int x = randint(ONE_FLOWER_WID, WND_WIDTH-ONE_FLOWER_WID);
            int y = WND_HEIGHT - ONE_FLOWER_HIG;
            shoots[n].resetShoot(max_height, x, y, state);

//            lightUpShoot(shoots[n].shoot_color);

        }
        last_shoot_generate_time = current_frame_start_time;

    }

    for (int i = 0; i < total_fire_shoot_num; i++) {
        if (current_frame_start_time - shoots[i].t_now > shoots[i].dt && shoots[i].show) {
            if (shoots[i].y > shoots[i].max_height) {
                shoots[i].is_bright = 1 - shoots[i].is_bright;  //0-1  明暗交替
                shoots[i].y -= 2;
            } else {
                shoots[i].show = false;
                flowers[i].resetFlower(shoots[i].x, shoots[i].max_height);
                std::thread t = std::thread(lightUpShoot, shoots[i].shoot_color);
                t.detach();
            }
            shoots[i].t_now = current_frame_start_time;
        }
    }

    int drt[16] = {5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 25, 55, 55, 55, 55, 55};    //dt

    for (int i = 0; i < total_fire_shoot_num; i++) {
        if (current_frame_start_time - flowers[i].t_now > flowers[i].dt && flowers[i].show) {
            if (flowers[i].cur_r < flowers[i].max_r) {
                flowers[i].cur_r++;
                flowers[i].dt = milliseconds(drt[flowers[i].cur_r / 16]*2);
                flowers[i].show = true;
            }

            if (flowers[i].cur_r >= flowers[i].max_r - 1) {
                flowers[i].show = false;
                eliminate_flower_on_image(*pMem, *pMem_ori, flowers[i]);
            }
            flowers[i].t_now = current_frame_start_time;
        }
    }

    return 0;
}

int FireworksFactory::generateCurrentImage() {
    for (int i = 0; i < total_fire_shoot_num; i++) {
        if (shoots[i].show) {
//            std::cout << "shoot: " << shoots[i].x << "," << shoots[i].y << ", " << shoots[i].max_height << std::endl;
            put_shoot_on_image(*pMem, shoot_m, shoots[i]);
        }
        if (flowers[i].show) {
//            std::cout << "flower: " << flowers[i].x << "," << flowers[i].y << ", " << flowers[i].cur_r << std::endl;
            put_flower_on_image(*pMem, flower_m, flowers[i]);
        }
    }
    cv::imshow("flower", *pMem);
    cv::waitKey(1);
    for (int i = 0; i < total_fire_shoot_num; i++) {
        if (shoots[i].show) {
            clear_shoot_on_image(*pMem, *pMem_ori, shoots[i]);
        }
        if (flowers[i].show) {
            clear_flower_on_image(*pMem, *pMem_ori, flowers[i]);
        }
    }
    return 0;
}

int FireworksFactory::generateCurrentColor(std::vector<int> &curr_color) {
    curr_color.resize(0);
    for (int i = 0; i < total_fire_shoot_num; i++) {
        if (shoots[i].show) {
            curr_color.push_back(shoots[i].shoot_color);
        }
    }
    return 0;
}

