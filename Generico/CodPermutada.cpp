#include "CodPermutada.hpp"

#include "util.hpp"

#include "Problem.hpp"
#include "Selection.hpp"

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

double CodPermutada::GA(){

	std::cout << "Indiv" << std::endl;
	this->print();

	this->score_r = this->fitness();
	std::vector<double> temp_s = this->score_r.scores;
	std::vector<size_t> idx = sort_indexes(temp_s);

	std::cout << "Melhores" << std::endl;
	for(auto i : idx){
		std::cout << i << ": " << temp_s[i] << std::endl;
	}

	vvi popul_temp = this->selection();

	// for(int i = 0; i < popul_temp.size(); i+2){
	// 	std::cout << 
	// }




}

//Chamada de fora
Score_Restricao CodPermutada::fitness(){
	Problem<int> prob;
	return prob.getFuncao(this->problem)(mat);
}

vvi CodPermutada::selection(){
	Selection<int> s;
	return s.getFuncao(this->selection_method)(mat, score_r.scores);
}
