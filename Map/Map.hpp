#pragma once

#include "../config/consts.hpp"
#include "../Loot/Loot.hpp"

class Map {
    int** data_;

    void createData(int);
    void destoryData();
    
    public:
        Loot** loots = 0;
        
        Map();
        ~Map();

    int** getMap() const;
    void update();
};