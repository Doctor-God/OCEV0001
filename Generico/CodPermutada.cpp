#include "CodPermutada.hpp"

#include "util.hpp"
#include "Problem.hpp"

#include <cmath>

CodPermutada::CodPermutada(){}

void CodPermutada::print(){
	print_matrix(mat);
}

void CodPermutada::gerar(){
	vvi pop(indiv, std::vector<int>(vars));
	for(int i = 0; i < indiv; i++){
		for(int j = 0; j < vars; j++){
			pop[i][j] = j;
		}
		shuffle(pop[i]);
	}
	mat = pop;
}

std::vector<double> CodPermutada::fitness(){
	Problem p;
	return fitness(p.get_iFunc(this->problem));
}

std::vector<double> CodPermutada::fitness(double (*func)(std::vector<int>)){
	std::vector<double> valores(indiv);

}
