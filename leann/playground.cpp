#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "snake.hpp"
#include "window.hpp"
#include "segment.hpp"
#include "playground.hpp"


Playground::Playground(){}

Playground::~Playground(){}

void Playground::Fruit(SDL_Renderer* renderer)
{
    int xp = 700;
    int yp = 300;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255 );
    SDL_Rect apple;
    apple = {xp, yp, 45, 45};
    SDL_RenderFillRect(renderer, &apple);
    SDL_RenderDrawRect(renderer, &apple); // Dessine la pomme
}  
