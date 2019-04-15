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

void shuffle(std::vector<int_permut_t> &v){
	int size = v.size();
	for(int i = 0; i < size-1; i++){
		int j = getRandInt(i, size-1);
		std::swap(v[i], v[j]);
	}
}

permut::permut(int value){this->value = value;}
permut::permut(){}

void permut::operator=(const int num) {this->value = num;}

int_permut_t permut::operator+(const int_permut_t &a) {return int_permut_t(this->value+a.value);}
int_permut_t permut::operator-(const int_permut_t &a) {return int_permut_t(this->value-a.value);}
int_permut_t permut::operator*(const int_permut_t &a) {return int_permut_t(this->value*a.value);}
int_permut_t permut::operator/(const int_permut_t &a) {return int_permut_t(this->value/a.value);}

int permut::operator+(const int &a) { return this->value + a; }
int permut::operator-(const int &a) { return this->value - a; }
int permut::operator*(const int &a) { return this->value * a; }
int permut::operator/(const int &a) { return this->value / a; }

void permut::operator++() {value++;}
void permut::operator--() {value--;}

void permut::operator+=(const int &num) {this->value+=num;}
void permut::operator-=(const int &num) {this->value-=num;}
void permut::operator*=(const int &num) {this->value*=num;}
void permut::operator/=(const int &num) {this->value/=num;}

bool permut::operator>(const int &num) {this->value>num;}
bool permut::operator<(const int &num) {this->value<num;}
bool permut::operator==(const int &num) {this->value==num;}
bool permut::operator!=(const int &num) {this->value!=num;}

bool permut::operator>(const int_permut_t &a) {this->value>a.value;}
bool permut::operator<(const int_permut_t &a) {this->value<a.value;}
bool permut::operator==(const int_permut_t &a) {this->value==a.value;}
bool permut::operator!=(const int_permut_t &a) {this->value!=a.value;}

permut::operator float() const {return (float) this->value;}

double abs(const int_permut_t &a) {return (a.value>0)? a.value : -a.value;}

std::ostream& operator<<(std::ostream& target, const int_permut_t &source){
  target << source.value;
  return target;
}


