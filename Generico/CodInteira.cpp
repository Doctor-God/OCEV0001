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
	vvi pop(indiv, std::vector<int>(vars));
	for(int i = 0; i < indiv; i++){
		for(int j = 0; j < vars; j++){
			pop[i][j] = std::floor(getRandDouble(upper, lower)); //Segfault se usar getRandInt diretamente
			// pop[i][j] = getRandInt(upper, lower); //Segfault se usar getRandInt diretamente
		}
	}
	mat = pop;
}

double CodInteira::GA(){
	
}

Score_Restricao CodInteira::fitness(){
	Problem<int> prob;
	return prob.getFuncao(this->problem)(mat);
}

vvi CodInteira::selection(){
	Selection<int> s;
	return s.getFuncao(this->selection_method)(mat, score_r.scores);
}

void CodInteira::setUpper(int u){
	upper = u;
}

void CodInteira::setLower(int l){
	lower = l;
}
