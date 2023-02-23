#include <algorithm>
#include "sorts.h"

void BubbleSort(uint32_t *begin, uint32_t *end)
{
    for (size_t i = 0; begin + i < end; i++)
        for (uint32_t* j = begin + 1; j < end; j++)
            if (j[-1] > j[0]) std::swap(j[-1], j[0]);
}

void InsertionSort(uint32_t *begin, uint32_t *end)
{
    for (uint32_t* i = begin + 1; i < end; i++)
        for (uint32_t* j = i + 1; j > begin; j--)
            if (j[-1] > j[0]) std::swap(j[-1], j[0]);
            else              break;
}
