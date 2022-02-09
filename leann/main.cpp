#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "window.hpp"
#include "snake.hpp"
#include "segment.hpp"
#include "playground.hpp"
#include "fruit.hpp"


#define RIGHT 4
  
int main(void) 
{
    MainWindow window;
    Uint32 frame_rate, frame_time, frame_delay = 20;
    Fruit *fruit;
    window.init("Snake", 1080, 720); // Creation de la fenetre 
    
    Snake *snake = new Snake(3, RIGHT);  
    
    while(window.running() == true ){
        frame_rate = SDL_GetTicks();
        snake->move();
        snake->addBack();
        snake->grow();
        fruit->eaten(snake);
        
        SDL_SetRenderDrawColor(window.getRenderer(), 46, 64, 83, 255); // Donne la couleur du render
        SDL_RenderClear(window.getRenderer());
        SDL_SetRenderDrawColor(window.getRenderer(), 255, 0, 0, 255); // Donne la couleur du rectangle

         

        // CREATION DU FRUIT
        fruit->fruit(window.getRenderer());

        snake->create(window.getRenderer());   
        SDL_RenderPresent(window.getRenderer());

        SDL_Event event;
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT || snake->coll() == true){
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