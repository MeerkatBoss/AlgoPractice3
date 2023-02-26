#include <random>
#include <cassert>

#include "tester.h"
#include "sorts/sorts.h"
#include "tester/helpers.h"

struct test_data
{
    uint32_t*   data;
    size_t      data_size;
};

static void fill_data(test_data* tdata);

#define EXPAND_ARGS(tdata) (tdata.data, tdata.data + tdata.data_size)
#define FUNCTION_ADAPTER(name) name EXPAND_ARGS

#define REPEAT_TEST(function, repetitions, tdata) do                        \
{                                                                           \
    for (size_t repeat = 0; repeat < repetitions; repeat++)                 \
    {                                                                       \
        int64_t time_delta = 0;                                             \
        fill_data(&tdata);                                                  \
        PROFILE_FUNCTION(FUNCTION_ADAPTER(function), tdata, time_delta);    \
        mean_time_ms += time_delta;                                         \
        if (time_delta >= 120*1000)                                         \
        {                                                                   \
            mean_time_ms = time_delta*repetitions;                          \
            break;                                                          \
        }                                                                   \
    }                                                                       \
    mean_time_ms /= (int64_t)repetitions;                                   \
} while(0)

#define RUN_TEST(sort_name, tdata, seed) do                                                     \
{                                                                                               \
    srand((unsigned)seed);                                                                      \
    for (size_t sample_size = initial_size; sample_size <= end_size; sample_size+=step_size)    \
    {                                                                                           \
        tdata.data_size = sample_size;                                                          \
        int64_t mean_time_ms = 0;                                                               \
        REPEAT_TEST(sort_name##Sort, repetitions, tdata);                                       \
        fprintf(output_file, "%s,%zu,%ld\n",                                                \
                            #sort_name, sample_size, mean_time_ms);                \
    }\
} while(0)

#define CAT(x, y) __BASIC_CAT(x, y)
#define __BASIC_CAT(x, y) x##y
#define STR(x) __BASIC_STR(x)
#define __BASIC_STR(x) #x

#define SORT_A(x) RUN_TEST(x, tdata, seed); SORT_B
#define SORT_B(x) RUN_TEST(x, tdata, seed); SORT_A
#define SORT_A_END
#define SORT_B_END

#define SORTS(seq) do                                               \
{                                                                   \
    time_t seed = time(NULL);                                       \
    test_data tdata = {};                                           \
    tdata.data = (uint32_t*) calloc(end_size, sizeof(*tdata.data)); \
    CAT(SORT_A seq, _END);                                          \
} while (0);


void run_all_tests()
{
#define INITIAL_SIZE(val) size_t initial_size = val;
#define END_SIZE(val)     size_t end_size = val;
#define STEP_SIZE(val)    size_t step_size = val;
#define REPEAT(val)       size_t repetitions = val;

    FILE* output_file = fopen("results/" STR(TEST_CASE_NAME) ".csv", "w+");
    setvbuf(output_file, NULL, _IONBF, 0);

    fputs("Algorithm,Sample Size,Elapsed Time (ms)\n", output_file);

    #include STR(TEST_CASE)

    fclose(output_file);
#undef INITIAL_SIZE
#undef END_SIZE
#undef STEP_SIZE
#undef REPEAT

}

static void fill_data(test_data *tdata)
{
    for (size_t i = 0; i < tdata->data_size; i++)
        tdata->data[i] = (unsigned) rand();
}
