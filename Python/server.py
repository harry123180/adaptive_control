import socket
import cv2
import numpy

capture = cv2.VideoCapture(0)

TCP_IP = "localhost"
TCP_PORT = 8002
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(True)

conn, addr = s.accept()

ret, frame = capture.read() 
encode_param=[int(cv2.IMWRITE_JPEG_QUALITY),90]

while ret:
    result, imgencode = cv2.imencode('.jpg', frame, encode_param)
    data = numpy.array(imgencode)
    stringData = data.tostring()

    conn.send( str(len(stringData)).ljust(16));
    conn.send( stringData );

    ret, frame = capture.read()
    decimg=cv2.imdecode(data,1)
    cv2.imshow('SERVER2',decimg)
    cv2.waitKey(30)

conn.close()
cv2.destroyAllWindows()