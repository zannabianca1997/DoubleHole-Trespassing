import common

DRY_RUN = True  # if this script will actually change anything

new_values = {
    ("Simulation", "samples"): 1000,
    ("Simulation", "samples_spacing"): 1000,
}

if __name__ == "__main__":

    for file, data in common.find_all("Sims/Serie/"):
        assert data is not None
        setup, _ = common.load(file, data)
        print(f"Simulation {file}")
        for section, name in new_values.keys():
            old_val = setup.getint(section, name)
            if old_val != new_values[(section, name)]:
                print(f"Correcting old {name} {old_val} with new {new_values[(section, name)]}")
                setup.set(section, name, str(new_values[(section, name)]))  # changing data in memory...

        if not DRY_RUN:
            with open(file, "w") as out:
                setup.write(out)