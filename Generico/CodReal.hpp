#ifndef CLASSE_CODREAL
#define CLASSE_CODREAL

#include "Populacao.hpp"

class CodReal : public Populacao{
friend class FactoryPopulacao;
private:
    vvd mat;
    int upper;
    int lower;


    CodReal();
    ~CodReal();

    void gerar();
    void print();

public:

    void setUpper(double u);
    void setLower(double u);

};


#endif
