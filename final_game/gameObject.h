#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <cmath>
#include <stdio.h>
#include <string>
#include <vector>
#include "sprite.h"
#include "map.h"

class GameObject {

public:
	GameObject();
	~GameObject();

	void obj_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int numCoins);
	void obj_update();
	void obj_render();
	void obj_quit();

	int obj_get_x_pos();
	void obj_set_x_pos(int x);

	int obj_get_y_pos();
	void obj_set_y_pos(int y);
	Sprite* obj_sprite;
	Map* obj_map;

	struct Coin{
		SDL_Texture* coin_tex;
		SDL_Rect dest_rect;
		SDL_Rect src_rect;
		bool show;
	};
	std::vector<Coin> coins;
	SDL_Surface* score_surface;
	SDL_Surface* remaining_surface;
	SDL_Texture* score_tex;
	SDL_Texture* remaining_tex;
	TTF_Font* font;
	int coinsCollected = 0;
	int coinsLeft;
	int totalCoins;
	SDL_Surface* timer_surface;
	SDL_Texture* timer_tex;
	SDL_Rect timer_rect;
	SDL_Rect score_rect;
	SDL_Rect remaining_rect;
	int start;

private:
	SDL_Renderer* obj_renderer;
	SDL_Surface* coin_surface = NULL;
	SDL_Rect obj_rect;
	SDL_Surface *spritesheet;

};

#endif
