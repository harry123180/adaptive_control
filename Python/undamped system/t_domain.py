import matplotlib.pyplot as plt
import numpy as np

POINTS = 100
sin_list = [0] * POINTS
indx = 0
# fig, ax = plt.subplots()
while True:
    if indx == 40:
        indx = 0
    indx += 1
    # 更新绘图数据

    sin_list = sin_list[1:] + [np.sin((indx / 20) * np.pi)]
    arr = np.arange(0 ,1, 0.01)
    #print(arr)
    plt.plot(arr, sin_list, marker="o")
    plt.xticks(range(len(arr)) , arr )
    # 显示时间
    plt.pause(0.01)
    # 清除上一次显示
    plt.cla()
    plt.plot(sin_list)
    # plt.draw()也可以放在这个位置，不会阻塞
plt.draw()