#ifndef CLASSE_GA
#define CLASSE_GA

#include <variant>

#include "util.hpp"
#include "Config.hpp"

template<typename T>
class GeneticAlgorithm{
protected:
    Config config;

    int geracao_atual;

    std::vector<std::vector<T> > popul;
    Score_Restricao score_r;

    std::vector<std::vector<T> > elite;
    Score_Restricao elite_score_r;

    double highest_diversity;


public:
    virtual ~GeneticAlgorithm();
    GeneticAlgorithm(Config &c);
    GeneticAlgorithm();
    
    virtual void run();

    void gerarPopulacao();


    void printPopulacao();

    Score_Restricao fitness();
    std::vector<std::vector<T> > selection();
    void crossover(std::vector<std::vector<T> > &popul);
    void mutacao(std::vector<std::vector<T> > &popul);

    double highestDiversity();
    double diversityMeasure();

    void escalonamentoLinear();
};

#include "GeneticAlgorithm.cpp"


#endif
