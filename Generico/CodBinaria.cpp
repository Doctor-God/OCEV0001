#include "CodBinaria.hpp"

#include "util.hpp"
#include "Problem.hpp"
#include "Selection.hpp"


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

double CodBinaria::GA(){

}


//Chamada de fora
Score_Restricao CodBinaria::fitness(){
	Problem<bool> prob;
	return prob.getFuncao(this->problem)(mat);
}

vvb CodBinaria::selection(){
	Selection<bool> s;
	return s.getFuncao(this->selection_method)(mat, score_r.scores);
}
