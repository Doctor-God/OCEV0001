#ifndef UTIL
#define UTIL

#include <vector>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <variant>

typedef struct{
    std::vector<double> scores;
    std::vector<bool> restritos;
}Score_Restricao;

typedef struct{
  std::variant<int, double> lower;
  std::variant<int, double> upper;
  std::string problem;
  std::string selection;
  int k; //Número de indiv no torneio ou distancia no selecao local
  double p; //Probabilidade no torneio
}Parameters;


typedef std::vector<std::vector<int> > vvi;
typedef std::vector<std::vector<bool> > vvb;
typedef std::vector<std::vector<double> > vvd;

int getRandInt(int a, int b);

double getRandDouble(double a, double b);

void shuffle(std::vector<int> &v);

template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v){

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});

  return idx;
}

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