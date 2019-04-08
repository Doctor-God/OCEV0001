#ifndef CLASSE_SELECTION
#define CLASSE_SELECTION    

#include <functional>
#include "util.hpp"
#include "Config.hpp"

template<typename T>
class Selection{
private:
    static std::vector<std::vector<T> > roleta(std::vector<std::vector<T> > &popul, std::vector<double> &score, Config &config);    
    static std::vector<std::vector<T> > ranking_uniform(std::vector<std::vector<T> > &popul, std::vector<double> &score, Config &config);
    static std::vector<std::vector<T> > torneio(std::vector<std::vector<T> > &popul, std::vector<double> &score, Config &config);
    static std::vector<std::vector<T> > vizinhanca(std::vector<std::vector<T> > &popul, std::vector<double> &score, Config &config);

public:
    Selection(){};
    std::function<std::vector<std::vector<T> >(std::vector<std::vector<T> >&, std::vector<double>&, Config&) > getFuncao(std::string name);

};

#include "Selection.cpp"

#endif
