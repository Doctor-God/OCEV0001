    #include "Config.hpp"
    
    //Seta os valores default
    Config::Config(){
        pop_size = 10;
        selection_method = "torneio";
        k = 2;
        prob = 1.0;
        tipo_selecao_vizinhanca = 0; //Melhor fitness
        prob_crossover = 0.9;
        prob_mutacao = 0.05;
    }
        
    int Config::getPopSize(){return pop_size;}
    int Config::getNumVars(){return n_vars;}
    std::variant<int, double> Config::getLowerBound() {return lower;}
    std::variant<int, double> Config::getUpperBound() {return upper;}
    std::string Config::getProblem() {return problem;}
    std::string Config::getSelectionMethod() {return selection_method;}
    int Config::getK() {return k;}
    double Config::getProb() {return prob;}
    int Config::getTipoSelec() {return tipo_selecao_vizinhanca;}
    double Config::getProbCrossover() {return prob_crossover;}
    double Config::getProbMutacao() {return prob_mutacao;}

    void Config::setPopSize(int pop_size){this->pop_size = pop_size;}
    void Config::setNumVars(int n_vars){this->n_vars = n_vars;}
    void Config::setLowerBound(std::variant<int, double> lower) {this->lower = lower;}
    void Config::setUpperBound(std::variant<int, double> upper) {this->upper = upper;}
    void Config::setProblem(std::string problem) {this->problem = problem;}
    void Config::setSelectionMethod(std::string selection_method) {this->selection_method = selection_method;}
    void Config::setK(int k) {this->k = k;}
    void Config::setProb(double prob) {this->prob = prob;}
    void Config::setTipoSelec(int tipo) {this->tipo_selecao_vizinhanca = tipo;}
    void Config::setProbCrossover(double prob_crossover) {this->prob_crossover = prob_crossover;}
    void Config::setProbMutacao(double prob_mutacao) {this->prob_mutacao = prob_mutacao;}