#-*- coding:utf-8 -*-

import sys
import numpy as np
import matplotlib.pyplot as plt
# from matplotlib import rc

# rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
# rc('text', usetex=True)

def main(argv):
    nro_testes = int(argv[2])
    nome_arq = argv[1]
    testes = [None]*nro_testes
    generations = 0
    for i in range(0,nro_testes):
        arq = open("testes/" + nome_arq + "-" + str(i))
        arq = arq.read().split("\n")
        generations = int(arq[0])+1
        del arq[0]
        del arq[-1]
        # arq = [float(i) for i in arq]
        testes[i] = np.array(arq, dtype=np.float64)

    maiores = np.empty([generations], dtype=np.float64)
    menores = np.empty([generations], dtype=np.float64)
    medias = np.empty([generations], dtype=np.float64)

    for i in range(0,generations):
        maior = 0.0
        menor = 0.0
        media = 0.0
        for j in range(nro_testes):
            maior += testes[j][i*3]
            menor += testes[j][i*3 + 1]
            media += testes[j][i*3 + 2]
        maior /= nro_testes
        menor /= nro_testes
        media /= nro_testes
        
        maiores[i] = maior
        menores[i] = menor
        medias[i] = media

    maiores = np.insert(maiores, 0, 0, axis=0)
    medias = np.insert(medias, 0, 0, axis=0)
    menores = np.insert(menores, 0, 0, axis=0)

    # plt.ylim(0.0, 1.0)


    plt.plot(maiores, color = 'red')
    plt.plot(medias, color = 'yellow')
    plt.plot(menores, color = 'blue')

    # plt.rc('text', usetex=True)
    # plt.rc('font', family='serif')

    # plt.xlabel(r'Gera\c{c}\~{a}o')
    # plt.ylabel(r'Fitness')

    plt.show()


if __name__ == "__main__":
    main(sys.argv)
    exit()