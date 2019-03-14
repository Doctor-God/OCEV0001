#ifndef CLASSE_POPULACAO
#define CLASSE_POPULACAO

#include <variant>
#include "util.hpp"

class Populacao{
private:
    std::variant<vvb, vvi, vvd> mat;
    int indiv;
    int vars;
    int tipo;
    std::variant<int, double> upper;
    std::variant<int, double> lower;

    template <typename T>
    void print();


public:
    Populacao(int size, int n_vars, int tipo, std::variant<int, double> upper, std::variant<int, double> lower);

    ~Populacao();

    void gerar();

    void print();

};

#endif
