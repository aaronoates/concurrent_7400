#pragma once

/**
 * Compares two values as required by qsort.  We assume that a and b are 
 * pointers to integers.
 */
int compare(const void* a, const void* b);