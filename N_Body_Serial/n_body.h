//
// Created by Victor Youdom Kemmoe on 11/23/2018.
//

#ifndef N_BODY_SERIAL_N_BODY_H
#define N_BODY_SERIAL_N_BODY_H

#include <cstdlib>
#include <cstring>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class n_body {
private:
    const double G = 6.6742E-11; //gravitational constant

    int T; //final time
    double delta_t; //intervals of times before recalculating the velocities and positions;
    int is_each_step; // 1 or 0, 1 print after each step, 0 don't
    int n; //number of bodies;
    double* masses; //array to hold the mass of the n body
    double* positions; // 2D array to hold the X,Y positions of bodies in space
    double* velocities; //2D array to hold the X,Y velocities of bodies in space
    double* forces; // 2D array to hold the force applied on a body on the X, Y axis
    double force_qk_x; //force exerted by particle K on Q on the X-axis
    double force_qk_y; //force exerted by particle K on Q on he Y-axis
    std::string file_path; //path to the file containing data

    void initialize_arrays();
    void calculate_forces_k_on_q();
    void read_data_from_txt();
    void write_data_to_txt(double timestep);

public:
    n_body(const std::string& file_path_, double delta_t_, int T_, int is_each_step_);
    void actualize_speed_pos();
};


#endif //N_BODY_SERIAL_N_BODY_H
