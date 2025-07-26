#pragma once

#include "../config/consts.hpp"

class Map {
    int** data_;

    public:
    Map();
    ~Map();

    int** getMap() const;
};