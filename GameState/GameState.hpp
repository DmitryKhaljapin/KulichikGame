#pragma once

enum Stage {
    START_MENU,
    ON_GOING,
    FINISH,
};

class GameState {
    
    void reset();
    public:
    Stage stage;
    int level;
    int score;
    
    int x_start;
    int y_start;
    
    int loot_left;
    
    GameState();
    void upLevel();
};