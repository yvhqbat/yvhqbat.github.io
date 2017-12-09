import numpy as np
import matplotlib.pyplot as plt

t=np.arange(0.0,2.0,0.01)
s=np.sin(2*np.pi*t)
plt.plot(t,s)
plt.show()

