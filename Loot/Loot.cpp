#include "Loot.hpp"
#include "../config/consts.hpp"
#include "../resorces/loot.hpp"
#include "../utils/dynamicArray.hpp"
#include "../utils/deleteDynamicArray.hpp"

Loot::Loot(int x, int y): x(x), y(y), looted(false) {
    this->pixels = dynamicArray<LOOT_HEIGHT, LOOT_WIDTH>(pringles);
}

Loot::~Loot() {
    deleteDynamicArray(this->pixels, LOOT_HEIGHT);
}

uint32_t** Loot::getPixels() const {
    return this->pixels;
}