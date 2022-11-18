import matplotlib.pyplot as plt
import soundfile as sf
import numpy as np

p = [x.split()[0] for x in open("rl002.f0").readlines()]
p = [float(x) for x in p]
p_ref = [x for x in open("rl002.f0ref").readlines()]
p_ref = [float(x) for x in p_ref]
	
t = np.arange(len(p))
	
plt.subplot(2,1,1)
plt.title("Pitch")
plt.xlabel("Amplitud")
plt.ylabel("[Hz]")
plt.plot(t, p)

plt.subplot(2,1,2)
plt.title("Pitch ref")
plt.xlabel("Amplitud")
plt.ylabel("[Hz]")
plt.plot(t,p_ref)
 

	
plt.show()
