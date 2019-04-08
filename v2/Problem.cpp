#include <cmath>
#include <iostream>
#include <omp.h>


//Permutação e inteiro não são diferenciado aqui, mas poderiam ser, com vontade o suficiente

template<> inline
Score_Restricao Problem<int>::nQueens(vvi &popul, Config &config){
	//Por enquanto vamos quantificar apenas uma colisão por rainha, mas é possivel quantificar todas elas
	// int max_colisoes = popul.size(); //Todas as rainhas colidem-se
	std::vector<double> valores(config.getPopSize());
	std::vector<bool> restricao(config.getPopSize(), false);


	#pragma omp parallel for shared(valores)
	for(int k = 0; k < config.getPopSize(); k++){
		std::vector<bool> colided(config.getPopSize(), false);	
		int colisoes = 0;
		for(int i = 0; i < config.getNumVars()-1; i++){
			for(int j = i + 1; j < config.getNumVars(); j++){
				if(std::abs(i - j) == std::abs(popul[k][i] - popul[k][j]) and not colided[j]){
					colisoes++;
					colided[j] = true;
				}
			}
		}
		valores[k] = colisoes;
	}

	// double mais_colisoes = *std::max_element(valores.begin(), valores.end());
	double mais_colisoes = popul[0].size();

	for(int i = 0; i < valores.size(); i++){
		// std::cout << i << "  " << valores[i] << "  " << mais_colisoes << std::endl;
		valores[i] = 1.0 - valores[i]/mais_colisoes;

	}

	Score_Restricao retorno;
	retorno.scores = valores;
	retorno.restritos = restricao;


	return retorno;
}

template<> inline
void Problem<int>::nQueens_decoder(std::vector<int> &indiv, Config &config){
	std::cout << "Posições escolhidas:  ";
	for(int i = 0; i < config.getNumVars(); i++){
		printf("(%d, %d)  ", i, indiv[i]);
	}
	std::cout << std::endl <<std::endl;

	std::cout << "Tabuleiro (1 = rainhas, 0 = vazio)" <<std::endl;
	for(int i = 0; i < config.getNumVars(); i++){
		for(int j = 0; j < config.getNumVars(); j++){
			if(j == indiv[i]) std::cout <<  std::setw(2) << "1";
			else std::cout << std::setw(2) << "0";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
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


		double fx = 5 + cos(20*x) - abs(x)/2 + pow(x, 3)/4;

		valores[i] = fx;
	}

	double maior = *std::max_element(valores.begin(), valores.end());

	for(int i = 0; i < config.getPopSize(); i++){
		valores[i] /= maior;
	}
	
	Score_Restricao retorno;
	retorno.scores = valores;
	retorno.restritos = restricao;


	return retorno;
}

template<> inline
void Problem<bool>::slide_max_decoder(std::vector<bool> &indiv, Config &config){
	double offset = (2.0 - (-2.0))/std::pow(2, config.getNumVars());
	
	unsigned long long int b = 0;
	int sign = 1;
	for(int j = config.getNumVars() - 1; j >= 0; j--){
		b += indiv[j]*sign;
		sign *= 2;
	}
	double x = -2 + b*offset;

	double fx = cos(20.0*x) - abs(x)/2.0 + pow(x, 3)/4.0;

	std::cout << "x = " << x << std::endl;
	std::cout << "f(x) = " << fx << std::endl;
}

template<> inline
Score_Restricao Problem<bool>::fabrica_radios(vvb &popul, Config &config){
	std::vector<double> valores(config.getPopSize(), 0); //Depois do tamanho da pop, tem 1.0 se o indivíduo violou alguma restrição
	std::vector<bool> restricao(config.getPopSize(), false);


	double offset_st = (24.0)/std::pow(2, 5);
	double offset_lx = (16.0)/std::pow(2, 5);
	// int optimizer_range = std::pow(2, config.getNumVars()) - 0;
	// int actual_range_st = 24 - 0; 
	// int actual_range_lx = 16 - 0; 

	#pragma omp parallel for shared(valores, restricao)
	for(int i = 0; i < config.getPopSize(); i++){
		unsigned long long int b_st = 0, b_lx = 0;
		int sign = 1;

		//Decodifica primeira variável (ST)
		for(int j = 9; j >= 5; j--){
			b_st += popul[i][j]*sign;
			sign *= 2;
		}

		sign = 1;
		//Decodifica segunda variável (LX)
		for(int j = 4; j >= 0; j--){
			b_lx += popul[i][j]*sign;
			sign *= 2;
		}

		


		int st = std::round(b_st*offset_st);
		int lx = std::round(b_lx*offset_lx);

		// int st = (b_st * actual_range_st) / optimizer_range;
		// int lx = (b_lx * actual_range_lx) / optimizer_range;

		//Restrição (st + 2lx <= 40)
		double h = std::max(0.0, (st + 2.0*lx - 40.0)/16.0);
		if(h !=0)
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
	double offset_st = (24.0)/std::pow(2, 5);
	double offset_lx = (16.0)/std::pow(2, 5);	
	// int optimizer_range = std::pow(2, config.getNumVars()) - 0;
	// int actual_range_st = 24 - 0; 
	// int actual_range_lx = 16 - 0; 
	
	unsigned long long int b_st = 0, b_lx = 0;
	int sign = 1;

	//Decodifica primeira variável (ST)
	for(int j = 9; j >= 5; j--){
		b_st += indiv[j]*sign;
		sign *= 2;
	}

	sign = 1;
	//Decodifica segunda variável (LX)
	for(int j = 4; j >= 0; j--){
		b_lx += indiv[j]*sign;
		sign *= 2;
	}

	int st = std::round(b_st*offset_st);
	int lx = std::round(b_lx*offset_lx);

	// int st = (b_st * actual_range_st) / optimizer_range;
	// int lx = (b_lx * actual_range_lx) / optimizer_range;

	double lucro = st*30.0 + lx*40.0;

	std::cout << "Trabalhadores Standard =  " << st << std::endl;
	std::cout << "Trabalhadores Luxo =  " << lx*2 << std::endl;
	std::cout << "Lucro =  R$" << lucro << std::endl;

}


template<> inline
Problem<bool>::Problem(){
	funcao.insert(std::pair<std::string, std::function<Score_Restricao(vvb&, Config&)> >("slide_max", slide_max));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<bool>&, Config&)> >("slide_max", slide_max_decoder));

	funcao.insert(std::pair<std::string, std::function<Score_Restricao(vvb&, Config&)> >("fabrica_radios", fabrica_radios));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<bool>&, Config&)> >("fabrica_radios", fabrica_radios_decoder));
}

template<> inline
Problem<int>::Problem(){
    funcao.insert(std::pair<std::string, std::function<Score_Restricao(vvi&, Config&)> >("nqueens", nQueens));
	decoder.insert(std::pair<std::string, std::function<void(std::vector<int>&, Config&)> >("nqueens", nQueens_decoder));

}

template<> inline
Problem<double>::Problem(){

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
