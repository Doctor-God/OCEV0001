#ifndef CLASSE_POPULACAO
#define CLASSE_POPULACAO

typedef vector<vector<int> > vvi;
typedef vector<vector<bool> > vvb;
typedef vector<vector<double> > vvd;

class Populacao{
private:
    std::variant<vvb, vvi, vvd> pop;
    int indiv;
    int vars;
    int tipo;
public:
    Populacao(int size, int n_vars, int tipo, std::variant<int, double> upper, std::variant<int, double> lower);

    print()

};

#endif
