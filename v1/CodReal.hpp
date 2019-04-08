#ifndef CLASSE_CODREAL
#define CLASSE_CODREAL

#include "Populacao.hpp"

class CodReal : public Populacao{
friend class FactoryPopulacao;
private:
    vvd mat;


    CodReal();
    ~CodReal();

    void gerar();
    void print();

    double GA();

    Score_Restricao fitness();
    vvd selection();


public:

};


#endif
