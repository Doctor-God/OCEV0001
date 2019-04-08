#ifndef CLASSE_GA
#define CLASSE_GA

#include <variant>

#include "util.hpp"
#include "Config.hpp"

template<typename T>
class GeneticAlgorithm{
protected:
    Config config;

    std::vector<std::vector<T> > popul;
    Score_Restricao score_r;

    std::vector<std::vector<T> > elite;
    Score_Restricao elite_score_r;


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

};

class CodInteira : public GeneticAlgorithm<int>{
public:
    CodInteira(Config &c);

    void run();

    void gerarPopulacao();

    void crossover(std::vector<std::vector<int> > &popul);
    void mutacao(std::vector<std::vector<int> > &popul);
};

class CodPermutada : public GeneticAlgorithm<int>{
public:
    CodPermutada(Config &c);
   
    void run();

    void gerarPopulacao();

    void crossover(std::vector<std::vector<int> > &popul);
    void mutacao(std::vector<std::vector<int> > &popul);
};

#include "GeneticAlgorithm.cpp"


#endif
