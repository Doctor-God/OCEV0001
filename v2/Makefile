CXXFLAGS = -std=c++17 -fopenmp -O3

all: trab

trab: util.cpp Config.cpp Problem.hpp Selection.hpp gera_pop.cpp
	g++-7 $(CXXFLAGS) util.cpp Config.cpp Problem.hpp Selection.hpp gera_pop.cpp
