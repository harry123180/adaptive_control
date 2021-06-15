
def cvt(bytes):
    ans = 0
    for i in range(len(bytes)):
        ans = (bytes[i]-48)*pow(10,len(bytes)-1-i)+ans
    return ans
