import numpy as np

from common import P_wkb, P_f, find_num_data
betas = [1,2,3,4]
lambdas = [1,2,3,4]

import matplotlib.pyplot as plt
import matplotlib.colors as colors

x = np.linspace(0,1)
plt.figure("Test_betas")
plt.title("WKB approximation for various $\\beta, \\lambda \\in " + str(lambdas) + "$")
for i,b in enumerate(betas):
    plt.subplot(2,2,i+1)
    plt.title("$\\bar{\\beta} = "+str(b)+"$")
    for l in lambdas:
        plt.plot(x,[P_wkb(x_,b,l) for x_ in x])
    plt.ylabel("$P$")

if True:
    betas = np.linspace(0.05, 10, 100)
    lambdas = np.linspace(0.05, 10, 100)
    max_N = 10**9

    N_s = np.empty((len(betas), len(lambdas)), dtype=np.int)
    for i, beta in enumerate(betas):
        print(f"Processing {100*i/len(betas)}%")
        for j, lambda_ in enumerate(lambdas):
            N = find_num_data(0.02, 0.1, P_wkb(1, beta, lambda_), max_N)
            if N is not None:
                N_s[i,j] = N
            else:
                N_s[i,j] = max_N

    plt.figure("Test_N")
    plt.imshow(N_s,
               origin="lower", extent=(lambdas[0], lambdas[-1],betas[0],betas[-1]),
               norm=colors.LogNorm(vmin=N_s.min(), vmax=N_s.max()))

    plt.colorbar(extend='max')
    plt.xlabel("$\\lambda$")
    plt.ylabel("$\\beta$")
plt.show()