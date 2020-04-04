import numpy as np
from scipy.special import binom
import scipy.integrate as integrate
import configparser as cgp
from io import StringIO
import subprocess
import os

EXE_NAME = 'DoubleHole.exe'
SETUP_EXT = ".ini"
DATA_EXT = ".npy"

MAX_COST = 10^10

BASE_SETUP = """[Physical]
t = {t_bar}
T_bar = {T_bar}
lambda = {lambda}
euclid_path = {euclid_path}
outher_vertex = {outher_vertex}
[Simulation]
SEED = {SEED}
N = {N}
M = {M}
alpha = {alpha}
repeats = {repeats}
delta = {delta}
delta_E = {delta_E}
samples = {samples}"""

def load(setup_path, values_path):
    # reading setup values
    setup=cgp.ConfigParser()
    setup.read(setup_path)
    # reading simulation results
    data=np.load(values_path)

    return setup, data

def to_string(setup):
    string_file = StringIO()
    setup.write(string_file)
    res = string_file.getvalue()
    string_file.close()
    return res;

def do_simulation(in_file, out_file, stdin=None, stdout=None, stderr=None):
    subprocess.call(f'{EXE_NAME} "{in_file}" "{out_file}"', stdin=stdin, stderr=stderr, stdout=stdout)

def is_modified(in_file, out_file):
    return os.stat(in_file).st_mtime > os.stat(out_file).st_mtime

def find_all(root_dir):
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            name, extension = os.path.splitext(file)
            if extension == SETUP_EXT:  # è un file di setup
                file = os.path.join(root, name + SETUP_EXT)
                data_file = os.path.join(root, name + DATA_EXT)
                if os.path.exists(data_file):
                    yield file, data_file # return both
                else:
                    yield file, None  # return the found file

#simulation estimates
def I_1(E):
     a= np.sqrt(1-np.sqrt(E))
     return integrate.quad(lambda y:np.sqrt((y**2 - 1)**2 - E), -a, a)[0]
def I_1_approx(E):
    return 4/3*(1-E)
    
def p_wkb(E, lambda_):
    if E>=1:
        return 1 # si può passare
    return np.exp(-8*lambda_*I_1(E))


def P_wkb(t, beta, lambda_, err = 10**-11):
    sums = 0
    n=0
    while True:  # summing all the levels up to err
        E = (n+(1/2))/lambda_
        addend = np.exp(-(4*np.pi*p_wkb(E, lambda_)*t + E*beta))
        if addend < err:
            break
        sums += addend
        n+=1
    return (np.sinh(-beta/(2*lambda_)))*sums

def P_f(num_data, precision, P):
    m_min = 1 + int((num_data + 1 - (precision**2 * (num_data + 3)))/(1+(precision**2 * (num_data + 3))))
    sums = (1-P)**num_data
    if m_min <=1: # abbiamo solo lo 0
        return sums
    binom = 0  # the exponent of the binomial
    for m in range(1, m_min):
        binom += np.log(num_data + 1 - m) - np.log(m)
        sums += np.exp(
            binom + np.log(1-P)*(num_data - m) + np.log(P)*m
            )
    return sums

# max cost is about 10^9
def cost(N,M,num_data, reps)
    return num_data * reps * (N + 2*M)
    

