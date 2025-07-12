#pragma once
#include <SDL2/SDL_image.h>

class Game;

class State
{
protected:
    Game *game;

public:
    State(/* args */);
    State(Game *game_);
    ~State();

    virtual void step(SDL_Renderer *renderer) =0;
};