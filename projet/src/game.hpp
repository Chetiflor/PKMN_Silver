#pragma once
#include <SDL2/SDL_image.h>
#include "writer.hpp"
#include "text_interface.hpp"
#include "enums.hpp"

struct keys_timer
{
    long int A = 0;
    long int B = 0;
    long int right = 0;
    long int up = 0;
    long int left = 0;
    long int down = 0;
    long int start = 0;
    long int select = 0;
    long int R = 0;
    long int L = 0;

    void reset();
    void print();
};

class Game
{
private:
    State state;
    keys_timer timer;

    Writer main_writer;
    TextInterface text_interface;

public:
    static int *w;
    static int *h;


    Game(/* args */);
    ~Game();

    void getEvent(GBA_event ev);
    void print_timer();
    void step(SDL_Renderer *renderer);
};
