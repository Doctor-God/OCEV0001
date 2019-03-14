#include "util.hpp"

#include <random>

std::random_device rd{};
std::mt19937 gen(rd());

int getRandInt(int a, int b){
	std::uniform_int_distribution<int> dis(a, b);
	return dis(gen);
}

double getRandDouble(double a, double b){
	std::uniform_real_distribution<double> dis(a, b);
	return dis(gen);
}

void shuffle(std::vector<int> &v){
	int size = v.size();
	for(int i = 0; i < size-1; i++){
		int j = getRandInt(i, size-1);
		std::swap(v[i], v[j]);
	}
}