#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <string>

Sprite::Sprite() {

}

Sprite::~Sprite() {
	SDL_DestroyRenderer(game_renderer);
	SDL_DestroyWindow(my_window);

	IMG_Quit();
	SDL_Quit();
}


void Sprite::sprite_init(const char* graphic, SDL_Renderer* ren, int frames, int frame_duration, int start_width, int start_height) {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << std::endl;
	}

	IMG_Init(IMG_INIT_PNG);

	game_renderer = SDL_CreateRenderer(my_window, -1, 0);
	
	SDL_Surface* temp = IMG_Load(graphic);
	sprite_graphic = SDL_CreateTextureFromSurface(game_renderer, temp);
	SDL_FreeSurface(temp);

	frame_rect.w = 72;
	frame_rect.h = 72;
	frame_rect.x = 0;
	frame_rect.y = 0;

	sprite_render(game_renderer);
}

SDL_Rect Sprite::sprite_update() {
	// 0 = IDLE
	// 3 = WALK RIGHT
	// 4 = WALK LEFT
	// 2 = WALK TOWARD
	// 1 = WALK AWAY
	// 5 = JUMP RIGHT
	// 6 = JUMP LEFT

	int frame_time = (int) (SDL_GetTicks() / frame_duration) % frame_count;
	//std::cout << "Frame: " << frame_time << std::endl;
	
	static int last_frame_time = 0;
	if(last_frame_time != frame_time){
		if(frame_time<1){
			frame_rect.x = 0;
		}
		if(currentAnimationFrame == frame_count-1){
			animationIndex = 0;
			currentAnimationFrame = 0;
		}
		else {
			switch(animationIndex) {
				case 0:
					break;
		
				case 1:
					frame_rect.y = 3*frame_rect.h;
					frame_rect.x += frame_rect.w;
					currentAnimationFrame++;
					prevAnimation = 3;
					break;		

				case 2:
					frame_rect.y = 2*frame_rect.h;
					frame_rect.x += frame_rect.w;
					currentAnimationFrame++;
					prevAnimation = 3;
					break;

				case 3:
					frame_rect.y = 0;
					frame_rect.x += frame_rect.w;
					currentAnimationFrame++;
					prevAnimation = 3;
					break;

				case 4:
					frame_rect.y = frame_rect.h;
					frame_rect.x += frame_rect.w;
					currentAnimationFrame++;
					prevAnimation = 4;
					break;
				case 5:
					frame_rect.y = 4*frame_rect.h;
					frame_rect.x += frame_rect.w;
					currentAnimationFrame++;
					prevAnimation = 3;
					break;
				case 6:
					frame_rect.y = 5*frame_rect.h;
					frame_rect.x += frame_rect.w;
					currentAnimationFrame++;
					prevAnimation = 4;
					break;
			}
		}
	}
	last_frame_time = frame_time;

	return(frame_rect);
}

void Sprite::sprite_render(SDL_Renderer* ren) {
	SDL_RenderCopy(ren, sprite_graphic, NULL, &frame_rect);
}

void Sprite::sprite_quit() {

}




