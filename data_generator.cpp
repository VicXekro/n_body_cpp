#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>

void write_data_to_txt(int n);
double random_double();

int main(int argc, char** argv){
    int n_data = std::atoi(argv[1]);
    write_data_to_txt(n_data);
}

void write_data_to_txt(int n) {
    srand(time(NULL));
    std::string outfile_name = std::string("data_50000");
    std::ofstream outfile (outfile_name);
    outfile<<n<<std::endl;
    for (int q = 0; q < n ; ++q) {
        outfile<<random_double()<<","<<random_double()<<","<<random_double()<<","<<random_double()<<","<<random_double()<<std::endl;
    }
    outfile.close();
}

double random_double(){
    double random_number;
    random_number = (double)rand()/RAND_MAX;
	random_number = 1 + random_number*(50-1);;
    return random_number;
}
