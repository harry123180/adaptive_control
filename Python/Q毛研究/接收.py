
import socket
import time

HOST = '169.254.22.50'
PORT = 350

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

while True:
    outdata = 'heartbeat'
    print('send: ' + outdata)
    s.send(outdata.encode())

    indata = s.recv(1024)
    if len(indata) == 0:  # connection closed
        s.close()
        print('server closed connection.')
        break
    print('recv: ' + indata.decode())

    time.sleep(1)