from math import *

解析度=0.001
G=9.81
t =0
初速度=input("請輸入初速度")
射角=input("請輸入射角")

射角=radians(int(射角))
初速度=int(初速度)
最大射程 = (pow(初速度,2)*sin(2*射角) )/2*G
最大射高 = (pow((初速度*sin(射角)),2))/2*G
print("最大射高=",最大射高,"最大射程=",最大射程)


水平速度=初速度*cos(射角)

費時=最大射程/水平速度
時間軸 = 費時/解析度
x=[]
y=[]
print(int(時間軸))
print("射角=",cos(射角))
鉛直速度積分=0
for i in range(int(時間軸)):
    t = t+解析度
    水平位移 = 初速度*cos(射角)*t
    鉛直位移=水平位移*tan(射角)-(G*pow(t,2)/(2*pow((初速度*cos(射角)),2)))
    x.append(水平位移)
    y.append(鉛直位移)
print(len(y))
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
xmin, xmax= 0, 最大射程
nx = np.array(x)
ny = np.array(y)
fig = plt.figure(figsize=(7, 6), dpi=100)
ax = fig.gca()
line, = ax.plot(nx, ny, color='blue', linestyle='-', linewidth=3)
dot, = ax.plot([], [], color='red', marker='o', markersize=10, markeredgecolor='black', linestyle='')
ax.set_xlabel('x', fontsize=14)
ax.set_ylabel('y', fontsize=14)

def update(i):
    dot.set_data(x[i], y[i])
    return dot,

def init():
    dot.set_data(x[0], y[0])
    return dot,

ani = animation.FuncAnimation(fig=fig, func=update, frames=int(時間軸), init_func=init, interval=1000/時間軸, blit=True, repeat=True)
plt.show()
ani.save('MovingPointMatplotlib.gif', writer='imagemagick', fps=1/解析度)





