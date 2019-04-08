#ifndef CLASSE_CONFIG
#define CLASSE_CONFIG

#include <string>
#include <variant>

class Config{
private:
    int pop_size;
    int n_vars;
    std::variant<int, double> lower;
    std::variant<int, double> upper;
    std::string problem;
    std::string selection_method;
    int k; //Número de indiv no torneio ou distancia no selecao local
    double prob; //Probabilidade no torneio
    int tipo_selecao_vizinhanca; //Tipo de seleacao dentro da vizinhanca
    double prob_crossover;
    double prob_mutacao;
public:
    Config();

    int getPopSize();
    int getNumVars();
    std::variant<int, double> getLowerBound();
    std::variant<int, double> getUpperBound();
    std::string getProblem();
    std::string getSelectionMethod();
    int getK();
    double getProb();
    int getTipoSelec();
    double getProbCrossover();
    double getProbMutacao();

    void setPopSize(int pop_size);
    void setNumVars(int n_vars);
    void setLowerBound(std::variant<int, double> lower);
    void setUpperBound(std::variant<int, double> upper);
    void setProblem(std::string problem);
    void setSelectionMethod(std::string selection_method);
    void setK(int k);
    void setProb(double prob);
    void setTipoSelec(int tipo);
    void setProbCrossover(double prob_crossover);
    void setProbMutacao(double prob_mutacao);
};

#endif
