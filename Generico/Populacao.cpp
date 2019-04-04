
#include <cmath>

#include "CodBinaria.hpp"
#include "CodInteira.hpp"
#include "CodPermutada.hpp"
#include "CodReal.hpp"


Populacao *FactoryPopulacao::build(int size, int n_vars, int tipo, std::string problem, std::string select, Parameters par){
	if(tipo == 0){
		CodBinaria *pop;
		pop = new CodBinaria();
		pop->indiv = size;
		pop->vars = n_vars;
		pop->problem = problem;
		pop->selection_method = select;
		pop->k_unid = par.k;
		pop->prob = par.p;
		pop->tipo_selecao_vizinhanca = par.t;
		return pop;
	}
	else if(tipo == 1){
		CodInteira *pop;
		pop = new CodInteira();
		pop->indiv = size;
		pop->vars = n_vars;
		pop->problem = problem;
		pop->selection_method = select;
		pop->setUpper(std::get<int>(par.upper));
		pop->setLower(std::get<int>(par.lower));
		pop->k_unid = par.k;
		pop->prob = par.p;
		pop->tipo_selecao_vizinhanca = par.t;
		return pop;
	}
	else if(tipo == 2){
		CodPermutada *pop;
		pop = new CodPermutada();
		pop->indiv = size;
		pop->vars = n_vars;
		pop->problem = problem;
		pop->selection_method = select;
		pop->k_unid = par.k;
		pop->prob = par.p;
		pop->tipo_selecao_vizinhanca = par.t;
		return pop;
	}
	else if(tipo == 3){
		CodReal *pop;
		pop = new CodReal();
		pop->indiv = size;
		pop->vars = n_vars;
		pop->problem = problem;
		pop->selection_method = select;
		pop->setUpper(std::get<double>(par.upper));
		pop->setLower(std::get<double>(par.lower));
		pop->k_unid = par.k;
		pop->prob = par.p;
		pop->tipo_selecao_vizinhanca = par.t;
		return pop;
	}

	return NULL;
}

// std::vector<double> getScores(){return score_r.scores;}


int Populacao::getKUn(){return k_unid;}
int Populacao::getProb(){return prob;}
int Populacao::getTipoSelecViz(){return tipo_selecao_vizinhanca;}


Populacao::Populacao(){}

Populacao::~Populacao(){}
