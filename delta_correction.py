import common

ACC_RANGE = (0.20, 0.40)
ACC_OBJ = 0.35
DRY_RUN = True  # if this script will actually change anything

if __name__=="__main__":
    
    for file, data in common.find_all("Sims/Serie/"):
        assert data is not None
        setup, _ = common.load(file, data)
        if common.is_modified(file, data):
            print(f"Simulation {file} has been modified, need a re-run. Ignoring")
            continue

        accepted = setup.getfloat("Stats","Accepted")
        if (accepted < ACC_RANGE[1] and accepted > ACC_RANGE[0]):
            print(f"Simulation {file} runned correctly with accepted ratio {accepted}")
        else:
            print(f"Simulation {file} runned problematically with accepted ratio {accepted}")
            delta = setup.getfloat("Simulation", "delta")
            new_delta = delta * accepted / ACC_OBJ  # correcting the delta value
            print(f"Correcting old delta {delta} with new {new_delta}")
            if not DRY_RUN:
                setup.set("Simulation", "delta", str(new_delta))  # changing data in memory...
                with open(file, "w") as out:
                    setup.write(out)
        accepted_E = setup.getfloat("Stats", "Accepted_E")
        if (accepted_E < ACC_RANGE[1] and accepted_E > ACC_RANGE[0]):
            print(f"Simulation {file} runned correctly with euclid accepted ratio {accepted_E}")
        else:
            print(f"Simulation {file} runned problematically with euclid accepted ratio {accepted_E}")
            delta_E = setup.getfloat("Simulation", "delta_E")
            new_delta_E = delta_E * accepted_E / ACC_OBJ  # correcting the delta_E value
            print(f"Correcting old delta {delta_E} with new {new_delta_E}")
            if not DRY_RUN:
                setup.set("Simulation", "delta_E", str(new_delta_E))  # changing data in memory...
                with open(file, "w") as out:
                    setup.write(out)