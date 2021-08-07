import wave
import matplotlib.pyplot as plt
import numpy as np

# 讀檔
f = wave.open(r"C:\\Users\\user\\Documents\\GitHub\\adaptive_contrrol\\adaptive_control\\Python\\wav\\sweep.wav", "rb")

# 格式資訊
# (nchannels, sampwidth, framerate, nframes, comptype, compname)
params = f.getparams()
nchannels, sampwidth, framerate, nframes = params[:4]

# 波形數據
str_data = f.readframes(nframes)
f.close()

# bytes to np.short
wave_data = np.fromstring(str_data, dtype=np.short)
# 轉換為雙聲道
wave_data.shape = -1, 2
wave_data = wave_data.T
# 總時間長度
time = np.arange(0, nframes) * (1.0 / framerate)

# 音訊資訊
print(nchannels, sampwidth, framerate, nframes)

# 畫波形
plt.subplot(211)
plt.plot(time, wave_data[0])
plt.subplot(212)
plt.plot(time, wave_data[1], c="g")
plt.xlabel("time (seconds)")
plt.show()