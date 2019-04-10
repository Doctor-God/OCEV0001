#ifndef CLASSE_CONFIG
#define CLASSE_CONFIG

#include <string>
#include <variant>
#include <iostream>

class Config{
private:
    int tipo;
    int pop_size;
    int n_vars;
    int generations;
    std::variant<int, double> lower;
    std::variant<int, double> upper;
    std::string problem;
    std::string selection_method;
    int n_elitistas;
    int k; //Número de indiv no torneio ou distancia no selecao local
    double prob; //Probabilidade no torneio
    int tipo_selecao_vizinhanca; //Tipo de seleacao dentro da vizinhanca
    int tipo_crossover; //um ou dois pontos
    double prob_crossover;
    double prob_mutacao;
    bool saida_arquivo;
public:
    Config();

    int getTipo();
    int getPopSize();
    int getNumVars();
    int getGenerations();
    std::variant<int, double> getLowerBound();
    std::variant<int, double> getUpperBound();
    std::string getProblem();
    std::string getSelectionMethod();
    int getNumElitistas();
    int getK();
    double getProb();
    int getTipoSelec();
    int getCrossoverType();
    double getProbCrossover();
    double getProbMutacao();
    bool getSaidaArquivo();


    void setTipo(int tipo);
    void setPopSize(int pop_size);
    void setNumVars(int n_vars);
    void setGenerations(int gen);
    void setLowerBound(std::variant<int, double> lower);
    void setUpperBound(std::variant<int, double> upper);
    void setProblem(std::string problem);
    void setSelectionMethod(std::string selection_method);
    void setNumElitistas(int num);
    void setK(int k);
    void setProb(double prob);
    void setTipoSelec(int tipo);
    void setCrossoverType(int tipo);
    void setProbCrossover(double prob_crossover);
    void setProbMutacao(double prob_mutacao);
    void setSaidaArquivo(bool flag);
};

#endif
