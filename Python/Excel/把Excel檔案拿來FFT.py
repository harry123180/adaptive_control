from openpyxl import load_workbook
from matplotlib import pyplot as plt
import numpy as np
Y_current = load_workbook('C:\\Users\\user\\Desktop\\研究\\研究紀錄By泓舉\\7碩一上第七周\\cncdata2.xlsx')['工作表2']['F26':'F63121']
y_data = [ int(c.value) for row in Y_current for c in row]
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