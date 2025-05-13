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

}

// STUDENTS: YOU CAN DEFINE A FUNCTOR RIGHT HERE FOR USE IN sortBucketsParallel2.


void sortBucketsParallel2(int **buckets, int numBuckets, int *bucketSizes)
{
    // STUDENTS: COMPLETE THIS FUNCTION AS PER THE COMMENT IN parallel.h.
    // IF YOU USE A FUNCTOR, YOU CAN DEFINE IT ABOVE.

}
