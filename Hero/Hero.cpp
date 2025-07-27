#include "Hero.hpp"
#include "../resorces/hero.hpp"
#include "../GameState/GameState.hpp"

extern GameState state;

 void Hero::upLevel() {
    state.upLevel();
    
    this->map->update();
    this->x = state.x_start;
    this->y = state.y_start;

    state.loot_left = (LOOT_COUNT);
}

Hero::Hero(Map* map): 
    width_pixels(HERO_PIXEL_WIDTH), 
    height_pixels(HERO_PIXEL_HEIGHT), 
    x(state.x_start),
    y(state.y_start),
    size(HERO_SIZE),
    map(map) {
        this->pixels = new uint32_t* [height_pixels];
        
        // exclude as a template function to utils
        for (size_t i = 0; i < height_pixels; ++i) {
            this->pixels[i] = new uint32_t[width_pixels];

            for (size_t j = 0; j < width_pixels; ++j) {
                this->pixels[i][j] = image[i][j];
            }
        }
}

Hero::~Hero() {
    for (size_t i = 0; i < height_pixels; ++i) {
        delete[] this->pixels[i];
    }

    delete[] this->pixels;
}

uint32_t** Hero::getPixels() const {
    return pixels;
}

void Hero::move(int key_code) {
    switch(key_code) {
        case 0x57: {
            int next_y = this->y - 1;

            if (map->getMap()[next_y][this->x] == 1) return;

            this->y = next_y;
            break;
        }
        case 0x44: {
            int next_x = this->x + 1;

            if (map->getMap()[this->y][next_x] == 1) return;

            this->x = next_x;
            break;
        }
        case 0x53: {
            int next_y = this->y + 1;

            if (map->getMap()[next_y][this->x] == 1) return;

            this->y = next_y;
            break;
        }
        case 0x41: {
            int next_x = this->x - 1;

            if (map->getMap()[this->y][next_x] == 1) return;

            this->x = next_x;
            break;
        }
    }

    for (size_t i = 0; i < LOOT_COUNT; ++i) {
        Loot* loot = this->map->loots[i];

        if (loot->x == this->x && loot->y == this->y) {
            if (!(loot->looted)) {
                state.score += 10;
                --state.loot_left;

                loot->looted = true;

                if (state.loot_left == 0) upLevel();
            }
        } 
    }
}