#ifndef __HELPERS_H
#define __HELPERS_H

#include <ctime>
#include <unistd.h>
#include <stdio.h>

#define PROFILE_ERROR_MSG(description) "{\"err\":\"" description "\"}"

#define PROFILE_FUNCTION(function, data, time_delta)                                    \
do                                                                                      \
{                                                                                       \
    clock_t time_start = std::clock();                                                  \
    function(data);                                                                     \
    clock_t time_end = std::clock();                                                    \
    time_delta = (uint64_t)(time_end - time_start) / (uint64_t)(CLOCKS_PER_SEC / 1000); \
} while (0)


#endif