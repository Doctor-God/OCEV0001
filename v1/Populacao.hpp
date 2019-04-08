#ifndef CLASSE_POPULACAO
#define CLASSE_POPULACAO

#include <variant>

#include "util.hpp"
#include "Config.hpp"

class Populacao{
protected:
    Config config;

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

    // std::vector<double> getScores();

};

class FactoryPopulacao{
private:
    FactoryPopulacao();
public:
    static Populacao *build(int tipo, Config &c);
};

#endif
