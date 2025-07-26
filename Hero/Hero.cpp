#include "Hero.hpp"
#include "../resorces/hero.hpp"

Hero::Hero(): 
    width_pixels(HERO_PIXEL_WIDTH), 
    height_pixels(HERO_PIXEL_HEIGHT), 
    x(HERO_START_X),
    y(HERO_START_Y),
    size(HERO_SIZE)  {
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

            this->y = next_y;
            break;
        }
        case 0x44: {
            int next_x = this->x + 1;

            this->x = next_x;
            break;
        }
        case 0x53: {
            int next_y = this->y + 1;

            this->y = next_y;
            break;
        }
        case 0x41: {
            int next_x = this->x - 1;

            this->x = next_x;
            break;
        }
    }
}