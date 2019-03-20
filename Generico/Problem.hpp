#ifndef CLASSE_PROBLEMS
#define CLASSE_PROBLEMS

#include <map>

class Problem{
private:
    map<std::string><FnPtr> funcao;
    double nQueens(vector<int> indiv);

public:
    Problem();
    FnPtr getFunc(std::string nome);
};

#endif
