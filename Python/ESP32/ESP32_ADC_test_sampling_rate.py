import serial  # 引用pySerial模組
from time import time
COM_PORT = 'COM3'  # 指定通訊埠名稱
BAUD_RATES = 1000000  # 設定傳輸速率
ser = serial.Serial(COM_PORT, BAUD_RATES)  # 初始化序列通訊埠
Sample = 12000#樣本數
try:
    start = time()# 開始測量
    i = 0
    while True:
        while ser.in_waiting:  # 若收到序列資料…
            data_raw = ser.readline()  # 讀取一行
            #data = data_raw.decode()  # 用預設的UTF-8解碼
            #print('接收到的原始資料：', data_raw)
            #print('接收到的資料：', data)
            i+=1
            if (i >= Sample):
                break
        if (i >= Sample):
            break
    end = time()
    print("執行時間：%f 秒" % (end - start))
    print(i)
except KeyboardInterrupt:
    ser.close()  # 清除序列通訊物件
    print('再見！')