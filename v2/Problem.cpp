#include <cmath>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <set>
#include "util.hpp"


//Permutação e inteiro não são diferenciado aqui, mas poderiam ser, com vontade o suficiente

template<> inline
Score_Restricao Problem<int_permut_t>::nQueens(std::vector<std::vector<int_permut_t> > &popul, Config &config){
	//Por enquanto vamos quantificar apenas uma colisão por rainha, mas é possivel quantificar todas elas
	// int max_colisoes = popul.size(); //Todas as rainhas colidem-se

	std::vector<double> valores(config.getPopSize());
	std::vector<bool> restricao(config.getPopSize(), false);

	// double mais_colisoes = config.getNumVars()+2*config.getNumVars()*(config.getNumVars()-1);
	double mais_colisoes = config.getNumVars();


	// #pragma omp parallel for shared(valores)
	// for(int k = 0; k < config.getPopSize(); k++){
	// 	std::vector<bool> colided(config.getNumVars(), false);	
	// 	int colisoes = 0;
	// 	for(int i = 0; i < config.getNumVars()-1; i++){
	// 		for(int j = i + 1; j < config.getNumVars(); j++){
	// 			if(std::abs(i - j) == std::abs(popul[k][i] - popul[k][j]) and not colided[j]){
	// 				colisoes++;
	// 				colided[j] = true;
	// 			}
	// 			// else if(std::abs(i - j) == std::abs(popul[k][i] - popul[k][j])){
	// 			// 	colisoes+=2;
	// 			// }
	// 		}
	// 	}
	// 	valores[k] = 1.0 - colisoes/mais_colisoes;

	// }

	#pragma omp parallel for shared(valores)
	for(int k = 0; k < config.getPopSize(); k++){
		std::vector<bool> colided(config.getNumVars(), false);
		for(int i = 0; i < config.getNumVars()-1; i++){
			for(int j = i + 1; j < config.getNumVars(); j++){
				if(std::abs(i - j) == std::abs(popul[k][i] - popul[k][j])){
					// colisoes++;
					colided[i] = true;
					colided[j] = true;
				}
				// else if(std::abs(i - j) == std::abs(popul[k][i] - popul[k][j])){
				// 	colisoes+=2;
				// }
			}
		}
		int nao_colidiu = 0;
		for(int i = 0; i < config.getNumVars(); i++){
			if(!colided[i]) nao_colidiu++;
		}
		valores[k] = ((double)nao_colidiu)/config.getNumVars();
	
	}

	// double mais_colisoes = *std::max_element(valores.begin(), valores.end());
	// for(auto i : valores)
	// 	std::cout << i << std::endl;

	Score_Restricao retorno;
	retorno.scores = valores;
	retorno.restritos = restricao;


	return retorno;
}

template<> inline
void Problem<int_permut_t>::nQueens_decoder(std::vector<int_permut_t> &indiv, Config &config){
    std::ofstream resultados;
	resultados.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ofstream::out | std::ofstream::app);

	resultados << "Posições escolhidas:  ";
	for(int i = 0; i < config.getNumVars(); i++){
		// printf("(%d, %d)  ", i, indiv[i].value);
		resultados << "(" << i << ", " << indiv[i].value << ") ";
	}
	resultados << std::endl <<std::endl;

	if(config.getNumVars() <= 20){
		resultados << "Tabuleiro (1 = rainhas, 0 = vazio)" <<std::endl;
		for(int i = 0; i < config.getNumVars(); i++){
			for(int j = 0; j < config.getNumVars(); j++){
				if(j == indiv[i]) resultados <<  std::setw(2) << "1";
				else resultados << std::setw(2) << "0";
			}
			resultados << std::endl;
		}
		resultados << std::endl;
	}

	resultados << std::endl;


	resultados.close();
}

template<> inline
Score_Restricao Problem<int_permut_t>::nQueens_weight(std::vector<std::vector<int_permut_t>> &popul, Config &config){	
	std::vector<double> valores(config.getPopSize());
	std::vector<bool> restricao(config.getPopSize(), false);

	// double mais_colisoes = config.getNumVars()+2*config.getNumVars()*(config.getNumVars()-1);
	double maior_peso = 0.0;
	if(config.getNumVars() % 2 == 0){
		for (int j = 0; j < config.getNumVars(); j++){
			maior_peso += std::sqrt((config.getNumVars()-1)*config.getNumVars() + (j+1));
		}
	}
	else{
		for (int j = 0; j < config.getNumVars(); j++){
			maior_peso += std::sqrt((config.getNumVars()-2) * config.getNumVars() + (j + 1));
		}
	}

	#pragma omp parallel for shared(valores)
	for(int k = 0; k < config.getPopSize(); k++){
		double valor_colisoes, valor_peso;
		std::vector<bool> colided(config.getNumVars(), false);
		for(int i = 0; i < config.getNumVars()-1; i++){
			for(int j = i + 1; j < config.getNumVars(); j++){
				if(std::abs(i - j) == std::abs(popul[k][i] - popul[k][j])){
					// colisoes++;
					colided[i] = true;
					colided[j] = true;
				}
				// else if(std::abs(i - j) == std::abs(popul[k][i] - popul[k][j])){
				// 	colisoes+=2;
				// }
			}
		}
		int colisoes = 0;
		for(int i = 0; i < config.getNumVars(); i++){
			if(colided[i]) colisoes++;
		}
		// valor_colisoes = 1.0 - ((double)colisoes) / config.getNumVars();
		valor_colisoes = ((double)colisoes) / config.getNumVars();

		double valor = 0.0;
		for(int i = 0; i < config.getNumVars(); i++){
			if(i % 2 == 0){ //sqrt
				valor += std::sqrt(i * config.getNumVars() + (popul[k][i] + 1));
			}
			else{ //log10
				valor += std::log10(i * config.getNumVars() + (popul[k][i] + 1));
			}
		}
		valor_peso = valor/maior_peso;

		double h = valor_colisoes*valor_peso; //Perda proporcional ao número de colisões
		if(colisoes != 0)
			restricao[k] = true; // Seta que o indivíduo violou restrição

		
		// valores[k] = valor_colisoes*0.5 + 0.5*valor_peso;
		valores[k] = valor_peso - h;
		
	}

	// for(int i = 0; i < config.getPopSize(); i++){
	// 	for(int j = 0; j < config.getNumVars(); j++){
	// 		std::cout << popul[i][j] << " ";
	// 	}
	// 	std::cout <<std::endl;
	// }

	// double mais_colisoes = *std::max_element(valores.begin(), valores.end());
	// for(auto i : valores)
	// 	std::cout << i << std::endl;

	Score_Restricao retorno;
	retorno.scores = valores;
	retorno.restritos = restricao;

	return retorno;
}

template<> inline
void Problem<int_permut_t>::nQueens_weight_decoder(std::vector<int_permut_t> &indiv, Config &config){
	std::ofstream resultados;
	resultados.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ofstream::out | std::ofstream::app);

	double valor_colisoes;
	double valor_peso;
	
	std::vector<bool> restricao(config.getPopSize(), false);


	double mais_colisoes = config.getNumVars();
	double maior_peso = 0.0;
	if(config.getNumVars() % 2 == 0){
		for (int j = 0; j < config.getNumVars(); j++){
			maior_peso += std::sqrt((config.getNumVars()-1)*config.getNumVars() + (j+1));
		}
	}
	else{
		for (int j = 0; j < config.getNumVars(); j++){
			maior_peso += std::sqrt((config.getNumVars()-2) * config.getNumVars() + (j + 1));
		}
	}


	std::vector<bool> colided(config.getNumVars(), false);
	for(int i = 0; i < config.getNumVars()-1; i++){
		for(int j = i + 1; j < config.getNumVars(); j++){
			if(std::abs(i - j) == std::abs(indiv[i] - indiv[j])){
				// colisoes++;
				colided[i] = true;
				colided[j] = true;
			}
			// else if(std::abs(i - j) == std::abs(indiv[i] - indiv[j])){
			// 	colisoes+=2;
			// }
		}
	}
	int colisoes = 0;
	for(int i = 0; i < config.getNumVars(); i++){
		if(colided[i]) colisoes++;
	}
	// valor_colisoes = 1.0 - colisoes / mais_colisoes;

	double valor = 0.0;
	for(int i = 0; i < config.getNumVars(); i++){
		if(i % 2 == 0){ //sqrt
			valor += std::sqrt(i * config.getNumVars() + (indiv[i] + 1));
		}
		else{ //log10
			valor += std::log10(i * config.getNumVars() + (indiv[i] + 1));
		}
	}
	resultados << "Valor: " << valor << std::endl;
	// valor_peso = valor/maior_peso;

	resultados << "Colisoes: " << colisoes << std::endl;
	resultados << std::endl;



	resultados << "Posições escolhidas:  ";
	for (int i = 0; i < config.getNumVars(); i++)
	{
		// printf("(%d, %d)  ", i, indiv[i].value);
		resultados << "(" << i << ", " << indiv[i].value << ") ";
	}
	resultados << std::endl
			   << std::endl;

	if (config.getNumVars() <= 20)
	{
		resultados << "Tabuleiro (1 = rainhas, 0 = vazio)" << std::endl;
		for (int i = 0; i < config.getNumVars(); i++)
		{
			for (int j = 0; j < config.getNumVars(); j++)
			{
				if (j == indiv[i])
					resultados << std::setw(2) << "1";
				else
					resultados << std::setw(2) << "0";
			}
			resultados << std::endl;
		}
		resultados << std::endl;
	}

	resultados << std::endl;

	resultados.close();
}

template<> inline
Score_Restricao Problem<bool>::slide_max(vvb &popul, Config &config){
	std::vector<double> valores(config.getPopSize());
	std::vector<bool> restricao(config.getPopSize(), false);


	double offset = (2.0 - (-2.0))/std::pow(2, popul[0].size());

	#pragma omp parallel for shared(valores)
	for(int i = 0; i < config.getPopSize(); i++){
		//Transformar o vector<bool> em um valor uint
		unsigned long long int b = 0;
		int sign = 1;
		for(int j = config.getNumVars() - 1; j >= 0; j--){
			b += popul[i][j]*sign;
			sign *= 2;
		}
		double x = -2 + b*offset;


		double fx = 5 + std::cos(20.0*x) - std::abs(x)/2.0 + pow(x, 3.0)/4.0;

		valores[i] = fx;
	}

	double maior = *std::max_element(valores.begin(), valores.end());


	// for(int i = 0; i < config.getPopSize(); i++){
	// 	valores[i] /= maior;
	// }
	
	Score_Restricao retorno;
	retorno.scores = valores;
	retorno.restritos = restricao;


	return retorno;
}

template<> inline
void Problem<bool>::slide_max_decoder(std::vector<bool> &indiv, Config &config){
    std::ofstream resultados;
	resultados.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ofstream::out | std::ofstream::app);
	
	double offset = (2.0 - (-2.0))/std::pow(2, config.getNumVars());
	
	unsigned long long int b = 0;
	int sign = 1;
	for(int j = config.getNumVars() - 1; j >= 0; j--){
		b += indiv[j]*sign;
		sign *= 2;
	}
	double x = -2 + b*offset;

	double fx = std::cos(20.0*x) - std::abs(x)/2.0 + pow(x, 3.0)/4.0;

	resultados << "x = " << x << std::endl;
	resultados << "f(x) = " << fx << std::endl;

	resultados << std::endl;

	resultados.close();
}

template<> inline
Score_Restricao Problem<bool>::fabrica_radios(vvb &popul, Config &config){
	std::vector<double> valores(config.getPopSize(), 0); //Depois do tamanho da pop, tem 1.0 se o indivíduo violou alguma restrição
	std::vector<bool> restricao(config.getPopSize(), false);

	#pragma omp parallel for shared(valores, restricao)
	for(int i = 0; i < config.getPopSize(); i++){
		unsigned long long int b_st = 0, b_lx = 0;
		int sign = 1;

		//Decodifica variáveis
		for(int j = 4; j >= 0; j--){
			b_st += popul[i][j+5]*sign;
			b_lx += popul[i][j]*sign;
			sign *= 2;
		}

		int st = (1.0 * b_st / 31.0) * 24.0;
		int lx = (1.0 * b_lx / 31.0) * 16.0;
		
		//Restrição (st + 2lx <= 40)
		double h = std::max(0.0, (st + 2.0*lx - 40.0)/16.0);
		if(h != 0)
			restricao[i] = true; // Seta que o indivíduo violou restrição

		//Função fitness (função objetivo/valor_máximo - restrição)
		valores[i] = (30.0*st + 40.0*lx)/1360.0 - h;
	}

	Score_Restricao retorno;
	retorno.scores = valores;
	retorno.restritos = restricao;


	return retorno;
}

template<> inline
void Problem<bool>::fabrica_radios_decoder(std::vector<bool> &indiv, Config &config){
    std::ofstream resultados;
	resultados.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ofstream::out | std::ofstream::app);

	unsigned long long int b_st = 0, b_lx = 0;
	int sign = 1;

	//Decodifica variáveis
	for(int j = 4; j >= 0; j--){
		b_st += indiv[j+5]*sign;
		b_lx += indiv[j]*sign;
		sign *= 2;
	}

	int st = (1.0 * b_st / 31.0) * 24.0;
	int lx = (1.0 * b_lx / 31.0) * 16.0;

	double lucro = st*30.0 + lx*40.0;

	resultados << "Trabalhadores Standard =  " << st << std::endl;
	resultados << "Trabalhadores Luxo =  " << lx*2 << std::endl;
	resultados << "Lucro =  R$" << lucro << std::endl;

	resultados << std::endl;


	resultados.close();
}

template<> inline
Score_Restricao Problem<bool>::cartas_prova(vvb &popul, Config &config){
	std::vector<double> valores(config.getPopSize(), 0); //Depois do tamanho da pop, tem 1.0 se o indivíduo violou alguma restrição
	std::vector<bool> restricao(config.getPopSize(), false);

	#pragma omp parallel for shared(valores, restricao)
	for(int i = 0; i < config.getPopSize(); i++){
		long int soma=0, mult=1;
		for(int j = 0; j < config.getNumVars(); j++){
			if(!popul[i][j]){ //Soma
				soma += j;
			}
			else{ //Multiplicação
				mult*=j;
			}
		}
		valores[i] = 1.0/(std::abs(soma - 36.0) + std::abs(mult - 360.0) + 1.0);
	}

	Score_Restricao retorno;
	retorno.scores = valores;
	retorno.restritos = restricao;


	return retorno;
}

template<> inline
void Problem<bool>::cartas_prova_decoder(std::vector<bool> &indiv, Config &config){
    std::ofstream resultados;
	resultados.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ofstream::out | std::ofstream::app);

	long int soma=0, mult=1;
	for(int j = 0; j < config.getNumVars(); j++){
		if(!indiv[j]){ //Soma
			soma += j;
		}
		else{ //Multiplicação
			mult*=j;
		}
	}

	resultados << "Soma = " << soma << std::endl;
	resultados << "Multiplicação = " << mult << std::endl;
	resultados << std::endl;

	resultados.close();
}

template<> inline
Score_Restricao Problem<int>::labirinto(std::vector<std::vector<int> > &popul, Config &config){
	std::vector<double> valores(config.getPopSize(), 0); //Depois do tamanho da pop, tem 1.0 se o indivíduo violou alguma restrição
	std::vector<bool> restricao(config.getPopSize(), false);

	std::vector<std::vector<int> > lab(30, std::vector<int>(25));
	
	lab = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,3,1,1,0,0},
		{0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,1,0},
		{0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0},
		{0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,0},
		{0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0},
		{0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,0},
		{0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,0,1,0},
		{0,2,1,1,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0},
		{0,1,0,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0},
		{0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0},
		{0,1,0,0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0},
		{0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0},
		{0,1,1,0,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,1,0,0,1,0},
		{0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0},
		{0,0,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,0,0},
		{0,1,1,0,0,0,1,1,0,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0},
		{0,0,0,0,1,0,0,0,0,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0},
		{0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0},
		{0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0},
		{0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0},
		{0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0},
		{0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0},
		{0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,0},
		{0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0},
		{0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	//x = linhas, y = colunas
	// int x_final = 1, y_final = 20;
	std::pair<int, int> destino(1, 20);
	std::pair<int, int> inicio(10, 1);
	// double maior_distancia = 142;
	#pragma omp parallel for shared(valores, restricao, popul, config) schedule(dynamic)
	for(int k = 0; k < config.getPopSize(); k++){
		std::set<std::pair<int, int> > ja_foi;
		std::vector<int> colisao;
		// int x_atual = 10, y_atual = 1;
		std::pair<int, int> atual(10, 1);
		int movimentos = 0;
		int movimentos_bons = 0;
		int repeticoes = 0; //passou pela mesma posição
		int dist_total = 0.0;
		bool colidiu = false;
		for(int v = 0; v < config.getNumVars(); v++){
			ja_foi.insert(atual);
			switch(popul[k][v]){
				case 0: //cima
					if(lab[atual.first-1][atual.second] != 0){
						atual.first--;
						if(ja_foi.find(atual) != ja_foi.end()) repeticoes++;
						else movimentos_bons++;
						break;
					}
					repeticoes++;
					colidiu = true;
					colisao.push_back(v);
					break;					
				case 1: //direita
					if(lab[atual.first][atual.second+1] != 0){
						atual.second++;
						if(ja_foi.find(atual) != ja_foi.end()) repeticoes++;
						else movimentos_bons++;
						break;
					}
					repeticoes++;
					colidiu = true;
					colisao.push_back(v);
					break;
				case 2: //baixo
					if(lab[atual.first+1][atual.second] != 0){
						atual.first++;
						if(ja_foi.find(atual) != ja_foi.end()) repeticoes++;
						else movimentos_bons++;						
						break;
					}
					repeticoes++;
					colidiu = true;
					colisao.push_back(v);					
					break;
				case 3: //esquerda
					if(lab[atual.first][atual.second-1] != 0){
						atual.second--;
						if(ja_foi.find(atual) != ja_foi.end()) repeticoes++;
						else movimentos_bons++;
						break;
					}
					repeticoes++;
					colidiu = true;
					colisao.push_back(v);
					break;

			}
			double dist_manhattan;
			// if(!colidiu){
				dist_manhattan =  std::abs(destino.first - atual.first) + std::abs(destino.second - atual.second);
				dist_total += dist_manhattan;
				movimentos ++;
			// }

			if(atual.first == destino.first and atual.second == destino.second){
				break;
			}	
		}
		for(int i = colisao.size()-1; i >= 0; i--){
			for(int j = colisao[i]; j < config.getNumVars()-1; j++){
				popul[k][j] = popul[k][j+1];
			}
			// popul[k][config.getNumVars()-1] = getRandInt(std::get<int>(config.getLowerBound()), std::get<int>(config.getUpperBound()));
		}


		double temp =1.0 - dist_total/(config.getNumVars()*55.0);
		// double temp = 1.0 - (std::abs(destino.first - atual.first) + std::abs(destino.second - atual.second))/55.0;
		// std::cout << repeticoes << std::endl;
		// valores[k] = 0.90*((movimentos_bons/(double)movimentos)) + 0.10*(1.0 - dist_total/(config.getNumVars()*55.0));
		valores[k] = temp - temp*(std::cbrt(repeticoes/(double)movimentos));
		// valores[k] = (config.getNumVars()*55.0) - dist_total;


		// if(dist_manhattan == 0){
		// 	std::cout << "Cheguei!\n";
		// 	// valores[k] *= 2;
		// }
	}


	Score_Restricao retorno;
	retorno.scores = valores;
	retorno.restritos = restricao;

	return retorno;
}

template<> inline
void Problem<int>::labirinto_decoder(std::vector<int> &indiv, Config &config){
	std::ofstream resultados;
	resultados.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ofstream::out | std::ofstream::app);

	std::vector<std::vector<int> > lab(30, std::vector<int>(25));
	
	lab = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,3,1,1,0,0},
		{0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,1,0},
		{0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0},
		{0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,0},
		{0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0},
		{0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,0},
		{0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,0,1,0},
		{0,2,1,1,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0},
		{0,1,0,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0},
		{0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0},
		{0,1,0,0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0},
		{0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0},
		{0,1,1,0,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,1,0,0,1,0},
		{0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0},
		{0,0,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,0,0},
		{0,1,1,0,0,0,1,1,0,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0},
		{0,0,0,0,1,0,0,0,0,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0},
		{0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0},
		{0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0},
		{0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0},
		{0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0},
		{0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0},
		{0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,0},
		{0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0},
		{0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};


	std::pair<int, int> destino(1, 20);
	// double maior_distancia = 142;
	std::set<std::pair<int, int>> ja_foi;
	// int x_atual = 10, y_atual = 1;
	std::pair<int, int> atual(10, 1);
	int movimentos = 0;
	int movimentos_bons = 0;
	int repeticoes = 0; //passou pela mesma posição
	int dist_total = 0.0;
	for(int v = 0; v < config.getNumVars(); v++){
		ja_foi.insert(atual);
		switch(indiv[v]){
			case 0: //cima
				if(lab[atual.first-1][atual.second] != 0){
					atual.first--;
					if(ja_foi.find(atual) != ja_foi.end()) repeticoes++;
					else movimentos_bons++;
					break;
				}
				// repeticoes++;
				break;					
			case 1: //direita
				if(lab[atual.first][atual.second+1] != 0){
					atual.second++;
					if(ja_foi.find(atual) != ja_foi.end()) repeticoes++;
					else movimentos_bons++;
					break;
				}
				// repeticoes++;
				break;
			case 2: //baixo
				if(lab[atual.first+1][atual.second] != 0){
					atual.first++;
					if(ja_foi.find(atual) != ja_foi.end()) repeticoes++;
					else movimentos_bons++;						
					break;
				}
				// repeticoes++;
				break;
			case 3: //esquerda
				if(lab[atual.first][atual.second-1] != 0){
					atual.second--;
					if(ja_foi.find(atual) != ja_foi.end()) repeticoes++;
					else movimentos_bons++;
					break;
				}
				// repeticoes++;
				break;
		}
		double dist_manhattan = std::abs(destino.first - atual.first) + std::abs(destino.second - atual.second);

		dist_total += dist_manhattan;
		movimentos ++;
		if(atual.first == destino.first and atual.second == destino.second){
			break;
		}	
	}

	double dist_manhattan = std::abs(destino.first - atual.first) + std::abs(destino.second - atual.second);


	resultados << "Posição final: (" << atual.first << ", " << atual.second << ")\n";
	resultados << "Movimentos: " << movimentos << std::endl;
	resultados << "Repeticoes: " << repeticoes << std::endl;
	resultados << "Movimentos Bons: " << movimentos_bons << std::endl;
	resultados << "Distância Manhattan: " << dist_manhattan << std::endl;
	resultados << "Distância Total:" << dist_total << std::endl;
	resultados << std::endl;

	resultados.close();
}

//torneio d=2 w=2 m=0.01
template<> inline
Score_Restricao Problem<double>::michalewicz(std::vector<std::vector<double> > &popul, Config &config){
	std::vector<double> valores(config.getPopSize(), 0); //Depois do tamanho da pop, tem 1.0 se o indivíduo violou alguma restrição
	std::vector<bool> restricao(config.getPopSize(), false);
	
	#pragma omp parallel for shared(valores, restricao, popul, config) schedule(dynamic)
	for(int k = 0; k < config.getPopSize(); k++){
		double sum = 0.0;
		for(int i = 0; i < config.getNumVars(); i++){
			sum += std::sin(popul[k][i])*std::pow(std::sin((i+1)*(popul[k][i]*popul[k][i])/M_PI), 20.0);
		}

		valores[k] = sum;
	}

	Score_Restricao retorno;
	retorno.scores = valores;
	retorno.restritos = restricao;

	return retorno;
}

template<> inline
void Problem<double>::michalewicz_decoder(std::vector<double> &indiv, Config &config){
	std::ofstream resultados;
	resultados.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ofstream::out | std::ofstream::app);

	double sum = 0.0;
	for(int i = 0; i < config.getNumVars(); i++){
		sum += std::sin(indiv[i])*std::pow(std::sin((i+1)*(indiv[i]*indiv[i])/M_PI), 20);
	}

	resultados << "f(xi) = " << sum << std::endl;

	resultados.close();

}

//torneio d=2 w=1 m=0.01
template<> inline
Score_Restricao Problem<double>::keane(std::vector<std::vector<double> > &popul, Config &config){
	std::vector<double> valores(config.getPopSize(), 0); //Depois do tamanho da pop, tem 1.0 se o indivíduo violou alguma restrição
	std::vector<bool> restricao(config.getPopSize(), false);
	
	#pragma omp parallel for shared(valores, restricao, popul, config) schedule(dynamic)
	for(int k = 0; k < config.getPopSize(); k++){
		// std::sort(popul[k].begin(), popul[k].end(), std::greater<double>());
		double sum1 = 0.0, sum2 = 0.0, mult = 1.0, 
				sum_xi = 0.0, mult_xi = 1.0;
		for(int i = 0; i < config.getNumVars(); i++){
			double temp = std::cos(popul[k][i]);
			sum1 += temp*temp*temp*temp;
			mult *= temp*temp;
			sum2 += (i+1.0)*popul[k][i]*popul[k][i];

			sum_xi += popul[k][i];
			mult_xi *= popul[k][i];
		}
		double fx = std::abs(sum1 - 2.0*mult)/std::sqrt(sum2);

		// mult_xi > 0.75
		//mult_xi - 0.75 > 0
		// <0 if mult_xi > 0.75
		double r1 = 0.0, r2 = 0.0;
		if(mult_xi < 0.75){ //Perto de 1 = penalização é menor
			r1 = (0.75 - mult_xi)/0.75;
		}
		if(sum_xi > 7.5*config.getNumVars()){
			r2 = (sum_xi - 7.5*config.getNumVars())/(500.0 - 7.5*config.getNumVars());
		}
		// double h1 = 1.0 - std::max(0.0, (-mult_xi + 0.75)/10000000000.75);
		// double h2 = 1.0 - std::max(0.0, (sum_xi - 7.5*config.getNumVars())/(100.0 - 7.5*config.getNumVars()));
		if(r1 > 0.0 or r2 > 0.0){
			restricao[k] = true;
		}

		// if(mult_xi <= 0.75) valores[k] = 0.0;
		valores[k] = fx - 0.5*fx*r1 - 0.5*fx*r2; // Função objetivo + penalizações
	}

	Score_Restricao retorno;
	retorno.scores = valores;
	retorno.restritos = restricao;

	return retorno;
}

template<> inline
void Problem<double>::keane_decoder(std::vector<double> &indiv, Config &config){
	std::ofstream resultados;
	resultados.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ofstream::out | std::ofstream::app);

	// std::sort(indiv.begin(), indiv.end(), std::greater<double>());
	double sum1 = 0.0, sum2 = 0.0, mult = 1.0, 
			sum_xi = 0.0, mult_xi = 1.0;
	for(int i = 0; i < config.getNumVars(); i++){
		double temp = std::cos(indiv[i]);
		sum1 += temp*temp*temp*temp;
		mult *= temp*temp;
		sum2 += (i+1)*indiv[i]*indiv[i];

		sum_xi += indiv[i];
		mult_xi *= indiv[i];
	}
	double fx = std::abs(sum1 - 2.0*mult)/std::sqrt(sum2);

	double r1 = 0.0, r2 = 0.0;
	if(mult_xi < 0.75){ //Perto de 1 = penalização é menor
		r1 = (0.75 - mult_xi)/0.75;
	}
	if(sum_xi > 7.5*config.getNumVars()){
		r2 = (sum_xi - 7.5*config.getNumVars())/(500.0 - 7.5*config.getNumVars());
	}

	resultados << "f(xi) = " << fx << std::endl;
	resultados << "Restricao 1 (Mult) = " << r1 << std::endl;
	resultados << "Restricao 2 (Soma) = " << r2 << std::endl;
	resultados << std::endl;

	resultados.close();

}

template<> inline
Problem<bool>::Problem(){
	funcao.insert(std::pair<std::string, std::function<Score_Restricao(vvb&, Config&)> >("slide_max", slide_max));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<bool>&, Config&)> >("slide_max", slide_max_decoder));

	funcao.insert(std::pair<std::string, std::function<Score_Restricao(vvb&, Config&)> >("fabrica_radios", fabrica_radios));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<bool>&, Config&)> >("fabrica_radios", fabrica_radios_decoder));

	funcao.insert(std::pair<std::string, std::function<Score_Restricao(vvb&, Config&)> >("cartas_prova", cartas_prova));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<bool>&, Config&)> >("cartas_prova", cartas_prova_decoder));
}

template<> inline
Problem<int>::Problem(){
	funcao.insert(std::pair<std::string, std::function<Score_Restricao(std::vector<std::vector<int>> &, Config &)>>("labirinto", labirinto));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<int> &, Config &)>>("labirinto", labirinto_decoder));
}

template<> inline
Problem<int_permut_t>::Problem(){
    funcao.insert(std::pair<std::string, std::function<Score_Restricao(std::vector<std::vector<int_permut_t> >&, Config&)> >("nqueens", nQueens));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<int_permut_t>&, Config&)> >("nqueens", nQueens_decoder));

	funcao.insert(std::pair<std::string, std::function<Score_Restricao(std::vector<std::vector<int_permut_t>> &, Config &)>>("nqueens_w", nQueens_weight));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<int_permut_t> &, Config &)>>("nqueens_w", nQueens_weight_decoder));
}

template<> inline
Problem<double>::Problem(){
	funcao.insert(std::pair<std::string, std::function<Score_Restricao(std::vector<std::vector<double>> &, Config &)>>("michal", michalewicz));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<double> &, Config &)>>("michal", michalewicz_decoder));

	funcao.insert(std::pair<std::string, std::function<Score_Restricao(std::vector<std::vector<double>> &, Config &)>>("keane", keane));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<double> &, Config &)>>("keane", keane_decoder));
}


template<typename T>
std::function<Score_Restricao(std::vector<std::vector<T> >&, Config&)> Problem<T>::getFuncao(std::string nome){
    return funcao[nome];

}

template<typename T>
std::function<void(std::vector<T>&, Config&)> Problem<T>::getDecoder(std::string nome){
	return decoder[nome];
}



// b_func Problem::get_bFunc(std::string nome){
//     return b_funcao[nome];

// }

// i_func Problem::get_iFunc(std::string nome){
//     return i_funcao[nome];
// }

// d_func Problem::get_dFunc(std::string nome){
//     return d_funcao[nome];
// }
