#include "compare.h"

int compare(const void* a, const void* b)
{
    int x = *((int*)a);
    int y = *((int*)b);
    return x - y;
}
