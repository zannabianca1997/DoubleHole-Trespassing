import numpy as np
import configparser as cgp
from io import StringIO
import subprocess
import os

EXE_NAME = 'DoubleHole.exe'
SETUP_EXT = ".ini"
DATA_EXT = ".npy"

BASE_SETUP = """[Physical]
T_bar = {T_bar}
lambda = {lambda_}
start_path = {start_path}
[Simulation]
SEED = {SEED}
N = {N}
repeats = {repeats}
delta = {delta}
samples = {samples}
samples_spacing = {samples_spacing}"""

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
