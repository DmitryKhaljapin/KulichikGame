#pragma once
#include <cstdint>

template<typename T>
void deleteDynamicArray(T** array, size_t columns) {
    for (size_t i = 0; i < columns; ++i) {
        delete[] array[i];
    }

    delete[] array;
}