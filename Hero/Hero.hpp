#pragma once
#include <cstdint>

#include "../config/consts.hpp"
#include "../Map/Map.hpp"

class Hero {
    int width_pixels;
    int height_pixels;
    
    uint32_t** pixels;

    void upLevel();

    public:
        int x = 0;
        int y = 0;

        int size = 0;
        Map* map;
        
        Hero(Map* map);
        ~Hero();

        uint32_t** getPixels() const;
        void move(int key_code);
};