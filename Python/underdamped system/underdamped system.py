import matplotlib.pyplot as plt  #导入matplotlib库
import numpy as np  #导入numpy库
import mpl_toolkits.axisartist as axisartist
from  math import *
#initial conditon
y_ini = 10 #amplitude (mm)
C = 200
mass = 200
k_constant = 126318
freq_natural= sqrt(k_constant/mass) #Hz
damping_ratio = C/(2*mass*freq_natural)
freq_damp = freq_natural*sqrt(1-pow(damping_ratio,2))
y_dot_ini = 5#Tangent slope of amplitude
t = 0.00 #time
POINTS = 100
wave_list = [0] * POINTS
damped_list = [0] * POINTS*10

fig = plt.figure()
ax1 = plt.subplot(2,2,1)
ax2 = plt.subplot(2,2,2)
ax3 = plt.subplot(2,1,2)
while(True):

    ct = freq_natural * t  # constant of omega*t
    cdt = freq_damp*t
    A= y_dot_ini/freq_natural
    B = y_ini
    Ax = A*cos(1.5*pi+ct)
    Ay = A*sin(1.5*pi+ct)
    Bx = B*cos(ct)
    By = B*sin(ct)
    row = sqrt(pow(A,2)+pow(B,2))
    angle_row = 2*pi-atan(A/B) + ct
    rowx = row*cos(angle_row)
    rowy = row*sin(angle_row)
    wave_list = wave_list[1:] + [A*sin(ct)+B*cos(ct)]
    damped_list = damped_list[1:]+[exp(-1*freq_natural*damping_ratio*t)*(A*sin(cdt)+B*cos(cdt))]
    if(t >=5):
        print(exp(-1*freq_natural*damping_ratio*t))
    plt.sca(ax1)

    plt.cla()
    plt.title('Phase diagram')
    x = np.arange(-15,15,0.1)
    #生成sigmiod形式的y数据
    y=1/(1+np.exp(-x))
    #设置x、y坐标轴的范围
    plt.xlim(-30,30)
    plt.ylim(-10, 10)
    #绘制图形

    Al = plt.plot([0,Ax],[0,Ay],color="black")
    Bl = plt.plot([0,Bx],[0,By],color="red")
    rowL = plt.plot([0,rowx],[0,rowy],color="blue")
    plt.sca(ax2)
    plt.cla()
    plt.title("Time domain response")
    plt.xlim(0, 100)
    plt.plot(wave_list)
    #plt.plot(x,y, c='b')
    plt.sca(ax3)

    plt.cla()
    #plt.title("Time domain response damping_ratio=%d"%damping_ratio)
    plt.xlabel("Time domain response damping_ratio=%f"%damping_ratio)
    plt.plot(damped_list)
    plt.pause(0.0001)
    t+= 0.01
    #print(t)
    if(t>10000):
        break
plt.draw()