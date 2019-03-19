#include "FactoryPopulacao.hpp"

Populacao *FactoryPopulacao::build(int size, int n_vars, int tipo, std::variant<int, double> upper, std::variant<int, double> lower){
	if(tipo == 1){
		CodInteira *pop;
		pop = new CodInteira();
		pop->indiv = size;
		pop->vars = n_vars;
		pop->setUpper(std::get<int>(upper));
		pop->setLower(std::get<int>(lower));
		return pop;
	}
}