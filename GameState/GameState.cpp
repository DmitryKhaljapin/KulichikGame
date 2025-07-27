#include "GameState.hpp"
#include "../config/consts.hpp"

GameState::GameState() : 
    stage(START_MENU), 
    level(1), 
    x_start(HERO_START_X), 
    y_start(HERO_START_Y), 
    loot_left(LOOT_COUNT) {}

void GameState::upLevel() {
    int next_level = this->level + 1;

    if (next_level > LEVELS) return;
    
    this->level = next_level;
}