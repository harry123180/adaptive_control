import matplotlib.pyplot as plt
import numpy as np
import math
# Generate a signal
samplingFreq = 1000 # sampled at 1 kHz = 1000 samples / second
tlims = [0,1]        # in seconds
signalFreq = [2,50] # Cycles / second
signalMag = [1,0] # magnitude of each sine
t = np.linspace(tlims[0],tlims[1],(tlims[1]-tlims[0])*samplingFreq)
y =  signalMag[0]*np.sin(2*math.pi*signalFreq[0]*t) + signalMag[1]*np.sin(2*math.pi*signalFreq[1]*t)

yhat = np.abs(np.fft.fft(y));
fcycles = np.fft.fftfreq(len(t),d=1.0/samplingFreq); # the frequencies in cycles/s
# Plot the signal
plt.figure()
plt.plot(t,y)
plt.ylabel("$y(t)$")
#plt.ylim(-1,1)
plt.xlabel("$t$ (s)")
plt.xlim([min(t),max(t)])
plt.axis('off')
# Plot the power spectrum
plt.figure()
plt.plot(fcycles,np.absolute(yhat));
plt.xlim([-100,100]);
plt.xlabel("$\omega$ (cycles/s)");
plt.ylabel("$|\hat{y}|$");
plt.show()