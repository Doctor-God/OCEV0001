#ifndef UTIL
#define UTIL

#include <vector>
#include <iostream>
#include <iomanip>

typedef std::vector<std::vector<int> > vvi;
typedef std::vector<std::vector<bool> > vvb;
typedef std::vector<std::vector<double> > vvd;

int getRandInt(int a, int b);

double getRandDouble(double a, double b);

void shuffle(std::vector<int> &v);


template <typename T>
void print_matrix(std::vector<std::vector<T> > matrix){
	std::cout << std::fixed;
    std::cout << std::setprecision(4);

	int rows = matrix.size();
	int cols = matrix[0].size();
	for(int i = 0; i <rows; i++){
		for(int j = 0; j < cols; j++){
			std::cout << std::setw(10) << matrix[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


#endif