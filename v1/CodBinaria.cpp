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
	vvb pop(config.getPopSize(), std::vector<bool>(config.getNumVars()));
	for(int i = 0; i < config.getPopSize(); i++){
		for(int j = 0; j < config.getNumVars(); j++){
			pop[i][j] = (bool) getRandInt(0, 1);
		}
	}
	mat = pop;
}

double CodBinaria::GA(){
	std::cout << "Indiv" << std::endl;
	this->print();

	this->score_r = this->fitness();
	std::vector<double> temp_s = this->score_r.scores;
	std::vector<size_t> idx = sort_indexes(temp_s);

	std::cout << "Melhores" << std::endl;
	for(auto i : idx){
		std::cout << i << ": " << temp_s[i] << std::endl;
	}

	vvb popul_temp = this->selection();

}


//Chamada de fora
Score_Restricao CodBinaria::fitness(){
	Problem<bool> problem;
	return problem.getFuncao(config.getProblem())(mat, config);
}

vvb CodBinaria::selection(){	
	Selection<bool> s;
	return s.getFuncao(config.getSelectionMethod())(this->mat, score_r.scores, config);
}
