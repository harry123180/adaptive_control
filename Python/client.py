import socket
import base64

HOST = '172.20.10.3'
PORT = 8000
clientMessage = ''


while(True):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((HOST, PORT))
    clientMessage = input("Key str")
    with open("bg.png", "rb") as image2string:
        converted_string = base64.b64encode(image2string.read())
    if(clientMessage != 'break'):
        #client.sendall(clientMessage.encode())
        client.send(converted_string)

        serverMessage = str(client.recv(1024), encoding='utf-8')
        print(type(serverMessage))
        print('Server:', serverMessage)
    else:
        break

client.close()