#ifndef CLASSE_POPULACAO
#define CLASSE_POPULACAO

#include <variant>

#include "util.hpp"

class Populacao{
protected:
    int indiv;
    int vars;
    std::string problem;

    Populacao();
    ~Populacao();

public:


    virtual void gerar() = 0;

    virtual void print() = 0;

    // virtual std::vector<double> fitness();
    virtual std::vector<double> fitness() = 0;

};

class FactoryPopulacao{
private:
    FactoryPopulacao();
public:
    static Populacao *build(int size, int n_vars, int tipo, std::string problem, std::variant<int, double> upper, std::variant<int, double> lower);
};

#endif
