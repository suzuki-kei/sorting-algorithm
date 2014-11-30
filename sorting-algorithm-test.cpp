#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "sorting-algorithm.hpp"
#include "sorting-algorithm-test.hpp"

#define ARRAY_LENGTH(array) (int)(sizeof(array) / sizeof(*array))

typedef void (*SetValuesFunction)(int *array, int size);

typedef struct {
    const char * const name;
    const SetValuesFunction function;
} SetValuesAlgorithm;

typedef void (*SortingFunction)(int *array, int size);

typedef struct {
    const char * const name;
    const SortingFunction function;
    const int benchmark_data_size;
} SortingAlgorithm;

static bool is_sorted(const int *array, int size);
static void print_array(const int *array, int size);
static void set_fixed_values(int *array, int size);
static void set_ascending_values(int *array, int size);
static void set_descending_values(int *array, int size);
static void set_random_values(int *array, int size);
static void test(const SortingAlgorithm &sorting, const SetValuesAlgorithm &set_values, bool debug);
void benchmark(const SortingAlgorithm &sorting, const SetValuesAlgorithm &set_values);

static const SetValuesAlgorithm SET_VALUES_ALGORITHMS[] = {
    {"Fixed Values",      set_fixed_values},
    {"Ascending Values",  set_ascending_values},
    {"Descending Values", set_descending_values},
    {"Random Values",     set_random_values},
};

static const SortingAlgorithm SORTING_ALGORITHMS[] = {
    {"Bubble Sort",    bubble_sort,    1 << 16},
    {"Selection Sort", selection_sort, 1 << 16},
    {"Insertion Sort", insertion_sort, 1 << 16},
    {"Shaker Sort",    shaker_sort,    1 << 16},
    {"Shell Sort",     shell_sort,     1 << 16},
    {"Comb Sort",      comb_sort,      1 << 25},
    {"Heap Sort",      heap_sort,      1 << 25},
    {"Merge Sort",     merge_sort,     1 << 25},
    {"Quick Sort",     quick_sort,     1 << 25},
};

void initialize()
{
    std::srand(std::time(NULL));
}

bool is_sorted(const int *array, int size)
{
    for(int i = 1; i < size; i++) {
        if(array[i - 1] > array[i]) {
            return false;
        }
    }
    return true;
}

void print_array(const int *array, int size)
{
    const char *delimiter = "";

    for(int i = 0; i < size; i++) {
        std::cout << delimiter << array[i];
        delimiter = ", ";
    }

    if(is_sorted(array, size)) {
        std::cout << " (sorted)";
    } else {
        std::cout << " (not sorted) ";
    }

    std::cout << std::endl;
}

void set_fixed_values(int *array, int size)
{
    for(int i = 0; i < size; i++) {
        array[i] = 0;
    }
}

void set_ascending_values(int *array, int size)
{
    for(int i = 0; i < size; i++) {
        array[i] = i;
    }
}

void set_descending_values(int *array, int size)
{
    for(int i = 0; i < size; i++) {
        array[i] = size - i -1;
    }
}

void set_random_values(int *array, int size)
{
    for(int i = 0; i < size; i++) {
        array[i] = std::rand() % 100;
    }
}

void test(const SortingAlgorithm &sorting, const SetValuesAlgorithm &set_values, bool debug)
{
    const int sizes[] = { 0, 1, 2, 3, 10, 100 };

    for(int i = 0; i < ARRAY_LENGTH(sizes); i++) {
        const int size = sizes[i];
        int array[size];

        set_values.function(array, size);
        sorting.function(array, size);
        std::printf("%s - %s - %s (size=%d)\n", is_sorted(array, size) ? "OK" : "NG", sorting.name, set_values.name, size);
        if(debug || !is_sorted(array, size)) { print_array(array, size); }
    }
}

void test_all(bool debug)
{
    std::cout << std::endl << "======== TEST ========" << std::endl;
    for(int i = 0; i < ARRAY_LENGTH(SORTING_ALGORITHMS); i++) {
        for(int j = 0; j < ARRAY_LENGTH(SET_VALUES_ALGORITHMS); j++) {
            test(SORTING_ALGORITHMS[i], SET_VALUES_ALGORITHMS[j], debug);
        }
    }
}

void benchmark(const SortingAlgorithm &sorting, const SetValuesAlgorithm &set_values)
{
    const int size = sorting.benchmark_data_size;
    int array[size];

    const clock_t start_time = std::clock();
    set_values.function(array, size);
    sorting.function(array, size);
    const double elapsed_time = static_cast<double>(std::clock() - start_time) / CLOCKS_PER_SEC;
    std::printf("%9.6lfms - %s - %s (size=%d)\n", elapsed_time, sorting.name, set_values.name, size);
}

void benchmark_all()
{
    std::cout << std::endl << "======== BENCHMARK ========" << std::endl;
    for(int i = 0; i < ARRAY_LENGTH(SORTING_ALGORITHMS); i++) {
        for(int j = 0; j < ARRAY_LENGTH(SET_VALUES_ALGORITHMS); j++) {
            benchmark(SORTING_ALGORITHMS[i], SET_VALUES_ALGORITHMS[j]);
        }
    }
}

