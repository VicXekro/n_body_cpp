/*
 * Created by Victor Youdom Kemmoe
 */

#include <omp.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <mpi.h>
#include <math.h>

class n_body{
private:
	const double G = 6.6742E-11; //gravitational constant

	int comm_sz; //total number of process
	int process_id; //id of the current process
	int process_master; //id of the master process
	int T; //final time
	double delta_t; //intervals of times before recalculating the velocities and positions;
	int is_each_step; // 1 or 0, 1 print after each step, 0 don't

	int n; //number of bodies;
	int local_n; //local number of bodies

	double* masses; //array to hold the mass of the n body
	double* positions; // 2D array to hold the X,Y positions of bodies in space
	double* velocities; //2D array to hold the X,Y velocities of bodies in space
	std::string file_path; //path to the file containing data
	int number_of_threads; //number of threads to be used

	double* local_velocities;
	double* local_positions;
	double* local_forces;

	void initialize_arrays();
	void calculate_forces_k_on_q();
	void read_data_from_txt();
	void write_data_to_txt(double timestep);

public:
    n_body(const std::string& file_path_, double delta_t_, int T_, int is_each_step_, int number_of_threads_, int process_id_, int process_master_, int comm_sz_);
    void actualize_speed_pos();
};
