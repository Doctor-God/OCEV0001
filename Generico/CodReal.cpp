#include "CodReal.hpp"

#include "util.hpp"
#include "Problem.hpp"

CodReal::CodReal(){}

void CodReal::print(){
	print_matrix(mat);
}

void CodReal::gerar(){
	vvd pop(indiv, std::vector<double>(vars));
	for(int i = 0; i < indiv; i++){
		for(int j = 0; j < vars; j++){
			pop[i][j] = getRandDouble(upper, lower); //Segfault se usar getRandInt diretamente
			// pop[i][j] = getRandInt(upper, lower)); //Segfault se usar getRandInt diretamente
		}
	}
	mat = pop;
}

std::vector<double> CodReal::fitness(){
	Problem<double> prob;
	return fitness(prob.getFuncao(this->problem));
}

void CodReal::setUpper(double u){
	upper = u;
}

void CodReal::setLower(double l){
	lower = l;
}
