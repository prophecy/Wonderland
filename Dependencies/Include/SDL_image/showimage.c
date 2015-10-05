#include "SDL.h"
#include "SDL_image.h"

#define bool	char
#define true	1
#define false	0

int main(int argc, char ** argv)
{
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
	int imgInitCode	= IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    //SDL_Surface * image = SDL_LoadBMP("enemy.bmp");
	SDL_Surface * image = IMG_Load("enemy.bmp");
	//SDL_Surface * image = IMG_Load("nice.jpg");
    //SDL_Surface * image = IMG_Load("taylor.jpg");
	//SDL_Surface * image = IMG_Load("sprite.png");

	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,
        image);

    while (!quit)
    {
       SDL_WaitEvent(&event);

       switch(event.type)
       {
       case SDL_QUIT:
           quit = true;
           break;
       }

       SDL_RenderCopy(renderer, texture, NULL, NULL);
       SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

	IMG_Quit();
    SDL_Quit();

    return 0;
}
