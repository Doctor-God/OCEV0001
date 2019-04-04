#include "CodReal.hpp"

#include "util.hpp"
#include "Problem.hpp"
#include "Selection.hpp"


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

double CodReal::GA(){
	
}

Score_Restricao CodReal::fitness(){
	Problem<double> prob;
	return prob.getFuncao(this->problem)(mat);
}

vvd CodReal::selection(){
	Parameters p;
	p.k = this->k_unid;
	p.p = this->prob;
	p.t = this->tipo_selecao_vizinhanca;
	
	Selection<double> s;
	return s.getFuncao(this->selection_method)(p, this->mat, score_r.scores);
}

void CodReal::setUpper(double u){
	upper = u;
}

void CodReal::setLower(double l){
	lower = l;
}
