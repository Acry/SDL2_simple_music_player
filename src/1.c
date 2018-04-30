//BEGIN PROGRAM HEAD
//BEGIN DESCRIPTION
/* SDL2_simple_music_player:
 * Plays mp3-music
 * Left mouse button on button / or space switches play and pause.
 * Left mouse button on hold button or
 * backspace stops music (rewind to start).
 * 
 */
//END   DESCRIPTION

//BEGIN INCLUDES
//local headers
#include "helper.h"
//END   INCLUDES

//BEGIN CPP DEFINITIONS
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
int ww=300;
int wh=150;
Mix_Music *Music 	= NULL;
//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
SDL_bool PointInCircle(SDL_Point *, SDL_Rect *);
//END	FUNCTION PROTOTYPES

/* DEFINED PROGRESS GOALS
 * 
 * todo todo todo
 *
 */
//END 	PROGRAM HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

//BEGIN INIT
init();
Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
Music=Mix_LoadMUS("assets/snd/The.madpix.project_-_Wish_You_Were_Here.mp3");

SDL_Surface *tempSurface = NULL;
tempSurface=IMG_Load("assets/gfx/buttons.png");

SDL_Texture *Texture	 = NULL;
Texture = SDL_CreateTextureFromSurface( Renderer, tempSurface );
// int w,h;
// SDL_QueryTexture(Texture, NULL, NULL, &w, &h);
// SDL_Log("w: %d h: %d", w,h);
SDL_Rect src_rect_pause		= {  0,  0, 50,  50};
SDL_Rect src_rect_halt		= { 60,  0, 50,  50};
SDL_Rect src_rect_play 		= {120,  0, 50,  50};

SDL_Rect src_rect;
src_rect=src_rect_play;

SDL_FreeSurface(tempSurface);

SDL_Point mouse_coords;
SDL_Rect  dst_rect_play_pause 	= {50,  20, 50,50};
SDL_Rect  dst_rect_halt 	= {50,  80, 50,50};

SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,ww,wh);
SDL_SetWindowTitle(Window, "Simple Music Player");
SDL_ShowWindow(Window);
SDL_Event event;
int running = 1;
//END   INIT

//BEGIN Event Loop
while(running){
//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		SDL_GetMouseState(&mouse_coords.x,&mouse_coords.y);
		if(event.type == SDL_QUIT){
			running = 0;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_LEFT && PointInCircle(&mouse_coords,&dst_rect_play_pause)){
				if(!Mix_PlayingMusic()){
					Mix_PlayMusic(Music, -1);
					src_rect=src_rect_pause;
				}
				else{
					if(Mix_PausedMusic()){
						Mix_ResumeMusic();
						src_rect=src_rect_pause;
					}
					else{
						Mix_PauseMusic();
						src_rect=src_rect_play;
					}
				}
			}
			
			if(event.button.button == SDL_BUTTON_LEFT && PointInCircle(&mouse_coords,&dst_rect_halt)){
					Mix_HaltMusic();
				src_rect=src_rect_play;
			}
		}
		if(event.type == SDL_KEYDOWN )
		{
			switch(event.key.keysym.sym ){
				case SDLK_ESCAPE:
					running = 0;
					break;
					
				case SDLK_BACKSPACE:
						Mix_HaltMusic();
					src_rect=src_rect_play;
					break;
					
				case SDLK_SPACE:
					if(!Mix_PlayingMusic()){
						Mix_PlayMusic(Music, -1);
						src_rect=src_rect_pause;
					}
					else{
						if(Mix_PausedMusic()){
							Mix_ResumeMusic();
							src_rect=src_rect_pause;
						}
						else{
							Mix_PauseMusic();
							src_rect=src_rect_play;
						}
					}
					break;
					
				default:
					break;
			}
		}
	}
//END   EVENT LOOP

//BEGIN RENDERING
SDL_Delay(66);//~15fps
SDL_SetRenderDrawColor(Renderer, 111, 111, 111, 255);
SDL_RenderClear(Renderer);
SDL_RenderCopy(Renderer, Texture, &src_rect, &dst_rect_play_pause);
SDL_RenderCopy(Renderer, Texture, &src_rect_halt, &dst_rect_halt);

SDL_RenderPresent(Renderer);
//END   RENDERING

}
//END   Event Loop
SDL_DestroyTexture(Texture);
Mix_FreeMusic(Music);
Mix_CloseAudio();
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
SDL_bool PointInCircle(SDL_Point *point, SDL_Rect *square)
{
	float x=square->x+square->w/2;
	float y=square->y+square->h/2;;
	float r=square->h/2;
	
	float dx=x-point->x;
	float dy=y-point->y;
	
	float distance=sqrtf(dx * dx + dy * dy);
	
	if (distance < r + 1)
		return SDL_TRUE;
	return SDL_FALSE;
}
//END   FUNCTIONS
