#ifndef UTIL
#define UTIL

#include <vector>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <variant>

#define BINARIA 0
#define INTEIRA 1
#define PERMUTADA 2
#define REAL 3

typedef struct{
    std::vector<double> scores;
    std::vector<bool> restritos;
}Score_Restricao;



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
int maior_elemento(std::vector<T> &v){
  int maior = 0;
  for(int i = 0; i < v.size(); i++){
    if(v[i] > v[maior]) maior = i;
  }
  return maior;
}

template <typename T>
int menor_elemento(std::vector<T> &v){
  int menor = 0;
  for(int i = 0; i < v.size(); i++){
    if(v[i] < v[menor]) menor = i;
  }
  return menor;
}

template <typename T>
void print_matrix(std::vector<std::vector<T> > &matrix){
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