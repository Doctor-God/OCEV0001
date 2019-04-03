#include <bits/stdc++.h>
#include <unistd.h>
#include "Populacao.hpp"
#include "util.hpp"
// #include <boost/variant.hpp>

using namespace std;


int main(int argc, char const *argv[]){
    
	//Serve pra fazer parse de opção de command line, ajustar o código depois
	// int c ;
    // while( ( c = getopt (argc, argv, "n:t:") ) != -1 ) 
    // {
    //     switch(c)
    //     {
    //         case 'n':
    //             if(optarg) nvalue = optarg;
    //             break;
    //         case 't':
    //             if(optarg) tvalue = std::atoi(optarg) ;
    //             break;
    //     }
    // }


	int size, n_vars, tipo;
	string problem, selection_method;
	//pop_size n_vars tipo_cod
	if(argc < 6){
		cout << "./a.out pop_size n_vars tipo_cod problem selection_method [lim_inferior] [lim_superior]" << endl;
		exit(1);
	}


	tipo = stoi(argv[3]); //bin = 0   int = 1   int_permut = 2    real = 3

	if((tipo == 0 or tipo == 2) and argc > 6){
		cout << "Codificações Binária ou Inteira Permutada não necessitam de limites inferior e superior." << endl;
		exit(1);
	}
	else if((tipo != 0 and tipo != 2) and argc < 8){
		cout << "Codificações Inteira e Real necessitam de limites inferior e superior." << endl;
		exit(1);
	}

	variant<int, double> upper = 0, lower = 0;
	if(tipo == 1 or tipo == 3){
		if(tipo == 1){
			lower = stoi(argv[6]);
			upper = stoi(argv[7]);
		}
		else{
			lower = stod(argv[6]);
			upper = stod(argv[7]);
		}
	}

	size = stoi(argv[1]);
	n_vars = stoi(argv[2]);
	problem = argv[4];
	selection_method = argv[5];

	Populacao *pop = FactoryPopulacao::build(size, n_vars, tipo, problem, selection_method, upper, lower);
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
