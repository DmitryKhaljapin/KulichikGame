#include <fstream>
#include <string>

#include "Map.hpp"
#include "../config/consts.hpp"
#include "../GameState/GameState.hpp"
#include "../utils/deleteDynamicArray.hpp"

extern GameState state;

void Map::createData(int level) {
    // fix me by a custom String implamentation
    std::string path = "resorces/map" + std::to_string(state.level) + ".txt";

    std::ifstream mapFile;
    mapFile.open(path);
    mapFile.seekg(0);
    
    this->data_ = new int* [MAP_HEIGHT];
    this->loots = new Loot* [LOOT_COUNT];

    int current_loot_count = 0;
    
    for (size_t i = 0; i < MAP_HEIGHT; ++i) {
        this->data_[i] = new int[MAP_WIDTH];

        for (size_t j = 0; j < MAP_WIDTH; ++j) {
            char symbol = 0;
            mapFile.get(symbol);

            if (symbol == '\n') mapFile.get(symbol);
            
            if (symbol == '$') {
                Loot* loot = new Loot(j, i);
                this->loots[current_loot_count] = loot;
                
                ++current_loot_count;
            }

            if (symbol == 'H') {
                state.x_start = j;
                state.y_start = i;
            }

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

void Map::destoryData()  {
    deleteDynamicArray(this->data_, MAP_HEIGHT);
}

Map::Map() {
   createData(state.level);
}

Map::~Map() {
    destoryData();
}

int** Map::getMap() const {
    return data_;
}

void Map::update()  {
    destoryData();
    createData(state.level);
}