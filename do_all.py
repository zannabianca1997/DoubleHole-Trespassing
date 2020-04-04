import os
import common
import multiprocessing

if __name__=="__main__":
    print(f"Detected {multiprocessing.cpu_count()} cpus...")
    pool = multiprocessing.Pool(processes=multiprocessing.cpu_count()-1)

    for file, data in common.find_all("Sims"):
        print(f"Found setup file {file}")
        if data is not None:
            if not common.is_modified(file, data):  # simulation already done
                print(f"Found up-to-date data file {data}")
                continue
            print(f"Found old data file {data}")
        else:
            print("No data file found")
            data = os.path.splitext(file)[0] + common.DATA_EXT
        print(f"Adding {file} to the pool...")
        pool.apply_async(common.do_simulation, (file, data))  # add the task to the pool

    pool.close()  # no more work
    print("Waiting for completion...")
    pool.join()  # wait until all work is done
    print("Done.")