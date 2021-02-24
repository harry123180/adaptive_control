import numpy as np
import time
import matplotlib.pyplot as plt

simple_point= 100
x = np.linspace(0, 10, simple_point)

y = np.cos(x)*3
y3 = np.zeros(shape=(simple_point))
M=simple_point# 參數量
a = np.zeros(shape=(M))
history_input = np.zeros(shape=(100))
#print(a)
估計誤差= 0
估計輸入 =0
avg_err=0
plt.ion()
cf = 0.001# 收斂係數 未知的 要問 此湛設為0.01
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
while(True):
    t+=1
    updated_y = np.cos(x - 0.05 * t)*3


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
    y4 = a.dot(y2)
    y3[0] = y4
    #y4 大小2 (y4(1),y4(2)) 放進去y3
    # 因為y4只有2個大小 所以要把它放進去有100個點的y3 先把y3的100個點往後移兩位
    y3 = y3.tolist()
    for i in range(1):  ###右移
        y3.insert(0, y3.pop())
    y3 = np.array(y3)
    error=y3[0]-y2[0] #純量誤差
    input_x= y2 # 輸入是向量
    #y2 type is array of numpy
    #print(np.shape(y2))
    err_list.append(error)


    估計誤差 = round(error, 2)#取小數點後二位
    #估計輸入= round(input_x,2)
    次數+=1

    if(次數%10==0):
        total_err = 0
        for i in range(len(err_list)):
            total_err = total_err+err_list[i]
        avg_err = total_err/len(err_list)
    if(次數>10):
        for i in range(1):  ###右移
            err_list.insert(0, err_list.pop())
    #history_input = np.append(history_input,input_x,axis=0)
    #print(history_input)
    #print("估計誤差=",估計誤差,"估計輸入",估計輸入)
    for i in range(M):
        #a[i] = 1
        a[i]=a[i]-2*cf*avg_err*input_x[i]
    print(a[0])
    line3.set_xdata(x)
    line3.set_ydata(y3)
    figure.canvas.draw()

    figure.canvas.flush_events()
    time.sleep(0.01)