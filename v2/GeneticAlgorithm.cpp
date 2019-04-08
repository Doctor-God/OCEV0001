
#include <cmath>

// #include "CodInteira.hpp"
// #include "CodPermutada.hpp"
#include "Problem.hpp"
#include "Selection.hpp"


/////////////////////////////////////////////////////////////////////////////////////////
//                                  Run
////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
void GeneticAlgorithm<T>::run(){
    //Gerar populacao inicial
    gerarPopulacao();

    for(int g = 0; g < config.getGenerations(); g++){
        //Avaliar populacao
        score_r = fitness();
        //Obter os melhores indivíduos e guardar
        std::vector<size_t> idx = sort_indexes(score_r.scores);
        std::vector<std::vector<T> > atual_elite = elite; //Salvar pra não perder o elite atual
        //Copiar cada elite para o vector
        for(int i = 0; i < config.getNumElitistas(); i++){
            elite[i].assign(popul[idx[i]].begin(), popul[idx[i]].end());
        }

        //Substituir os piores pelos melhores da última geracao
        if(g != 0 and config.getNumElitistas() != 0){
            int j = 0;
            for(int i = config.getPopSize()-1; i > config.getPopSize()-1-config.getNumElitistas(); i--){
                popul[idx[i]].assign(atual_elite[j].begin(), atual_elite[j].end());
                j++;
            }
        }

        //Obtem populacao para crossover e mutacao
        std::vector<std::vector<T> > popul_temp = selection();
        crossover(popul_temp);        
        mutacao(popul_temp);

        //Atualiza a populacao para a próxima geração
        popul.assign(popul_temp.begin(), popul_temp.end());

    }

    score_r = fitness();

    std::vector<size_t> idx = sort_indexes(score_r.scores);

    std::cout << "Melhor indivíduo válido no final da otimização" << std::endl;
    for(auto i : idx){
        //indiv válido
        if(not score_r.restritos[i]){
            std::cout <<"Indivíduo " << i << std::endl << "\tfitness: " << score_r.scores[i] << std::endl; 
            std::cout << "\tCromossomo: ";
            for(int j = 0; j < config.getNumVars(); j++){
                std::cout << std::setw(2) << popul[i][j];
            }
            std::cout << std::endl;
            
            Problem<T> p;
            p.getDecoder(config.getProblem())(popul[i], config);
            break;
        }
    }


}

template<> inline
void GeneticAlgorithm<int>::run(){}

void CodInteira::run(){
    //Gerar populacao inicial
    gerarPopulacao();

    for(int g = 0; g < config.getGenerations(); g++){
        //Avaliar populacao
        score_r = fitness();
        //Obter os melhores indivíduos e guardar
        std::vector<size_t> idx = sort_indexes(score_r.scores);
        std::vector<std::vector<int> > atual_elite = elite; //Salvar pra não perder o elite atual
        //Copiar cada elite para o vector
        for(int i = 0; i < config.getNumElitistas(); i++){
            elite[i].assign(popul[idx[i]].begin(), popul[idx[i]].end());
        }

        //Substituir os piores pelos melhores da última geracao
        if(g != 0 and config.getNumElitistas() != 0){
            int j = 0;
            for(int i = config.getPopSize()-1; i > config.getPopSize()-1-config.getNumElitistas(); i--){
                popul[idx[i]].assign(atual_elite[j].begin(), atual_elite[j].end());
                j++;
            }
        }

        //Obtem populacao para crossover e mutacao
        std::vector<std::vector<int> > popul_temp = selection();
        crossover(popul_temp);        
        mutacao(popul_temp);

        //Atualiza a populacao para a próxima geração
        popul.assign(popul_temp.begin(), popul_temp.end());

    }

    score_r = fitness();

    std::vector<size_t> idx = sort_indexes(score_r.scores);

    std::cout << "Melhor indivíduo válido no final da otimização" << std::endl;
    for(auto i : idx){
        //indiv válido
        if(not score_r.restritos[i]){
            std::cout <<"Indivíduo " << i << std::endl << "\tfitness: " << score_r.scores[i] << std::endl; 
            std::cout << "\tCromossomo: ";
            for(int j = 0; j < config.getNumVars(); j++){
                std::cout << std::setw(2) << popul[i][j];
            }
            std::cout << std::endl;
            
            Problem<int> p;
            p.getDecoder(config.getProblem())(popul[i], config);
            break;
        }
    }

}

void CodPermutada::run(){
    //Gerar populacao inicial
    gerarPopulacao();

    for(int g = 0; g < config.getGenerations(); g++){
        //Avaliar populacao
        score_r = fitness();
        //Obter os melhores indivíduos e guardar
        std::vector<size_t> idx = sort_indexes(score_r.scores);
        std::vector<std::vector<int> > atual_elite = elite; //Salvar pra não perder o elite atual
        //Copiar cada elite para o vector
        for(int i = 0; i < config.getNumElitistas(); i++){
            elite[i].assign(popul[idx[i]].begin(), popul[idx[i]].end());
        }

        //Substituir os piores pelos melhores da última geracao
        if(g != 0 and config.getNumElitistas() != 0){
            int j = 0;
            for(int i = config.getPopSize()-1; i > config.getPopSize()-1-config.getNumElitistas(); i--){
                popul[idx[i]].assign(atual_elite[j].begin(), atual_elite[j].end());
                j++;
            }
        }

        //Obtem populacao para crossover e mutacao
        std::vector<std::vector<int> > popul_temp = selection();
        crossover(popul_temp);        
        mutacao(popul_temp);

        //Atualiza a populacao para a próxima geração
        popul.assign(popul_temp.begin(), popul_temp.end());

    }

    score_r = fitness();

    std::vector<size_t> idx = sort_indexes(score_r.scores);

    std::cout << "Melhor indivíduo válido no final da otimização" << std::endl;
    for(auto i : idx){
        //indiv válido
        if(not score_r.restritos[i]){
            std::cout <<"Indivíduo " << i << std::endl << "\tfitness: " << score_r.scores[i] << std::endl; 
            std::cout << "\tCromossomo: ";
            for(int j = 0; j < config.getNumVars(); j++){
                std::cout << std::setw(2) << popul[i][j];
            }
            std::cout << std::endl;
            
            Problem<int> p;
            p.getDecoder(config.getProblem())(popul[i], config);
            break;
        }
    }
}

template<typename T>
Score_Restricao GeneticAlgorithm<T>::fitness(){
	Problem<T> problem;
	return problem.getFuncao(config.getProblem())(this->popul, this->config);
}

template<typename T>
std::vector<std::vector<T> > GeneticAlgorithm<T>::selection(){
	Selection<T> s;
	return s.getFuncao(config.getSelectionMethod())(this->popul, this->score_r.scores, this->config);
}


/////////////////////////////////////////////////////////////////////////////////////////
//                                  Crossover
////////////////////////////////////////////////////////////////////////////////////////
template<> inline
void GeneticAlgorithm<bool>::crossover(std::vector<std::vector<bool> > &popul){
    //Faz crossover entre os pares
    for(int i = 0; i < config.getPopSize(); i+=2){
        double will_it_happen = getRandDouble(0.0, 1.0);
        if(will_it_happen < config.getProbCrossover()){
            if(config.getCrossoverType() == 1){
                int ponto = getRandInt(0, config.getPopSize() - 2);
                //Trocar informação dos indivíduos
                for(int j = 0; j <= ponto; j++){
                    bool temp;
                    temp = popul[i][j];
                    popul[i][j] = popul[i+1][j];
                    popul[i+1][j] = temp;
                }
            }
            else if(config.getCrossoverType() == 2){
                int ponto1 = getRandInt(0, config.getPopSize()-4);
                int ponto2 = getRandInt(ponto1+2, config.getPopSize()-2);
                
                for(int j = ponto1+1; j <= ponto2-1; j++){
                    bool temp;
                    temp = popul[i][j];
                    popul[i][j] = popul[i+1][j];
                    popul[i+1][j] = temp;
                }
            }
        }
    }
}

void CodInteira::crossover(std::vector<std::vector<int> > &popul){
    //Faz crossover entre os pares
    for(int i = 0; i < config.getPopSize(); i+=2){
        double will_it_happen = getRandDouble(0.0, 1.0);
        if(will_it_happen < config.getProbCrossover()){
            if(config.getCrossoverType() == 1){
                int ponto = getRandInt(0, config.getPopSize() - 2);
                //Trocar informação dos indivíduos
                for(int j = 0; j <= ponto; j++){
                    bool temp;
                    temp = popul[i][j];
                    popul[i][j] = popul[i+1][j];
                    popul[i+1][j] = temp;
                }
            }
            else if(config.getCrossoverType() == 2){
                int ponto1 = getRandInt(0, config.getPopSize()-4);
                int ponto2 = getRandInt(ponto1+2, config.getPopSize()-2);
                
                for(int j = ponto1+1; j <= ponto2-1; j++){
                    bool temp;
                    temp = popul[i][j];
                    popul[i][j] = popul[i+1][j];
                    popul[i+1][j] = temp;
                }
            }
        }
    }

}

void CodPermutada::crossover(std::vector<std::vector<int> > &popul){
    //Implementar
}


template<> inline
void GeneticAlgorithm<double>::crossover(std::vector<std::vector<double> > &popul){
    //Implementar
}


/////////////////////////////////////////////////////////////////////////////////////////
//                                  Mutacao
////////////////////////////////////////////////////////////////////////////////////////
template<> inline
void GeneticAlgorithm<bool>::mutacao(std::vector<std::vector<bool> > &popul){
    //Para cada bit rola a chance para ver se sofrerá mutação
    for(int i = 0; i < config.getPopSize(); i++){
        for(int j = 0; j < config.getNumVars(); j++){
            double dice_roll = getRandDouble(0.0, 1.0);
            if(dice_roll < config.getProbMutacao()){
                popul[i][j] = not popul[i][j]; //bit flip
            }
        }
    }
}

void CodInteira::mutacao(std::vector<std::vector<int> > &popul){
        //Para cada bit rola a chance para ver se sofrerá mutação
    for(int i = 0; i < config.getPopSize(); i++){
        for(int j = 0; j < config.getNumVars(); j++){
            double dice_roll = getRandDouble(0.0, 1.0);
            if(dice_roll < config.getProbMutacao()){
                //Substitui a variável por um valor aleatório no domínio
                popul[i][j] = getRandInt(std::get<int>(config.getLowerBound()), std::get<int>(config.getUpperBound())); 
            }
        }
    }
}

void CodPermutada::mutacao(std::vector<std::vector<int> > &popul){
    //Implementar
}


template<> inline
void GeneticAlgorithm<double>::mutacao(std::vector<std::vector<double> > &popul){
    //Implementar
}



/////////////////////////////////////////////////////////////////////////////////////////
//                            Geração de População
////////////////////////////////////////////////////////////////////////////////////////
template<> inline
void GeneticAlgorithm<bool>::gerarPopulacao(){
	vvb pop(config.getPopSize(), std::vector<bool>(config.getNumVars()));
	for(int i = 0; i < config.getPopSize(); i++){
		for(int j = 0; j < config.getNumVars(); j++){
			pop[i][j] = (bool) getRandInt(0, 1);
		}
	}
	this->popul = pop;
}


void CodInteira::gerarPopulacao(){
    vvi pop(config.getPopSize(), std::vector<int>(config.getNumVars()));
	for(int i = 0; i < config.getPopSize(); i++){
		for(int j = 0; j < config.getNumVars(); j++){
			// pop[i][j] = std::floor(getRandDouble(upper, lower)); //Segfault se usar getRandInt diretamente
			pop[i][j] = getRandInt(std::get<int>(config.getLowerBound()), std::get<int>(config.getUpperBound())); //Segfault se usar getRandInt diretamente
		}
	}
	this->popul = pop;
}

void CodPermutada::gerarPopulacao(){
	vvi pop(config.getPopSize(), std::vector<int>(config.getNumVars()));
	for(int i = 0; i < config.getPopSize(); i++){
		for(int j = 0; j < config.getNumVars(); j++){
			pop[i][j] = j;
		}
		shuffle(pop[i]);
	}
	this->popul = pop;
}

template<> inline
void GeneticAlgorithm<double>::gerarPopulacao(){
	vvd pop(config.getPopSize(), std::vector<double>(config.getNumVars()));
	for(int i = 0; i < config.getPopSize(); i++){
		for(int j = 0; j < config.getNumVars(); j++){
			pop[i][j] = getRandDouble(std::get<double>(config.getLowerBound()), std::get<double>(config.getUpperBound())); //Segfault se usar getRandInt diretamente
			// pop[i][j] = getRandInt(upper, lower)); //Segfault se usar getRandInt diretamente
		}
	}
	this->popul = pop;
}

template<typename T>
void GeneticAlgorithm<T>::printPopulacao(){
    print_matrix<T>(this->popul);
}

template<typename T>
GeneticAlgorithm<T>::GeneticAlgorithm(Config &c){
    this->config = c;
    elite = std::vector<std::vector<T> >(config.getNumElitistas(), std::vector<T>(config.getNumVars())); 
}

template<typename T>
GeneticAlgorithm<T>::GeneticAlgorithm(){}

template<typename T>
GeneticAlgorithm<T>::~GeneticAlgorithm(){}


CodInteira::CodInteira(Config &c){
    this->config = c;
    elite = std::vector<std::vector<int> >(config.getNumElitistas(), std::vector<int>(config.getNumVars()));    
}

CodPermutada::CodPermutada(Config &c){
    this->config = c;
    elite = std::vector<std::vector<int> >(config.getNumElitistas(), std::vector<int>(config.getNumVars()));    
}
