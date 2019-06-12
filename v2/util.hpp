#ifndef UTIL
#define UTIL

#include <vector>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <variant>
#include <stdio.h>

#define BINARIA 0
#define INTEIRA 1
#define PERMUTADA 2
#define REAL 3

typedef struct{
    std::vector<double> scores;
    std::vector<bool> restritos;
}Score_Restricao;

typedef struct permut{
  int value;
  friend std::ostream& operator<<(std::ostream& target, const permut& source);

  permut(int value);
  permut();

  void operator=(const int num);

  permut operator+(const permut &a);
  permut operator-(const permut &a);
  permut operator*(const permut &a);
  permut operator/(const permut &a);

  int operator+(const int &a);
  int operator-(const int &a);
  int operator*(const int &a);
  int operator/(const int &a);

  void operator++();
  void operator--();

  void operator+=(const int &num);
  void operator-=(const int &num);
  void operator*=(const int &num);
  void operator/=(const int &num);

  bool operator>(const int &num);
  bool operator<(const int &num);
  bool operator==(const int &num);
  bool operator!=(const int &num);
  
  bool operator>(const permut &a); 
  bool operator<(const permut &a); 
  bool operator==(const permut &a);
  bool operator!=(const permut &a); 

  operator float() const;


} int_permut_t;

double abs(const int_permut_t &a);

std::ostream& operator<<(std::ostream& target, const int_permut_t &source);


typedef std::vector<std::vector<int> > vvi;
typedef std::vector<std::vector<bool> > vvb;
typedef std::vector<std::vector<double> > vvd;

int getRandInt(int a, int b);

double getRandDouble(double a, double b);

void shuffle(std::vector<int_permut_t> &v);

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

template<typename T>
int findEqual(std::vector<std::vector<T> > &popul, std::vector<T> &indiv){
  for(int k = 0; k < popul.size(); k++){
    // std::cout << "oi\n";
    bool diff = false; //É diferente de indiv ou não
    for(int v = 0; v < indiv.size(); v++){
      // std::cout << "oi2\n";
      if(indiv[v] != popul[k][v]){
        diff = true;
        break;
      }
    }
    if(not diff)
      return k;
  }
  return -1; //Teoricamente nunca vai acontecer
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