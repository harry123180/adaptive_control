from scipy import signal
import matplotlib.pyplot as plt
m=1
c = 5
k = 5000
ka =[0,1.5,5]
kv = [0,0,0]
kp =[0,0,0]
參數 = [[1,5,5000,ka[0],kv[0],kp[0]],[1,5,5000,ka[1],kv[1],kp[1]],[1,5,5000,ka[2],kv[2],kp[2]]]

sys = []
colors = ['blue','green','red']
label_n = ['Original(No Gain) ','High Gain','Low Gain']
p = []
plt.figure()
for i in range(3):
	u = i
	sys.append(signal.TransferFunction([參數[u][1],參數[u][2]], [參數[u][0]+參數[u][3],參數[u][1]+參數[u][4], 參數[u][2]+參數[u][5]]))
	w, mag, phase = signal.bode(sys[u])
	plt.semilogx(w, mag,color = colors[i],label =label_n[i] )
	#p.appeend(a )   # Bode magnitude plot

	print(mag)
plt.xlabel("Freq(Hz)")  # x轴的标签
plt.ylabel("Transmissibility(dB)")  # y轴的标签
plt.legend()
#l1 = plt.legend([p[0], p[1],p[2]], ["line 2", "line 1","LINEGG"], loc='upper left')
#plt.figure()
#plt.semilogx(w, phase)  # Bode phase plot
plt.show()