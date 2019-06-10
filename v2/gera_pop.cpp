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
	printf("[-E num_execucoes]\n");
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
	printf("[-C tipo_ajuste_diversidade]\n");
	printf("[-w tipo_crowding]\n");	
	printf("[-f competidores_standard_crowding]\n");
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
	while( ( c = getopt (argc, (char**) argv, "u:l:k:p:t:s:z:g:e:d:c:m:o:a:b:r:E:C:G:w:f:") ) != -1 ) 
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
			case 'C':
				if(optarg) config.setConstC(stod(optarg));
				break;
			case 'G':
				if(optarg) config.setGenerationGap(stod(optarg));
					break;
			case 'w':
				if(optarg) config.setCrowdingType(atoi(optarg));
					break;
			case 'f':
				if(optarg) config.setStandardCrowdingSize(atoi(optarg));
					break;

        }
    }


	//Limpar o arquivo
	ofstream temp;
	temp.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ifstream::out | std::ifstream::trunc);
	temp << "Configuração:\n";
	temp << "tam_pop = " << config.getPopSize() << std::endl; 
	temp << "num_geracoes = " << config.getGenerations() << std::endl; 
	temp << "num_elitistas = " << config.getNumElitistas() << std::endl; 
	temp << "prob_crossover = " << config.getProbCrossover() << std::endl; 
	temp << "prob_mutacao = " << config.getProbMutacao() << std::endl; 
	temp << "metodo_selecao = " << config.getSelectionMethod() << std::endl; 
	temp << "tipo_crossover = " << config.getCrossoverType() << std::endl; 
	temp << "tam_torneio/vizinhanca = " << config.getK() << std::endl; 
	temp << "tipo_selecao_vizinhanca = " << config.getTipoSelec() << std::endl; 
	temp << "prob_melhor_torneio = " << config.getProb() << std::endl; 
	temp << "tam_pop = " << config.getPopSize() << std::endl; 
	temp << "diversidade = " << config.getConstC() << std::endl; 
	temp << "alpha_blx = " << config.getAlpha() << std::endl; 
	temp << "tunelamento_michalewicz = " << config.getB() << std::endl;
	temp << "tipo_crowding = " << config.getCrowdingType() << std::endl;
	temp << "competidores_standard_crowding = " << config.getStandardCrowdingSize() << std::endl;
	temp << std::endl << std::endl; 

	
	temp.close();
	

	temp.open("./testes/" + config.getArquivoDestino() + "-geracoes", std::ifstream::out | std::ifstream::trunc);
	temp << config.getNumExecucoes() << std::endl;
	temp << config.getGenerations() << std::endl;
	temp.close();

	temp.open("./testes/" + config.getArquivoDestino() + "-diversidades", std::ifstream::out | std::ifstream::trunc);
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
		int a = system(grafico.c_str());

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
