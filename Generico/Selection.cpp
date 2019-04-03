template <typename T>
std::vector<std::vector<T> > Selection<T>::roleta(std::vector<std::vector<T> > popul, std::vector<double> score){
    //Cria população intermediária
    std::vector<std::vector<T> > popul_temp(popul.size(), std::vector<T>(popul.size()));
    // std::vector<int> popul_temp(popul.size()*2);
    
    std::vector<double> score_relativo(popul.size());
    std::vector<std::vector<double> > score_relativo_sem(popul.size(), std::vector<double>(popul.size())); //Guardar a roleta sem um indivíduo específico
    std::vector<double> score_total_sem(popul.size(), -1); //Soma de score sem um indivíduo específico


    //Calcula o score total da popul (soma dos scores)
    double score_total = 0;
    for(int i = 0; i < popul.size(); i++){
        score_total += score[i];
    }
    //Calcular o score relativo ao total na população e já adequar à roleta
    for(int i = 0; i < popul.size()-1; i++){
        if(i == 0)
            score_relativo[i] = score[i]/score_total;
        else
            score_relativo[i] = score[i]/score_total + score[i-1];
    }
    score_relativo[popul.size()-1] = 1.0;

    //Escolhem-se pares de indivíduos
    for(int i = 0; i < popul.size(); i += 2){
        double dice_roll = getRandDouble(0.0, 1.0);
        int escolhido = -1;
        int escolhido2 = -1;

        //Percorremos a roleta até encontrar um valor maior que dice_rol
        //ou seja, encontramos o intervalo do escolhido
        for(int j = 0; j < popul.size(); j++){
            if(dice_roll < score_relativo[j]){
                escolhido = j;
                break;
            }
        }

        //Colocamos escolhido na populacao intermediaria
        popul_temp[i].assign(popul[escolhido].begin(), popul[escolhido].end());
        // popul_temp[i] = escolhido;
        std::cout << escolhido << std::endl;

        //A roleta ainda não está definida para a retirada deste indivíduo
        if(score_total_sem[escolhido] == -1){
            double novo_total = score_total - score[escolhido];
            score_total_sem[escolhido] = novo_total;

            //Refatorar a roleta
            for(int j = 0; j < popul.size()-1; j++){
                if(j != escolhido)
                {
                    if(j == 0 or (escolhido == 0 and j == 1))
                        score_relativo_sem[escolhido][j] = score[j]/novo_total;
                    else if(j == escolhido+1)
                        score_relativo_sem[escolhido][j] = score[j]/novo_total + score[j-2];
                    else
                        score_relativo_sem[escolhido][j] = score[j]/novo_total + score[j-1];
                }
            }
            if(escolhido == popul.size()-1)
                score_relativo_sem[escolhido][popul.size()-2] = 1.0;
            else
                score_relativo_sem[escolhido][popul.size()-1] = 1.0;
            score_relativo_sem[escolhido][escolhido] = -1; //Inválido

        }

        dice_roll = getRandDouble(0.0, 1.0);
        for(int j = 0; j < popul.size(); j++){
            // std::cout << dice_roll << "  " << score_relativo_sem[escolhido][j] << std::endl;
            if(dice_roll < score_relativo_sem[escolhido][j]){
                escolhido2 = j;
                break;
            }
        }

        popul_temp[i+1].assign(popul[escolhido2].begin(), popul[escolhido2].end());
        // popul_temp[i+1] = escolhido2;
        std::cout << escolhido2 << std::endl << std::endl;

    }

    return popul_temp;
}


template <typename T>
std::vector<std::vector<T> > Selection<T>::ranking_uniform(std::vector<std::vector<T> > popul, std::vector<double> score){
    std::vector<std::vector<T> > popul_temp(popul.size()*2, std::vector<T>(popul.size()));
    return popul_temp;
}

template <typename T>
std::vector<std::vector<T> > Selection<T>::torneio(std::vector<std::vector<T> > popul, std::vector<double> score){
    std::vector<std::vector<T> > popul_temp(popul.size()*2, std::vector<T>(popul.size()));
    return popul_temp;
}

template <typename T>
std::vector<std::vector<T> > Selection<T>::selecao_local(std::vector<std::vector<T> > popul, std::vector<double> score){
    std::vector<std::vector<T> > popul_temp(popul.size()*2, std::vector<T>(popul.size()));
    return popul_temp;  
}


template <typename T>
std::function<std::vector<std::vector<T> >(std::vector<std::vector<T> >, std::vector<double>) > Selection<T>::getFuncao(std::string name){
    if(name == "roleta"){
        return roleta;
    }
    else if(name == "ranking"){
        return ranking_uniform;
    }
    else if(name == "torneio"){
        return torneio;
    }
    else if(name == "local"){
        return selecao_local;
    }
    else{
        return NULL;
    }
}
