import matplotlib.pyplot as plt  #导入matplotlib库
import numpy as np  #导入numpy库
import mpl_toolkits.axisartist as axisartist
from  math import *
#initial conditon
y_ini = 10 #amplitude (mm)
freq_natural= 20 #Hz
y_dot_ini = 200#Tangent slope of amplitude
t = 0.00 #time

fig = plt.figure(figsize=(8, 8))


while(True):

    ct = freq_natural * t  # constant of omega*t
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

    ax = axisartist.Subplot(fig, 111)
    fig.add_axes(ax)
    #通过set_visible方法设置绘图区所有坐标轴隐藏
    ax.axis[:].set_visible(True)
    plt.cla()
    #ax.new_floating_axis代表添加新的坐标轴
    ax.axis["x"] = ax.new_floating_axis(0,0)
    #给x坐标轴加上箭头
    ax.axis["x"].set_axisline_style("->", size = 1.0)
    #添加y坐标轴，且加上箭头
    ax.axis["y"] = ax.new_floating_axis(1,0)
    ax.axis["y"].set_axisline_style("-|>", size = 1.0)
    #设置x、y轴上刻度显示方向
    ax.axis["x"].set_axis_direction("top")
    ax.axis["y"].set_axis_direction("right")
    #生成x步长为0.1的列表数据
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


    #plt.plot(x,y, c='b')

    plt.pause(0.033)
    t+= 0.01
    print(t)
    if(t>100):
        break