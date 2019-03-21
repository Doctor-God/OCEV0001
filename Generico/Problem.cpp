#include "Problem.hpp"

Problem::Problem();
    i_funcao.add["nqueens"] = nQUeens;
}

b_func Problem::get_bFunc(std::string nome){
    return b_funcao[nome];

}

i_func Problem::get_iFunc(std::string nome){
    return i_funcao[nome];
}

d_func Problem::get_dFunc(std::string nome){
    return d_funcao[nome];
}


double Problem::nQueens(std::vector<int> indiv){

}
