#ifndef CLASSE_CODINTEIRA
#define CLASSE_CODINTEIRA

#include "Populacao.hpp"

class CodInteira : public Populacao{
friend class FactoryPopulacao;
private:
    vvi mat;


    CodInteira();
    ~CodInteira();

    void gerar();
    void print();

    double GA();

    Score_Restricao fitness();

    vvi selection();

public:

};


#endif
