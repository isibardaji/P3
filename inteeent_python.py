import matplotlib.pyplot as plt
import soundfile as sf
import numpy as np


fitxer, fs = sf.read("prueba.wav")
inici = 0
final = len(fitxer)
duracio = final-inici
fitxer_s = fitxer[inici:final]
x = []
x=fitxer_s
r = np.zeros(duracio)
	
for k in range(duracio):
    
    if(k>0.0055):
        x[k]=fitxer_s[k]
    if(k< -1*0.005):
        x[k]=fitxer_s[k]
    if((k<0.0055)&(k>-1*0.0055)):
        x[k]=0



plt.subplot(2,1,1)
plt.title("Senyal temporal")
plt.xlabel("Temps (s)")
plt.ylabel("Amplitud")
plt.plot(fitxer_s)


plt.subplot(2,1,2)
plt.title("Senyal amb clipping")
plt.xlabel("(s)")
plt.ylabel("Amplitud")
plt.plot(x)
plt.show()
	




    
        