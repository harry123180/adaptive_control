h=6.62607004*pow(10,-34) #普朗克常數
m=9.10938356*pow(10,-31) #電子質量
e=1.60217662*pow(10,-19)#基本電荷 constant
E= 20 #input
c=299792458#光速

def eq(E):

    p= pow((2*m*e*E*1000),0.5)
    #print("未考慮相對論的p=",p)
    return h/p*pow(10,10)#Amstrom
def eq相對論(h,E,m):
    E=E*1000
    C2 = pow(c, 2)
    E2 = pow(E, 2)
    e2 = pow(e,2)
    add = (e2*E2/C2)
    p =pow(2*m*e*E+add,0.5)
    #print("add = ",add)
    #print("h=",h)
    #print("p=",p)
    return h/p*pow(10,10)
val = 20
print("ans1= ",eq(val))
print("ans2= ",eq相對論(h,val,m))