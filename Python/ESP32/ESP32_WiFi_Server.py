import socket

s = socket.socket()

s.bind(('172.20.10.3', 8090))
s.listen(0)

while True:

    client, addr = s.accept()

    while True:
        content = client.recv(32)

        if len(content) == 0:
            break

        else:
            print(content)

    #print("Closing connection")
client.close()