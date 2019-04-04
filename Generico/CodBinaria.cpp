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
	Problem<bool> prob;
	return prob.getFuncao(this->problem)(mat);
}

vvb CodBinaria::selection(){
	Parameters p;
	p.k = this->k_unid;
	p.p = this->prob;
	p.t = this->tipo_selecao_vizinhanca;
	
	Selection<bool> s;
	return s.getFuncao(this->selection_method)(p, this->mat, score_r.scores);
}
