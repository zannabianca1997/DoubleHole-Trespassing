import numpy as np
import common

DIMS = (11, 11)
eta_max = 0.02  # the maximum value of eta_0 and eta_d


#generating seeds
np.random.seed(1234)
seeds = np.random.choice(1000000, DIMS, replace=False)  # using six digits number as seeds (eh eh eh... =3)

if __name__ == "__main__":

    for i, lambda_ in enumerate(np.logspace(-1,1,DIMS[0])):
        for j, T_bar in enumerate(np.logspace(-1,1,DIMS[1])):
            #calculating N
            N_min = int(1/(eta_max * T_bar * min(1, lambda_))) + 1  # the min value N can take
            if N_min < 2: # the algorithm work only for N > 2
                print("WARNING: N is going under 2. Impossible to guarantee uniform lattice spacing")
                N = 2
            else:
                N = N_min
                T_bar = 1/(eta_max * N_min * min(1, lambda_))  #thanks to this the lattice spacing will be constant at eta_max

            print(seeds[i,j], N, T_bar, lambda_, 1/(N*T_bar), 1/(N*T_bar*lambda_), sep="\t")

            with open(f"Sims/Serie/{i}_{j}.ini", "w") as out:
                out.write(
                    common.BASE_SETUP.format(
                        T_bar=T_bar,
                        lambda_=lambda_,

                        start_path="RIGTH",  # is simmetrized later
                        SEED=seeds[i, j],
                        N=N,
                        repeats=10,
                        delta=0.08,
                        samples=50,
                        samples_spacing=100
                    )
                )