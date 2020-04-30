import common

ACC_RANGE = (0.20, 0.40)
ACC_OBJ = 0.35
DRY_RUN = False  # if this script will actually change anything

if __name__=="__main__":
    
    for file, data in common.find_all("Sims/"):
        if data is None:
            print(f"No simulation data found for {file}")
            continue
        setup, _ = common.load(file, data)
        if common.is_modified(file, data):
            print(f"Simulation {file} has been modified, need a re-run. Ignoring")
            continue

        accepted_E = setup.getfloat("Stats", "Accepted_E")
        if (accepted_E < ACC_RANGE[1] and accepted_E > ACC_RANGE[0]):
            print(f"Simulation {file} euclid part runned correctly with accepted ratio {accepted_E}")
        else:
            print(f"Simulation {file} euclid part runned problematically with accepted ratio {accepted_E}")
            delta = setup.getfloat("Simulation", "delta")
            new_delta = delta * accepted_E / ACC_OBJ  # correcting the delta_E value
            print(f"Correcting old delta {delta} with new {new_delta}")
            if not DRY_RUN:
                setup.set("Simulation", "delta", str(new_delta))  # changing data in memory...
                with open(file, "w") as out:
                    setup.write(out)
            continue

        if False:
            accepted = setup.getfloat("Stats","Accepted")
            if (accepted < ACC_RANGE[1] and accepted > ACC_RANGE[0]):
                print(f"Simulation {file} minkowskian part runned correctly with accepted ratio {accepted}")
            else:
                print(f"Simulation {file} minkowskian part runned problematically with accepted ratio {accepted}")
                alpha = setup.getfloat("Simulation", "alpha")
                new_alpha = alpha * ACC_OBJ / accepted  # correcting the alpha value
                print(f"Correcting old alpha {alpha} with new {new_alpha}")
                if not DRY_RUN:
                    setup.set("Simulation", "alpha", str(new_alpha))  # changing data in memory...
                    with open(file, "w") as out:
                        setup.write(out)