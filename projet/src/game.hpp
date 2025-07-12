#pragma once
#include <SDL2/SDL_image.h>
#include "writer.hpp"
#include "text_interface.hpp"
#include "enums.hpp"
#include "state.hpp"
#include "map_state.hpp"
#include "text_state.hpp"
#include "timer.hpp"

State * state_from_string(std::string str, Game * game);

class Game
{
private:
    State *current_state;
    State *next_state;

    keys_timer timer;
    Writer main_writer;
    TextInterface text_interface;

public:
    static int *w;
    static int *h;

    Game(/* args */);
    ~Game();

    void getEvent(GBA_event ev);
    void set_next_state(State *next_state_);
    void print_timer();
    void step(SDL_Renderer *renderer);
    
    
    friend MapState;
    friend TextState;
};
