#include "Populacao.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>

Populacao::Populacao(int size, int n_vars, int tipo, std::variant<int, double> upper, std::variant<int, double> lower){
	indiv = size;
	vars = n_vars;
	this->tipo = tipo;
	this->upper = upper;
	this->lower = lower;
}

Populacao::~Populacao(){
	// if(tipo == 1 or tipo == 2){
	// 	vvi matrix = std::get<vvi>(mat);
	// 	for(int i = 0; i < indiv; i++){
	// 		delete matrix[i];
	// 	}
	// 	delete matrix;
	// }
	// else if(tipo == 0){
	// 	vvb matrix = std::get<vvb>(mat);
	// 	for(int i = 0; i < indiv; i++){
	// 		delete matrix[i];
	// 	}
	// 	delete matrix;
	// }
	// else if(tipo == 3){
	// 	vvd matrix = std::get<vvd>(mat);
	// 	for(int i = 0; i < indiv; i++){
	// 		delete matrix[i];
	// 	}
	// 	delete matrix;
	// }
}

void Populacao::gerar(){
	if(tipo == 0){ //Binário
		vvb pop(indiv, std::vector<bool>(vars));
		for(int i = 0; i < indiv; i++){
			for(int j = 0; j < vars; j++){
				pop[i][j] = (bool) getRandInt(0, 1);
			}
		}
		mat = pop;
	}
	else if(tipo == 1){ //Inteiro
		vvi pop(indiv, std::vector<int>(vars));
		for(int i = 0; i < indiv; i++){
			for(int j = 0; j < vars; j++){
				pop[i][j] = std::round(getRandDouble(std::get<int>(upper), std::get<int>(lower))); //Segfault se usar getRandInt diretamente
				// pop[i][j] = getRandInt(std::get<int>(upper), std::get<int>(lower)); //Segfault se usar getRandInt diretamente
			}
		}
		mat = pop;
	}
	else if(tipo == 2){ //Inteiro Permutado
		vvi pop(indiv, std::vector<int>(vars));
		for(int i = 0; i < indiv; i++){
			for(int j = 0; j < vars; j++){
				pop[i][j] = j;
			}
			shuffle(pop[i]);
		}
		mat = pop;
	}
	else if(tipo == 3){ //Real
		vvd pop(indiv, std::vector<double>(vars));
		for(int i = 0; i < indiv; i++){
			for(int j = 0; j < vars; j++){
				pop[i][j] = getRandDouble(std::get<double>(upper), std::get<double>(lower));
			}
		}
		mat = pop;
	}
}

void Populacao::print(){
	if(tipo == 1 or tipo == 2){
		print<vvi>();
	}
	else if(tipo == 0){
		print<vvb>();
	}
	else if(tipo == 3){
		print<vvd>();
	}
}


template <typename T>
void Populacao::print(){
	std::cout << std::fixed;
    std::cout << std::setprecision(4);
	
	T matrix = std::get<T>(mat);

	int rows = matrix.size();
	int cols = matrix[0].size();
	for(int i = 0; i <rows; i++){
		for(int j = 0; j < cols; j++){
			std::cout << std::setw(10) << matrix[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}
