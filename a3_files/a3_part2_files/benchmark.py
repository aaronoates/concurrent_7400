#!/usr/bin/env python3
import os
import matplotlib.pyplot as plt

# The location of the executable, relative to the location of this script.
# STUDENTS: YOU MAY NEED TO CHANGE THIS TO THE LOCATION OF YOUR EXECUTABLE.
executable = "./test_generator"

#
# Parameters to use for benchmarking...
# STUDENTS: FEEL FREE TO EXPERIMENT WITH DIFFERENT VALUES FOR THESE PARAMETERS.
#
num_polys = 100
num_trials = 5
max_threads = 12
num_threads_choices = [i for i in range(1, max_threads + 1)]

def benchmark(variant):

    # The result will be a dictionary, storing average times in the form {num_threads: average_time}
    average_time_dict = {}

    for num_threads in num_threads_choices:

        times = []
        for seed in range(num_trials):

            # Run the executable, passing in all arguments and storing the output.
            command = f"{executable} {num_polys} {variant} {num_threads} {seed}"
            print(f"benchmark.py: Running command: {command}")
            pipe = os.popen(command)
            output = pipe.read()
            return_code = pipe.close()
            if return_code != None:
                # Command failed.  Print error message and exit.
                print("benchmark.py: Command failed. Exiting...")
                exit()

            
            print(f"benchmark.py: Command output: {output}")
            # Store this run's time
            times.append(int(output))

        # Calculate the average time and place it in the dictionary.
        average_time = sum(times) / len(times)
        average_time_dict[num_threads] = average_time

    return average_time_dict

def main():

    # Run the benchmark for all three versions of the code
    average_time_dict_list = [benchmark(i) for i in range(3)]
    label_list = ["Seq. (w/o break)", "Seq. (w/ break)", "Parallel"]

    # Plot the average times for each number of threads
    for i in range(len(average_time_dict_list)):
        average_time_dict = average_time_dict_list[i]
        plt.plot(average_time_dict.keys(), average_time_dict.values(), label=label_list[i])
    plt.legend()
    plt.xlabel("Number of Threads")
    plt.ylabel("Average Execution Time (ms)")
    plt.savefig("times.pdf")
    plt.show()

    speedup_over_variant_0 = {}
    speedup_over_variant_1 = {}
    for num_threads in num_threads_choices:
        speedup_over_variant_0[num_threads] = average_time_dict_list[0][num_threads] / average_time_dict_list[2][num_threads]
        speedup_over_variant_1[num_threads] = average_time_dict_list[1][num_threads] / average_time_dict_list[2][num_threads]

    # Plot the speedup
    plt.figure()
    plt.plot(speedup_over_variant_0.keys(), speedup_over_variant_0.values(), label="Speedup over var. 1")
    plt.plot(speedup_over_variant_1.keys(), speedup_over_variant_1.values(), label="Speedup over var. 2")
    plt.legend()
    plt.xlabel("Number of Threads")
    plt.ylabel("Speedup")
    plt.savefig("speedups.pdf")
    plt.show()

if __name__ == "__main__":
    main()
