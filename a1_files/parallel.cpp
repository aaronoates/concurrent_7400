#include <thread>
#include <memory> // for unique_ptr, make_unique
#include "parallel.h"
#include "compare.h"

// The following allows you to refer to thread, unique_ptr, ... without using
// std:: as a prefix.  Alternatively, you could use: using namespace std;
using std::thread, std::unique_ptr, std::make_unique, std::ref;




void sortBucketsParallel1(int **buckets, int numBuckets, int *bucketSizes)
{
    // STUDENTS: COMPLETE THIS FUNCTION AS PER THE COMMENT IN parallel.h.
    thread *thr[numBuckets];

    for (int i = 0; i < numBuckets; i++) {
        thr[i] = new thread(qsort, buckets[i], bucketSizes[i], sizeof(int), compare);
        thr[i]->join();
        delete thr[i];
    }
    
}

// STUDENTS: YOU CAN DEFINE A FUNCTOR RIGHT HERE FOR USE IN sortBucketsParallel2.

struct sortoneBucket {
    int *bucket = nullptr;
    int bucketSize;

    void operator()() {
        qsort(bucket, bucketSize, sizeof(int), compare);
    }
        
};

void sortBucketsParallel2(int **buckets, int numBuckets, int *bucketSizes)
{
    // STUDENTS: COMPLETE THIS FUNCTION AS PER THE COMMENT IN parallel.h.
    // IF YOU USE A FUNCTOR, YOU CAN DEFINE IT ABOVE.
    unique_ptr<thread> threads[numBuckets];
    sortoneBucket functors[numBuckets];

    for (int i = 0; i < numBuckets; ++i) {
        functors[i].bucket = buckets[i];
        functors[i].bucketSize = bucketSizes[i];
        threads[i] = make_unique<thread>(ref(functors[i]));
    }

    for (int i = 0; i < numBuckets; ++i) {
        threads[i]->join();
    }
}
