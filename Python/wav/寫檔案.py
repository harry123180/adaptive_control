# -*- coding: utf-8 -*-
import wave
import numpy as np
import matplotlib.pyplot as plt

time = 0.1  # second
framerate = 44100  # Hz


def sinSweepFrq(f0, f1, framerate, time):
    '''
    依線性產生從 f0 到 f1 的 sine
    f0 : 起始頻率
    f1 : 結束頻率
    framerate: 取樣率
    time: 時間長度
    '''
    nframes = time * framerate
    k = (f1 - f0) / time
    t = np.linspace(0, time, num=nframes)
    # f = f0 + kt
    # w = 2 * pi * f = 2 * pi * f0 + 2 * pi * kt
    # w 對 t 積分得 phase
    # phase = 2 * pi * f0 * t + pi * kt^2
    phase = 2 * np.pi * f0 * t + np.pi * k * t * t

    return np.sin(phase)


nframes = time * framerate

n = np.linspace(0, time, num=nframes)

f_start = 20  # Hz
f_stop = 1000  # Hz

sinus_f_start = np.sin(2 * np.pi * f_start * n)
sinus_f_stop = np.sin(2 * np.pi * f_stop * n)
# 產生 10秒 44.1kHz 的 20Hz - 1kHz 的 sine
sinus_f_sweep = sinSweepFrq(f_start, f_stop, framerate, time)

# 先放大以免轉換 np.short 為 0，並且太小聲
wave_data = sinus_f_sweep * 10000
wave_data = wave_data.astype(np.short)

# 寫入檔案
f = wave.open(r"sweep.wav", "wb")

# 設定聲道數、sample 大小(byte) 和取樣頻率
f.setnchannels(1)
f.setsampwidth(2)
f.setframerate(framerate)
# 寫入波形數據
f.writeframes(wave_data.tostring())
f.close()

# 畫圖確認
fig = plt.figure()

fig.add_subplot(411)
plt.plot(n, sinus_f_start)
fig.add_subplot(412)
plt.plot(n, sinus_f_stop)
fig.add_subplot(413)
plt.plot(n, sinus_f_sweep)
fig.add_subplot(414)
plt.plot(n, wave_data)
plt.show()