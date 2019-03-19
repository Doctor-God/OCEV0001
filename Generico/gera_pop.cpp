#include <bits/stdc++.h>
#include "Populacao.hpp"
#include "util.hpp"
// #include <boost/variant.hpp>

using namespace std;


int main(int argc, char const *argv[]){

	//pop_size n_vars tipo_cod
	if(argc < 4){
		cout << "./a.out pop_size n_vars tipo_cod [lim_inferior] [lim_superior]" << endl;
		exit(1);
	}

	int size, n_vars, tipo;

	tipo = stoi(argv[3]); //bin = 0   int = 1   int_permut = 2    real = 3

	if((tipo == 0 or tipo == 2) and argc > 4){
		cout << "Codificações Binária ou Inteira Permutada não necessitam de limites inferior e superior." << endl;
		exit(1);
	}
	else if((tipo != 0 and tipo != 2) and argc < 6){
		cout << "Codificações Inteira e Real necessitam de limites inferior e superior." << endl;
		exit(1);
	}

	variant<int, double> upper = 0, lower = 0;
	if(tipo == 1 or tipo == 3){
		if(tipo == 1){
			lower = stoi(argv[4]);
			upper = stoi(argv[5]);
		}
		else{
			lower = stod(argv[4]);
			upper = stod(argv[5]);
		}
	}

	size = stoi(argv[1]);
	n_vars = stoi(argv[2]);

	Populacao *pop = FactoryPopulacao::build(size, n_vars, tipo, upper, lower);
	if(pop){
		pop->gerar();
		pop->print();
	}
	else{
		cout << "Erro na instaciação da população\n";
		exit(1);
	}



	return 0;
}

