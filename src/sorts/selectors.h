#ifndef __SELECTORS_H
#define __SELECTORS_H

#include <cstdint>

uint32_t* Median3Select     (uint32_t* begin, uint32_t* end);

uint32_t* MiddleSelect      (uint32_t* begin, uint32_t* end);

uint32_t* RandomSelect      (uint32_t* begin, uint32_t* end);

uint32_t* MedianMedianSelect(uint32_t* begin, uint32_t* end);

#endif