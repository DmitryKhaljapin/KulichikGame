#pragma once
#include <cstdint>

template<size_t C, size_t R>
uint32_t** dynamicArray(const uint32_t resource_array[C][R]) {
    uint32_t** array = new uint32_t* [C];
    
    for (size_t i = 0; i < C; ++i) {
        array[i] = new uint32_t[R];

        for (size_t j = 0; j < R; ++j) {
            array[i][j] = resource_array[i][j];
        }
    }
    
    return array;
}