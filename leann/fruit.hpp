#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "snake.hpp"
#include "window.hpp"
#include "segment.hpp"
#include "playground.hpp"

        
class Fruit{
    public: 
        Fruit();
        ~Fruit();
        void fruit(SDL_Renderer* renderer);
        int getX();
        int getY();
        void eaten(Snake *snake);

    private:
        int xp;
        int yp;
};     
