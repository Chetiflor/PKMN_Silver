#include <chrono>
#include <ctime>
#include "text_state.hpp"
#include "text_interface.hpp"
#include "timer.hpp"
#include "game.hpp"
#include "writer.hpp"
#define time_sensitivity 50000000
#define time_delay 4 * time_sensitivity

TextState::TextState(/* args */)
{
}
TextState::TextState(Game *game_)
{
    game = game_;
    last_A = false;
    last_B = false;
}

TextState::~TextState()
{
}

void TextState::step(SDL_Renderer *renderer)
{

    std::string next_state;
    if (game->timer.A != 0 && last_A == false)
    {
        game->text_interface.select_yes_no(next_state, true);
        last_A = true;
        game->text_interface.forward(next_state);
    }
    if (game->timer.B != 0 && last_B == false)
    {
        game->text_interface.select_yes_no(next_state, false);
        last_B = true;
        game->text_interface.forward(next_state);
    }
    if (game->timer.A == 0)
    {
        last_A = false;
    }
    if (game->timer.B == 0)
    {
        last_B = false;
    }
    game->text_interface.step(last_A||last_B);
    game->set_next_state(state_from_string(next_state, game));
    // main_writer.write_style(renderer, 0, 2.f / 3, stamp_w_ratio, stamp_h_ratio, 20, 6);
    game->main_writer.write_wrapped_text(renderer, game->text_interface.get_basic_dialog_content());
    game->main_writer.write_wrapped_text(renderer, game->text_interface.get_basic_dialog_query());
    if (game->text_interface.is_chosing())
    {
        auto time = std::chrono::system_clock::now().time_since_epoch().count();
        if (game->timer.right != 0 && time - game->timer.right > time_sensitivity)
        {
            game->timer.right = time + time_delay;
            game->text_interface.switch_choice({0, 1});
        }
        if (game->timer.up != 0 && time - game->timer.up > time_sensitivity)
        {
            game->timer.up = time + time_delay;
            game->text_interface.switch_choice({-1, 0});
        }
        if (game->timer.left != 0 && time - game->timer.left > time_sensitivity)
        {
            game->timer.left = time + time_delay;
            game->text_interface.switch_choice({0, -1});
        }
        if (game->timer.down != 0 && time - game->timer.down > time_sensitivity)
        {
            game->timer.down = time + time_delay;
            game->text_interface.switch_choice({1, 0});
        }
    }
}