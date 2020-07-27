//
// Created by Victor Youdom Kemmoe on 11/23/2018.
//

#include "n_body.h"

n_body::n_body(const std::string& file_path_, double delta_t_, int T_, int is_each_step_) {
    file_path = file_path_;
    delta_t = delta_t_;
    T = T_;
    is_each_step = is_each_step_;

    read_data_from_txt();
}

void n_body::initialize_arrays() {
    /*initialize the size of each arrays to hold the different
     * parameter of a particles.
     */
    masses = (double *)malloc(n* sizeof(double));
    velocities = (double *)malloc(n* 2 * sizeof(double));
    positions = (double *)malloc(n* 2 * sizeof(double));
    forces = (double *)malloc(n * 2 * sizeof(double));

    memset(forces, 0, n * 2 * sizeof(double));
}

void n_body::calculate_forces_k_on_q() {
    /*calculate the forces exerted by K_particles on particle Q
     * use the newton third law which state that for each action, there is an equal an opposite reaction
     */
    for (int q = 0; q < n; q++) {
        for (int k = (q+1) ; k < n ; k++) {
            double x_diff = *(positions + q*2 + 0) - *(positions + k*2 + 0);
            double y_diff = *(positions + q*2 + 1) - *(positions + k*2 + 1);
            double dist = sqrt(x_diff*x_diff + y_diff*y_diff);
            double dist_cubed = dist*dist*dist;

            force_qk_x = G*masses[q]*masses[k]/dist_cubed * x_diff;
            force_qk_y = G*masses[q]*masses[k]/dist_cubed * y_diff;

            *(forces + q*2 + 0) += force_qk_x;
            *(forces + q*2 + 1) += force_qk_y;
            *(forces + k*2 + 0) -= force_qk_x;
            *(forces + k*2 + 1) -= force_qk_y;
        }
    }
}

void n_body::actualize_speed_pos() {
    /*
     * calculate the new values of position and velocity of a particles
     * write result to file for each timestep if asked by the user
     */
    for (int timestep = 0; timestep < T; ++timestep) {
        if(is_each_step == 1) {
            write_data_to_txt(timestep*delta_t);
        }
        calculate_forces_k_on_q();
        for (int q = 0; q < n ; ++q) {
            //updating velocity and speed
            *(positions + q*2 + 0) += delta_t * (*(velocities + q*2 + 0));
            *(positions + q*2 + 1) += delta_t * (*(velocities + q*2 + 1));
            *(velocities + q*2 + 0) += delta_t/masses[q] * (*(forces + q*2 + 0));
            *(velocities + q*2 + 1) += delta_t/masses[q] * (*(forces + q*2 + 1));
        }
    }
   // option write at each timestep was not selected hence write at delta_t * T
        write_data_to_txt(T*delta_t);


}

void n_body::read_data_from_txt() {
    /* open file containing data and read them
     * format of the file is:
     * first line represent number of data
     * rest of file is: x-position, y-position, x-velocity, y-velocity, masses
     * After reading the number of data from the file at the first line, it initialize the arrays
     */
    std::ifstream file(file_path.c_str());
    if(file.is_open()) {
        std::string line;
        getline(file, line); //read first line
        n = std::stoi(line); //get number of elements from first line

        initialize_arrays();

        int i = 0;
        while (getline(file, line)) {
            std::stringstream linestream(line);
            std::string value;

            getline(linestream, value, ',');
            *(positions + i*2 + 0) = std::stod(value); // X position

            getline(linestream, value, ',');
            *(positions + i*2 + 1) = std::stod(value); // Y position

            getline(linestream, value, ',');
            *(velocities + i*2 + 0) = std::stod(value); // X velocity

            getline(linestream, value, ',');
            *(velocities + i*2 + 1) = std::stod(value); // Y velocity

            getline(linestream, value, ',');
            masses[i] = std::stod(value);

            i++;
        }
        file.close();
    }else{
        std::cerr<<"Error while opening the file"<<std::endl;
        exit(EXIT_FAILURE);
    }
}

void n_body::write_data_to_txt(double timestep) {
    /*
     * Write calculated data in a file using the same format i.e
     * first line: number of particle
     * rest of file: x-pos,y-pos,x-velo,y-velo,masse
     */
    std::string outfile_name = std::string("data_")+ std::to_string(timestep);
    std::ofstream outfile (outfile_name);
    outfile<<n<<std::endl;
    for (int q = 0; q < n ; ++q) {
        outfile<<*(positions +q*2 +0)<<","<<*(positions +q*2 +1)<<","<<*(velocities +q*2 +0)<<","<<*(velocities +q*2 +1)<<","<<masses[q]<<std::endl;
    }
    outfile.close();
}

