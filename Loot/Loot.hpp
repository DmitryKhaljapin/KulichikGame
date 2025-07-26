#pragma once
#include <cstdint>

class Loot {
    uint32_t** pixels;
    
    public:
        int x;
        int y;
        bool looted;

        Loot(int, int);
        ~Loot();

    uint32_t** getPixels() const;
};