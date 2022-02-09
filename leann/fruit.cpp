#include "fruit.hpp"
#include "snake.hpp"
#include "window.hpp"
#include "segment.hpp"
#include "playground.hpp"

// FONCTION QUI CREE LA POMME
void Fruit::fruit(SDL_Renderer* renderer)
{
    int xp = 700;
    int yp = 300;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255 );
    SDL_Rect apple;
    apple = {xp, yp, 35, 35};
    SDL_RenderFillRect(renderer, &apple);
    SDL_RenderDrawRect(renderer, &apple); // Dessine la pomme
}  

 int Fruit::getX(){
     return xp;
 }

  int Fruit::getY(){
     return yp;
 }

void Fruit::eaten(Snake *snake){
    Segment seg = snake->getHead();

    while (seg.next == NULL)
    {
        if(seg.getX() == xp && seg.getY() == yp){
            this->xp = rand() % 1081;
            this->yp = rand() % 721; 
        }
    }
}