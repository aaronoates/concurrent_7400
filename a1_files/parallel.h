#pragma once

/**
 * Sorts the buckets in parallel using threads.  The implementation of this
 * version should pass a list of parameters to the thread constructor, in the
 * same style as version 1 of computeSum from the notes. The actual sorting
 * should be done using qsort, used in the same way as in the sequential
 * version (see bucketsort.h and bucketsort.cpp).
 *
 * @param buckets The buckets to sort.
 * @param numBuckets The number of buckets.
 * @param bucketSizes The sizes of the buckets.
 */
void sortBucketsParallel1(int **buckets, int numBuckets, int *bucketSizes);

/**
 * The same as sortBucketsParallel1, but now the implementation should make
 * use of a functor, in the same style as version 2 of computeSum. This
 * implementation should also avoid the use of new/delete for allocating threads.
 */
void sortBucketsParallel2(int **buckets, int numBuckets, int *bucketSizes);
