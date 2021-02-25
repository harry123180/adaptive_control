import numpy as np
import time
import random
import matplotlib.pyplot as plt

simple_point= 100
x = np.linspace(0, 10, simple_point)
y1 =np.zeros(shape=(simple_point))
y = np.cos(x)*3
y3 = np.zeros(shape=(simple_point))
M=3# 參數量

a = np.zeros(shape=(M))
history_input = np.zeros(shape=(100))
#print(a)
估計誤差= 0
估計輸入 =0
avg_err=0
avg_x1 =0
avg_x2 =0
avg_x3 =0
plt.ion()
cf = 0.017# 收斂係數 未知的 要問 此湛設為0.01
figure, ax = plt.subplots(figsize=(8, 6))
line1, = ax.plot(x, y)#CH1 輸入
line2,= ax.plot(x,y) #CH2 跟CH2
line3,= ax.plot(x,y) #FIR filter output wave

plt.title("Adaptive control", fontsize=25)

plt.xlabel("X", fontsize=18)
plt.ylabel("OUTPUT", fontsize=18)
t = 0
#y3[0]=1 #測試用
次數=0

err_list=[]
x1_list=[]
x2_list=[]
x3_list=[]
while(True):
    t+=1
    updated_y = np.cos(x - 0.05 * t)*random.randint(1,1)
    input_cos = np.cos(x - 0.05 * t)
    y1= y1.tolist()
    y1.insert(0,updated_y[0])
    y1.pop()
    y1=np.array(y1)
    ######################
    #更新CH1 wave
    line1.set_xdata(x)
    line1.set_ydata(y1)
    ###################
    #更新CH2 wave
    line2.set_xdata(x)
    y2 = np.array([updated_y[0],updated_y[1],updated_y[2]])
    line2.set_ydata(y1/3)
    ######################################
    #更新line3
    y4 = a.dot(y2)
    error = y2[0]-y3[0]  # 純量誤差
    #print(y3[0],y4)
    #y4 大小2 (y4(1),y4(2)) 放進去y3
    # 因為y4只有2個大小 所以要把它放進去有100個點的y3 先把y3的100個點往後移兩位
    y3 = y3.tolist()
    for i in range(1):  ###右移
        y3.insert(0, y4)
        y3.pop()
    y3 = np.array(y3)
    input_x= y2 # 輸入是向量
    err_list.append(error)
    x1_list.append(input_x[0])
    x2_list.append(input_x[1])
    x3_list.append(input_x[2])
    次數+=1

    if(次數%10==0):
        total_err = 0
        x1_total = 0
        x2_total = 0
        x3_total = 0
        for i in range(len(err_list)):
            total_err = total_err+err_list[i]
            x1_total = x1_total+x1_list[i]
            x2_total = x2_total+x2_list[i]
            x3_total = x3_total+x3_list[i]

        avg_err = total_err/len(err_list)
        avg_x1 = x1_total/len(x1_list)
        avg_x2 = x2_total / len(x2_list)
        avg_x3 = x3_total / len(x3_list)
    if(次數>10):
        for i in range(1):  ###右移
            err_list.insert(0, error)
            x1_list.insert(0,input_x[0])
            x2_list.insert(0, input_x[1])
            x3_list.insert(0, input_x[2])
            err_list.pop()
            x1_list.pop()
            x2_list.pop()
            x3_list.pop()
    for i in range(M):
        #a[i] = 1
        if(i==0):
            a[i] = a[i] + 2 * cf * avg_err * avg_x1
        elif(i==1):
            a[i] = a[i] + 2 * cf * avg_err * avg_x2
        elif (i == 2):
            a[i] = a[i] + 2 * cf * avg_err * avg_x3

    print(avg_x1,avg_x2,avg_x3)

    line3.set_xdata(x)
    line3.set_ydata(y3)
    #figure.
    #print(len(y3),len(y2),len(updated_y))
    figure.canvas.draw()

    figure.canvas.flush_events()
    time.sleep(0.01)