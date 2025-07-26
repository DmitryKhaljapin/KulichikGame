#pragma once
#include <cstdint>

#include "../config/consts.hpp"

class Hero {
    int width_pixels;
    int height_pixels;
    
    uint32_t** pixels;

    public:
        int x = 0;
        int y = 0;

        int size = 0;
        //add map
        Hero();
        ~Hero();

        uint32_t** getPixels() const;
        void move(int key_code);
};