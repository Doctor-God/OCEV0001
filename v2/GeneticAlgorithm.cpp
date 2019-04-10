
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
    if(config.getSaidaArquivo()){
        std::cout << config.getGenerations() << std::endl;
    }

    //Gerar populacao inicial
    gerarPopulacao();

    for(int g = 0; g < config.getGenerations(); g++){
        //Avaliar populacao
        score_r = fitness();
        //Obter os melhores indivíduos e guardar
        std::vector<size_t> idx = sort_indexes(score_r.scores);
 
        std::vector<std::vector<T> > atual_elite = elite; //Salvar pra não perder o elite atual
        Score_Restricao elite_sr_atual;
            elite_sr_atual.scores = elite_score_r.scores;
            elite_sr_atual.restritos = elite_score_r.restritos;

        //Copiar cada elite para o vector
        for(int i = 0; i < config.getNumElitistas(); i++){
            elite[i].assign(popul[idx[i]].begin(), popul[idx[i]].end());
            elite_score_r.scores[i] = score_r.scores[idx[i]];
            elite_score_r.restritos[i] = score_r.restritos[idx[i]];

        }

        double pior_score = score_r.scores[idx[config.getPopSize()-1]];

        //Substituir os piores pelos melhores da última geracao
        if(g != 0 and config.getNumElitistas() != 0){
            int j = 0;
            for(int i = config.getPopSize()-1; i > config.getPopSize()-1-config.getNumElitistas(); i--){
                popul[idx[i]].assign(atual_elite[j].begin(), atual_elite[j].end());
                score_r.scores[idx[i]] = elite_sr_atual.scores[j];
                score_r.restritos[idx[i]] = elite_sr_atual.restritos[j];
                j++;
            }
        }

        if(config.getSaidaArquivo()){
            if(config.getNumElitistas() != 0){
                std::cout << std::max(score_r.scores[idx[0]], elite_sr_atual.scores[0]) << std::endl; //Melhor
            }
            else{
                std::cout << score_r.scores[idx[0]] << std::endl;
            }
            std::cout << pior_score << std::endl; //Pior
            double media = 0.0;
            for(auto i : idx) media += score_r.scores[i];
            media /= config.getPopSize();
            std::cout << media << std::endl;
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

    if(config.getSaidaArquivo()){
        std::cout << score_r.scores[idx[0]] << std::endl; //Melhor
        std::cout << score_r.scores[idx[config.getPopSize()-1]] << std::endl; //Pior
        double media = 0.0;
        for(auto i : idx) media += score_r.scores[i];
        media /= config.getPopSize();
        std::cout << media << std::endl;
        return;
    }


    std::cout << "Melhor indivíduo válido no final da otimização" << std::endl;
    for(auto i : idx){
        //indiv válido
        if(not score_r.restritos[i]){

            std::cout <<"Indivíduo " << i << std::endl << "\tfitness: " << score_r.scores[i] << std::endl; 
            std::cout << "\tCromossomo: ";
            for(int j = 0; j < config.getNumVars(); j++){
                std::cout << popul[i][j] << " ";
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
    if(config.getSaidaArquivo()){
        std::cout << config.getGenerations() << std::endl;
    }

    //Gerar populacao inicial
    gerarPopulacao();

    for(int g = 0; g < config.getGenerations(); g++){
        //Avaliar populacao
        score_r = fitness();
        //Obter os melhores indivíduos e guardar
        std::vector<size_t> idx = sort_indexes(score_r.scores);

        std::vector<std::vector<int> > atual_elite = elite; //Salvar pra não perder o elite atual
        Score_Restricao elite_sr_atual;
            elite_sr_atual.scores = elite_score_r.scores;
            elite_sr_atual.restritos = elite_score_r.restritos;

        //Copiar cada elite para o vector
        for(int i = 0; i < config.getNumElitistas(); i++){
            elite[i].assign(popul[idx[i]].begin(), popul[idx[i]].end());
            elite_score_r.scores[i] = score_r.scores[idx[i]];
            elite_score_r.restritos[i] = score_r.restritos[idx[i]];

        }

        double pior_score = score_r.scores[idx[config.getPopSize()-1]];

        //Substituir os piores pelos melhores da última geracao
        if(g != 0 and config.getNumElitistas() != 0){
            int j = 0;
            for(int i = config.getPopSize()-1; i > config.getPopSize()-1-config.getNumElitistas(); i--){
                popul[idx[i]].assign(atual_elite[j].begin(), atual_elite[j].end());
                score_r.scores[idx[i]] = elite_sr_atual.scores[j];
                score_r.restritos[idx[i]] = elite_sr_atual.restritos[j];
                j++;
            }
        }

        if(config.getSaidaArquivo()){
            std::cout << std::max(score_r.scores[idx[0]], elite_sr_atual.scores[0]) << std::endl; //Melhor
            std::cout << pior_score << std::endl; //Pior
            double media = 0.0;
            for(auto i : idx) media += score_r.scores[i];
            media /= config.getPopSize();
            std::cout << media << std::endl;
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

    Score_Restricao elite_sr_atual;
        elite_sr_atual.scores = elite_score_r.scores;
        elite_sr_atual.restritos = elite_score_r.restritos;

    if(config.getSaidaArquivo()){
        std::cout << score_r.scores[idx[0]] << std::endl; //Melhor
        std::cout << score_r.scores[idx[config.getPopSize()-1]] << std::endl; //Pior
        double media = 0.0;
        for(auto i : idx) media += score_r.scores[i];
        media /= config.getPopSize();
        std::cout << media << std::endl;
        return;
    }

    std::cout << "Melhor indivíduo válido no final da otimização" << std::endl;
    for(auto i : idx){
        //indiv válido
        if(not score_r.restritos[i]){
            std::cout <<"Indivíduo " << i << std::endl << "\tfitness: " << score_r.scores[i] << std::endl; 
            std::cout << "\tCromossomo: ";
            for(int j = 0; j < config.getNumVars(); j++){
                std::cout << popul[i][j] << " ";
            }
            std::cout << std::endl;
            
            Problem<int> p;
            p.getDecoder(config.getProblem())(popul[i], config);
            break;
        }
    }

}

void CodPermutada::run(){
    if(config.getSaidaArquivo()){
        std::cout << config.getGenerations() << std::endl;
    }

    //Gerar populacao inicialscore_r.scores[idx[0]]
    gerarPopulacao();

    for(int g = 0; g < config.getGenerations(); g++){
        //Avaliar populacao
        score_r = fitness();
        //Obter os melhores indivíduos e guardar
        std::vector<size_t> idx = sort_indexes(score_r.scores);
       
        std::vector<std::vector<int> > atual_elite = elite; //Salvar pra não perder o elite atual
        Score_Restricao elite_sr_atual;
            elite_sr_atual.scores = elite_score_r.scores;
            elite_sr_atual.restritos = elite_score_r.restritos;

        //Copiar cada elite para o vector
        for(int i = 0; i < config.getNumElitistas(); i++){
            elite[i].assign(popul[idx[i]].begin(), popul[idx[i]].end());
            elite_score_r.scores[i] = score_r.scores[idx[i]];
            elite_score_r.restritos[i] = score_r.restritos[idx[i]];
        }


        double pior_score = score_r.scores[idx[config.getPopSize()-1]];

        //Substituir os piores pelos melhores da última geracao
         if(g != 0 and config.getNumElitistas() != 0){
            int j = 0;
            for(int i = config.getPopSize()-1; i > config.getPopSize()-1-config.getNumElitistas(); i--){
                popul[idx[i]].assign(atual_elite[j].begin(), atual_elite[j].end());
                score_r.scores[idx[i]] = elite_sr_atual.scores[j];
                score_r.restritos[idx[i]] = elite_sr_atual.restritos[j];
                j++;
            }
        }

        if(config.getSaidaArquivo()){
            std::cout << std::max(score_r.scores[idx[0]], elite_sr_atual.scores[0]) << std::endl; //Melhor
            std::cout << pior_score << std::endl; //Pior
            double media = 0.0;
            for(auto i : idx) media += score_r.scores[i];
            media /= config.getPopSize();
            std::cout << media << std::endl;
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
    
    
    if(config.getSaidaArquivo()){
        std::cout << score_r.scores[idx[0]] << std::endl; //Melhor
        std::cout << score_r.scores[idx[config.getPopSize()-1]] << std::endl; //Pior
        double media = 0.0;
        for(auto i : idx) media += score_r.scores[i];
        media /= config.getPopSize();
        std::cout << media << std::endl;
        return;
    }

    std::cout << "Melhor indivíduo válido no final da otimização" << std::endl;
    for(auto i : idx){
        //indiv válido
        if(not score_r.restritos[i]){
            std::cout <<"Indivíduo " << i << std::endl << "\tfitness: " << score_r.scores[i] << std::endl; 
            std::cout << "\tCromossomo: ";
            for(int j = 0; j < config.getNumVars(); j++){
                std::cout << popul[i][j]<< " ";
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
            if(config.getCrossoverType() == 1){ //Um ponto
                int ponto = getRandInt(0, config.getNumVars() - 2);
                //Trocar informação dos indivíduos
                for(int j = 0; j <= ponto; j++){
                    bool temp;
                    temp = popul[i][j];
                    popul[i][j] = popul[i+1][j];
                    popul[i+1][j] = temp;
                }
            }
            else if(config.getCrossoverType() == 2){ //Dois pontos
                int ponto1 = getRandInt(0, config.getNumVars()-4);
                int ponto2 = getRandInt(ponto1+2, config.getNumVars()-2);
                
                for(int j = ponto1+1; j <= ponto2; j++){
                    bool temp;
                    temp = popul[i][j];
                    popul[i][j] = popul[i+1][j];
                    popul[i+1][j] = temp;
                }
            }
            else if(config.getCrossoverType() == 0){ //Uniforme
                for(int j = 0; j < config.getNumVars(); j++){
                    double swap_or_no = getRandDouble(0.0, 1.0);
                    if(will_it_happen < 0.5){
                        bool temp;
                        temp = popul[i][j];
                        popul[i][j] = popul[i+1][j];
                        popul[i+1][j] = temp;
                    }
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
                int ponto = getRandInt(0, config.getNumVars() - 2);
                //Trocar informação dos indivíduos
                for(int j = 0; j <= ponto; j++){
                    bool temp;
                    temp = popul[i][j];
                    popul[i][j] = popul[i+1][j];
                    popul[i+1][j] = temp;
                }
            }
            else if(config.getCrossoverType() == 2){
                int ponto1 = getRandInt(0, config.getNumVars()-4);
                int ponto2 = getRandInt(ponto1+2, config.getNumVars()-2);
                
                for(int j = ponto1+1; j <= ponto2; j++){
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
    std::vector<std::vector<int> > popul_temp(config.getPopSize(), std::vector<int>(config.getNumVars()));  
    popul_temp.assign(popul.begin(), popul.end());  
    for(int i = 0; i < config.getPopSize(); i+=2){
        double will_it_happen = getRandDouble(0.0, 1.0);
        if(will_it_happen < config.getProbCrossover()){
            int ponto1 = getRandInt(0, config.getNumVars()-4);
            int ponto2 = getRandInt(ponto1+2, config.getNumVars()-2);
            std::map<int, int> section_first; //Mapeia o valor do indiv 1 no valor do indiv 2
            std::map<int, int> section_second; //Mapeia o valor do indiv 2 no valor do indiv 1

            //Dar swap na seção
            for(int j = ponto1+1; j <= ponto2; j++){
                section_first.insert(std::make_pair(popul[i][j], popul[i+1][j]));
                section_second.insert(std::make_pair(popul[i+1][j], popul[i][j]));
                popul_temp[i][j] = popul[i+1][j];
                popul_temp[i+1][j] = popul[i][j];
            }

            //Antes da seção
            for(int j = 0; j <= ponto1; j++){
                auto temp1 = section_first.find(popul[i+1][j]);
                if(temp1 != section_first.end()){
                    popul_temp[i][j] = temp1->second;
                }

                auto temp2 = section_second.find(popul[i][j]);
                if(temp2 != section_second.end()){
                    popul_temp[i+1][j] = temp2->second;
                }
            }

            //Depois da seção  
            for(int j = ponto2+1; j < config.getNumVars(); j++){
                auto temp1 = section_first.find(popul[i+1][j]);
                if(temp1 != section_first.end()){
                    popul_temp[i][j] = temp1->second;
                }

                auto temp2 = section_second.find(popul[i][j]);
                if(temp2 != section_second.end()){
                    popul_temp[i+1][j] = temp2->second;
                }
            }
        }
    }
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
    for(int i = 0; i < config.getPopSize(); i++){
        for(int j = 0; j < config.getNumVars(); j++){
            double dice_roll = getRandDouble(0.0, 1.0);
            if(dice_roll < config.getProbMutacao()){
                int who = getRandInt(0, config.getNumVars());
                while(who == j) who = getRandInt(0, config.getNumVars());
                for(int k = 0; k < config.getNumVars(); k++){
                    if(k == who){
                        int temp = popul[i][j];
                        popul[i][j] = popul[i][k];
                        popul[i][k] = temp;
                        break;
                    }
                }
            }
        }
    }
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
    elite_score_r.scores = std::vector<double>(config.getNumElitistas());
    elite_score_r.restritos = std::vector<bool>(config.getNumElitistas());
}

template<typename T>
GeneticAlgorithm<T>::GeneticAlgorithm(){}

template<typename T>
GeneticAlgorithm<T>::~GeneticAlgorithm(){}


CodInteira::CodInteira(Config &c){
    this->config = c;
    elite = std::vector<std::vector<int> >(config.getNumElitistas(), std::vector<int>(config.getNumVars()));    
    elite_score_r.scores = std::vector<double>(config.getNumElitistas());
    elite_score_r.restritos = std::vector<bool>(config.getNumElitistas());
}

CodPermutada::CodPermutada(Config &c){
    this->config = c;
    elite = std::vector<std::vector<int> >(config.getNumElitistas(), std::vector<int>(config.getNumVars()));
    elite_score_r.scores = std::vector<double>(config.getNumElitistas());
    elite_score_r.restritos = std::vector<bool>(config.getNumElitistas());
}
