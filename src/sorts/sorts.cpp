#include <stddef.h>

#include "sorts.h"

__always_inline
static void swap(uint32_t* a, uint32_t* b)
{
    uint32_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void BubbleSort(uint32_t *begin, uint32_t *end)
{
    for (size_t i = 0; begin + i < end; i++)
        for (uint32_t* j = begin + 1; j < end; j++)
            if (j[-1] > j[0]) swap(j-1, j);
}

void InsertionSort(uint32_t *begin, uint32_t *end)
{
    for (uint32_t* i = begin + 1; i < end; i++)
        for (uint32_t* j = i + 1; j > begin; j--)
            if (j[-1] > j[0]) swap(j-1, j);
            else              break;
}

void SelectionSort(uint32_t *begin, uint32_t *end)
{
    for (uint32_t* i = begin; i < end; i++)
    {
        uint32_t* min = i;
        for (uint32_t* j = i + 1; j < end; j++)
            if (*j < *min) min = j;
        swap(i, min);
    }
}
