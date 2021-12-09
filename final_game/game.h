#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <iostream>
#include <string>

#include "gameObject.h"
#include "sprite.h"
#include "map.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


Sprite* my_sprite;

class Game {
public:
	Game();
	~Game();

	void init(int numCoins);
	void handleEvents();
	void update();
	void render();
	void quit();
	void handleEventsTitle();
	void handleEventsGameOver();
	void initTitle(SDL_Window* title_window, SDL_Renderer* title_renderer);
	void updateTitle(SDL_Window* title_window, SDL_Renderer* title_renderer);
	void initGameOver(SDL_Window* over_window, SDL_Renderer* over_renderer);
	void updateGameOver(SDL_Window* over_window, SDL_Renderer* over_renderer);

	bool is_game_active = true;
	bool is_titlescreen;
	bool is_game_running;
	bool is_game_over;

	//EVENT FLAGS
	bool MOVE_LEFT;
	bool MOVE_RIGHT;
	bool MOVE_TOWARD;
	bool MOVE_AWAY;
	bool JUMP_LEFT;
	bool JUMP_RIGHT;

	TTF_Font* font;
	GameObject* my_game;
	int final_time;
	int numCoins;

private:
	SDL_Window* game_window;
	SDL_Event game_event;
	SDL_Renderer* game_renderer;

	
};

#endif
