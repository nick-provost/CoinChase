#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

Game::Game() {

}

Game::~Game() {

}

void Game::init(int numCoins) {
	my_game = new GameObject();
	my_game->obj_init("./spideyspritesheet3.png", game_renderer, 784, 588, numCoins);
	is_game_running = true;
}

void Game::handleEvents() {
	SDL_Event game_event;
	SDL_PollEvent(&game_event);
	
	if(game_event.type == SDL_KEYDOWN){
		switch(game_event.key.keysym.sym){
			case SDLK_w:
				MOVE_AWAY = true;
				break;
			case SDLK_a:
				MOVE_LEFT = true;
				break;
			case SDLK_s:
				MOVE_TOWARD = true;
				break;
			case SDLK_d:
				MOVE_RIGHT = true;
				break;
			case SDLK_SPACE:
				if(my_game->obj_sprite->prevAnimation == 3){
					JUMP_RIGHT = true;
				}
				else {
					JUMP_LEFT = true;
				}
				break;
		}
	}
	else if(game_event.type == SDL_KEYUP){
		switch(game_event.key.keysym.sym){
			case SDLK_w:
				MOVE_AWAY = false;
				break;
			case SDLK_a:
				MOVE_LEFT = false;
				break;
			case SDLK_s:
				MOVE_TOWARD = false;
				break;
			case SDLK_d:
				MOVE_RIGHT = false;
				break;
			case SDLK_SPACE:
				JUMP_RIGHT = false;
				JUMP_LEFT = false;
				break;
		}
	}
	
	if(MOVE_LEFT && MOVE_AWAY) {
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() + 3);
		my_game->obj_set_y_pos(my_game->obj_get_y_pos() + 3);
		my_game->obj_sprite->animationIndex = 4;
	}
	else if(MOVE_LEFT && MOVE_TOWARD){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() + 3);
		my_game->obj_set_y_pos(my_game->obj_get_y_pos() - 3);
		my_game->obj_sprite->animationIndex = 4;
	}
	else if(MOVE_RIGHT && MOVE_AWAY){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() - 3);
		my_game->obj_set_y_pos(my_game->obj_get_y_pos() + 3);
		my_game->obj_sprite->animationIndex = 3;
	}
	else if(MOVE_RIGHT && MOVE_TOWARD){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() - 3);
		my_game->obj_set_y_pos(my_game->obj_get_y_pos() - 3);
		my_game->obj_sprite->animationIndex = 3;
	}
	else if(JUMP_LEFT && MOVE_AWAY){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() + 9);
		my_game->obj_set_y_pos(my_game->obj_get_y_pos() + 3);
		my_game->obj_sprite->animationIndex = 6;
	}
	else if(JUMP_LEFT && MOVE_TOWARD){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() + 9);
		my_game->obj_set_y_pos(my_game->obj_get_y_pos() - 3);
		my_game->obj_sprite->animationIndex = 6;
	}
	else if(JUMP_RIGHT && MOVE_AWAY){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() - 9);
		my_game->obj_set_y_pos(my_game->obj_get_y_pos() + 3);
		my_game->obj_sprite->animationIndex = 5;
	}
	else if(JUMP_RIGHT && MOVE_TOWARD){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() - 9);
		my_game->obj_set_y_pos(my_game->obj_get_y_pos() - 3);
		my_game->obj_sprite->animationIndex = 5;
	}
	else if(MOVE_LEFT){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() + 3);
		my_game->obj_sprite->animationIndex = 4;
	}
	else if(MOVE_RIGHT){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() - 3);
		my_game->obj_sprite->animationIndex = 3;
	}
	else if(MOVE_AWAY){
		my_game->obj_set_y_pos(my_game->obj_get_y_pos() + 3);
		my_game->obj_sprite->animationIndex = 1;
	}
	else if(MOVE_TOWARD){
		my_game->obj_set_y_pos(my_game->obj_get_y_pos() - 3);
		my_game->obj_sprite->animationIndex = 2;
	}
	else if(JUMP_LEFT){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() + 9);
		my_game->obj_sprite->animationIndex = 6;
	}
	else if(JUMP_RIGHT){
		my_game->obj_set_x_pos(my_game->obj_get_x_pos() - 9);
		my_game->obj_sprite->animationIndex = 5;
	}
}

void Game::update() {
	final_time = (SDL_GetTicks()-my_game->start)/1000;
	if(my_game->coinsLeft == 0) is_game_running = false;
	else{
		my_game->obj_update();
	}
}

void Game::render() {}

void Game::quit() {}

void::Game::initTitle(SDL_Window* title_window, SDL_Renderer* title_renderer){
	if(TTF_Init()==-1)
		std::cout << "TTF_Init: " << SDL_GetError() << std::endl;

	font = TTF_OpenFont("./font.ttf", 32);
	if(!font)
		std::cout << "TTF_OpenFont: " << SDL_GetError() << std::endl;

	

}

void Game::updateTitle(SDL_Window* title_window, SDL_Renderer* title_renderer){
	SDL_RenderClear(title_renderer);

	SDL_Rect title_rect;
	title_rect.x = 10;
	title_rect.y = 10;
	title_rect.w = 620;
	title_rect.h = 100;
	SDL_Color color={255,0,0};
	string title = "Coin Chase";
	const char * c = title.c_str();
	SDL_Surface* title_surface=TTF_RenderText_Solid(font,c,color);
	SDL_Texture* title_tex = SDL_CreateTextureFromSurface(title_renderer, title_surface);
	SDL_FreeSurface(title_surface);
	SDL_RenderCopy(title_renderer, title_tex, NULL, &title_rect);

	SDL_Rect rules_rect;
	rules_rect.x = 10;
	rules_rect.y = 150;
	rules_rect.w = 620;
	rules_rect.h = 25;
	SDL_Color white={255,255,255};
	string rules = "The goal of this game is to collect all of the coins as quickly as possible.";
	const char* rule = rules.c_str();
	SDL_Surface* rules_surface = TTF_RenderText_Solid(font,rule,white);
	SDL_Texture* rules_tex = SDL_CreateTextureFromSurface(title_renderer, rules_surface);
	SDL_FreeSurface(rules_surface);
	SDL_RenderCopy(title_renderer, rules_tex, NULL, &rules_rect);

	SDL_Rect begin_rect;
	begin_rect.x = 95;
	begin_rect.y = 270;
	begin_rect.w = 450;
	begin_rect.h = 50;
	string begin = "Press LSHIFT to play with 5 coins!";
	const char* beg = begin.c_str();
	SDL_Surface* begin_surface = TTF_RenderText_Solid(font,beg,color);
	SDL_Texture* begin_tex = SDL_CreateTextureFromSurface(title_renderer, begin_surface);
	SDL_FreeSurface(begin_surface);
	SDL_RenderCopy(title_renderer, begin_tex, NULL, &begin_rect);

	SDL_Rect begin2_rect;
	begin2_rect.x = 95;
	begin2_rect.y = 320;
	begin2_rect.w = 450;
	begin2_rect.h = 50;
	string begin2 = "Press ENTER to play with 10 coins!";
	const char* beg2 = begin2.c_str();
	SDL_Surface* begin2_surface = TTF_RenderText_Solid(font,beg2,color);
	SDL_Texture* begin2_tex = SDL_CreateTextureFromSurface(title_renderer, begin2_surface);
	SDL_FreeSurface(begin2_surface);
	SDL_RenderCopy(title_renderer, begin2_tex, NULL, &begin2_rect);

	SDL_Rect begin3_rect;
	begin3_rect.x = 95;
	begin3_rect.y = 370;
	begin3_rect.w = 450;
	begin3_rect.h = 50;
	string begin3 = "Press SPACE to play with 25 coins!";
	const char* beg3 = begin3.c_str();
	SDL_Surface* begin3_surface = TTF_RenderText_Solid(font,beg3,color);
	SDL_Texture* begin3_tex = SDL_CreateTextureFromSurface(title_renderer, begin3_surface);
	SDL_FreeSurface(begin3_surface);
	SDL_RenderCopy(title_renderer, begin3_tex, NULL, &begin3_rect);

	SDL_RenderPresent(title_renderer);
}

void Game::handleEventsTitle() {
	SDL_Event game_event;
	SDL_PollEvent(&game_event);

	if(game_event.type == SDL_KEYDOWN){
		switch(game_event.key.keysym.sym){
			case SDLK_LSHIFT:
				is_titlescreen = false;
				is_game_running = true;
				numCoins = 5;
				break;
			case SDLK_RETURN:
				is_titlescreen = false;
				is_game_running = true;
				numCoins = 10;
				break;
			case SDLK_SPACE:
				is_titlescreen = false;
				is_game_running = true;
				numCoins = 25;
				break;
		}
	}
}

void::Game::initGameOver(SDL_Window* over_window, SDL_Renderer* over_renderer){
	if(TTF_Init()==-1)
		std::cout << "TTF_Init: " << SDL_GetError() << std::endl;

	font = TTF_OpenFont("./font.ttf", 32);
	if(!font)
		std::cout << "TTF_OpenFont: " << SDL_GetError() << std::endl;
}

void Game::updateGameOver(SDL_Window* over_window, SDL_Renderer* over_renderer){
	SDL_RenderClear(over_renderer);

	SDL_Rect over_rect;
	over_rect.x = 10;
	over_rect.y = 10;
	over_rect.w = 620;
	over_rect.h = 100;
	SDL_Color color={255,0,0};
	string over = "GAME OVER";
	const char * c = over.c_str();
	SDL_Surface* over_surface=TTF_RenderText_Solid(font,c,color);
	SDL_Texture* over_tex = SDL_CreateTextureFromSurface(over_renderer, over_surface);
	SDL_FreeSurface(over_surface);
	SDL_RenderCopy(over_renderer, over_tex, NULL, &over_rect);

	SDL_Rect yscore_rect;
	yscore_rect.x = 185;
	yscore_rect.y = 125;
	yscore_rect.w = 270;
	yscore_rect.h = 50;

	SDL_Color white={255,255,255};
	string your_score = "Your Time:";
	const char* your_time = your_score.c_str();
	SDL_Surface* yscore_surface = TTF_RenderText_Solid(font,your_time,white);
	SDL_Texture* yscore_tex = SDL_CreateTextureFromSurface(over_renderer, yscore_surface);
	SDL_FreeSurface(yscore_surface);
	SDL_RenderCopy(over_renderer, yscore_tex, NULL, &yscore_rect);

	SDL_Rect score_rect;
	score_rect.x = 160;
	score_rect.y = 175;
	score_rect.w = 320;
	score_rect.h = 50;
	string score = std::to_string(final_time) + " seconds";
	const char* time = score.c_str();
	SDL_Surface* score_surface = TTF_RenderText_Solid(font,time,white);
	SDL_Texture* score_tex = SDL_CreateTextureFromSurface(over_renderer, score_surface);
	SDL_FreeSurface(score_surface);
	SDL_RenderCopy(over_renderer, score_tex, NULL, &score_rect);

	SDL_Rect close_rect;
	close_rect.x = 120;
	close_rect.y = 300;
	close_rect.w = 400;
	close_rect.h = 50;
	string close = "Press ESC to close the game";
	const char* clo = close.c_str();
	SDL_Surface* close_surface = TTF_RenderText_Solid(font,clo,color);
	SDL_Texture* close_tex = SDL_CreateTextureFromSurface(over_renderer, close_surface);
	SDL_FreeSurface(close_surface);
	SDL_RenderCopy(over_renderer, close_tex, NULL, &close_rect);

	SDL_Rect again_rect;
	again_rect.x = 120;
	again_rect.y = 350;
	again_rect.w = 400;
	again_rect.h = 50;
	string again = "Press ENTER to play again!";
	const char* aga = again.c_str();
	SDL_Surface* again_surface = TTF_RenderText_Solid(font,aga,color);
	SDL_Texture* again_tex = SDL_CreateTextureFromSurface(over_renderer, again_surface);
	SDL_FreeSurface(again_surface);
	SDL_RenderCopy(over_renderer, again_tex, NULL, &again_rect);

	SDL_RenderPresent(over_renderer);
}

void Game::handleEventsGameOver() {
	SDL_Event game_event;
	SDL_PollEvent(&game_event);
	
	if(game_event.type == SDL_QUIT){
		is_game_active = false;
		is_game_over = false;
	}

	if(game_event.type == SDL_KEYDOWN){
		switch(game_event.key.keysym.sym){
			case SDLK_RETURN:
				is_game_over = false;
				is_titlescreen = false;
				is_game_running = true;
				break;
			case SDLK_ESCAPE:
				is_game_active = false;
				is_game_over = false;
				break;
		}
	}
}

