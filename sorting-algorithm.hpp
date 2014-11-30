#ifndef SORTING_ALGORITHM_HPP
#define SORTING_ALGORITHM_HPP

#include <algorithm>

template <typename T>
void bubble_sort(T *array, int size)
{
    for(int unsorted_size = size; unsorted_size > 0; unsorted_size--) {
        for(int i = 1; i < unsorted_size; i++) {
            if(array[i] < array[i - 1]) {
                std::swap(array[i], array[i - 1]);
            }
        }
    }
}

template <typename T>
void selection_sort(T *array, int size)
{
    for(int sorted_size = 0; sorted_size < size; sorted_size++) {
        int minimum_index = sorted_size;
        for(int i = sorted_size + 1; i < size; i++) {
            if(array[i] < array[minimum_index]) {
                minimum_index = i;
            }
        }
        std::swap(array[sorted_size], array[minimum_index]);
    }
}

template <typename T>
void insertion_sort(T *array, int size)
{
    for(int sorted_size = 1; sorted_size < size; sorted_size++) {
        const T insertion_value = array[sorted_size];
        int insertion_index = sorted_size - 1;

        while(insertion_index > 0 && array[insertion_index] > insertion_value) {
            array[insertion_index + 1] = array[insertion_index];
            insertion_index--;
        }
        array[insertion_index] = insertion_value;
    }
}

template <typename T>
void shaker_sort(T *array, int size)
{
    int lower_limit = 0;
    int upper_limit = size - 1;

    while(lower_limit <= upper_limit) {
        for(int i = lower_limit + 1; i <= upper_limit; i++) {
            if(array[i] < array[i - 1]) {
                std::swap(array[i], array[i - 1]);
            }
        }
        upper_limit--;

        for(int i = upper_limit - 1; i >= lower_limit; i--) {
            if(array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
            }
        }
        lower_limit++;
    }
}

template <typename T>
void shell_sort(T *array, int size)
{
    int initial_hop = 1;
    for(; initial_hop * 3 + 1 < size; initial_hop = initial_hop * 3 + 1);

    for(int hop = initial_hop; hop > 0; hop /= 3) {
        for(int offset = 0; offset < hop; offset++) {
            for(int sorted_size = 1; sorted_size * hop + offset < size; sorted_size++) {
                const T insertion_value = array[sorted_size * hop + offset];
                int insertion_index = sorted_size * hop - hop;

                while(insertion_index > 0 && array[insertion_index] > insertion_value) {
                    array[insertion_index + hop] = array[insertion_index];
                    insertion_index -= hop;
                }
                array[insertion_index] = insertion_value;
            }
        }
    }
}

template <typename T>
void comb_sort(T *array, int size)
{
    int gap = size;
    bool done = false;

    while(!done || gap > 1) {
        done = true;
        gap = std::max(gap * 10 / 13, 1);

        for(int i = gap; i < size; i++) {
            if(array[i] < array[i - gap]) {
                done = false;
                std::swap(array[i], array[i - gap]);
            }
        }
    }
}

template <typename T>
void merge(T *target, const T *begin1, const T *end1, const T *begin2, const T *end2)
{
    while(begin1 != end1 && begin2 != end2) {
        *target++ = *begin1 < *begin2 ? *begin1++ : *begin2++;
    }
    while(begin1 != end1) {
        *target++ = *begin1++;
    }
    while(begin2 != end2) {
        *target++ = *begin2++;
    }
}

template <typename T>
void merge_sort(T *array, int size)
{
    T *source = array;
    T *buffer = new T[size];
    T *target = buffer;

    for(int block_size = 1; block_size < size; block_size *= 2) {
        for(int offset = 0; offset < size; offset += block_size * 2) {
            merge(&target[offset],
                  &source[std::min(offset + block_size * 0, size)],
                  &source[std::min(offset + block_size * 1, size)],
                  &source[std::min(offset + block_size * 1, size)],
                  &source[std::min(offset + block_size * 2, size)]);
        }
        std::swap(source, target);
    }
    if(array == target) {
        std::copy(source, source + size, array);
    }

    delete[] buffer;
}

template <typename T>
bool is_heap(const T *array, int size)
{
    for(int i = 1, parent_index = 0; i < size; i++, parent_index = (i - 1) / 2) {
        if(array[i] > array[parent_index]) {
            return false;
        }
    }
    return true;
}

template <typename T>
void heap_push(T *array, int size, const T value)
{
    array[size] = value;

    for(int i = size, parent_index = (i - 1) / 2; i > 0 && array[i] > array[parent_index]; i = parent_index, parent_index = (i - 1) / 2) {
        std::swap(array[i], array[parent_index]);
    }
}

template <typename T>
T heap_pop(T *array, int size)
{
    const T value = array[0];
    array[0] = array[--size];

    for(int i = 0, child_index = 1; child_index < size; i = child_index, child_index = i * 2 + 1) {
        if(child_index + 1 < size && array[child_index] < array[child_index + 1]) {
            child_index++;
        }
        if(array[i] > array[child_index]) {
            break;
        }
        std::swap(array[i], array[child_index]);
    }

    return value;
}

template <typename T>
void heap_sort(T *array, int size)
{
    for(int heap_size = 0; heap_size < size; heap_size++) {
        heap_push(array, heap_size, array[heap_size]);
    }

    for(int heap_size = size; heap_size > 0; heap_size--) {
        array[heap_size-1] = heap_pop(array, heap_size);
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
    quick_sort(array, 0, size - 1);
}

#endif

