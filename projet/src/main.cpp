#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <vector>
#include "game.hpp"

#define pressed true
#define released false

std::vector<SDL_Keycode> controls = {SDLK_w, SDLK_x, SDLK_RIGHT, SDLK_UP, SDLK_LEFT, SDLK_DOWN, SDLK_RETURN, SDLK_BACKSPACE, SDLK_s, SDLK_q};

GBA_event control_map(SDL_Keycode k, bool is_pressed)
{
	int found = -1;
	int count = 0;
	while (found < 0 && count < controls.size())
	{
		if (controls[count] == k)
		{
			found = count;
		}
		count++;
	}
	switch (found)
	{
	case 0:
		return is_pressed ? A_pressed : A_released;
	case 1:
		return is_pressed ? B_pressed : B_released;
	case 2:
		return is_pressed ? right_pressed : right_released;
	case 3:
		return is_pressed ? up_pressed : up_released;
	case 4:
		return is_pressed ? left_pressed : left_released;
	case 5:
		return is_pressed ? down_pressed : down_released;
	case 6:
		return is_pressed ? start_pressed : start_released;
	case 7:
		return is_pressed ? select_pressed : select_released;
	case 8:
		return is_pressed ? R_pressed : R_released;
	case 9:
		return is_pressed ? L_pressed : L_released;

	default:
		return none;
	}
}
int *w = new int(640);
int *h = new int(560);
int *Game::w = new int();
int *Game::h = new int();
int *Writer::w = new int();
int *Writer::h = new int();

int main(int argc, char *argv[])
{
	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
	SDL_Window *win = SDL_CreateWindow("GAME",
									   SDL_WINDOWPOS_CENTERED,
									   SDL_WINDOWPOS_CENTERED,
									   *w, *h, SDL_WINDOW_RESIZABLE);
	SDL_Renderer *renderer = SDL_CreateRenderer(win,
												-1,
												SDL_RENDERER_ACCELERATED);
	Game *g = new Game();
	bool run = true;
	Game::w = w;
	Game::h = h;
	Writer::w = w;
	Writer::h = h;
	while (run)
	{

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_GetWindowSize(win, w, h);
		SDL_Event ev;
		if (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				run = false;
				break;
			case SDL_KEYDOWN:
				g->getEvent(control_map(ev.key.keysym.sym, pressed));
				break;
			case SDL_KEYUP:
				g->getEvent(control_map(ev.key.keysym.sym, released));
				break;
			default:
				break;
			}
		}
		g->step(renderer);

		SDL_RenderPresent(renderer);
	}

	return 0;
}
