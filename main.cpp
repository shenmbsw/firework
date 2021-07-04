#include "FireworksFactory.h"


using namespace std::chrono;


int main() {
    auto fire = FireworksFactory();
    std::vector<int> current_color;
    int loop_idx = 0;

    while (loop_idx<int(1e10)) {
        loop_idx++;
        auto t1 = std::chrono::high_resolution_clock::now();
        fire.getCurrentState(t1);
        fire.generateCurrentImage();
        fire.generateCurrentColor(current_color);

//        relay_operator.lightUpShoot(current_color);
        auto time_cost = std::chrono::duration_cast<milliseconds>(std::chrono::high_resolution_clock::now() - t1);
//        std::cout << "Process time: " << time_cost.count() << std::endl;

    }
    return 0;
}



