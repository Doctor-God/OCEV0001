#-*-coding:utf8-*-

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as anim
import matplotlib.cm as cm
import sys

#Movimentos
mov = []
with open(sys.argv[1]) as f:
    for line in f:
        mov = [int(i) for i in line.split()]


#Labirinto
lab = [[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0],[0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,1,0],[0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0],[0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,0],[0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0],[0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0],[0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0],[0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,0],[0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,0,1,0],[0,1,1,1,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0],[0,1,0,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0],[0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0],[0,1,0,0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0],[0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0],[0,1,1,0,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,1,0,0,1,0],[0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0],[0,0,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,0,0],[0,1,1,0,0,0,1,1,0,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,0],[0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0],[0,0,0,0,1,0,0,0,0,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0],[0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0],[0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0],[0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0],[0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0],[0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0],[0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,0],[0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0],[0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]
#Transforma em rgb
for x in range(30):
    for y in range(25):
        if(lab[x][y] == 0):
            lab[x][y] = [0,0,0]
        else:
            lab[x][y] = [1,1,1]
lab = np.asarray(lab)

fig = plt.figure()
ims = []
atual = [10, 1]

def update(i):
# for i in range(len(mov)):
    temp_lab = lab[:]
    temp_lab[int(atual[0])][int(atual[1])] = [1, 0, 0]
    if(atual[0] == 1 and atual[1] == 20):
        return plt.imshow(temp_lab, interpolation = 'nearest')

    fig.clear()
    im = plt.imshow(temp_lab, interpolation = 'nearest')


    if(mov[i]==0 and atual[0]-1 >=0):
        atual[0] -=1
    elif(mov[i]==1 and atual[1]+1 < 25):
        atual[1] +=1
    elif(mov[i]==2 and atual[0]+1 < 30):
        atual[0] +=1
    elif(mov[i]==3 and atual[1]-1 >= 0):
        atual[1] -=1

    return im

# ax1.imshow(a, interpolation='nearest')
# ani = anim.ArtistAnimation(fig, ims, interval=100, blit=True, repeat_delay=1000)
ani = anim.FuncAnimation(fig, update, frames=len(mov), interval=50, blit=False, repeat = False)

plt.show()
################################
fig = plt.figure()


# def f(x, y):
#     return np.sin(x) + np.cos(y)

# x = np.linspace(0, 2 * np.pi, 120)
# y = np.linspace(0, 2 * np.pi, 100).reshape(-1, 1)
# # ims is a list of lists, each row is a list of artists to draw in the
# # current frame; here we are just animating one artist, the image, in
# # each frame
# ims = []
# for i in range(60):
#     x += np.pi / 15.
#     y += np.pi / 20.
#     im = plt.imshow(f(x, y), animated=True)
#     ims.append([im])

# ani = anim.ArtistAnimation(fig, ims, interval=50, blit=True, repeat_delay=1000)

# # ani.save('dynamic_images.mp4')

# plt.show()