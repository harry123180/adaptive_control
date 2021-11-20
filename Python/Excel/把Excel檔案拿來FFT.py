from openpyxl import load_workbook
from matplotlib import pyplot as plt
import numpy as np
wb = load_workbook('C:\\Users\\user\\Desktop\\研究\\研究紀錄By泓舉\\9碩一上第九周\\6000RPM_GT_HU4_o.xlsx')
sheet = wb['sheet1']
Y_current = sheet['A2':'A60000']
y_data=[]
for row in Y_current:
    for c in row:
        y_data.append(c.value)
x_data = [i for i in range(0, len(y_data))]
#plt.plot(x_data,y_data)
#plt.show()
y_data = np.array(y_data)
x_data = np.array(x_data)
#創建畫布
plt.ion()
fig = plt.figure(figsize=(10,8))
ax1 = fig.add_subplot(211)
ax2 = fig.add_subplot(212)
#ax3 = fig.add_subplot(313)
ax1.plot(x_data,y_data)
fftData=np.abs(np.fft.rfft(y_data))#np.fft.rfft(y_data)
fftTime=np.fft.rfftfreq(len(y_data), 1./1000)
ax2.plot(fftTime,fftData)
#ax3.plot(fftTime,fftData)
fig.show()
plt.pause(100)