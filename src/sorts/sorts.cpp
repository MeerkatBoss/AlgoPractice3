#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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
    for (uint32_t* i = begin; i < end - 1; i++)
    {
        uint32_t current = i[1];
        uint32_t* j = i;
        while (j >= begin && *j > current)
        {
            j[1] = *j;
            j--;
        }
        j[1] = current;
    }
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

static uint32_t* partition(uint32_t* pivot, uint32_t* begin, uint32_t* end);

void QuickSort(uint32_t *begin, uint32_t *end, pivot_selector_t *get_pivot)
{
    if (end - begin <= 1) return;
    uint32_t* pivot = get_pivot(begin, end);
    uint32_t* middle = partition(pivot, begin, end);

    if (begin < middle) QuickSort(begin,  middle, get_pivot);
    if (middle < end)   QuickSort(middle, end,    get_pivot);
}

static void merge_sort_implementation(uint32_t* begin, uint32_t* end, uint32_t* buffer);

void MergeSort(uint32_t *begin, uint32_t *end)
{
    uint32_t *buffer = (uint32_t*) calloc((size_t)(end - begin), sizeof(*begin));
    merge_sort_implementation(begin, end, buffer);
    free(buffer);
}

static void lsd_step(unsigned step, uint32_t* dest, uint32_t* src, size_t size);

void RadixLSDSort(uint32_t *begin, uint32_t *end)
{
    size_t data_size = (size_t)(end - begin);
    uint32_t* array  = begin;
    uint32_t* buffer = (uint32_t*) calloc(data_size, sizeof(*begin));

    for (unsigned step = 0; step < 4; step++)
    {
        lsd_step(step, buffer, array, data_size);
        uint32_t* tmp = array;
        array = buffer;
        buffer = tmp;
    }
    
    // After 4 iterations (even number), array == begin again
    // and the result of last step is recorded to array

    free(buffer);
}

static void radix_msd_sort_implementation(uint32_t* begin, uint32_t* end, unsigned step, uint32_t* buffer);

void RadixMSDSort(uint32_t *begin, uint32_t *end)
{
    uint32_t* buffer = (uint32_t*) calloc((size_t)(end - begin), sizeof(*begin));
    radix_msd_sort_implementation(begin, end, 0, buffer);
    free(buffer);
}

uint32_t* partition(uint32_t* pivot, uint32_t *start, uint32_t *end)
{
    uint32_t *left = start - 1;
    uint32_t *right = end;

    uint32_t p_value = *pivot;

    while (1)                               // I do not know why this works
    {
        do {
            left++;
        } while (*left < p_value);
        do {
            right--;
        } while (*right > p_value);

        if (left >= right) return right + 1 < end ? right + 1 : end - 1;

        swap(left, right);
    }

    return NULL;                            // Unreachable
}

void merge_sort_implementation(uint32_t *begin, uint32_t *end, uint32_t *buffer)
{
    if (end - begin <= 1) return;
    uint32_t* middle = begin + (end - begin) / 2;
    merge_sort_implementation(begin,  middle, buffer);
    merge_sort_implementation(middle, end,    buffer);

    uint32_t* i      = begin;
    uint32_t* j      = middle;
    uint32_t* result = buffer;

    while (i < middle && j < end)
    {
        if (*i <= *j) *(result++) = *(i++);
        else          *(result++) = *(j++);
    }

    while (i < middle) *(result++) = *(i++);
    while (j < end)    *(result++) = *(j++);

    memcpy(begin, buffer, (size_t) (end - begin) * sizeof(*begin));
}

__always_inline
static unsigned lsd_get_bucket(uint32_t value, unsigned step)
{
    return (value >> (step * 8)) & 0xFF;
}

void lsd_step(unsigned step, uint32_t *dest, uint32_t *src, size_t size)
{
    static size_t buckets[0x100] = { 0 };

    memset(buckets, 0, sizeof(*buckets) * 0x100);

    for (size_t i = 0; i < size; i++)
    {
        unsigned bucket_number = lsd_get_bucket(src[i], step);
        buckets[bucket_number]++;
    }
    
    size_t acc = 0;
    for (size_t i = 0; i < 0x100; i+=2)         // loop unrolled by 2
    {
        size_t current1 = buckets[i];
        size_t current2 = buckets[i+1];

        buckets[i]   = acc;
        buckets[i+1] = acc + current1;

        acc += (current1 + current2);
    }

    for (size_t i = 0; i < size; i++)
    {
        unsigned bucket_number = lsd_get_bucket(src[i], step);
        dest[buckets[bucket_number]] = src[i];
        buckets[bucket_number]++;
    }
}

__always_inline
static unsigned msd_get_bucket(uint32_t value, unsigned step)
{
    return (value >> ((3 - step) * 8)) & 0xFF;
}

void radix_msd_sort_implementation(uint32_t *begin, uint32_t *end, unsigned step, uint32_t* buffer)
{
    if (step >= 4) return;
    size_t buckets[0x100] = { 0 };

    memset(buckets, 0, sizeof(*buckets) * 0x100);

    size_t size = (size_t)(end - begin);

    for (size_t i = 0; i < size; i++)
    {
        unsigned bucket_number = msd_get_bucket(begin[i], step);
        buckets[bucket_number]++;
    }
    
    size_t acc = 0;
    for (unsigned i = 0; i < 0x100; i+=2)         // loop unrolled by 2
    {
        size_t current1 = buckets[i];
        size_t current2 = buckets[i+1];

        buckets[i]   = acc;
        buckets[i+1] = acc + current1;

        acc += (current1 + current2);
    }

    for (size_t i = 0; i < size; i++)
    {
        unsigned bucket_number = msd_get_bucket(begin[i], step);
        buffer[buckets[bucket_number]] = begin[i];
        buckets[bucket_number]++;
    }

    memcpy(begin, buffer, size * sizeof(*begin));

    size_t last_index = 0;
    for (unsigned i = 0; i < 0x100; i++)
    {
        if (buckets[i] > last_index + 1)
            radix_msd_sort_implementation(begin + last_index, begin + buckets[i], step + 1, buffer);
        last_index = buckets[i];
    }
}
