CXXFLAGS = -std=c++17 -fopenmp

all: trab

trab: util.cpp Config.cpp Problem.hpp Selection.hpp gera_pop.cpp
	g++-7 $(CXXFLAGS) util.cpp Config.cpp Problem.hpp Selection.hpp gera_pop.cpp
