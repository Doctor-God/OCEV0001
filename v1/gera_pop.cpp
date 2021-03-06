#include <bits/stdc++.h>
#include <unistd.h>
#include <stdio.h>
#include "Populacao.hpp"
#include "Config.hpp"
#include "util.hpp"
// #include <boost/variant.hpp>

using namespace std;

void print_help(){
	printf("./a.out nro_variaveis tipo_cod problema\n");
	printf("[-z population_size]\n");
	printf("[-l lower_bound]\n");
	printf("[-u upper_bound]\n");
	printf("[-k distancia_vizinhanca/tam_torneio]\n");
	printf("[-p prob_melhor_torneio]\n");
	printf("[-t tipo_selecao_vizinhanca]\n");
	printf("[-c prob_crossover]\n");
	printf("[-m prob_mutacao]\n");
	printf("[-s metodo_selecao]\n");
}

int main(int argc, char const *argv[]){
    
	Config config;
	int tipo;
	
	if(argc == 1){
		print_help();
		exit(0);
	}

	config.setNumVars(stoi(argv[1]));
	tipo = stoi(argv[2]); //bin = 0   int = 1   int_permut = 2    real = 3
	config.setProblem(argv[3]);
	
	//Serve pra fazer parse de opção de command line (flags)
	int c ;
	while( ( c = getopt (argc, (char**) argv, "u:l:k:p:t:s:z") ) != -1 ) 
    {
        switch(c)
        {
			case 'l':
				if(optarg){
					if(tipo == 1)	
						config.setLowerBound(atoi(optarg));
					else
						config.setLowerBound(stod(optarg));
				}
				break;
            case 'u':
                if(optarg){
					if(tipo == 1)	
						config.setUpperBound(atoi(optarg));
					else
						config.setUpperBound(stod(optarg));
				}
				break;
			case 'k':
				if(optarg) config.setK(atoi(optarg));
				break;
			
			case 'p':
				if(optarg) config.setProb(stod(optarg));
				break;
			case 't':
				if(optarg) config.setTipoSelec(atoi(optarg));
				break;
			case 's':
				if(optarg) config.setSelectionMethod(optarg);
				break;
			case 'z':
				if(optarg) config.setPopSize(atoi(optarg));
				break;
			
        }
    }

	// selection_method = argv[5];


	//pop_size n_vars tipo_cod
	// if(argc < 6){
	// 	cout << "./a.out pop_size n_vars tipo_cod problem selection_method [lim_inferior] [lim_superior]" << endl;
	// 	exit(1);
	// }



	// if((tipo == 0 or tipo == 2) and argc > 6){
	// 	cout << "Codificações Binária ou Inteira Permutada não necessitam de limites inferior e superior." << endl;
	// 	exit(1);
	// }
	// else if((tipo != 0 and tipo != 2) and argc < 8){
	// 	cout << "Codificações Inteira e Real necessitam de limites inferior e superior." << endl;
	// 	exit(1);
	// }


	Populacao *pop = FactoryPopulacao::build(tipo, config);
	if(pop){
		pop->gerar();
	}
	else{
		cout << "Erro na instaciação da população\n";
		exit(1);
	}

	pop->GA();
	// cout << "Indivíduos" << endl;
	// pop->print();


	// vector<double> temp = pop->fitness();
	// vector<size_t> idx = sort_indexes(temp);
	//
	// cout << "Melhores" << endl;
	// for(auto i : idx){
	// 	cout << i << ": " << temp[i] << endl;
	// }



	return 0;
}


