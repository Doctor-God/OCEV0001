#include "CodInteira.hpp"

#include "util.hpp"
#include "Problem.hpp"
#include "Selection.hpp"

#include <cmath>

CodInteira::CodInteira(){}

void CodInteira::print(){
	print_matrix(mat);
}

void CodInteira::gerar(){
	vvi pop(config.getPopSize(), std::vector<int>(config.getNumVars()));
	for(int i = 0; i < config.getPopSize(); i++){
		for(int j = 0; j < config.getNumVars(); j++){
			// pop[i][j] = std::floor(getRandDouble(upper, lower)); //Segfault se usar getRandInt diretamente
			pop[i][j] = getRandInt(std::get<int>(config.getLowerBound()), std::get<int>(config.getUpperBound())); //Segfault se usar getRandInt diretamente
		}
	}
	mat = pop;
}

double CodInteira::GA(){
	
}

Score_Restricao CodInteira::fitness(){
	Problem<int> prob;
	return prob.getFuncao(config.getProblem())(mat, config);
}

vvi CodInteira::selection(){
	Selection<int> s;
	return s.getFuncao(config.getSelectionMethod())(this->mat, score_r.scores, config);
}

