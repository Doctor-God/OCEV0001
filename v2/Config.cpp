    #include "Config.hpp"
    
    //Seta os valores default
    Config::Config(){
        pop_size = 10;
        generations = 1000;
        selection_method = "torneio";
        n_elitistas = 1;
        k = 2;
        prob = 1.0;
        tipo_selecao_vizinhanca = 0; //Melhor fitness
        tipo_crossover = 1;
        prob_crossover = 0.9;
        prob_mutacao = 0.05;
    }
        
    int Config::getTipo(){return tipo;}
    int Config::getPopSize(){return pop_size;}
    int Config::getNumVars(){return n_vars;}
    int Config::getGenerations() {return generations;}
    std::variant<int, double> Config::getLowerBound() {return lower;}
    std::variant<int, double> Config::getUpperBound() {return upper;}
    std::string Config::getProblem() {return problem;}
    std::string Config::getSelectionMethod() {return selection_method;}
    int Config::getNumElitistas(){return n_elitistas;}
    int Config::getK() {return k;}
    double Config::getProb() {return prob;}
    int Config::getTipoSelec() {return tipo_selecao_vizinhanca;}
    int Config::getCrossoverType() {return tipo_crossover;}
    double Config::getProbCrossover() {return prob_crossover;}
    double Config::getProbMutacao() {return prob_mutacao;}

    void Config::setTipo(int tipo) {this->tipo = tipo;}
    void Config::setPopSize(int pop_size) {this->pop_size = pop_size;}
    void Config::setNumVars(int n_vars) {this->n_vars = n_vars;}
    void Config::setGenerations(int gen) {this->generations = gen;}
    void Config::setLowerBound(std::variant<int, double> lower) {this->lower = lower;}
    void Config::setUpperBound(std::variant<int, double> upper) {this->upper = upper;}
    void Config::setProblem(std::string problem) {this->problem = problem;}
    void Config::setSelectionMethod(std::string selection_method) {this->selection_method = selection_method;}
    void Config::setNumElitistas(int num) {this->n_elitistas = num;}
    void Config::setK(int k) {this->k = k;}
    void Config::setProb(double prob) {this->prob = prob;}
    void Config::setTipoSelec(int tipo) {this->tipo_selecao_vizinhanca = tipo;}
    void Config::setCrossoverType(int tipo) {this->tipo_crossover = tipo;}
    void Config::setProbCrossover(double prob_crossover) {this->prob_crossover = prob_crossover;}
    void Config::setProbMutacao(double prob_mutacao) {this->prob_mutacao = prob_mutacao;}