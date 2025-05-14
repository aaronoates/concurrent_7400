#include <thread>
#include <memory> // for unique_ptr, make_unique
#include "parallel.h"
#include "compare.h"
#include <iostream>
#include <vector>

// The following allows you to refer to thread, unique_ptr, ... without using
// std:: as a prefix.  Alternatively, you could use: using namespace std;
//using std::thread, std::unique_ptr, std::make_unique, std::ref;
using namespace std;

void sortBucketsParallel1(int **buckets, int numBuckets, int *bucketSizes)
{
    // STUDENTS: COMPLETE THIS FUNCTION AS PER THE COMMENT IN parallel.h.
    vector<thread> threads; // creates a vector of threads called threads, with a size of numBuckets. This makes it so there is one thread for each bucket.
    
    for (int i = 0; i < numBuckets; i++){
        //threads[i] = qsort(buckets[i], bucketSizes[i], sizeof(int), compare);
        threads.emplace_back(qsort, buckets[i], bucketSizes[i], sizeof(int), compare);
    }

    for (auto& t : threads) {
        t.join();
    }

}

// STUDENTS: YOU CAN DEFINE A FUNCTOR RIGHT HERE FOR USE IN sortBucketsParallel2.


void sortBucketsParallel2(int **buckets, int numBuckets, int *bucketSizes)
{
    // STUDENTS: COMPLETE THIS FUNCTION AS PER THE COMMENT IN parallel.h.
    // IF YOU USE A FUNCTOR, YOU CAN DEFINE IT ABOVE.

}
