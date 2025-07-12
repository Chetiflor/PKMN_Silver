#pragma once
#include"state.hpp"

class TextState : public State
{
private:
    bool last_A;
    bool last_B;

public:
TextState(/* args */);
TextState(Game * game_);
    ~TextState();

    void step(SDL_Renderer *renderer);
};

