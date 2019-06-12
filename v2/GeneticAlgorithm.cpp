
#include <cmath>
#include <fstream>

// #include "CodInteira.hpp"
// #include "CodPermutada.hpp"
#include "Problem.hpp"
#include "Selection.hpp"


/////////////////////////////////////////////////////////////////////////////////////////
//                                  Run
////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
void GeneticAlgorithm<T>::run(){
    std::ofstream geracoes;
    std::ofstream resultados;
    std::ofstream diversidades;

    // if(config.getSaidaArquivo()){
    //     saida = std::ofstream(config.getArquivoDestino());
    // }

    resultados.open("./testes/" + config.getArquivoDestino() + "-resultados", std::ofstream::out | std::ofstream::app);

    if(config.getTipoRelatorio() != 0){
        geracoes.open("./testes/" + config.getArquivoDestino() + "-geracoes", std::ofstream::out | std::ofstream::app);
        diversidades.open("./testes/" + config.getArquivoDestino() + "-diversidades", std::ofstream::out | std::ofstream::app);

        highest_diversity = highestDiversity();
    }

    //Gerar populacao inicial
    gerarPopulacao();
    //Avaliar a populacao inicial
    score_r = fitness(popul);

    for(geracao_atual = 0; geracao_atual < config.getGenerations(); geracao_atual++){
        // std::cout << score_r.scores[0];
        //Ordenar os indivíduos de melhor para pior
        std::vector<size_t> idx = sort_indexes(score_r.scores);

        //Substituir os piores pelos melhores da última geracao
        if(geracao_atual != 0 and config.getNumElitistas() != 0){
            int j = 0;
            for(int i = config.getPopSize()-1; i > config.getPopSize()-1-config.getNumElitistas(); i--){
                popul[idx[i]].assign(elite[j].begin(), elite[j].end());
                score_r.scores[idx[i]] = elite_score_r.scores[j];
                score_r.restritos[idx[i]] = elite_score_r.restritos[j];
                j++;
            }
        }

        idx = sort_indexes(score_r.scores);

        //Copiar os melhores indivíduos para o array de elites
        for(int i = 0; i < config.getNumElitistas(); i++){
            elite[i].assign(popul[idx[i]].begin(), popul[idx[i]].end());
            elite_score_r.scores[i] = score_r.scores[idx[i]];
            elite_score_r.restritos[i] = score_r.restritos[idx[i]];

        }



        if(config.getTipoRelatorio() != 0){
            geracoes << score_r.scores[idx[0]] << std::endl; //Melhor
            geracoes << score_r.scores[idx[config.getPopSize()-1]] << std::endl; //Pior
            double media = 0.0;
            for(auto i : idx) media += score_r.scores[i];
            media /= config.getPopSize();
            geracoes << media << std::endl;
            diversidades << diversityMeasure() << std::endl;
        }

        std::vector<double> backup_scores = score_r.scores;

        //Faz o ajuste do Fitness
        if(config.getConstC() != 0){
            escalonamentoLinear();
        }

        //Obtem populacao temporária para crossover e mutacao
        std::vector<std::vector<T> > popul_temp = selection();
        std::vector<std::vector<T> > parents;
        if(config.getCrowdingType() != 0){ //Deterministic or Standard
            parents.assign(popul_temp.begin(), popul_temp.end());
        }
        score_r.scores = backup_scores;
        crossover(popul_temp);
        mutacao(popul_temp);
        Score_Restricao offspring_score_r = fitness(popul_temp);

        //Calcula os scores da população gerada

        //Deterministic Crowding
        if(config.getCrowdingType() == 2){
            Score_Restricao parent_score_r;
            parent_score_r.scores = std::vector<double>(config.getPopSize());
            parent_score_r.restritos = std::vector<bool>(config.getPopSize());
            //Procura quem é o parent e obtém o seu score
            for(int i = 0; i < config.getPopSize(); i++){
                int who = findEqual(popul, parents[i]);
                parent_score_r.scores[i] = score_r.scores[who];
                parent_score_r.restritos[i] = score_r.restritos[who];
            }
            deterministicCrowding(parents, parent_score_r, popul_temp, offspring_score_r);
        }
        else if(config.getCrowdingType() == 1){
            standardCrowding(parents, popul_temp);
        }


        //Passa uma porcentagem da população desta geração para próxima
        if(config.getGenerationGap() < 1.0){
            int quantos = std::round((1.0 - config.getGenerationGap())*config.getPopSize());
            for(int i =0; i < quantos; i++){
                int who = getRandInt(0, config.getPopSize()-1);
                popul_temp[i].assign(popul[who].begin(), popul[who].end());
                offspring_score_r.scores[i] = score_r.scores[who];
                offspring_score_r.restritos[i] = score_r.restritos[who];
            }
        }

        //Atualiza a populacao e scores para a próxima geração
        popul.assign(popul_temp.begin(), popul_temp.end());
        score_r.scores.assign(offspring_score_r.scores.begin(), offspring_score_r.scores.end());
        score_r.restritos.assign(offspring_score_r.restritos.begin(), offspring_score_r.restritos.end());

    }

    std::vector<size_t> idx = sort_indexes(score_r.scores);

    if(config.getNumElitistas() != 0){
        int j = 0;
        for(int i = config.getPopSize()-1; i > config.getPopSize()-1-config.getNumElitistas(); i--){
            popul[idx[i]].assign(elite[j].begin(), elite[j].end());
            score_r.scores[idx[i]] = elite_score_r.scores[j];
            score_r.restritos[idx[i]] = elite_score_r.restritos[j];
            j++;
        }
    }

    idx = sort_indexes(score_r.scores);

    if(config.getTipoRelatorio() != 0){
        geracoes << score_r.scores[idx[0]] << std::endl; //Melhor
        geracoes << score_r.scores[idx[config.getPopSize()-1]] << std::endl; //Pior
        double media = 0.0;
        for(auto i : idx) media += score_r.scores[i];
        media /= config.getPopSize();
        geracoes << media << std::endl;
        geracoes.close();
        diversidades << diversityMeasure() << std::endl;
        diversidades.close();
    }


    resultados << "Execução " << config.getExecucao() << ":" << std::endl;

    int i = idx[0];
    if(score_r.restritos[i]) resultados << "Indivíduo infringiu restrição!" << std::endl;
    else resultados << "Indivíduo válido." << std::endl;

    Problem<T> p;

    if(config.getTipoRelatorio() == 0){ //Básico
        resultados.close();
        p.getDecoder(config.getProblem())(popul[i], config);
    }
    else if(config.getTipoRelatorio() == 1){ //Intermediário
        resultados.close();
        p.getDecoder(config.getProblem())(popul[i], config);
    }
    else if(config.getTipoRelatorio() == 2){ //Completo
        resultados <<"Indivíduo " << i << std::endl << "\tfitness: " << score_r.scores[i] << std::endl;
        resultados << "\tCromossomo: ";
        for(int j = 0; j < config.getNumVars(); j++){
            resultados << popul[i][j] << " ";
        }
        resultados << std::endl;
        resultados.close();
        p.getDecoder(config.getProblem())(popul[i], config);
    }

    // int i = idx[0];
    // if(score_r.restritos[i]) std::cout << "Infringiu restrição!" << std::endl;
    // else std::cout << "Indivíduo válido." << std::endl;
    // std::cout <<"Indivíduo " << i << std::endl << "\tfitness: " << score_r.scores[i] << std::endl;
    // std::cout << "\tCromossomo: ";
    // for(int j = 0; j < config.getNumVars(); j++){
    //     std::cout << popul[i][j] << " ";
    // }
    // std::cout << std::endl;

}

/////////////////////////////////////////////////////////////////////////////////////////
//                                  Fitness
////////////////////////////////////////////////////////////////////////////////////////
#pragma region fitness
template<typename T>
Score_Restricao GeneticAlgorithm<T>::fitness(std::vector<std::vector<T> > &popul_temp){
    Problem<T> problem;
    return problem.getFuncao(config.getProblem())(popul_temp, this->config);
}
#pragma endregion
/////////////////////////////////////////////////////////////////////////////////////////
//                                  Selection
////////////////////////////////////////////////////////////////////////////////////////
#pragma region selection   
template<typename T>
std::vector<std::vector<T> > GeneticAlgorithm<T>::selection(){
    Selection<T> s;
    return s.getFuncao(config.getSelectionMethod())(this->popul, this->score_r.scores, this->config);
}
#pragma endregion selection


/////////////////////////////////////////////////////////////////////////////////////////
//                                  Crossover
////////////////////////////////////////////////////////////////////////////////////////
#pragma region crossover
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
                    if(swap_or_no < 0.5){
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

template<> inline
void GeneticAlgorithm<int>::crossover(std::vector<std::vector<int> > &popul){
    //Faz crossover entre os pares
    vvi popul_temp;
    popul_temp.assign(popul.begin(), popul.end());
    for(int i = 0; i < config.getPopSize(); i+=2){
        double will_it_happen = getRandDouble(0.0, 1.0);
        if(will_it_happen < config.getProbCrossover()){
            if(config.getCrossoverType() == 1){ //1 ponto
                int ponto = getRandInt(0, config.getNumVars() - 2);
                //Trocar informação dos indivíduos
                for(int j = 0; j <= ponto; j++){
                    bool temp;
                    temp = popul[i][j];
                    popul[i][j] = popul[i+1][j];
                    popul[i+1][j] = temp;
                }
            }
            else if(config.getCrossoverType() == 2){ //2 pontos
                int ponto1 = getRandInt(0, config.getNumVars()-4);
                int ponto2 = getRandInt(ponto1+2, config.getNumVars()-2);

                for(int j = ponto1+1; j <= ponto2; j++){
                    bool temp;
                    temp = popul[i][j];
                    popul[i][j] = popul[i+1][j];
                    popul[i+1][j] = temp;
                }
            }
            else if(config.getCrossoverType() == 3){ //Crossover especial do labirinto, crossover nos pontos em comum
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
                    std::vector<std::pair<int, int> > visitados_A; //Guarda posição no lab e movimento em que estava lá
                    std::vector<std::pair<int, int> > intersec; //guarda os movimentos onde ocorreu interesecção
                    // int x_atual = 10, y_atual = 1;
                    std::pair<int, int> atual(10, 1);
                    std::pair<int, int> destino(1, 20);

                    //Acha as posições atingidas pelo primeiro pai
                    for(int v = 0; v < config.getNumVars(); v++){
                        visitados_A.push_back(atual);
                        switch(popul[i][v]){
                            case 0: //cima
                                if(lab[atual.first-1][atual.second] != 0){
                                    atual.first--;
                                    break;
                                }
                                break;					
                            case 1: //direita
                                if(lab[atual.first][atual.second+1] != 0){
                                    atual.second++;
                                    break;
                                }
                                break;
                            case 2: //baixo
                                if(lab[atual.first+1][atual.second] != 0){
                                    atual.first++;
                                    break;
                                }
                                break;
                            case 3: //esquerda
                                if(lab[atual.first][atual.second-1] != 0){
                                    atual.second--;
                                    break;
                                }
                                break;
                        }
                        if(atual.first == destino.first and atual.second == destino.second){
                            break;
                        }
                    }

                    atual = std::make_pair(10, 1);

                    //Acha pontos de intersecção percorrendo o segundo pai e comparando com posições atingidas do primeiro
                    for(int v = 0; v < config.getNumVars(); v++){
                        int cont = 0;
                        for(auto &p : visitados_A){
                            if(atual.first == p.first and atual.second == p.second){
                                intersec.push_back(std::make_pair(cont, v));
                            }
                            cont++;
                        }
                        switch(popul[i+1][v]){
                            case 0: //cima
                                if(lab[atual.first-1][atual.second] != 0){
                                    atual.first--;
                                    break;
                                }
                                break;					
                            case 1: //direita
                                if(lab[atual.first][atual.second+1] != 0){
                                    atual.second++;
                                    break;
                                }
                                break;
                            case 2: //baixo
                                if(lab[atual.first+1][atual.second] != 0){
                                    atual.first++;
                                    break;
                                }
                                break;
                            case 3: //esquerda
                                if(lab[atual.first][atual.second-1] != 0){
                                    atual.second--;
                                    break;
                                }
                                break;
                        }
                        if(atual.first == destino.first and atual.second == destino.second){
                            break;
                        }
                    }

                    //Escolhe ponto de crossover
                    int what = getRandInt(3*intersec.size()/4, intersec.size()-1);
                    std::pair<int, int> p = intersec[what];

                    if(p.first < p.second){
                        //Antes do corte nos dois filhos
                        for(int v1 = 0, v2 = p.second-p.first; v1 <= p.first; v1++, v2++){
                            popul_temp[i][v1] = popul[i][v1];
                            popul_temp[i+1][v1] = popul[i+1][v2];
                        }
                        //depois do corte no filho 2 (terá todo o resto do pai 1)
                        for(int v1 = p.first+1; v1 < config.getNumVars(); v1++){
                            popul_temp[i+1][v1] = popul[i][v1];
                        }
                        
                        //filho 1 depois do corte (terá uma parte de aleatórios)
                        for(int v1 = p.first+1, v2 = p.second+1; v2 < config.getNumVars(); v1++, v2++){
                            popul_temp[i][v1] = popul[i+1][v2];
                        }
                        //aleatórios no fim do filho 1
                        for(int v = p.first+config.getNumVars()-p.second+1; v < config.getNumVars(); v++){
                            popul_temp[i][v] = getRandInt(std::get<int>(config.getLowerBound()), std::get<int>(config.getUpperBound()));
                        }
                    }
                    else if(p.second < p.first){
                        //Antes do corte nos dois filhos
                        for(int v1 = 0, v2 = p.first-p.second; v1 <= p.second; v1++, v2++){
                            popul_temp[i+1][v1] = popul[i+1][v1];
                            popul_temp[i][v1] = popul[i][v2];
                        }
                        //depois do corte no filho 1 (terá todo o resto do pai 2)
                        for(int v1 = p.second+1; v1 < config.getNumVars(); v1++){
                            popul_temp[i][v1] = popul[i+1][v1];
                        }
                        
                        //filho 2 depois do corte (terá uma parte de aleatórios)
                        for(int v1 = p.second+1, v2 = p.first+1; v2 < config.getNumVars(); v1++, v2++){
                            popul_temp[i+1][v1] = popul[i][v2];
                        }
                        //aleatórios no fim do filho 2
                        for(int v = p.second+config.getNumVars()-p.first+1; v < config.getNumVars(); v++){
                            popul_temp[i+1][v] = getRandInt(std::get<int>(config.getLowerBound()), std::get<int>(config.getUpperBound()));
                        }
                    }
                    else{ //iguais
                        for(int j = 0; j <= p.first; j++){
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

template<> inline
void GeneticAlgorithm<int_permut_t>::crossover(std::vector<std::vector<int_permut_t> > &popul){
    std::vector<std::vector<int_permut_t> > popul_temp(config.getPopSize(), std::vector<int_permut_t>(config.getNumVars()));
    popul_temp.assign(popul.begin(), popul.end());
    for(int i = 0; i < config.getPopSize(); i+=2){
        double will_it_happen = getRandDouble(0.0, 1.0);
        if(will_it_happen < config.getProbCrossover()){
            int ponto1 = getRandInt(0, config.getNumVars()-4);
            int ponto2 = getRandInt(ponto1+2, config.getNumVars()-2);
            std::map<int_permut_t, int_permut_t> section_first; //Mapeia o valor do indiv 1 no valor do indiv 2
            std::map<int_permut_t, int_permut_t> section_second; //Mapeia o valor do indiv 2 no valor do indiv 1

            //Dar swap na seção
            for(int j = ponto1+1; j <= ponto2; j++){
                section_first.insert(std::make_pair(popul[i][j], popul[i+1][j]));
                section_second.insert(std::make_pair(popul[i+1][j], popul[i][j]));
                popul_temp[i][j] = popul[i+1][j];
                popul_temp[i+1][j] = popul[i][j];
            }

            //Antes da seção
            for(int j = 0; j <= ponto1; j++){
                auto temp1 = section_second.find(popul[i][j]);
                if(temp1 != section_second.end()){
                    popul_temp[i][j] = temp1->second;
                }

                auto temp2 = section_first.find(popul[i+1][j]);
                if(temp2 != section_first.end()){
                    popul_temp[i+1][j] = temp2->second;
                }
            }

            //Depois da seção
            for(int j = ponto2+1; j < config.getNumVars(); j++){
                auto temp1 = section_second.find(popul[i][j]);
                if(temp1 != section_second.end()){
                    popul_temp[i][j] = temp1->second;
                }

                auto temp2 = section_first.find(popul[i+1][j]);
                if(temp2 != section_first.end()){
                    popul_temp[i+1][j] = temp2->second;
                }
            }
        }
    }
}


template<> inline
void GeneticAlgorithm<double>::crossover(std::vector<std::vector<double> > &popul){
    for(int i = 0; i < config.getPopSize(); i+=2){
        double will_it_happen = getRandDouble(0.0, 1.0);
        if(will_it_happen < config.getProbCrossover()){
            if(config.getCrossoverType() == 1){ //BLX-a
                for(int j = 0; j < config.getNumVars(); j++){
                    double max_i = std::max(popul[i][j], popul[i+1][j]);
                    double min_i = std::min(popul[i][j], popul[i+1][j]);
                    double d_i = max_i - min_i;

                    //Intervalo para geração do número aleatório
                    double sec_lower = min_i - d_i*config.getAlpha();
                    double sec_upper = max_i + d_i*config.getAlpha();

                    double lower = std::get<double>(config.getLowerBound());
                    double upper = std::get<double>(config.getUpperBound());

                    double filho1 = getRandDouble(sec_lower, sec_upper);
                    double filho2 = getRandDouble(sec_lower, sec_upper);

                    //Ajustar para o intervalo válido
                    filho1 = (filho1 - sec_lower)*(upper-lower)/(sec_upper-sec_lower) + lower;
                    filho2 = (filho2 - sec_lower)*(upper-lower)/(sec_upper-sec_lower) + lower;

                    popul[i][j] = filho1;
                    popul[i+1][j] = filho2;
                }
            }
            else if(config.getCrossoverType() == 2){ //Aritmético
                double a = getRandDouble(0.0, 1.0);
                for(int j = 0; j < config.getNumVars(); j++){
                    double filho1 = a*popul[i][j] + (1.0-a)*popul[i+1][j];
                    double filho2 = (1.0-a)*popul[i][j] + a*popul[i+1][j];

                    popul[i][j] = filho1;
                    popul[i+1][j] = filho2;
                }
            }
        }
    }
}
#pragma endregion crossover


/////////////////////////////////////////////////////////////////////////////////////////
//                                  Mutacao
////////////////////////////////////////////////////////////////////////////////////////
#pragma region mutacao
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

template<> inline
void GeneticAlgorithm<int>::mutacao(std::vector<std::vector<int> > &popul){
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

template<> inline
void GeneticAlgorithm<int_permut_t>::mutacao(std::vector<std::vector<int_permut_t> > &popul){
    for(int i = 0; i < config.getPopSize(); i++){
        for(int j = 0; j < config.getNumVars(); j++){
            double dice_roll = getRandDouble(0.0, 1.0);
            if(dice_roll < config.getProbMutacao()){
                int who = getRandInt(0, config.getNumVars()-1);
                while(who == j) who = getRandInt(0, config.getNumVars()-1);
                int temp = popul[i][j];
                popul[i][j] = popul[i][who];
                popul[i][who] = temp;
                break;
            }
        }
    }
}

template<> inline
void GeneticAlgorithm<double>::mutacao(std::vector<std::vector<double> > &popul){
    for(int i = 0; i < config.getPopSize(); i++){
        for(int j = 0; j < config.getNumVars(); j++){
            double will_it_happen = getRandDouble(0.0, 1.0);
            if(will_it_happen < config.getProbMutacao()){
                bool ba = getRandInt(0,1);
                double a = getRandDouble(0.0, 1.0);
                double y;
                if(ba == 1){
                    y = std::get<double>(config.getUpperBound()) - popul[i][j];
                    // printf("u=%lf x=%lf  y=%lf\n", std::get<double>(config.getUpperBound()), popul[i][j], y);
                }
                else{
                    y = std::get<double>(config.getLowerBound()) - popul[i][j];
                    // printf("x=%lf l=%lf  y=%lf\n", popul[i][j], std::get<double>(config.getLowerBound()), y);
                }
                double delta = y*(1-std::pow(a, std::pow(1.0l-(double)geracao_atual/(double)config.getGenerations(), config.getB())));
                // if(delta < 0.0 or delta > y) std::cout << "Antes: " << popul[i][j] << std::endl;
                // double temp = popul[i][j];
                popul[i][j] += delta;   
                // if(popul[i][j] > M_PI or popul[i][j] < 0.0)
                //     printf("Antes=%lf Depois=%lf  y=%lf ba=%d Delta=%lf\n", temp, popul[i][j], y, ba, delta);
            //    if(delta < 0.0 or delta > y) std::cout << "Depois: " << popul[i][j] << " Delta: " << delta << std::endl;
            }
        }
    }
}
#pragma endregion mutacao

/////////////////////////////////////////////////////////////////////////////////////////
//                            Diversidade
////////////////////////////////////////////////////////////////////////////////////////

//Highest Diversity
#pragma region highest_diversity
template<> inline
double GeneticAlgorithm<bool>::highestDiversity(){}


template<> inline
double GeneticAlgorithm<int>::highestDiversity(){
    double dist = std::get<int>(config.getUpperBound()) - std::get<int>(config.getLowerBound());
    dist *= config.getNumVars();
    dist *= (config.getPopSize()/2)*(config.getPopSize()/2);

    return dist;
}

template<> inline
double GeneticAlgorithm<int_permut_t>::highestDiversity(){
    int aContar = config.getNumVars()/2;
    int dist = config.getNumVars();
    int sum = 0;
    for(int i = 0 ; i < aContar; i++){
        sum += dist;
        dist -= 2;
    }
    sum *= 2;

    sum *= config.getPopSize()/2;

    return (double) sum;
}

template<> inline
double GeneticAlgorithm<double>::highestDiversity(){
    return 1; // só pra ele não encher o saco
}
#pragma endregion highest_diversity


//Diversity Measure
#pragma region diversity_measure
template<> inline
double GeneticAlgorithm<bool>::diversityMeasure(){
    std::vector<double> centroide(config.getNumVars());
    for(int v = 0; v < config.getNumVars(); v++){
        double variavel = 0.0;
        for(int k = 0; k < config.getPopSize(); k++){
            variavel += popul[k][v];
        }
        centroide[v] = variavel/config.getPopSize();
    }

    double inercia = 0.0;
    for(int v = 0; v < config.getNumVars(); v++){
        for(int k = 0; k < config.getPopSize(); k++){
            double diff = popul[k][v] - centroide[v];
            inercia += diff * diff;            
        }
    }

    return inercia;
}

template<> inline
double GeneticAlgorithm<int>::diversityMeasure(){
    //Manhattan Distance
    double distancia_total = 0.0;
    for(int i = 0; i < config.getPopSize(); i++){
        for(int j = 0; j < config.getPopSize(); j++){
            if(i == j) continue;
            for(int v = 0; v < config.getNumVars(); v++){
                distancia_total += std::abs(popul[i][v] - popul[j][v]);
            }
        }
    }
    distancia_total /= highest_diversity;
    return distancia_total;
}

template<> inline
double GeneticAlgorithm<int_permut_t>::diversityMeasure(){
    //Manhattan Distance
    double distancia_total = 0.0;
    for(int i = 0; i < config.getPopSize(); i++){
        for(int j = 0; j < config.getPopSize(); j++){
            if(i == j) continue;
            for(int v = 0; v < config.getNumVars(); v++){
                distancia_total += std::abs(popul[i][v] - popul[j][v]);
            }
        }
    }
    distancia_total /= 2;
    // distancia_total /= config.getPopSize();
    return distancia_total;
}


template<> inline
double GeneticAlgorithm<double>::diversityMeasure(){
        std::vector<double> centroide(config.getNumVars());
    for(int v = 0; v < config.getNumVars(); v++){
        double variavel = 0.0;
        for(int k = 0; k < config.getPopSize(); k++){
            variavel += popul[k][v];
        }
        centroide[v] = variavel/config.getPopSize();
    }

    double inercia = 0.0;
    for(int v = 0; v < config.getNumVars(); v++){
        for(int k = 0; k < config.getPopSize(); k++){
            double diff = popul[k][v] - centroide[v];
            inercia += diff * diff;            
        }
    }

    return inercia;
}
#pragma endregion diversity_measure

template<typename T> 
void GeneticAlgorithm<T>::escalonamentoLinear(){

    double C;
    if(config.getConstC() == 1){ //Linear

        C = 1.2 + geracao_atual*(0.8/config.getGenerations()); //C é atualizado linearmente em relação ao número da geração
    }
    else if(config.getConstC() == 2){ //Additiva trigonométrica
        C = 2.0 - 0.4*(1 + std::cos(geracao_atual*M_PI/config.getGenerations()));
    }

    double media;
    for(auto s : score_r.scores) media += s;
    media /= config.getPopSize(); 
    double maior = score_r.scores[maior_elemento(score_r.scores)];
    double menor = score_r.scores[menor_elemento(score_r.scores)];

    double a, b;

    if(menor > (C*media - maior)/C - 1){
        a = media*(C-1)/(maior-media);
        b = media*(maior-C*media)/(maior-media);
    }
    else{
        a = media/(media - menor);
        b = (-menor*media)/(media-menor);
    }

    for(auto &s : score_r.scores){
        s = a*s + b;
    }

}

template<typename T>
void GeneticAlgorithm<T>::deterministicCrowding(std::vector<std::vector<T> > &parents, Score_Restricao &parents_score_r, std::vector<std::vector<T> > &offspring, Score_Restricao &offspring_score_r){
    for(int k = 0; k < config.getPopSize(); k+=2){
        double div1, div2; //Diversidades dos conjuntos p1xf1 e p2xf2 OU p1xf2 e p2xf1 
        for(int v = 0; v < config.getNumVars(); v++){
            div1 += std::abs(parents[k][v] - offspring[k][v]);
            div1 += std::abs(parents[k+1][v] - offspring[k+1][v]);

            div2 += std::abs(parents[k][v] - offspring[k+1][v]);
            div2 += std::abs(parents[k+1][v] - offspring[k][v]);
        }

        //Menor diversidade é escolhida
        if(div1 <= div2){
            if(offspring_score_r.scores[k] < parents_score_r.scores[k]){
                offspring[k].assign(parents[k].begin(), parents[k].end());
                offspring_score_r.scores[k] = parents_score_r.scores[k];
                offspring_score_r.restritos[k] = parents_score_r.restritos[k];
            }
            //else offspring k não se altera

            if(offspring_score_r.scores[k+1] < parents_score_r.scores[k+1]){
                offspring[k+1].assign(parents[k+1].begin(), parents[k+1].end());
                offspring_score_r.scores[k+1] = parents_score_r.scores[k+1];
                offspring_score_r.restritos[k+1] = parents_score_r.restritos[k+1];
            }
            //else offspring k+1 não se altera
        }
        else{
            if(offspring_score_r.scores[k] < parents_score_r.scores[k+1]){
                offspring[k].assign(parents[k+1].begin(), parents[k+1].end());
                offspring_score_r.scores[k] = parents_score_r.scores[k+1];
            }
            //else offspring k não se altera

            if(offspring_score_r.scores[k+1] < parents_score_r.scores[k]){
                offspring[k+1].assign(parents[k].begin(), parents[k].end());
                offspring_score_r.scores[k+1] = parents_score_r.scores[k];
                offspring_score_r.restritos[k+1] = parents_score_r.restritos[k];
            }
            //else offspring k+1 não se altera  
        }
    }
}

template<typename T>
void GeneticAlgorithm<T>::standardCrowding(std::vector<std::vector<T> > &parents, std::vector<std::vector<T> > &offspring){
    std::vector<std::vector<T> > popul_temp(config.getPopSize(), std::vector<T>(config.getNumVars()));
    popul_temp.assign(parents.begin(), parents.end());
    for(int k = 0; k < config.getPopSize(); k++){
        std::vector<int> competidores(config.getStandardCrowdingSize());
        std::vector<double> distancia(config.getStandardCrowdingSize(), 0.0);
        for(int i = 0; i < config.getStandardCrowdingSize(); i++){
            int who = getRandInt(0, config.getPopSize()-1);
            competidores[i] = who;
            for(int v = 0; v < config.getNumVars(); v++){
                distancia[i] += std::abs(offspring[k][v] - popul_temp[competidores[i]][v]);
            }
        }

        int menor = menor_elemento(distancia);
        popul_temp[competidores[menor]].assign(offspring[k].begin(), offspring[k].end());
    }
    offspring.assign(popul_temp.begin(), popul_temp.end());
}



/////////////////////////////////////////////////////////////////////////////////////////
//                            Geração de População
////////////////////////////////////////////////////////////////////////////////////////
#pragma region gera_populacao
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

template<> inline
void GeneticAlgorithm<int>::gerarPopulacao(){
    vvi pop(config.getPopSize(), std::vector<int>(config.getNumVars()));
    for(int i = 0; i < config.getPopSize(); i++){
        for(int j = 0; j < config.getNumVars(); j++){
            // pop[i][j] = std::floor(getRandDouble(upper, lower)); //Segfault se usar getRandInt diretamente
            pop[i][j] = getRandInt(std::get<int>(config.getLowerBound()), std::get<int>(config.getUpperBound())); //Segfault se usar getRandInt diretamente
        }
    }
    this->popul = pop;
}

template<> inline
void GeneticAlgorithm<int_permut_t>::gerarPopulacao(){
    std::vector<std::vector<int_permut_t> > pop(config.getPopSize(), std::vector<int_permut_t>(config.getNumVars()));
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
#pragma endregion gera_populacao


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
