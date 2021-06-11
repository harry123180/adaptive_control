from math import exp
from math import sin
from math import cos
m= 200
C= 200
K = 126318
omegan = pow((K/m),0.5)
ida = C/(2*m*omegan)
omegad = omegan*pow((1-pow(ida,2)),0.5)
y0dot =5
y0 = 10

print(ida)

def function(t):
    A = exp(-1*ida*omegan*t)
    B = (((y0dot+(y0*ida*omegan))/omegad)*sin(omegad*t))
    C = y0*cos(omegad*t)
    return A*(B+C)
print(function(5))