#pragma once

#define MAX_VALUE 1000

/**
 * Sorts the integers in data using the bucket sort algorithm.  The data is
 * assumed to be in the range [0 - MAX_VALUE].
 *
 * @param data An array of integers in the range [0 - MAX_VALUE].
 * @param N The number of elements in the data.
 * @param parallel If 0, use a sequential algorithm to sort buckets.  
 *                 If 1, use parallel algorithm (version 1).
 *                 If 2, use parallel algorithm (version 2).
 * @param numBuckets The number of buckets to use.
 */
void bucketSort(int *data, int N, int parallel, int numBuckets);

/**
 * Sorts the data in each bucket using a sequential (i.e. non-parallel) algorithm.
 *
 * @param buckets The buckets to sort.
 * @param numBuckets The number of buckets.
 * @param bucketSizes The sizes of the buckets.
 */
void sortBucketsSequential(int **buckets, int numBuckets, int *bucketSizes);
