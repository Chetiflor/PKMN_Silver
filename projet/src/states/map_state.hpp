#pragma once
#include "state.hpp"

class MapState : public State
{
public:
    MapState(/* args */);
    MapState(Game *game_);
    ~MapState();

    void step(SDL_Renderer *renderer);
};
