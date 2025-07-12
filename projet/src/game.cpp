#include <iostream>
#include <chrono>
#include <ctime>
#include "game.hpp"
#include "wrapper.hpp"
#include "text_state.hpp"
#include "map_state.hpp"

State *state_from_string(std::string str, Game *game)
{
    if (str == "map")
    {
        return new MapState(game);
    }
    if (str == "text")
    {
        return new TextState(game);
    }
    return nullptr;
}

Game::Game(/* args */)
{
    main_writer.load_font("../projet/data/fonts/ascii_pkm_RGBA.txt",false);
    main_writer.load_font("../projet/data/fonts/style_1_RGBA.txt",true);
    current_state = new MapState(this);
    // text_interface.load_dialog(text_interface.build_monolog_from_string("Hello World ! How are you ? I'm fine, thank you.", 18));
}

Game::~Game()
{
}

void Game::getEvent(GBA_event ev)
{
    auto time = std::chrono::system_clock::now();
    // std::cout << time.time_since_epoch().count() << " received : " << ev << std::endl;
    switch (ev)
    {
    case none:
        timer.reset();
        break;
    case A_pressed:
        if (timer.A == 0)
            timer.A = time.time_since_epoch().count();
        break;
    case A_released:
        timer.A = 0;
        break;
    case B_pressed:
        if (timer.B == 0)
            timer.B = time.time_since_epoch().count();
        break;
    case B_released:
        timer.B = 0;
        break;
    case start_pressed:
        if (timer.start == 0)
            timer.start = time.time_since_epoch().count();
        break;
    case start_released:
        timer.start = 0;
        break;
    case select_pressed:
        if (timer.select == 0)
            timer.select = time.time_since_epoch().count();
        break;
    case select_released:
        timer.select = 0;
        break;
    case R_pressed:
        if (timer.R == 0)
            timer.R = time.time_since_epoch().count();
        break;
    case R_released:
        timer.R = 0;
        break;
    case L_pressed:
        if (timer.L == 0)
            timer.L = time.time_since_epoch().count();
        break;
    case L_released:
        timer.L = 0;
        break;
    case right_pressed:
        if (timer.right == 0)
            timer.right = time.time_since_epoch().count();
        break;
    case right_released:
        timer.right = 0;
        break;
    case up_pressed:
        if (timer.up == 0)
            timer.up = time.time_since_epoch().count();
        break;
    case up_released:
        timer.up = 0;
        break;
    case left_pressed:
        if (timer.left == 0)
            timer.left = time.time_since_epoch().count();
        break;
    case left_released:
        timer.left = 0;
        break;
    case down_pressed:
        if (timer.down == 0)
            timer.down = time.time_since_epoch().count();
        break;
    case down_released:
        timer.down = 0;
        break;
    default:
        break;
    }
}

void Game::print_timer()
{
    timer.print();
}

void Game::set_next_state(State *next_state_)
{
    next_state = next_state_;
}

void Game::step(SDL_Renderer *renderer)
{
    current_state->step(renderer);
    if (next_state != nullptr)
    {
        delete (current_state);
        current_state = next_state;
        next_state = nullptr;
    }
}