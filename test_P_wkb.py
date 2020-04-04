from common import P_wkb
betas = [0.1,1,2,4]
lambdas = [0.5,1,2,4]

import matplotlib.pyplot as plt
x = np.linspace(0,1)
plt.figure("Test_betas")
plt.title("WKB approximation for various $\\beta, \\lambda \\in " + str(lambdas) + "$")
for i,b in enumerate(betas):
    plt.subplot(2,2,i+1)
    plt.title("$\\bar{\\beta} = "+str(b)+"$")
    for l in lambdas:
        plt.plot(x,[P_wkb(x_,b,l) for x_ in x])
    plt.xlabel("$\\bar{t}$")
    plt.ylabel("$P$")
plt.show()
