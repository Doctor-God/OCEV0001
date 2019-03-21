#include "CodBinaria.hpp"

#include "util.hpp"

#include <cmath>

CodBinaria::CodBinaria(){}

void CodBinaria::print(){
	print_matrix(mat);
}

void CodBinaria::gerar(){
	vvb pop(indiv, std::vector<bool>(vars));
	for(int i = 0; i < indiv; i++){
		for(int j = 0; j < vars; j++){
			pop[i][j] = (bool) getRandInt(0, 1);
		}
	}
	mat = pop;
}

std::vector<double> CodBinaria::fitness(){

}