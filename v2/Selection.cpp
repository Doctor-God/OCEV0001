#include <vector>
#include "Selection.hpp"

template <typename T>
std::vector<std::vector<T> > Selection<T>::roleta(std::vector<std::vector<T> > &popul, std::vector<double> &score, Config &config){
    //Cria população intermediária
    std::vector<std::vector<T> > popul_temp(config.getPopSize(), std::vector<T>(config.getNumVars()));
    // std::vector<int> popul_temp(config.getPopSize()*2);
    
    std::vector<double> score_relativo(config.getPopSize());
    std::vector<std::vector<double> > score_relativo_sem(config.getPopSize(), std::vector<double>(config.getPopSize())); //Guardar a roleta sem um indivíduo específico
    std::vector<double> score_total_sem(config.getPopSize(), -1); //Soma de score sem um indivíduo específico


    //Calcula o score total da popul (soma dos scores)
    double score_total = 0.0;
    for(int i = 0; i < config.getPopSize(); i++){
        score_total += score[i];
    }
    //Calcular o score relativo ao total na população e já adequar à roleta
    for(int i = 0; i < config.getPopSize()-1; i++){
        if(i == 0)
            score_relativo[i] = score[i]/score_total;
        else
            score_relativo[i] = score[i]/score_total + score_relativo[i-1];
    }
    score_relativo[config.getPopSize()-1] = 1.0;

    // std::cout << "Roleta\n"; 
    // for(int i = 0; i < config.getPopSize(); i++){
    //     std::cout <<score_relativo[i] << std::endl;
    // }
    // std::cout << "\n"; 



    //Escolhem-se pares de indivíduos
    for(int i = 0; i < config.getPopSize(); i += 2){
        double dice_roll = getRandDouble(0.0, 1.0);
        int escolhido = -1;
        int escolhido2 = -1;

        //Percorremos a roleta até encontrar um valor maior que dice_rol
        //ou seja, encontramos o intervalo do escolhido
        for(int j = 0; j < config.getPopSize(); j++){
            if(dice_roll < score_relativo[j]){
                escolhido = j;
                break;
            }
        }

        //Colocamos escolhido na populacao intermediaria
        popul_temp[i].assign(popul[escolhido].begin(), popul[escolhido].end());
        // popul_temp[i] = escolhido;
        // std::cout << escolhido << std::endl;

        //A roleta ainda não está definida para a retirada deste indivíduo
        if(score_total_sem[escolhido] == -1){
            double novo_total = score_total - score[escolhido];
            score_total_sem[escolhido] = novo_total;

            //Refatorar a roleta
            for(int j = 0; j < config.getPopSize()-1; j++){
                if(j != escolhido)
                {
                    if(j == 0 or (escolhido == 0 and j == 1))
                        score_relativo_sem[escolhido][j] = score[j]/novo_total;
                    else if(j == escolhido+1)
                        score_relativo_sem[escolhido][j] = score[j]/novo_total + score_relativo_sem[escolhido][j-2];
                    else
                        score_relativo_sem[escolhido][j] = score[j]/novo_total + score_relativo_sem[escolhido][j-1];
                }
            }
            if(escolhido == config.getPopSize()-1)
                score_relativo_sem[escolhido][config.getPopSize()-2] = 1.0;
            else
                score_relativo_sem[escolhido][config.getPopSize()-1] = 1.0;
            score_relativo_sem[escolhido][escolhido] = -1; //Inválido

        }

        //Procurar o segundo escolhido nesse par
        dice_roll = getRandDouble(0.0, 1.0);
        for(int j = 0; j < config.getPopSize(); j++){
            // std::cout << dice_roll << "  " << score_relativo_sem[escolhido][j] << std::endl;
            if(dice_roll < score_relativo_sem[escolhido][j]){
                escolhido2 = j;
                break;
            }
        }

        popul_temp[i+1].assign(popul[escolhido2].begin(), popul[escolhido2].end());
        // popul_temp[i+1] = escolhido2;
        // std::cout << escolhido2 << std::endl << std::endl;

    }

    return popul_temp;
}

template <typename T>
std::vector<std::vector<T> > Selection<T>::ranking_uniform(std::vector<std::vector<T> > &popul, std::vector<double> &score, Config &config){

    std::vector<size_t> idx = sort_indexes(score);
    std::vector<double> uniform_scores(config.getPopSize());
    // for(int i = 0; i < config.getPopSize(); i++){
    //     uniform_scores[i] = idx[i]+1;
    //     std::cout << uniform_scores[i] << std::endl;
    // }

    double rank = config.getPopSize();
    for(auto i : idx){
        
        uniform_scores[i] = rank;
        // std::cout << uniform_scores[i] << std::endl;        
        rank -= 1.0;
    }

    return roleta(popul, uniform_scores, config);
}


template <typename T>
std::vector<std::vector<T> > Selection<T>::torneio(std::vector<std::vector<T> > &popul, std::vector<double> &score, Config &config){
    std::vector<std::vector<T> > popul_temp(config.getPopSize(), std::vector<T>(config.getPopSize()));
    //São feitos n torneios, onde n é o tamanho da população
    for(int i = 0; i < config.getPopSize() ; i++){
        //Para cada torneio são escolhidos k indivíduos aleatoriamente, podendo haver repetição
        std::vector<int> torneiristas(config.getK());
        std::vector<double> seus_scores(config.getK());
        for(int j = 0; j < config.getK() ; j++){
            int who = getRandInt(0, config.getPopSize()-1);
            torneiristas[j] = who;
            seus_scores[j] = score[who];
        }
        //Se dice_roll < que a chance p (ou kp), o melhor é escolhido, caso contrário o pior
        double dice_roll = getRandDouble(0.0, 1.0);
        int escolhido;
        if(dice_roll < config.getProb()){
            escolhido = torneiristas[maior_elemento(seus_scores)];
        }
        else{
            escolhido = torneiristas[menor_elemento(seus_scores)];
        }
        // std::cout << escolhido << std::endl;

        //Colocamos o indiv escolhido na população temporária
        popul_temp[i].assign(popul[escolhido].begin(), popul[escolhido].end());
    }
    return popul_temp;
}

template <typename T>
std::vector<std::vector<T> > Selection<T>::vizinhanca(std::vector<std::vector<T> > &popul, std::vector<double> &score, Config &config){
    std::vector<std::vector<T> > popul_temp(config.getPopSize(), std::vector<T>(config.getPopSize()));
      
    //São escolhidos n/2 centros e 1 par para cada
    for(int i = 0; i < config.getPopSize(); i+=2){

        int center = getRandInt(0, config.getPopSize()-1);
        // std::cout << center << std::endl;
        popul_temp[i].assign(popul[center].begin(), popul[center].end());

        std::vector<int> vizinhos(config.getK()*2);
        std::vector<double> seus_scores(config.getK()*2);    
        
        //Criar a vizinhança circular
        int offset = -(center-config.getK());
        for(int j = center-config.getK(); j < center; j++){
            if(j < 0){
                vizinhos[j+offset] = config.getPopSize() + j;
                seus_scores[j+offset] = score[vizinhos[j+offset]];
            }
            else{
                vizinhos[j+offset] = j;
                seus_scores[j+offset] = score[vizinhos[j+offset]];
            }
        }

        for(int j = center+1; j < center+config.getK()+1; j++){
            if(j > config.getPopSize() - 1){
                vizinhos[j+offset-1] = j - config.getPopSize();
                seus_scores[j+offset-1] = score[vizinhos[j+offset-1]];
            }
            else{
                vizinhos[j+offset-1] = j;
                seus_scores[j+offset-1] = score[vizinhos[j+offset-1]];
            }
        }

        int escolhido = -1;
        if(config.getTipoSelec() == 0){ // Melhor fitness
            escolhido = vizinhos[maior_elemento(seus_scores)];
        }
        else if(config.getTipoSelec() == 1){ //Proporcional (Roleta)
            double score_total = 0.0;
            for(int j = 0; j < vizinhos.size(); j++){
                score_total += seus_scores[j];
            }

            std::vector<double> score_relativo(vizinhos.size());
            score_relativo[0] = seus_scores[0]/score_total;
            for(int j = 1; j < vizinhos.size(); j++){
                score_relativo[j] = seus_scores[j]/score_total + score_relativo[j-1];
            }


            double dice_roll = getRandDouble(0.0, 1.0);
            for(int j = 1; j < vizinhos.size(); j++){
                if(dice_roll < score_relativo[j]){
                    escolhido = vizinhos[j];
                    break;
                }
            }

        }
        else if(config.getTipoSelec() == 2){ //Aleatório
            escolhido = vizinhos[getRandInt(0, vizinhos.size()-1)];
        }
        popul_temp[i+1].assign(popul[escolhido].begin(), popul[escolhido].end());

        // std::cout << escolhido << std::endl << std::endl;

    }
   
    return popul_temp;  
}


template <typename T>
std::function<std::vector<std::vector<T> >(std::vector<std::vector<T> >&, std::vector<double>&, Config&) > Selection<T>::getFuncao(std::string name){
    if(name == "roleta"){
        return roleta;
    }
    else if(name == "ranking"){
        return ranking_uniform;
    }
    else if(name == "torneio"){
        return torneio;
    }
    else if(name == "vizinhanca"){
        return vizinhanca;
    }
    else{
        return NULL;
    }
}
