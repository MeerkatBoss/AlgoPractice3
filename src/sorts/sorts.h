#ifndef __SORTS_H
#define __SORTS_H

#include <cstdint>

#include "selectors.h"

typedef uint32_t* pivot_selector_t (uint32_t* begin, uint32_t* end);

void BubbleSort     (uint32_t* begin, uint32_t* end);

void InsertionSort  (uint32_t* begin, uint32_t* end);

void SelectionSort  (uint32_t* begin, uint32_t* end);

void QuickSort      (uint32_t* begin, uint32_t* end, pivot_selector_t* get_pivot);

__always_inline
void QuickMedian3Sort (uint32_t* begin, uint32_t* end) { QuickSort(begin, end, Median3Select); }

__always_inline
void QuickMiddleSort (uint32_t* begin, uint32_t* end) { QuickSort(begin, end, MiddleSelect); }

__always_inline
void QuickRandomSort (uint32_t* begin, uint32_t* end) { QuickSort(begin, end, RandomSelect); }

__always_inline
void QuickMedianMedianSort (uint32_t* begin, uint32_t* end) { QuickSort(begin, end, MedianMedianSelect); }

void MergeSort      (uint32_t* begin, uint32_t* end);

void RadixLSDSort   (uint32_t* begin, uint32_t* end);

void RadixMSDSort   (uint32_t* begin, uint32_t* end);

#endif