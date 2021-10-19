import base64

with open("bg.png", "rb") as image2string:
    converted_string = base64.b64encode(image2string.read())
print(converted_string)
print(type(converted_string))
print(len(converted_string))
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

cvimg = readb64(converted_string)
cv2.imshow('titlle',cvimg)
cv2.waitKey()
cv2.destroyAllWindows()