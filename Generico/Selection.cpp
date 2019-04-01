std::vector<std::vector<T> > roleta(std::vector<std::vector<T> > popul, std::vector<double> score){
    //Cria população intermediária
    std::vector<std::vector<T> > popul_temp(popul.size()*2, std::vector<std::vector<T> >(popul.size()));
    std::vector<double> score_relativo(popul.size());
    std::vector<std::vector<double> > score_relativo_sem(popul.size(), vector<double>(popul.size())); //Guardar a roleta sem um indivíduo específico
    std:vector<double> score_total_sem(popul.size(), -1); //Soma de score sem um indivíduo específico

    double score_total = 0;
    for(int i = 0; i < popul.size(); i++){
        score_total += score[i];
    }

    //Calcular o score relativo ao total na população e já adequar à roleta
    for(int i = 0; i < popul.size()-1; i++){
        if(i == 0)
            score_relativo = score[i]/score_total;
        else
            score_relativo = score[i]/score_total + score[i-1];
    }
    score_relativo[popul.size()-1] = 1.0;

    //Escolhem-se pares de indivíduos
    for(int i = 0; i < popul.size(); i++){
        double dice_roll = getRandDouble(0.0, 1.0);
        int escolhido = -1;
        int escolhido2 = -1;

        for(int j = popul.size()-1; j >= 0; j--){
            //Se dice_roll for maior significa que passamos do escolhido
            if(dice_roll > score_relativo[j]){
                escolhido = j+1;
                break;
            }
        }
        if(escolhido == -1)
            escolhido = 0;

        //Colocamos escolhido na populacao intermediaria
        popul_temp[i].assign(popul[escolhido].begin(), popul[escolhido].end());

        if(score_total_sem[escolhido] == -1){
            double novo_total = score_total - score[escolhido];
            score_total_sem[escolhido] = novo_total;

            //Refatorar a roleta partir do indivíduo escolhido, pois foi retirado
            for(int j = 0; j < popul.size()-1; j++){
                if(j != escolhido)
                {
                    if(j == 0 or (escolhido == 0 and j == 1))
                        score_relativo_sem[escolhido][j] = score[j]/novo_total;
                    else if(j == escolhido+1)
                        score_relativo_sem[escolhido][j] = score[j]/novo_total + score[j-2]
                    else
                        score_relativo_sem[escolhido][j] = score[j]/novo_total + score[j-1];
                }
            }
            score_relativo[popul.size()-1] = 1.0;

        }
        for(int j = popul.size()-1; j >= 0; j--){
            //Se dice_roll for maior significa que passamos do escolhido
            if(j != escolhido){
                if(dice_roll > score_relativo_sem[escolhido][j]){
                    if(j == escolhido-1)
                        escolhido2 = j+2;
                    escolhido2 = j+1;
                    break;
                }
            }
        }
        if(escolhido2 == -1)
            escolhido2 = 0;

        popul_temp[i+1].assign(popul[escolhido2].begin(), popul[escolhido2].end());
    }

    return popul_temp;
}


std::function<std::vector<std::vector<T> >(std::vector<std::vector<T> >, std::vector<double>) > Selection::getFuncao(std::string name){
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
