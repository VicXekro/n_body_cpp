/*
 * author: Victor Youdom Kemmoe
 * this project was compiled using -std=c++11, -lstdc++, -lm
 */

#include <iostream>
#include <chrono>

#include "n_body.h"

int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;
    double delta_t = std::stod(argv[2]);
    int T = std::stoi(argv[3]);

    //should be 0 or 1; represent value to print at each step; 0 print only final timestep
    // 1 print all timesteps
    int i = std::stoi(argv[4]);

    std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now(); //get the starting time

    n_body body(argv[1],delta_t, T, i);
    body.actualize_speed_pos();

    std::chrono::high_resolution_clock::time_point t_end = std::chrono::high_resolution_clock::now(); //get the ending time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t_end - t_start).count(); // ending_time - starting_time to get the total duration
    std::cout << "Execution time: "<<duration<<" milliseconds"<<std::endl;
    return 0;
}