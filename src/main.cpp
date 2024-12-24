#include <iostream>
#include <SDL2/SDL.h>

#include "game.h"
#include "data.h"

const Uint8 BACKGROUND_COLOR[] =  {0, 0, 0, 0};





bool isOpen = true;


int main(){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window;
    SDL_Renderer *renderer;

    int error = SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    if(error != 0){
        std::cout << error;
    }


    start();

    SDL_Event e;
    while(isOpen){
        SDL_Delay(200);
        //Handle events on queue
        while( SDL_PollEvent(&e) != 0 ){
            if(e.type == SDL_QUIT ) {
                isOpen = false;
            }
            input(e);
        }
        update(&isOpen);

        //Clear screen
        SDL_RenderClear(renderer);

        render(renderer);

        SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], BACKGROUND_COLOR[3]);
        //Update screen
        SDL_RenderPresent(renderer);

    }
    SDL_Quit();
    return 0;
}


//build command: g++ src/main.cpp src/game.cpp -Iinclude -Llib -lSDL2 -o builds/program