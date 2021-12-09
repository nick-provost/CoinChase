#include "map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <string>

Map::Map() {
}

Map::~Map() {
	SDL_DestroyWindow(my_window);

	IMG_Quit();
	SDL_Quit();
}

void Map::map_init(const char* graphic, SDL_Renderer* ren){

	int tilemap[16][16] = {
	{ 33,34,35,49,49,43,50,43,49,49,49,49,50,33,34,35 },
	{ 42,43,51,39,39,39,39,28,28,39,39,39,39,53,43,44 },
	{ 51,35,49,33,34,35,49,48,48,49,33,34,35,49,33,53 },
	{ 49,48,33,53,43,42,43,48,48,49,44,50,51,35,48,49 },
	{ 49,48,42,43,50,51,28,53,51,28,53,43,49,44,48,43 },
	{ 49,48,51,34,35,50,48,03,05,48,43,33,34,53,48,50 },
	{ 50,48,50,43,36,39,20,16,13,18,39,38,50,43,48,49 },
	{ 43,36,39,39,53,03,13,00,02,13,05,51,39,39,38,49 },
	{ 50,36,39,39,35,21,16,18,20,16,23,33,39,39,38,43 },
	{ 49,48,50,49,36,39,02,16,16,00,39,38,50,50,48,50 },
	{ 43,48,33,52,53,43,48,21,23,48,49,51,52,35,48,50 },
	{ 43,48,42,50,50,33,46,35,33,46,35,49,43,44,48,49 },
	{ 49,48,51,35,43,42,43,48,48,49,44,43,33,53,48,43 },
	{ 33,53,43,51,52,53,49,48,48,50,51,52,53,43,51,35 },
	{ 42,43,33,39,39,39,39,46,46,39,39,39,39,35,43,44 },
	{ 51,52,53,49,49,49,43,43,49,49,49,49,43,51,52,53 }
	};


	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << std::endl;
	}

	IMG_Init(IMG_INIT_PNG);

	tilesheet_surface = IMG_Load(graphic);

	for (int row = 0; row < NUM_TILES_X; row++ ) {
		for (int col = 0; col < NUM_TILES_Y; col++ ) {
			map[row][col].tileNum = tilemap[row][col];

			map[row][col].src_rect.x = TILE_WIDTH*((int) map[row][col].tileNum % 10);
			map[row][col].src_rect.y = TILE_HEIGHT*((int) map[row][col].tileNum / 10);
			map[row][col].src_rect.w = TILE_WIDTH;
			map[row][col].src_rect.h = TILE_HEIGHT;

			map[row][col].dest_rect.x = TILE_WIDTH*col;
			map[row][col].dest_rect.y = TILE_HEIGHT*row;
			map[row][col].dest_rect.w = TILE_WIDTH;
			map[row][col].dest_rect.h = TILE_HEIGHT;
		}
	}
}

void Map::map_update(){
	
	for (int row = 0; row < NUM_TILES_X; row++ ) {
		for (int col = 0; col < NUM_TILES_Y; col++ ) {
			map[row][col].dest_rect.x = (col*TILE_WIDTH)+(x_pos-466);
			map[row][col].dest_rect.y = (row*TILE_HEIGHT)+(y_pos-520);
		}
	}
}

void Map::map_render(SDL_Renderer* ren){

}

void Map::map_quit(){

}