#ifndef CLASSE_CODINTEIRA
#define CLASSE_CODINTEIRA

#include "Populacao.hpp"

class CodInteira : public Populacao{
friend class FactoryPopulacao;
private:
    vvi mat;
    int upper;
    int lower;


    CodInteira();
    ~CodInteira();

    void gerar();
    void print();

    std::vector<double> fitness();

public:

    void setUpper(int u);
    void setLower(int u);

};


#endif
