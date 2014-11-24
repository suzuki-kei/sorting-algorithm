#include <algorithm>

template <typename T>
void bubble_sort(T *array, int size)
{
    for(int limit = size; limit > 0; limit--) {
        for(int i = 1; i < limit; i++) {
            if(array[i-1] > array[i]) {
                std::swap(array[i-1], array[i]);
            }
        }
    }
}

template <typename T>
void quick_sort(T *array, int lower_limit, int upper_limit)
{
    int lower_index = lower_limit;
    int upper_index = upper_limit;
    const T pivot = array[(lower_limit + upper_limit) / 2];

    while(lower_index <= upper_index) {
        while(lower_index <= upper_index && array[lower_index] < pivot) {
            lower_index++;
        }
        while(lower_index <= upper_index && array[upper_index] > pivot) {
            upper_index--;
        }
        if(lower_index <= upper_index) {
            std::swap(array[lower_index++], array[upper_index--]);
        }
    }

    if(lower_limit < upper_index) {
        quick_sort(array, lower_limit, upper_index);
    }
    if(lower_index < upper_limit) {
        quick_sort(array, lower_index, upper_limit);
    }
}

template <typename T>
void quick_sort(T *array, int size)
{
    quick_sort(array, 0, size-1);
}

