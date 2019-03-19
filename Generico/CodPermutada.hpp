#ifndef CLASSE_CODPERMUTADA
#define CLASSE_CODPERMUTADA

#include "Populacao.hpp"

class CodPermutada : public Populacao{
friend class FactoryPopulacao;
private:
    vvi mat;

    CodPermutada();
    ~CodPermutada();

    void gerar();
    void print();

public:
};


#endif
