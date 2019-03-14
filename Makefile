CXXFLAGS = -std=c++17

all: trab
 
trab: util.cpp Populacao.cpp gera_pop.cpp
	g++-7 $(CXXFLAGS) util.cpp Populacao.cpp gera_pop.cpp

