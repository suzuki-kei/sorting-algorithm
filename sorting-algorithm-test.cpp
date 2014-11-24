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
} SortingAlgorithm;

static bool is_sorted(const int *array, int size);
static void print_array(const int *array, int size);
static void set_fixed_values(int *array, int size);
static void set_ascending_values(int *array, int size);
static void set_descending_values(int *array, int size);
static void set_random_values(int *array, int size);
static void test(const SortingAlgorithm &sorting, const SetValuesAlgorithm &set_values, bool debug);

static const SetValuesAlgorithm SET_VALUES_ALGORITHMS[] = {
    {"fixed values",      set_fixed_values},
    {"ascending values",  set_ascending_values},
    {"descending values", set_descending_values},
    {"random values",     set_random_values},
};

static const SortingAlgorithm SORTING_ALGORITHMS[] = {
    {"bubble_sort", bubble_sort},
    {"quick_sort", quick_sort},
};

void initialize()
{
    std::srand(std::time(NULL));
}

bool is_sorted(const int *array, int size)
{
    for(int i = 1; i < size; i++) {
        if(array[i-1] > array[i]) {
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
        if(debug || !is_sorted(array, size)) { print_array(array, size); }
        std::printf("%s - %s - array[%d] ... %s\n", sorting.name, set_values.name, size, is_sorted(array, size) ? "OK" : "NG");
    }
}

void test_all(bool debug)
{
    for(int i = 0; i < ARRAY_LENGTH(SORTING_ALGORITHMS); i++) {
        for(int j = 0; j < ARRAY_LENGTH(SET_VALUES_ALGORITHMS); j++) {
            test(SORTING_ALGORITHMS[i], SET_VALUES_ALGORITHMS[j], debug);
        }
    }
}

