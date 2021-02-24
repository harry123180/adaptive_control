import numpy as np
import time
import matplotlib.pyplot as plt
simple_point= 100
x = np.linspace(0, 10, simple_point)
y = np.cos(x)*30
y3 = np.zeros(shape=(simple_point))
M=simple_point# 參數量
a = np.zeros(shape=(M))
#print(a)
估計誤差= 0
估計輸入 =0
plt.ion()
cf = 0.00001# 收斂係數 未知的 要問 此湛設為0.01
figure, ax = plt.subplots(figsize=(8, 6))
line1, = ax.plot(x, y)#CH1 輸入
line2,= ax.plot(x,y) #CH2 跟CH2
line3,= ax.plot(x,y) #FIR filter output wave

plt.title("Dynamic Plot of sinx", fontsize=25)

plt.xlabel("X", fontsize=18)
plt.ylabel("sinX", fontsize=18)
t = 0
#y3[0]=1 #測試用
次數=0
while(True):
    t+=1
    updated_y = np.cos(x - 0.05 * t)*3
    次數+=1
    if 次數==10:
        次數=0
        for u in range(simple_point):
            for u_ in range(M):
                y3[u] += a[u_]*updated_y[u-u_]
    ######################
    #更新CH1 wave
    line1.set_xdata(x)
    line1.set_ydata(updated_y)
    ###################
    #更新CH2 wave
    line2.set_xdata(x)
    y2 = updated_y/3
    line2.set_ydata(y2)
    ######################################
    #更新line3

    #y4 大小2 (y4(1),y4(2)) 放進去y3
    # 因為y4只有2個大小 所以要把它放進去有100個點的y3 先把y3的100個點往後移兩位
    y3 = y3.tolist()
    for i in range(2):  ###右移
        y3.insert(0, y3.pop())
    y3 = np.array(y3)
    誤差=y3-y2
    輸入= y2

    for i in range(len(誤差)):
        估計誤差 +=誤差[i]*1/len(誤差) #E(d[n])
    for i in range(len(輸入)):
        估計輸入+=輸入[i]*1/len(輸入)
    估計誤差 = round(估計誤差, 2)
    估計輸入= round(估計輸入,2)
    估計誤差陣列=[]
    #print("估計誤差=",估計誤差,"估計輸入",估計輸入)
    for i in range(M):
        if(i ==M-1):
            i = i-1
        a[i+1]=a[i]-2*cf*估計誤差*估計輸入
    print(a)
    line3.set_xdata(x)
    line3.set_ydata(y3)
    figure.canvas.draw()

    figure.canvas.flush_events()
    time.sleep(0.1)