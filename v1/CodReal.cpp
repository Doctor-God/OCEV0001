#include "CodReal.hpp"

#include "util.hpp"
#include "Problem.hpp"
#include "Selection.hpp"


CodReal::CodReal(){}

void CodReal::print(){
	print_matrix(mat);
}

void CodReal::gerar(){
	vvd pop(config.getPopSize(), std::vector<double>(config.getNumVars()));
	for(int i = 0; i < config.getPopSize(); i++){
		for(int j = 0; j < config.getNumVars(); j++){
			pop[i][j] = getRandDouble(std::get<double>(config.getLowerBound()), std::get<double>(config.getUpperBound())); //Segfault se usar getRandInt diretamente
			// pop[i][j] = getRandInt(upper, lower)); //Segfault se usar getRandInt diretamente
		}
	}
	mat = pop;
}

double CodReal::GA(){
	
}

Score_Restricao CodReal::fitness(){
	Problem<double> prob;
	return prob.getFuncao(config.getProblem())(mat, config);
}

vvd CodReal::selection(){
	Selection<double> s;
	return s.getFuncao(config.getSelectionMethod())(this->mat, score_r.scores, config);
}
