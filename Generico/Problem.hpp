#ifndef CLASSE_PROBLEM
#define CLASSE_PROBLEM

#include <map>

typedef double (*b_func)(std::vector<bool>);
typedef double (*i_func)(std::vector<int>);
typedef double (*d_func)(std::vector<double>);

class Problem{
private:
    std::map<std::string, b_func> b_funcao;
    std::map<std::string, i_func> i_funcao;
    std::map<std::string, d_func> d_funcao;
    double nQueens(std::vector<double> indiv);

public:
    Problem();
    b_func get_bFunc(std::string nome);
    i_func get_iFunc(std::string nome);
    d_func get_dFunc(std::string nome);
};

#endif
