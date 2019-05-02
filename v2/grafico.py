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

    final = len(maiores)-1
    fig, ax = plt.subplots()
    ax.set_xlim(left=0, right=generations+1)

    plt.plot(maiores, color = 'red', label="Melhor")
    plt.plot(medias, color = 'green', label="Média")
    plt.plot(menores, color = 'blue', label = "Pior")


    ax2 = ax.twinx()
    ax2.set_yticks(list(ax.get_yticks()) + [maiores[final]])
    fig.canvas.draw()
    temp_ticks = ax2.get_yticklabels()
    for tick in temp_ticks:
        if(tick.get_position()[1] != maiores[final]):
            tick.set_visible(False)
        else:
            tick.set_color("red")

    # for i in xrange(5):
    #     line, = ax.plot(x, i * x, label='$y = %ix$'%i)

    box = ax.get_position()
    ax.set_position([box.x0, box.y0 + box.height * 0.1, box.width, box.height * 0.9])
    box = ax2.get_position()
    ax2.set_position([box.x0, box.y0 + box.height * 0.1, box.width, box.height * 0.9])


    ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.05),
                fancybox=True, shadow=True, ncol=3)

    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    ax2.spines['top'].set_visible(False)
    ax2.spines['right'].set_visible(False)


    # plt.yticks(list(plt.yticks()[0]) + [maiores[final]])
    # ticks = ax.get_yticks()

    # ax2 = ax.twinx()
    
    # ax2.set_yticks(maiores[final])

    # yticks = ax2.yaxis.get_major_ticks()
    # for tick in yticks:
    #     ticks.label1.set_visible(False)

    # yticks = list(yticks)[0] + [maiors[final]]

    # plt.rc('text', usetex=True)
    # plt.rc('font', family='serif')

    # plt.xlabel(r'Gera\c{c}\~{a}o')
    # plt.ylabel(r'Fitness')

    plt.savefig("testes/" + nome_arq + "_conv.png")

    plt.close()

    res_finais = np.empty([nro_testes], dtype=np.float64)

    for j in range(nro_testes):
        res_finais[j] = testes[j][(generations-1)*3]

    mu = res_finais.mean()
    sigma = res_finais.std()
    textstr = '\n'.join((
    r'$\mu=%.4f$' % (mu, ),
    r'$\sigma=%.4f$' % (sigma, )))

    fig, ax = plt.subplots();

    ax.text(0.05, 0.95, textstr, transform=ax.transAxes, fontsize=14,
        verticalalignment='top')

    plt.boxplot(res_finais)

    plt.savefig("testes/" + nome_arq + "_boxplot.png")




if __name__ == "__main__":
    main(sys.argv)
    exit()