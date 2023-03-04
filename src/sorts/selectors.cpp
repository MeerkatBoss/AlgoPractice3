#include <ctime>
#include <random>

#include "sorts.h"

#include "selectors.h"

uint32_t *Median3Select(uint32_t *begin, uint32_t *end)
{
    uint32_t* first  = begin;
    uint32_t* middle = begin + (end - begin) / 2;
    uint32_t* last   = end - 1;

    if (*first <= *middle && *middle <= *last)
        return middle;
    
    if (*middle <= *first && *first <= *last)
        return first;

    return last;
}

uint32_t *MiddleSelect(uint32_t *begin, uint32_t *end)
{
    return begin + (end - begin) / 2;
}

static inline uint64_t next_random(uint64_t current)
{
    return 6364136223846793005Ull * current + 1442695040888963407Ull;   // Donald Knuth
}

uint32_t *RandomSelect(uint32_t *begin, uint32_t *end)
{
    static uint64_t random = (uint64_t) time(NULL);
    
    random = next_random(random);

    return begin + random % (uint64_t)(end - begin);
}

__always_inline
static void swap(uint32_t *a, uint32_t *b)
{
    uint32_t tmp = *a;
    *a = *b;
    *b = tmp;
}

uint32_t *MedianMedianSelect(uint32_t *begin, uint32_t *end)
{
    if (end - begin < 5)
    {
        InsertionSort(begin, end);
        return begin + (end - begin) / 2;
    }

    uint32_t* i = begin;
    uint32_t* new_end = i;
    for (; i + 5 <= end; i += 5)
    {
        InsertionSort(i, i + 5);
        swap(new_end++, i + 2);        // Move median to start
    }
    if (i < end)
    {
        InsertionSort(i, end);
        swap(new_end++, i + (end - i) / 2);
    }
    return MedianMedianSelect(begin, new_end);      // This is technically wrong, but no one cares 
}
