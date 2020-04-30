import numpy as np
import matplotlib.pyplot as plt
import common

setup, data =common.load("Sims/Test1.ini", "Sims/Test1.npy")
t=setup.getfloat("Physical", "t")
T=setup.getfloat("Physical", "T_bar")
N=setup.getint("Simulation", "N")
M=setup.getint("Simulation", "M")

num_sample = 10
plt.figure("Paths")

x_s = np.empty(N+2*M)
x_s[:N] = np.linspace(0,1/T, N)
x_s[N:N+M] = 1/T + np.linspace(0,t, M)
x_s[N+M:] = 1/T + t + np.linspace(0,t, M)

for path in (data[i] for i in range(0,data.shape[0], data.shape[0]//num_sample)):
    plt.plot(x_s, path)

plt.show()