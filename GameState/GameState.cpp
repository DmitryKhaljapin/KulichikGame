#include "GameState.hpp"
#include "../config/consts.hpp"

GameState::GameState() : 
    stage(START_MENU),
    score(0), 
    level(1), 
    x_start(HERO_START_X), 
    y_start(HERO_START_Y), 
    loot_left(LOOT_COUNT) {}

void GameState::upLevel() {
    int next_level = this->level + 1;

    if (next_level > LEVELS) {
        reset();
        this->stage = FINISH;
        return;
    }
    
    this->level = next_level;
}

void GameState::reset() {
    this->stage = ON_GOING;
    this->level = 1;
    this->score = 0;

    this->x_start = HERO_START_X;
    this->y_start = HERO_START_Y;

    this->loot_left = LOOT_COUNT;
}