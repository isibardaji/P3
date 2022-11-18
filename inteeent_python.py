import matplotlib.pyplot as plt
import soundfile as sf
import numpy as np


fitxer, fs = sf.read("rl002.wav")
inici = int(0.340*fs)
final = inici + int(0.03*fs)
duracio = final-inici
fitxer_s = fitxer[inici:final]
	
r = np.zeros(duracio)
	
for k in range(duracio):
    for n in range(len(fitxer_s)-k):
        r[k]=r[k]+(fitxer_s[n]*fitxer_s[k+n])
        r[k]=r[k]/len(fitxer_s)

	

plt.subplot(2,1,1)
plt.title("Senyal temporal")
plt.xlabel("Temps (s)")
plt.ylabel("Amplitud")
plt.plot(fitxer_s)

#fem la gràfica de l'autocorrelació
plt.subplot(2,1,2)
plt.title("Autocorrelació de la senyal de veu")
plt.xlabel("Mostres")
plt.ylabel("Autocorrelació")
plt.plot(r)
plt.show()
	




    
        