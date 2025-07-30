#include "Loot.hpp"
#include "../config/consts.hpp"
#include "../resorces/loot.hpp"
#include "../utils/dynamicArray.hpp"

Loot::Loot(int x, int y): x(x), y(y), looted(false) {
    this->pixels = dynamicArray<LOOT_HEIGHT, LOOT_WIDTH>(pringles);
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