#include <chrono>
#include <ctime>
#include "map_state.hpp"
#include "text_state.hpp"
#include "text_interface.hpp"
#include "timer.hpp"
#include "game.hpp"
#include "writer.hpp"

MapState::MapState(/* args */)
{
}
MapState::MapState(Game *game_)
{
    game = game_;
}

MapState::~MapState()
{
}

void MapState::step(SDL_Renderer *renderer)
{



    if (game->timer.start != 0)
    {
        // text_interface.load_dialog(text_interface.build_monolog_from_string("Hello World ! How are you today ? I am fine for my part.", 18));

        game->text_interface.load_dialog(game->text_interface.craft_test_dialog());
        game->set_next_state(new TextState(game));
    }
}