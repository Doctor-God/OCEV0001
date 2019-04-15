#ifndef CLASSE_PROBLEM
#define CLASSE_PROBLEM

#include <map>
#include <functional>
#include <algorithm>
#include "Config.hpp"
#include "util.hpp"


template <typename T>
class Problem{
private:
    std::map<std::string, std::function<Score_Restricao(std::vector<std::vector<T> >&, Config&)> > funcao;
    std::map<std::string, std::function<void(std::vector<T>&, Config&)> > decoder;
   
    static Score_Restricao nQueens(std::vector<std::vector<int_permut_t> > &popul, Config &config);
    static void nQueens_decoder(std::vector<int_permut_t> &indiv, Config &config);

    static Score_Restricao nQueens_weight(std::vector<std::vector<int_permut_t>> &popul, Config &config);
    static void nQueens_weight_decoder(std::vector<int_permut_t> &indiv, Config &config);

    static Score_Restricao slide_max(vvb &popul, Config &config);
    static void slide_max_decoder(std::vector<bool> &indiv, Config &config);
    
    static Score_Restricao fabrica_radios(vvb &popul, Config &config);
    static void fabrica_radios_decoder(std::vector<bool> &indiv, Config &config);



public:
    Problem();
    std::function<Score_Restricao(std::vector<std::vector<T> >&, Config&)> getFuncao(std::string nome);
    std::function<void(std::vector<T>&, Config&)> getDecoder(std::string nome);
};

#include "Problem.cpp"

#endif
