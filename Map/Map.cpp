#include <fstream>

#include "Map.hpp"
#include "../config/consts.hpp"

Map::Map() {
    std::ifstream mapFile;
    mapFile.open("resorces/map.txt");
    mapFile.seekg(0);
    
    this->data_ = new int* [MAP_HEIGHT];
    
    for (size_t i = 0; i < MAP_HEIGHT; ++i) {
        this->data_[i] = new int[MAP_WIDTH];

        for (size_t j = 0; j < MAP_WIDTH; ++j) {
            char symbol = 0;
            mapFile.get(symbol);

            if (symbol == '\n') mapFile.get(symbol);

            if (symbol == '#') {
                this->data_[i][j] = 1;
            }
            else {
                this->data_[i][j] = 0;
            }
        }
    }

    mapFile.close();
}

Map::~Map() {
    for (size_t i = 0; i < MAP_HEIGHT; ++i) {
        delete[] this->data_[i];
    }

    delete[] this->data_;
}

int** Map::getMap() const {
    return data_;
}