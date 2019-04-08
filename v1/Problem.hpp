#ifndef CLASSE_PROBLEM
#define CLASSE_PROBLEM

#include <map>
#include <functional>
#include <algorithm>
#include "Config.hpp"
#include "util.hpp"


// typedef double (*b_func)(std::vector<bool>);
// typedef double (*i_func)(std::vector<int>);
// typedef double (*d_func)(std::vector<double>);



template <typename T>
class Problem{
private:
    std::map<std::string, std::function<Score_Restricao(std::vector<std::vector<T> >&, Config&)> > funcao;
    static Score_Restricao nQueens(vvi &popul, Config &config);
	static Score_Restricao slide_max(vvb &popul, Config &config);
    static Score_Restricao fabrica_radios(vvb &popul, Config &config);


public:
    Problem();
    std::function<Score_Restricao(std::vector<std::vector<T> >&, Config&)> getFuncao(std::string nome);
};

#include "Problem.cpp"

#endif
