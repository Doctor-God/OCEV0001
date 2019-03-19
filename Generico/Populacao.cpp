
#include <cmath>

#include "CodBinaria.hpp"
#include "CodInteira.hpp"
#include "CodPermutada.hpp"
#include "CodReal.hpp"


Populacao *FactoryPopulacao::build(int size, int n_vars, int tipo, std::variant<int, double> upper, std::variant<int, double> lower){
	if(tipo == 0){
		CodBinaria *pop;
		pop = new CodBinaria();
		pop->indiv = size;
		pop->vars = n_vars;
		return pop;
	}
	else if(tipo == 1){
		CodInteira *pop;
		pop = new CodInteira();
		pop->indiv = size;
		pop->vars = n_vars;
		pop->setUpper(std::get<int>(upper));
		pop->setLower(std::get<int>(lower));
		return pop;
	}
	else if(tipo == 2){
		CodPermutada *pop;
		pop = new CodPermutada();
		pop->indiv = size;
		pop->vars = n_vars;
		return pop;
	}
	else if(tipo == 3){
		CodReal *pop;
		pop = new CodReal();
		pop->indiv = size;
		pop->vars = n_vars;
		pop->setUpper(std::get<double>(upper));
		pop->setLower(std::get<double>(lower));
		return pop;
	}

	return NULL;
}


Populacao::Populacao(){}

Populacao::~Populacao(){}
