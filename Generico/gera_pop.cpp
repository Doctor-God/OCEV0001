#include <bits/stdc++.h>
#include "Populacao.hpp"
#include "util.hpp"
// #include <boost/variant.hpp>

using namespace std;


int main(int argc, char const *argv[]){
	int size, n_vars, tipo;
	string problem;
	//pop_size n_vars tipo_cod
	if(argc < 5){
		cout << "./a.out pop_size n_vars tipo_cod problem [lim_inferior] [lim_superior]" << endl;
		exit(1);
	}


	tipo = stoi(argv[3]); //bin = 0   int = 1   int_permut = 2    real = 3

	if((tipo == 0 or tipo == 2) and argc > 5){
		cout << "Codificações Binária ou Inteira Permutada não necessitam de limites inferior e superior." << endl;
		exit(1);
	}
	else if((tipo != 0 and tipo != 2) and argc < 7){
		cout << "Codificações Inteira e Real necessitam de limites inferior e superior." << endl;
		exit(1);
	}

	variant<int, double> upper = 0, lower = 0;
	if(tipo == 1 or tipo == 3){
		if(tipo == 1){
			lower = stoi(argv[5]);
			upper = stoi(argv[6]);
		}
		else{
			lower = stod(argv[5]);
			upper = stod(argv[6]);
		}
	}

	size = stoi(argv[1]);
	n_vars = stoi(argv[2]);
	problem = argv[4];

	Populacao *pop = FactoryPopulacao::build(size, n_vars, tipo, problem, upper, lower);
	if(pop){
		pop->gerar();
	}
	else{
		cout << "Erro na instaciação da população\n";
		exit(1);
	}
	cout << "Indivíduos" << endl;
	pop->print();


	// vector<double> temp = pop->fitness();
	// vector<size_t> idx = sort_indexes(temp);
	//
	// cout << "Melhores" << endl;
	// for(auto i : idx){
	// 	cout << i << ": " << temp[i] << endl;
	// }



	return 0;
}
