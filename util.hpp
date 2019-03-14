#ifndef UTIL
#define UTIL

#include <vector>


typedef std::vector<std::vector<int> > vvi;
typedef std::vector<std::vector<bool> > vvb;
typedef std::vector<std::vector<double> > vvd;

int getRandInt(int a, int b);

double getRandDouble(double a, double b);

void shuffle(std::vector<int> &v);


#endif