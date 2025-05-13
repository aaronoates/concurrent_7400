#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>

using std::string, std::cout, std::cerr, std::endl, std::stoi;
using namespace std::chrono;

#include "bucketsort.h"

void randomFill(int* store, int N)
{
    for (int i = 0; i < N; i++)
        store[i] = rand() % MAX_VALUE;
}

void print(const string &msg, const int* array, int N)
{
    cerr << msg << endl;

    for (int i = 0; i < N; ++i)
    {
        cerr << array[i];
        if (i < N - 1)
            cout << " ";
    }
    cerr << endl;
}

void checkResult(const int* array, int N)
{
    bool sorted = true;
    for (int i = 1; sorted && i < N; ++i)
        if (array[i - 1] > array[i])
            sorted = false;

    if (!sorted)
        cout << "Sort failed!" << endl;
}

int main(int argc, char* argv[])
{
    // Deal with command-line arguments.  There must be four, in addition to the program name.
    if (argc != 5)
    {
        cout << "Usage: " << argv[0] << " SIZE_OF_ARRAY_TO_SORT PARALLEL NUM_BUCKETS_THREADS RANDOM_SEED" << endl;
        cout << "  SIZE_OF_ARRAY_TO_SORT: The number of integers to sort." << endl;
        cout << "  PARALLEL: 0 for sequential sort, " << endl;
        cout << "            1 for parallel sort (version 1)," << endl;
        cout << "            2 for parallel sort (version 2)," << endl;
        cout << "  NUM_BUCKETS_THREADS: The number of buckets to use for sequential sort" << endl;
        cout << "                       or the number of buckets and threads to use for parallel sort." << endl;
        cout << "  RANDOM_SEED: The seed for the random number generator." << endl;
        exit(0);
    }

    int N = stoi(argv[1]);
    int parallel = stoi(argv[2]);
    int numThreads = stoi(argv[3]);
    int randomSeed = stoi(argv[4]);

    // Seet the random number generator
    srand(randomSeed);

    // Only print the before/after results if the array is small.
    bool doBeforeAfterPrint = N < 20;

    // Create an array of integers in the range 0 - 999.
    int* data = new int[N];
    randomFill(data, N);

    if (doBeforeAfterPrint)
        print("Before sort:", data, N);

    // Run bucket sort and time it.
    auto beforeTime = high_resolution_clock::now();

    bucketSort(data, N, parallel, numThreads);

    auto afterTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(afterTime - beforeTime);
    int durationInt = static_cast<int>(duration.count());

    // Print the time the sort took in milliseconds.
    cout << durationInt << endl;

    checkResult(data, N);

    if (doBeforeAfterPrint)
        print("After sort:", data, N);

    delete[] data;

    return durationInt;
}
