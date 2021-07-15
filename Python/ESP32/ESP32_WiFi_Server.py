
"""
這個程式是測試WIFI連線的，對應的ESP32程式:
ESP32_WIFI_ADC
ESP32_WIFI_disanble_Serial
"""


import socket
import convert as con
s = socket.socket()
#10.1.1.10
#172.20.10.3
s.bind(('10.1.1.10', 8090))
s.listen(0)

#while True:
"""
while True:
    client, addr = s.accept()

    while True:
        content = client.recv(32)
        #print("              ",content)
        content = con.cvt(content)
        print(content)
        if content == 0:

            #print(content)
            break

        #else:
            #contents = con.cvt(content)
            #print(content)

    #print("Closing connection")
"""
client, addr = s.accept()

while True:
    content = client.recv(32)
    #print("              ",content)
    contents = con.cvt(content)
    print(contents)
    if len(content) == 0:
        #print(content)
        break
    else:
        #contents = con.cvt(content)
        print(contents)
client.close()