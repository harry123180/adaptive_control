import numpy as np
#import pandas as pd
from scipy import signal
from openpyxl import load_workbook
from matplotlib import pyplot as plt
wb = load_workbook('C:\\Users\\user\\Desktop\\研究\\研究紀錄By泓舉\\8碩一上第八周\\hu_1.xlsx')
sheet = wb['sheet1']
Y_current = sheet['A2':'A20000']
y_data=[]
for row in Y_current:
    for c in row:
        y_data.append(float(c.value))
x_data = [i for i in range(0, len(y_data))]
def butter_highpass(cutoff, fs, order=5):
    nyq = 0.5 * fs
    normal_cutoff = cutoff / nyq
    b, a = signal.butter(order, normal_cutoff, btype='high', analog=False)
    return b, a

def butter_highpass_filter(data, cutoff, fs, order=5):
    b, a = butter_highpass(cutoff, fs, order=order)
    y = signal.filtfilt(b, a, data)
    return y

def butter_lowpass(cutoff, fs, order=5):
    nyq = 0.5 * fs
    normal_cutoff = cutoff / nyq
    b, a = signal.butter(order, normal_cutoff, btype='low', analog=False)
    return b, a

def butter_lowpass_filter(data, cutoff, fs, order=5):
    b, a = butter_lowpass(cutoff, fs, order=order)
    y = signal.lfilter(b, a, data)
    return y

def ROI_list(Target_array, min, max):
    min_indx = [i for i in range(0, min)]
    modifiedArray = np.delete(Target_array, min_indx,None)
    max = max - min
    min_indx = [i for i in range(max,len(modifiedArray))]
    return np.delete(modifiedArray, min_indx, None)
y_data = np.array(y_data)
x_data = np.array(x_data)
#將訊號清到剩下加工區段
#13140,47530
t = 4000
y_data = ROI_list(y_data,t,t+2048)
x_data = ROI_list(x_data,t,t+2048)

filted = butter_highpass_filter(y_data,5.47,1000)#高通
filted = butter_lowpass_filter(filted,270,1000)#低通
#創建畫布
#plt.ion()
fig = plt.figure(figsize=(10,8))
ax1 = fig.add_subplot(411)
ax2 = fig.add_subplot(412)
ax3 = fig.add_subplot(413)
ax4 = fig.add_subplot(414)

fftData=np.abs(np.fft.rfft(y_data))#np.fft.rfft(y_data)
fftTime=np.fft.rfftfreq(len(y_data), 1./1000)
filteredfftData=np.abs(np.fft.rfft(filted))#np.fft.rfft(y_data)
#13140~47530

ax1.plot(x_data,y_data)
ax2.plot(fftTime,fftData)
ax3.plot(x_data,filted )
ax4.plot(fftTime,filteredfftData)
plt.show()
#plt.pause(100)

