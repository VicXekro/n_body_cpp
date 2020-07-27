/*
 * Author: Victor Youdom Kemmoe
 * This program was compiled using MPIICC with the argument -lstdc++, -std=c++11, -qopenmp
 */

#include <mpi.h>
#include <stdexcept>
#include <chrono>
#include "n_body.h"
#include <iostream>

int main(int argc, char** argv){
	//std::cout << "N_Body MPI_OMP" << std::endl;
	if (argc != 6){
		    std::cerr<< "Invalid number of command line arguments" << std::endl;
		    return EXIT_FAILURE;
	}

	int my_rank, comm_sz, i,thread_num,T;
	double delta_t;
	double local_t_start, local_t_end, t_start, t_end;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	delta_t = std::stod(argv[2]);
	T = std::stoi(argv[3]);

	//should be 0 or 1.
	//0 means print at T* delta_T, 1 means print at all time step
	i = std::stoi(argv[4]);

	//number of threads to be used by each processes
	thread_num = std::stoi(argv[5]);

	local_t_start = MPI_Wtime();//getting the time at which a process start

	n_body body(argv[1],delta_t,T,i,thread_num,my_rank,0,comm_sz);
	body.actualize_speed_pos();

	local_t_end = MPI_Wtime(); //getting the time at which a process end

	MPI_Reduce(&local_t_start, &t_start, 1, MPI_DOUBLE, MPI_MIN, 0,
			MPI_COMM_WORLD); //get the smallest starting
	//time among processes and send it to process 0

	MPI_Reduce(&local_t_end, &t_end, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);//get the greatest starting time of
	//among processes and send it to process 0

	if (my_rank == 0)
		//if process 0; print the excution time of the program
		std::cout << "Execution time: " << t_end - t_start << "s" << std::endl;

	MPI_Finalize();
	return 0;
}
