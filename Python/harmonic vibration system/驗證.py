import math
#已知的
係數=200#題目給的
P1 = 0*係數
P2 = -1*係數
m = 200#質量
K = 126318#彈簧常數
C=200#阻尼
ωd=100#外力頻率
ωn = math.sqrt(K/m)#自然頻率
β = ωd/ωn
ζ = C/(2*m*ωn)
分母 = m*pow(ωn,2)*((pow((1-pow(β,2)),2))+pow((2*ζ*β),2))

y1 = (((1-pow(β,2))*P1)+((2*ζ*β)*P2))/分母
y2 =-(2*ζ*β)*P1+(1-pow(β,2))*P2/分母

y0 = math.sqrt(pow(y1,2)+pow(y2,2))
θy = math.atan(y2/y1)
def yoft(t):
    print("y0= " ,y0)
    print("ωd = ",ωd)
    print("θy = ",θy)
    return y0*math.cos(ωd*t+θy)
print("y(5) = " ,yoft(5))
print("y1= ", y1)
print("y2= ", y2)