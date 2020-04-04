import matplotlib.pyplot as plt
import numpy as np

import common
import os

if __name__ == "__main__":
    serie_data = {}

    for file, data_file in common.find_all("Sims/Serie/"):
        assert data_file is not None
        setup, data = common.load(file, data_file)
        serie_data[
            tuple(int(n) for n in  os.path.splitext(os.path.split(file)[1])[0].split("_"))  # isolating numbers
        ] = setup, data


    for eg_i in set(i for i, _ in serie_data):  # isolating unique i_s
        # finding out limits
        limits = [float("inf"),-float("inf")]
        for eg_j in (j for i, j in serie_data if i == eg_i):
            _, data = serie_data[(eg_i,eg_j)]
            limits[0] = min(limits[0], np.min(data))
            limits[1] = max(limits[1], np.max(data))

        plt.figure(num=eg_i)  # opening figure

        y_s = np.linspace(limits[0], limits[1], 50) # bins
        etas = []
        datas = []  # we keep them so we can order them
        for eg_j in (j for i, j in serie_data if i == eg_i):
            setup, data = serie_data[(eg_i, eg_j)]
            T_bar = setup.getfloat("Physical", "T_bar")
            etas.append(setup.getfloat("Values", "Eta_0"))

            #simmetrizing the data
            data = data.flatten()
            simmdata = np.empty(data.shape[0]*2, dtype=data.dtype)
            simmdata[:data.shape[0]] =   data
            simmdata[data.shape[0]:] = - data

            hist, edges = np.histogram(simmdata, y_s ,density=True)
            centre = (edges[:-1]+edges[1:])/2 #moving to the centre of the bins

            datas.append((T_bar, centre, hist))

        datas.sort(key=(lambda x: x[0])) #sorting for T_bar
        for T_bar, centre, hist in datas:
            plt.plot(centre, hist, label=f"T_bar = {T_bar}")  # print wavefunc

        eg_j = next(j for i, j in serie_data if i == eg_i)  # taking one example j to find lambda
        lambda_ = serie_data[(eg_i, eg_j)][0].getfloat('Physical', 'lambda')

        plt.title(f"Lambda = {lambda_}")
        plt.ylabel("Potential")
        plt.xlabel("Position")
        plt.legend()

        V = (y_s ** 2 - 1) ** 2
        plt.autoscale(False)  # so it won't change the scale
        plt.plot(y_s, V, color="black")

        plt.figure(num=100) # the eta figure
        plt.scatter([lambda_]*len(etas), etas)

    plt.show()