"""
這邊把socket打包成一個模塊，負責與ESP32通訊


"""
import socket
import convert as con
s = socket.socket()
def read_vol():
    client, addr = s.accept()

    while True:
        content = client.recv(32)

        if len(content) == 0:
            break
        else:
            print(con.cvt(content))
            return con.cvt(content)


def init(IP):
    s.bind((IP, 8090))
    s.listen(0)


