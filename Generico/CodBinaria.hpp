#ifndef CLASSE_CODBINARIA
#define CLASSE_CODBINARIA

#include "Populacao.hpp"

class CodBinaria : public Populacao{
friend class FactoryPopulacao;
private:
    vvb mat;

    CodBinaria();
    ~CodBinaria();

    void gerar();
    void print();

    double GA();

    Score_Restricao fitness();

    vvb selection();


public:
};


#endif
