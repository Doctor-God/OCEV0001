#ifndef CLASSE_CODINTEIRA
#define CLASSE_CODINTEIRA

#include <functional>
#include "util.hpp"

template<typename T>
class Selection{
private:
    Selection(){};
    std::vector<std::vector<T> > roleta(std::vector<std::vector<T> > popul, std::vector<double> score);    
    std::vector<std::vector<T> > ranking_uniform(std::vector<std::vector<T> > popul, std::vector<double> score);
    std::vector<std::vector<T> > torneio(std::vector<std::vector<T> > popul, std::vector<double> score);
    std::vector<std::vector<T> > selecao_local(std::vector<std::vector<T> > popul, std::vector<double> score);

public:
    std::function<std::vector<std::vector<T> >(std::vector<std::vector<T> >, std::vector<double>) > getFuncao(std::string name);

};

#include "Selection.cpp"

#endif
