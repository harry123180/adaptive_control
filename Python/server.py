import socket
import base64
from PIL import Image
import cv2
from io import BytesIO
import numpy as np
def readb64(base64_string):
    sbuf = BytesIO()
    sbuf.write(base64.b64decode(base64_string))
    pimg = Image.open(sbuf)
    return cv2.cvtColor(np.array(pimg), cv2.COLOR_RGB2BGR)

HOST = '172.20.10.3'
PORT = 8000

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(10)

while True:
    conn, addr = server.accept()
    clientMessage = conn.recv(100*1024)
    print(type(clientMessage))
    print(len(clientMessage)-64112)
    print('Client message is:', clientMessage)
    cvimg = readb64(clientMessage)
    cv2.imshow('titlle',cvimg)
    cv2.waitKey()
    cv2.destroyAllWindows()
    serverMessage = 'I\'m here!'
    conn.sendall(serverMessage.encode())
    conn.close()
