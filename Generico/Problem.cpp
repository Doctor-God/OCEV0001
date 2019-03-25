#include <cmath>
#include <iostream>

//Permutação e inteiro não são diferenciado aqui, mas poderiam ser, com vontade o suficiente

template<> inline
std::vector<double> Problem<int>::nQueens(vvi popul){
	//Por enquanto vamos quantificar apenas uma colisão por rainha, mas é possivel quantificar todas elas
	// int max_colisoes = popul.size(); //Todas as rainhas colidem-se
	std::vector<double> valores(popul.size());

	#pragma omp parallel for
	for(int k = 0; k < popul.size(); k++){
		int colisoes = 0;
		for(int i = 0; i < popul[k].size()-1; i++){
			for(int j = i + 1; j < popul[k].size(); j++){
				if(std::abs(i - j) == std::abs(popul[k][i] - popul[k][j])){
					colisoes++;
				}
			}
		}
		valores[k] = colisoes;
	}

	double mais_colisoes = *std::max_element(valores.begin(), valores.end());

	for(int i = 0; i < valores.size(); i++){
		valores[i] = 1.0 - valores[i]/mais_colisoes;

	}

	return valores;
}

template<> inline
std::vector<double> Problem<bool>::slide_max(vvb popul){
	std::vector<double> valores(popul.size());

	double offset = (2.0 - (-2.0))/std::pow(2, popul[0].size());

	#pragma omp parallel for
	for(int i = 0; i < popul.size(); i++){
		//Transformar o vector<bool> em um valor uint
		unsigned long long int b = 0;
		int sign = 1;
		for(int j = popul[i].size() - 1; j >= 0; j--){
			b += popul[i][j]*sign;
			sign *= 2;
		}
		double x = -2 + b*offset;


		double fx = 5 + cos(20*x) - abs(x)/2 + pow(x, 3)/4;

		valores[i] = fx;
	}

	double maior = *std::max_element(valores.begin(), valores.end());

	for(int i = 0; i < popul.size(); i++){
		valores[i] /= maior;
	}

	return valores;
}

template<> inline
std::vector<double> Problem<bool>::fabrica_radios(vvb popul){
	std::vector<double> valores(popul.size());

	double offset_st = (24.0)/std::pow(2, 5);
	double offset_lx = (16.0)/std::pow(2, 5);

	#pragma omp parallel for
	for(int i = 0; i < popul.size(); i++){
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

		//Restrição (st + 2lx <= 40)
		double h = std::max(0.0, (st + 2.0*lx - 40.0)/16.0);

		//Função fitness (função objetivo/valor_máximo - restrição)
		valores[i] = (30.0*st + 40.0*lx)/1360.0 - h;
	}

	return valores;
}


template<> inline
Problem<bool>::Problem(){
	funcao.insert(std::pair<std::string, std::function<std::vector<double>(vvb)> >("slide_max", slide_max));
	funcao.insert(std::pair<std::string, std::function<std::vector<double>(vvb)> >("fabrica_radios", fabrica_radios));
}

template<> inline
Problem<int>::Problem(){
    funcao.insert(std::pair<std::string, std::function<std::vector<double>(vvi)> >("nqueens", nQueens));
}

template<> inline
Problem<double>::Problem(){

}

template<typename T>
std::function<std::vector<double>(std::vector<std::vector<T> >)> Problem<T>::getFuncao(std::string nome){
    return funcao[nome];

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
