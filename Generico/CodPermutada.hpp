#ifndef CLASSE_CODPERMUTADA
#define CLASSE_CODPERMUTADA

#include "Populacao.hpp"
#include "Problem.hpp"


class CodPermutada : public Populacao{
friend class FactoryPopulacao;
private:
    vvi mat;

    CodPermutada();
    ~CodPermutada();

    void gerar();
    void print();

    std::vector<double> fitness();

    std::vector<double> fitness(std::function<std::vector<double>(vvi) > avalia);

    // vector<int> bestFit();


public:
};


#endif
