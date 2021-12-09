#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

const int TILE_WIDTH = 98;
const int TILE_HEIGHT = 98;
const int NUM_TILES_X = 16;
const int NUM_TILES_Y = 16;
const int TILE_SPRITES = 54;
class Map {

public:
	Map();
	~Map();

	void map_init(const char* graphic, SDL_Renderer* ren);
	void map_update();
	void map_render(SDL_Renderer* ren);
	void map_quit();
	SDL_Rect map_rect;

	struct Tile {
		SDL_Texture* tile_tex;
		SDL_Rect src_rect;
		SDL_Rect dest_rect;
		int tileNum;
	};
	Tile map[NUM_TILES_X][NUM_TILES_Y];
	int tilemap[NUM_TILES_X][NUM_TILES_Y];
	SDL_Surface* tilesheet_surface;

private:

};

#endif