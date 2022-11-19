import matplotlib.pyplot as plt
import soundfile as sf
import numpy as np


fitxer, fs = sf.read("prueba.wav")
inici = 0
final = len(fitxer)
duracio = final-inici
fitxer_s = fitxer[inici:final]

f0_filtrat = [len(fitxer_s)]

   
for k in range(duracio):
    if((fitxer_s[k-1]>fitxer_s[k] & fitxer_s[k-1]<fitxer_s[k+1])|(fitxer_s[k-1]<fitxer_s[k]&fitxer_s[k-1]>fitxer_s[k+1])):
        f0_filtrat[k] = fitxer_s[k-1]
    if((fitxer_s[k-1]<fitxer_s[k] & fitxer_s[k]<fitxer_s[k+1])|(fitxer_s[k-1]>fitxer_s[k]&fitxer_s[k]>fitxer_s[k+1])):
        f0_filtrat[k] = fitxer_s[k]
    if((fitxer_s[k-1]<fitxer_s[k+1] & fitxer_s[k]>fitxer_s[k+1])|(fitxer_s[k-1]>fitxer_s[k+1]&fitxer_s[k]<fitxer_s[k+1])):
        f0_filtrat[k] = fitxer_s[k+1]

plt.subplot(2,1,1)
plt.title("Senyal temporal")
plt.xlabel("Temps (s)")
plt.ylabel("Amplitud")
plt.plot(fitxer_s)


plt.subplot(2,1,2)
plt.title("Senyal amb  filtre mediana")
plt.xlabel("(s)")
plt.ylabel("Amplitud")
plt.plot(f0_filtrat)
plt.show()