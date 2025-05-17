#include <stdlib.h>
#include "bucketsort.h"
#include "compare.h"
#include "parallel.h"

void bucketSort(int* data, int N, int parallel, int numBuckets)
{
    int* buckets[numBuckets];
    int bucketSizes[numBuckets];
    int bucketRange = MAX_VALUE / numBuckets + 1;

    // Initialize the buckets. A bucket is just an array of integers. We keep
    // track of the valid size of each bucket in the bucketSizes array.
    for (int i = 0; i < numBuckets; i++)
    {
        // The worst-case possible size of a bucket is N. This approach is fine,
        // but not the most memory efficient.
        buckets[i] = new int[N];
        bucketSizes[i] = 0;
    }

    // Distribute the data into the buckets.
    for (int i = 0; i < N; i++)
    {
        int buckNum = data[i] / bucketRange;
        int buckSize = bucketSizes[buckNum];
        buckets[buckNum][buckSize] = data[i];

        // We have just increased the size of this bucket.
        bucketSizes[buckNum]++;
    }

    if (parallel == 0)
        sortBucketsSequential(buckets, numBuckets, bucketSizes);
    else if (parallel == 1)
        sortBucketsParallel1(buckets, numBuckets, bucketSizes);
    else if (parallel == 2)
        sortBucketsParallel2(buckets, numBuckets, bucketSizes);
    else
        throw "Invalid value for parallel";

    // Copy the sorted data from each bucket back into the data array.
    int k = 0;
    for (int i = 0; i < numBuckets; i++)
        for (int j = 0; j < bucketSizes[i]; j++)
            data[k++] = buckets[i][j];

    for (int i = 0; i < numBuckets; i++)
        delete[] buckets[i];
}

void sortBucketsSequential(int **buckets, int numBuckets, int *bucketSizes)
{
    for (int i = 0; i < numBuckets; i++){
        qsort(buckets[i], bucketSizes[i], sizeof(int), compare);
    }
}

