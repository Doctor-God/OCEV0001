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

vector<double> fitness(){
	Problem p();
	return fitness(p.getFunc(this->problem));
}

vector<double> fitness(double (*func)(std::vector<int>)){

}

}
