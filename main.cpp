#include "FireworksFractory.h"
#include "iostream"


using namespace std::chrono;


int main() {
    auto fire = FireworksFractory();

    int loop_idx = 0;
    while (loop_idx<1000) {
        loop_idx++;
        auto t1 = std::chrono::high_resolution_clock::now();
        fire.getCurrentState(t1);
        fire.generateCurrentImage();
        auto time_cost = std::chrono::duration_cast<milliseconds>(std::chrono::high_resolution_clock::now() - t1);
        std::cout << "Process time: " << time_cost.count() << std::endl;

    }
    return 0;
}



