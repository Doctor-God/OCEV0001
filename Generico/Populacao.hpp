#ifndef CLASSE_POPULACAO
#define CLASSE_POPULACAO

#include <variant>

#include "util.hpp"

class Populacao{
protected:
    int indiv;
    int vars;
    std::string problem;
    std::string selection_method;

    int k_unid;
    double prob;

    Score_Restricao score_r;

    Populacao();
    ~Populacao();

public:
    virtual void gerar() = 0;

    virtual void print() = 0;

    // virtual std::vector<double> fitness();
    virtual Score_Restricao fitness() = 0;
    virtual double GA() = 0; //Precisa pensar em um retorno genérico 
    // virtual std::vector<int> bestFit() = 0;

};

class FactoryPopulacao{
private:
    FactoryPopulacao();
public:
    static Populacao *build(int size, int n_vars, int tipo, std::string problem, std::string select, Parameters p);
};

#endif
