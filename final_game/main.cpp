#include <iostream>
#include <string>

#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "gameObject.h"
#include "game.h"
#include "gameObject.cpp"
#include "game.cpp"
#include "sprite.cpp"
#include "sprite.h"
#include "map.cpp"
#include "map.h"

SDL_Window* title_window;
SDL_Renderer* title_renderer;
SDL_Window* over_window;
SDL_Renderer* over_renderer;

int main(int argc, char* args[]) 
{
	Game* my_game;
	while(my_game->is_game_active){
	my_game = new Game();
	my_game->is_titlescreen = 1;
	if(my_game->is_titlescreen){
		if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		}
		title_window = SDL_CreateWindow("Coin Chase", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		title_renderer = SDL_CreateRenderer(title_window, -1, 0);

		my_game->initTitle(title_window, title_renderer);
		while(my_game->is_titlescreen){
			my_game->handleEventsTitle();
			my_game->updateTitle(title_window, title_renderer);
		}
		SDL_Quit();
	}

	my_game->init(my_game->numCoins);

	while(my_game->is_game_running){
		int this_start_time = SDL_GetTicks();

		my_game->handleEvents();
		my_game->update();    

		int this_duration = SDL_GetTicks() - this_start_time;
		if(this_duration < (1000/120)){
			SDL_Delay((1000/120)-this_duration);
		}
	}
	my_game->is_game_over = true;
	SDL_Quit();

	if(my_game->is_game_over){
		if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		}
		over_window = SDL_CreateWindow("Coin Chase", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		over_renderer = SDL_CreateRenderer(over_window, -1, 0);

		my_game->initGameOver(over_window, over_renderer);
		while(my_game->is_game_over){
			my_game->handleEventsGameOver();
			my_game->updateGameOver(over_window, over_renderer);
		}
		SDL_Quit();

	}
	}
  
	return 0; 
}
