#include "Problem.hpp"

Problem::Problem(){
    funcao.add["nqueens"] = nQUeens;
}

FnPtr getFunc(std::string nome){
    return funcao[nome];
}


double Problem::nQueens(vector<int> indiv){

}
