
"""
這個程式是測試WIFI連線的，對應的ESP32程式:
ESP32_WIFI_ADC
ESP32_WIFI_disanble_Serial
"""


import socket

s = socket.socket()

s.bind(('172.20.10.3', 8090))
s.listen(0)

#while True:

client, addr = s.accept()

while True:
    content = client.recv(32)

    if len(content) == 0:
        print(content)
        break

    else:
        print(content)

    #print("Closing connection")
client.close()