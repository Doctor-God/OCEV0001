#-*- coding:utf-8 -*-

import sys
import numpy as np
import matplotlib.pyplot as plt
# from matplotlib import rc

# rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
# rc('text', usetex=True)

def main(argv):
    nome_arq = argv[1]
    arq = open("testes/" + nome_arq + "-geracoes")
    arq = arq.read().split("\n")
    nro_testes = int(arq[0])
    generations = int(arq[1])+1
    del arq[0]
    del arq[0]

    testes = [None]*nro_testes
    for i in range(0,nro_testes):
        # arq = [float(i) for i in arq]
        testes[i] = np.array(arq[i*generations*3:i*generations*3 + (generations)*3], dtype=np.float64)


    maiores = np.empty([generations], dtype=np.float64)
    menores = np.empty([generations], dtype=np.float64)
    medias = np.empty([generations], dtype=np.float64)


    for i in range(0,generations):
        maior = 0.0
        menor = 0.0
        media = 0.0
        for j in range(0, nro_testes):
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
    # print(maiores)

    # plt.ylim(0.0, 1.0)


    plt.plot(maiores, color = 'red')
    plt.plot(medias, color = 'yellow')
    plt.plot(menores, color = 'blue')

    # plt.rc('text', usetex=True)
    # plt.rc('font', family='serif')

    # plt.xlabel(r'Gera\c{c}\~{a}o')
    # plt.ylabel(r'Fitness')

    plt.savefig("testes/" + nome_arq + "_conv.png")

    plt.close()

    res_finais = np.empty([nro_testes], dtype=np.float64)

    for j in range(nro_testes):
        res_finais = testes[j][(generations-1)*3]

    plt.boxplot(res_finais)

    plt.savefig("testes/" + nome_arq + "_boxplot.png")




if __name__ == "__main__":
    main(sys.argv)
    exit()