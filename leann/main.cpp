#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "window.hpp"
#include "snake.hpp"
#include "segment.hpp"
#include "playground.hpp"


#define RIGHT 4
  
int main(void) 
{
    MainWindow window;
    Uint32 frame_rate, frame_time, frame_delay = 20;
    Playground *fruit;
    window.init("Snake", 1080, 720); // Creation de la fenetre 
    
    SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255); // Donne la couleur du rectangle
    Snake *snake = new Snake(3, RIGHT);  //new Snake(3, RIGHT)
    
    while(window.running() == true ){
        frame_rate = SDL_GetTicks();
        snake->direction();
        snake->move();

        //snake->grow();

        // CREATION DE LA HEAD
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255); // Donne la couleur du render
        SDL_RenderClear(window.getRenderer());
        SDL_SetRenderDrawColor(window.getRenderer(), 255, 0, 0, 255); // Donne la couleur du rectangle

        snake->create(window.getRenderer());    
        //SDL_RenderPresent(window.getRenderer());

        // CREATION DU FRUIT
        fruit->Fruit(window.getRenderer());
        SDL_RenderPresent(window.getRenderer());

        
        SDL_RenderPresent(window.getRenderer());

        SDL_Event event;
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT ){
                window.clean();
                break;
            }
        }
        frame_time = SDL_GetTicks() - frame_rate;
        if(frame_time < frame_delay){
            SDL_Delay( frame_delay - frame_time );
        }
    }

    return 0;
}