
#include <cmath>

#include "CodBinaria.hpp"
#include "CodInteira.hpp"
#include "CodPermutada.hpp"
#include "CodReal.hpp"


Populacao *FactoryPopulacao::build(int tipo, Config &c){
	if(tipo == 0){
		CodBinaria *pop;
		pop = new CodBinaria();
		pop->config = c;
		return pop;
	}
	else if(tipo == 1){
		CodInteira *pop;
		pop = new CodInteira();
		pop->config = c;
		return pop;
	}
	else if(tipo == 2){
		CodPermutada *pop;
		pop = new CodPermutada();
		pop->config = c;
		return pop;
	}
	else if(tipo == 3){
		CodReal *pop;
		pop = new CodReal();
		pop->config = c;
		return pop;
	}

	return NULL;
}

// std::vector<double> getScores(){return score_r.scores;}

Populacao::Populacao(){}

Populacao::~Populacao(){}
