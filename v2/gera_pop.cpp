#include <bits/stdc++.h>
#include <unistd.h>
#include <stdio.h>

#include "GeneticAlgorithm.hpp"
#include "Config.hpp"
#include "util.hpp"

using namespace std;

void print_help(){
	printf("./a.out nro_variaveis tipo_cod problema arquivo_destino\n");
	printf("[-z population_size]\n");	
	printf("[-g generations]\n");
	printf("[-l lower_bound]\n");
	printf("[-u upper_bound]\n");
	printf("[-e num_elitistas]\n");
	printf("[-k distancia_vizinhanca/tam_torneio]\n");
	printf("[-p prob_melhor_torneio]\n");
	printf("[-t tipo_selecao_vizinhanca]\n");
	printf("[-d tipo_crossover]\n");
	printf("[-c prob_crossover]\n");
	printf("[-m prob_mutacao]\n");
	printf("[-s metodo_selecao]\n");
	printf("[-a alpha_blx]\n");
	printf("[-b tunelamento_michalewicz]\n");
	printf("[-o saida_geracoes_arquivo]\n");
	printf("[-r tipo_relatorio]\n");

}

void runGeneticAlgorithm(Config &c);

int main(int argc, char const *argv[]){
    
	Config config;
	int tipo;
	
	if(argc == 1){
		print_help();
		exit(0);
	}

	config.setNumVars(stoi(argv[1]));
	config.setTipo(stoi(argv[2])); //bin = 0   int = 1   int_permut = 2    real = 3
	config.setProblem(argv[3]);
	config.setArquivoDestino(argv[4]);
	
	//Serve pra fazer parse de opção de command line (flags)
	int c ;
	while( ( c = getopt (argc, (char**) argv, "u:l:k:p:t:s:z:g:e:d:c:m:o:a:b:r:E:") ) != -1 ) 
    {
        switch(c)
        {
			case 'l':
				if(optarg){
					if(config.getTipo() == INTEIRA)	
						config.setLowerBound(atoi(optarg));
					else if(config.getTipo() == REAL)
						config.setLowerBound(stod(optarg));
				}
				break;
            case 'u':
                if(optarg){
					if(config.getTipo() == INTEIRA)	
						config.setUpperBound(atoi(optarg));
					else if(config.getTipo() == REAL)
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
			case 'g':
				if(optarg) config.setGenerations(atoi(optarg));
				break;
			case 'e':
				if(optarg) config.setNumElitistas(atoi(optarg));
				break;
			case 'd':
				if(optarg) config.setCrossoverType(atoi(optarg));
				break;
			case 'c':
				if(optarg) config.setProbCrossover(stod(optarg));
				break;
			case 'm':
				if(optarg) config.setProbMutacao(stod(optarg));
				break;
			// case 'o':
			// 	if(optarg) config.setArquivoDestino(optarg);
			// 	config.setSaidaArquivo(true);
			// 	break;
			case 'a':
				if(optarg) config.setAlpha(stod(optarg));
				break;
			case 'b':
				if(optarg) config.setB(stod(optarg));
				break;
			case 'r':
				if(optarg) config.setTipoRelatorio(atoi(optarg));
				break;
			case 'E':
				if(optarg) config.setNumExecucoes(atoi(optarg));
				break;

        }
    }

	//Limpar o arquivo
	ofstream temp;
	temp.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ifstream::out | std::ifstream::trunc);
	temp.close();

	temp.open("./testes/" + config.getArquivoDestino() + "-geracoes", std::ifstream::out | std::ifstream::trunc);
	temp << config.getNumExecucoes() << std::endl;
	temp << config.getGenerations() << std::endl;
	temp.close();

	for(int i = 0; i < config.getNumExecucoes(); i++){
		config.setExecucao(i);
		runGeneticAlgorithm(config);
	}

    cout << "Resultados das execuções em ./testes/" + config.getArquivoDestino() + "-resultados" << std::endl;

	if(config.getTipoRelatorio() != 0){
		string grafico = "python3 grafico.py " + config.getArquivoDestino() + " " + to_string(config.getNumExecucoes()); 
		system(grafico.c_str());

		cout << "Para gerar o gráfico manualmente: python3 grafico.py " + config.getArquivoDestino() + " " << config.getNumExecucoes() << endl;
	}


	return 0;
}


void runGeneticAlgorithm(Config &c){
	if(c.getTipo() == BINARIA){
		GeneticAlgorithm<bool> *ga = new GeneticAlgorithm<bool>(c);
		ga->run();
		delete ga;
	}
	else if(c.getTipo() == INTEIRA){
		GeneticAlgorithm<int> *ga = new GeneticAlgorithm<int>(c);
		ga->run();
		delete ga;
	}
	else if(c.getTipo() == PERMUTADA){
		GeneticAlgorithm<int_permut_t> *ga = new GeneticAlgorithm<int_permut_t>(c);
		ga->run();
		delete ga;	
	}
	else if(c.getTipo() == REAL){
		GeneticAlgorithm<double> *ga = new GeneticAlgorithm<double>(c);
		ga->run();
		delete ga;	
	}
}
