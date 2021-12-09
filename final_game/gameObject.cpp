#include "gameObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <string>
#include <stdlib.h> //for random coin locations
#include <time.h> // for random coin locations
#include <cmath>
#include <SDL_ttf.h>
#include <stdio.h>
#include <sstream>
#include <vector>

const int width = 640;
const int height = 480;
const int GAME_BOUND_LEFT_X = 0;
const int GAME_BOUND_RIGHT_X = 640;
const int GAME_BOUND_UPPER_Y = 0;
const int GAME_BOUND_LOWER_Y = 480;

int x_pos = 0, y_pos = 0, x_vel = 0, y_vel = 0;

SDL_Texture* my_texture = NULL;
SDL_Texture* bg_texture = NULL;
SDL_Texture* tileset_texture = NULL;
SDL_Renderer* my_renderer = NULL;
SDL_Window* my_window = NULL;
SDL_Event input;
SDL_Rect img;
SDL_Rect background;
bool game_is_running;

using std::string;

GameObject::GameObject() {}

GameObject::~GameObject() {
	SDL_DestroyRenderer(obj_renderer);
	SDL_DestroyWindow(my_window);

	IMG_Quit();
	SDL_Quit();
}

void GameObject::obj_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int numCoins) {
	coinsLeft = numCoins;
	totalCoins = numCoins;

	start = SDL_GetTicks();
	srand(time(NULL));
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}

	if(TTF_Init()==-1)
		std::cout << "TTF_Init: " << SDL_GetError() << std::endl;

	font = TTF_OpenFont("./font.ttf", 20);
	if(!font)
		std::cout << "TTF_OpenFont: " << SDL_GetError() << std::endl;

	IMG_Init(IMG_INIT_PNG);

	my_window = SDL_CreateWindow("Coin Chase", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	obj_renderer = SDL_CreateRenderer(my_window, -1, 0);
	
	SDL_Surface* temp = IMG_Load(graphic);
	my_texture = SDL_CreateTextureFromSurface(obj_renderer, temp);
	SDL_FreeSurface(temp);

	coin_surface = IMG_Load("./coin.png");
	SDL_Texture* coin_tex = SDL_CreateTextureFromSurface(obj_renderer, coin_surface);
	SDL_FreeSurface(coin_surface);
	for(int i=0;i<numCoins;i++){
		Coin temp_coin;
		temp_coin.coin_tex = coin_tex;
		temp_coin.dest_rect.x = rand()%(1054+414+1)-414;
		temp_coin.dest_rect.y = rand()%(974+494+1)-494;
		temp_coin.dest_rect.w = 64;
		temp_coin.dest_rect.h = 40;
		temp_coin.src_rect.x = temp_coin.dest_rect.x;
		temp_coin.src_rect.y = temp_coin.dest_rect.y;
		temp_coin.show = true;
		coins.emplace_back(temp_coin);

	}

	score_rect.x = 10;
	score_rect.y = 420;
	score_rect.w = 200;
	score_rect.h = 50;

	remaining_rect.x = 430;
	remaining_rect.y = 420;
	remaining_rect.w = 200;
	remaining_rect.h = 50;

	timer_rect.x = 295;
	timer_rect.y = 0;
	timer_rect.w = 40;
	timer_rect.h = 50;


	obj_rect.x = 0;
	obj_rect.y = 0;
	obj_rect.w = 90;
	obj_rect.h = 90;

	x_pos = 0;
	y_pos = 0;

	game_is_running = true;

	obj_sprite = new Sprite();
	obj_sprite->sprite_init(graphic, ren, 5, 100, 40, 40);
	SDL_RenderClear(obj_renderer);
	obj_map = new Map();
	obj_map->map_init("my_tileset.png", ren);

}

void GameObject::obj_update() {

	if (x_pos > 765) x_pos = 765;
	if (x_pos < -760) x_pos = -760;
	if (y_pos < -775) y_pos = -775;
	if (y_pos > 730) y_pos = 730;

	for(int i=0;i<totalCoins;i++){
		coins.at(i).dest_rect.x = coins.at(i).src_rect.x + x_pos;
		coins.at(i).dest_rect.y = coins.at(i).src_rect.y + y_pos;
		
		if( (-1*coins.at(i).src_rect.x+264 <= x_pos && x_pos <= -1*coins.at(i).src_rect.x+284+32) && (-1*coins.at(i).src_rect.y+184 <= y_pos && y_pos <= -1*coins.at(i).src_rect.y+204+20) && coins.at(i).show ){
			coins.at(i).show = false;
			coinsCollected++;
			coinsLeft--;
		}

	}


	img.x = 284;
	img.y = 204;
	img.w = 72;
	img.h = 72;

	obj_sprite->sprite_update();
	obj_map->map_update();
	obj_render();

}

void GameObject::obj_render() {

	SDL_RenderClear(obj_renderer);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(obj_renderer, obj_map->tilesheet_surface);
	for(int row=0; row<NUM_TILES_X; row++){
		for(int col=0; col<NUM_TILES_Y; col++){

			SDL_RenderCopy(obj_renderer, tex, &obj_map->map[row][col].src_rect, &obj_map->map[row][col].dest_rect);

		}
	}
	SDL_RenderCopy(obj_renderer, my_texture, &obj_sprite->frame_rect, &img);
	
	for(int i=0;i<totalCoins;i++){
		if (coins.at(i).show){
			SDL_RenderCopy(obj_renderer, coins.at(i).coin_tex, NULL, &coins.at(i).dest_rect);
		}
	}

	SDL_Color color={255,0,0};
	string score = "Coins Collected: " + std::to_string(coinsCollected);
	const char * c = score.c_str();
	score_surface=TTF_RenderText_Solid(font,c,color);
	score_tex = SDL_CreateTextureFromSurface(obj_renderer, score_surface);
	SDL_FreeSurface(score_surface);
	SDL_RenderCopy(obj_renderer, score_tex, NULL, &score_rect);

	string left = "Coins Remaining: " + std::to_string(coinsLeft);
	const char * d = left.c_str();
	remaining_surface=TTF_RenderText_Solid(font,d,color);
	remaining_tex = SDL_CreateTextureFromSurface(obj_renderer, remaining_surface);
	SDL_FreeSurface(remaining_surface);
	SDL_RenderCopy(obj_renderer, remaining_tex, NULL, &remaining_rect);

	std::stringstream time;
	time << (SDL_GetTicks()-start)/1000;
	timer_surface = TTF_RenderText_Solid(font,time.str().c_str(),color);
	timer_tex = SDL_CreateTextureFromSurface(obj_renderer, timer_surface);
	SDL_FreeSurface(timer_surface);
	SDL_RenderCopy(obj_renderer, timer_tex, NULL, &timer_rect);

	SDL_RenderPresent(obj_renderer);

	//std::cout << "x_pos: " << x_pos << std::endl;
	//std::cout << "y_pos:  " << y_pos << std::endl;


}

void GameObject::obj_quit() {}

void GameObject::obj_set_y_pos(int y) {
	y_pos = y;
}

void GameObject::obj_set_x_pos(int x) {
	x_pos = x;
}

int GameObject::obj_get_y_pos() {
	return y_pos;
}

int GameObject::obj_get_x_pos() {
	return x_pos;
}