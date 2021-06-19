x = -10
y = -9

z = -5
step = 1
v = 5000
sol = 100
ans_x = []
ans_y = []
ans_z = []
target = 0.5
def f1(x,y,z):
    x=x/sol
    y=y/sol
    z=z/sol
    return y+pow(x,2)+2*x*y+pow(y,2)-1
def f2(x,y,z):
    x = x / sol
    y = y / sol
    z = z / sol
    return y-z-pow(z,2)-2*y*z-pow(z,2)-2
def f3(x,y,z):
    x = x / sol
    y = y / sol
    z = z / sol
    return x-y-z-((2*y+2*z)*(x+y))

for i in range(x,v,step):
    for j in range(y,v,step):
        for k in range(z,v,step):
            print(i,j,k,"    ",f1(i,j,k),f2(i,j,k),f3(i,j,k))
            if(f1(i,j,k)>=-target and f1(i,j,k)<=target ):
                if (f2(i, j, k) >= -target and f2(i, j,k)<=target):
                    if (f3(i, j, k) >= -target and f3(i, j, k )<=target):
                        print("答案:===",i,j,k)

                        ans_x.append(i)
                        ans_y.append(j)
                        ans_z.append(k)
                        break
print(ans_x)
print(ans_y)
print(ans_z)

