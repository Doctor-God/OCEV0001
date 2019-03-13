#include <bits/stdc++.h>
#include <boost/variant.hpp>

using namespace std;

typedef vector<vector<int> > vvi;
typedef vector<vector<bool> > vvb;
typedef vector<vector<double> > vvd;

random_device rd{};
mt19937 gen(rd());

// double** gera_populacao(int size, int n_vars, double upper, double lower);
// int** gera_populacao(int size, int n_vars, int upper, int lower);
// bool** gera_populacao(int size, int n_vars, int tipo);

int getRandInt(int a, int b);
double getRandDouble(double a, double b);

void print_matrix(boost::variant<vvb, vvi, vvd> &matrix, int tipo);
template<typename T>
void print_matrix(boost::variant<vvb, vvi, vvd> &matrix);

boost::variant<vvb, vvi, vvd> gera_populacao(int size, int n_vars, int tipo, boost::variant<int, double> upper, boost::variant<int, double> lower);
// boost::variant<vvb, vvi> gera_populacao(int size, int n_vars, int tipo);
// void delete_pop


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
	
	boost::variant<int, double> upper = 0, lower = 0;
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

	boost::variant<vvb, vvi, vvd> populacao;
	populacao = gera_populacao(size, n_vars, tipo, upper, lower);

	print_matrix(populacao, tipo);
	

	return 0;
}

int getRandInt(int a, int b){
	uniform_int_distribution<int> dis(a, b);
	return dis(gen);
}

double getRandDouble(double a, double b){
	uniform_real_distribution<double> dis(a, b);
	return dis(gen);
}

void print_matrix(boost::variant<vvb, vvi, vvd> &matrix, int tipo){
	if(tipo == 1 or tipo == 2){
		print_matrix<vvi>(matrix);
	}
	else if(tipo == 0){
		print_matrix<vvb>(matrix);
	}
	else if(tipo == 3){
		print_matrix<vvd>(matrix);
	}
}


template<typename T>
void print_matrix(boost::variant<vvb, vvi, vvd> &m){
	cout << fixed;
    cout << setprecision(4);
	T matrix = boost::get<T>(m);
	int rows = matrix.size();
	int cols = matrix[0].size();
	for(int i = 0; i <rows; i++){
		for(int j = 0; j < cols; j++){
			cout << setw(10) << matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
}


boost::variant<vvb, vvi, vvd> gera_populacao(int size, int n_vars, int tipo, boost::variant<int, double> upper, boost::variant<int, double> lower){
	if(tipo == 0){
		vvb pop(size, vector<bool>(n_vars));
		for(int i = 0; i < size; i++){
			for(int j = 0; j < n_vars; j++){
				pop[i][j] = (bool) getRandInt(0, 1);
			}
		}
		return pop;		
	}
	else if(tipo == 1){
		vvi pop(size, vector<int>(n_vars));
		for(int i = 0; i < size; i++){
			for(int j = 0; j < n_vars; j++){
				pop[i][j] = round(getRandDouble(boost::get<int>(upper), boost::get<int>(lower))); //Segfault se usar getRandInt diretamente
				// pop[i][j] = getRandInt(boost::get<int>(upper), boost::get<int>(lower)); //Segfault se usar getRandInt diretamente
			}
		}
		return pop;
	}
	else if(tipo == 2){
		vvi pop(size, vector<int>(n_vars));
		for(int i = 0; i < size; i++){
			for(int j = 0; j < n_vars; j++){
				pop[i][j] = j;
			}
			shuffle(pop[i].begin(), pop[i].end(), gen);
		}
		return pop;
	}
	else if(tipo == 3){
		vvd pop(size, vector<double>(n_vars));
		for(int i = 0; i < size; i++){
			for(int j = 0; j < n_vars; j++){
				pop[i][j] = getRandDouble(boost::get<double>(upper), boost::get<double>(lower));
			}
		}
		return pop;
	}
}

