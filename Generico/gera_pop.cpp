#include <bits/stdc++.h>
#include <unistd.h>
#include "Populacao.hpp"
#include "util.hpp"
// #include <boost/variant.hpp>

using namespace std;


int main(int argc, char const *argv[]){
    
	Parameters parat;
	int size, n_vars, tipo;
	std::string problem, selection_method;

	size = stoi(argv[1]);
	n_vars = stoi(argv[2]);
	tipo = stoi(argv[3]); //bin = 0   int = 1   int_permut = 2    real = 3
	problem = argv[4];
	selection_method = argv[5];
	
	//Serve pra fazer parse de opção de command line, ajustar o código depois
	int c ;
	while( ( c = getopt (argc, (char**) argv, "u:l:h:k:p") ) != -1 ) 
    {
        switch(c)
        {
			case 'h':
                //Print help
				exit(0);
			case 'l':
				if(optarg){
					if(tipo == 1)	
						parat.lower = atoi(optarg);
					else
						parat.lower = stod(optarg);
				}
				break;
            case 'u':
                if(optarg){
					if(tipo == 1)	
						parat.upper = atoi(optarg);
					else
						parat.upper = stod(optarg);
				}
				break;
			case 'k':
				if(optarg) parat.k = atoi(optarg);
				break;
			
			case 'p':
				if(optarg) parat.p = stod(optarg);
				break;
        }
    }


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


	Populacao *pop = FactoryPopulacao::build(size, n_vars, tipo, problem, selection_method, parat);
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
