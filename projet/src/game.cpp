#include <iostream>
#include <chrono>
#include <ctime>
#include "game.hpp"
#include "wrapper.hpp"

#define time_sensitivity 50000000
#define time_delay 4*time_sensitivity

void keys_timer::reset()
{
    A = 0;
    B = 0;
    right = 0;
    up = 0;
    left = 0;
    down = 0;
    start = 0;
    select = 0;
    R = 0;
    L = 0;
}

void keys_timer::print()
{
    float x = 1000000000.f;
    auto time = std::chrono::system_clock::now().time_since_epoch().count();
#define since(a) (a > 0 ? time - a : 0)
    std::cout << "A:" << since(A) / x << ", B:" << since(B) / x << ", right:" << since(right) / x << ", up:" << since(up) / x << ", left:" << since(left) / x << ", down:" << since(down) / x << ", start:" << since(start) / x << ", select:" << since(select) / x << ", R:" << since(R) / x << ", L:" << since(L) / x << std::endl;
}

Game::Game(/* args */)
{
    main_writer.load_font("../projet/ascii_pkm.txt");
    main_writer.load_style("../projet/style_0.txt");
    state = map;
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

void Game::step(SDL_Renderer *renderer)
{
    float stamp_w_ratio = 1.f / 20;
    float stamp_h_ratio = 1.f / 18;
    // main_writer.write_style(renderer,0,2.f/3,stamp_w_ratio,stamp_h_ratio,20,6);
    // main_writer.write_string(renderer,"Hello World !",0,2.f/3+2*stamp_h_ratio,stamp_w_ratio,stamp_h_ratio,18);
    // main_writer.write_string(renderer,"How are you ?",0,2.f/3+4*stamp_h_ratio,stamp_w_ratio,stamp_h_ratio,18);
    State nextstate = state;
    bool do_print = false;
    switch (state)
    {
    case map:
        if (timer.start != 0)
        {
            // text_interface.load_dialog(text_interface.build_monolog_from_string("Hello World ! How are you today ? I am fine for my part.", 18));

            text_interface.load_dialog(text_interface.craft_test_dialog());
            nextstate = text;
        }
        if (do_print)
            std::cout << "map" << std::endl;

        break;
    case text:
        if (timer.A != 0)
        {
            timer.A = 0;
            text_interface.forward(nextstate);
        }
        // main_writer.write_style(renderer, 0, 2.f / 3, stamp_w_ratio, stamp_h_ratio, 20, 6);
        main_writer.write_wrapped_text(renderer, text_interface.get_basic_dialog_content());
        main_writer.write_wrapped_text(renderer, text_interface.get_basic_dialog_query());
        if (text_interface.is_chosing())
        {
            auto time = std::chrono::system_clock::now().time_since_epoch().count();
            if (timer.right != 0 && time - timer.right > time_sensitivity)
            {
                timer.right = time + time_delay;
                text_interface.switch_choice({0, 1});
            }
            if (timer.up != 0 && time - timer.up > time_sensitivity)
            {
                timer.up = time + time_delay;
                text_interface.switch_choice({-1, 0});
            }
            if (timer.left != 0 && time - timer.left > time_sensitivity)
            {
                timer.left = time + time_delay;
                text_interface.switch_choice({0, -1});
            }
            if (timer.down != 0 && time - timer.down > time_sensitivity)
            {
                timer.down = time + time_delay;
                text_interface.switch_choice({1, 0});
            }
        }

        if (do_print)
            std::cout << "text" << std::endl;
        break;

    case title:

        if (do_print)
            std::cout << "title" << std::endl;
        break;

    case battle:

        if (do_print)
            std::cout << "battle" << std::endl;
        break;

    case pokedex:

        if (do_print)
            std::cout << "pokedex" << std::endl;
        break;

    case team:

        if (do_print)
            std::cout << "team" << std::endl;
        break;

    case inventory:
        if (do_print)
            std::cout << "inventory" << std::endl;
        break;

    case save:

        if (do_print)
            std::cout << "save" << std::endl;
        break;

    case settings:

        if (do_print)
            std::cout << "settings" << std::endl;
        break;

    case special:

        if (do_print)
            std::cout << "special" << std::endl;
        break;

    default:
        std::cout
            << state
            << std::endl;
        break;
    }
    state = nextstate;
}