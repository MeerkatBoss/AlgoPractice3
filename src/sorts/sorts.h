#ifndef __SORTS_H
#define __SORTS_H

#include <cstdint>

typedef uint32_t* pivot_selector_t (uint32_t* begin, uint32_t* end);

void BubbleSort     (uint32_t* begin, uint32_t* end);

void InsertionSort  (uint32_t* begin, uint32_t* end);

void QuickSort      (uint32_t* begin, uint32_t* end, pivot_selector_t* get_pivot);

void MergeSort      (uint32_t* begin, uint32_t* end);

void RadixLSDSort   (uint32_t* begin, uint32_t* end);

void RadixMSDSort   (uint32_t* begin, uint32_t* end);

#endif