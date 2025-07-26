#include "Loot.hpp"
#include "../config/consts.hpp"
#include "../resorces/loot.hpp"

Loot::Loot(int x, int y): x(x), y(y), looted(false) {
    this->pixels = new uint32_t*[LOOT_HEIGHT];

    for(size_t i = 0; i < LOOT_HEIGHT; ++i) {
        this->pixels[i] = new uint32_t[LOOT_HEIGHT];

        for (size_t j = 0; j < LOOT_WIDTH; ++j) {
            this->pixels[i][j] = pringles[i][j];
        }
    }
}

Loot::~Loot() {
    for (size_t i = 0; i < LOOT_HEIGHT; ++i) {
        delete[] this->pixels[i];
    }

    delete[] this->pixels;
}

uint32_t** Loot::getPixels() const {
    return this->pixels;
}