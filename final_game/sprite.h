#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <iostream>
#include <string>

const int SPRITE_WIDTH = 60;
const int SPRITE_HEIGHT = 40;

class Sprite {
	public:
        	Sprite();
        	~Sprite();

	        void sprite_init(const char* graphic, SDL_Renderer* ren, int frames, int frame_duration, int start_width, int start_height);
		SDL_Rect sprite_update();
		void sprite_render(SDL_Renderer* ren);
		void sprite_quit();
		SDL_Rect frame_rect;
		int prevAnimation = 0;
		int animationIndex = 0;

	private:
	        SDL_Texture* sprite_graphic;
		int frame = 0;
		int frame_count = 6;
		int currentAnimationFrame = 0;
		int frame_duration = 100;
		SDL_Renderer* game_renderer;
};

#endif
