#ifndef CLASSE_CODBINARIA
#define CLASSE_CODBINARIA

#include "Populacao.hpp"
#include "Problem.hpp"

class CodBinaria : public Populacao{
friend class FactoryPopulacao;
private:
    vvb mat;

    CodBinaria();
    ~CodBinaria();

    void gerar();
    void print();

    std::vector<double> fitness();
	std::vector<double> fitness(std::function<std::vector<double>(vvb) > avalia);


public:
};


#endif
