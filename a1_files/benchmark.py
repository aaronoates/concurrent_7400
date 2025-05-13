#!/usr/bin/env python3
import os
import matplotlib.pyplot as plt

# The location of the executable, relative to the location of this script.
# STUDENTS: YOU MAY NEED TO CHANGE THIS TO THE LOCATION OF YOUR EXECUTABLE.
executable = "./build/test_bs"

#
# Parameters to use for benchmarking...
# STUDENTS: FEEL FREE TO ADJUST THESE PARAMETERS AS NEEDED.  FOR EXAMPLE, REDUCE
# THE ARRAY SIZE IF THE EXECUTION TIME IS TOO LONG, OR INCREASE THE NUMBER OF
# TRIALS TO GET MORE ACCURATE RESULTS.
#
array_size = 1000000
num_trials = 10
max_threads = 20
num_threads_choices = [i for i in range(1, max_threads + 1)]

def benchmark(parallel):

    # The result will be a dictionary, storing average times in the form {num_threads: average_time}
    average_time_dict = {}

    for num_threads in num_threads_choices:

        times = []
        for seed in range(num_trials):

            # Run the executable, passing in all arguments and storing the output.
            command = f"{executable} {array_size} {parallel} {num_threads} {seed}"
            print(f"Running command: {command}")
            output = os.popen(command).read()
            print(f"Command output: {output}")

            # Store this run's time
            times.append(int(output))

        # Calculate the average time and place it in the dictionary.
        average_time = sum(times) / len(times)
        average_time_dict[num_threads] = average_time

    return average_time_dict

def main():

    # Run the benchmark for all three versions of the code
    average_time_dict_list = [benchmark(i) for i in range(3)]
    label_list = ["Sequential", "Parallel (Ver. 1)", "Parallel (Ver. 2)"]

    # Plot the average times for each number of threads
    for i in range(len(average_time_dict_list)):
        average_time_dict = average_time_dict_list[i]
        plt.plot(average_time_dict.keys(), average_time_dict.values(), label=label_list[i])
    plt.legend()
    plt.xlabel("Number of Threads")
    plt.ylabel("Average Execution Time (ms)")
    plt.savefig("times.pdf")
    plt.show()

    # STUDENTS: ADD CODE BELOW TO CALCULATE AND PLOT THE SPEEDUP VS. NUMBER OF THREADS.
    # THERE SHOULD BE TWO LINES ON THE PLOT, ONE FOR EACH VERSION OF THE PARALLEL CODE.
    speedup_ver1 = {}
    speedup_ver2 = {}
    for num_threads in num_threads_choices:
        speedup_ver1[num_threads] = average_time_dict_list[0][num_threads] / average_time_dict_list[1][num_threads]
        speedup_ver2[num_threads] = average_time_dict_list[0][num_threads] / average_time_dict_list[2][num_threads]

    # Plot the speedup
    plt.figure()
    plt.plot(speedup_ver1.keys(), speedup_ver1.values(), label="Ver. 1")
    plt.plot(speedup_ver2.keys(), speedup_ver2.values(), label="Ver. 2")
    plt.legend()
    plt.xlabel("Number of Threads")
    plt.ylabel("Speedup")
    plt.savefig("speedup.pdf")
    plt.show()

if __name__ == "__main__":
    main()
