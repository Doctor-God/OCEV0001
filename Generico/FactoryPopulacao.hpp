#ifndef CLASSE_FACTORY
#define CLASSE_FACTORY

#include "CodInteira.hpp"

class FactoryPopulacao{
private:
    FactoryPopulacao();
public:
    static Populacao *build(int size, int n_vars, int tipo, std::variant<int, double> upper, std::variant<int, double> lower);
};

#endif