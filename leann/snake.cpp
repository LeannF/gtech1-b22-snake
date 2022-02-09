#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "snake.hpp"
#include "window.hpp"
#include "segment.hpp"
#include "playground.hpp"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define MOVE 7

SDL_Renderer* renderer;
const Uint8 *keystates = SDL_GetKeyboardState(NULL);


Snake::Snake(int length, int direction){
  this->head = new Segment(xpos, ypos, direction);

  for(int i=0; i<length; i++){
    int x = xpos;
    int y = ypos;
    switch (direction)
    {
      case 1:
      case 2:
        ypos += MOVE;
        break;
      case 3:
      case 4:
        xpos += MOVE;
        break;
      default:
        break;
    }   
  }
  this->dir = direction;
}

Snake::~Snake(){
  //if (this->head != NULL) delete this->head;
}

// FONCTION CREATION DU SERPENT

void Snake::create(SDL_Renderer* renderer)
{
  Segment *seg = this->head;

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 );
  SDL_Rect body;
  body = {seg->getX(),seg->getY(),45,45};
  SDL_RenderFillRect(renderer, &body);
  SDL_RenderDrawRect(renderer, &body); // Dessine la tête du serpent
  //seg = seg->next;
  
}


// FONCTION DIRECTION DU SERPENT

int Snake::direction()
{  
  if ( keystates[SDL_SCANCODE_UP] && this->dir != DOWN ) {
    this->dir = UP;
    ypos -= MOVE;
  }

  else if ( keystates[SDL_SCANCODE_DOWN] && this->dir != UP ) {
    this->dir = DOWN;
    ypos += MOVE;
  }
    
  else if ( keystates[SDL_SCANCODE_LEFT] && this->dir != RIGHT) {
    this->dir = LEFT;
    xpos -= MOVE;
  }
    
  else if ( keystates[SDL_SCANCODE_RIGHT] && this->dir != LEFT ) {
    this->dir = RIGHT;
    xpos += MOVE;
  }      
  return this->dir;  
}

Segment Snake::getHead(){
    return *head;
}

// FONCTION QUI BOUGE LE SERPENT

void Snake::move()
{
  turn();
  addHead();
}

// FONCTION QUI AJOUTE UN SEGMENT A LA TETE DU SERPENT

void Snake::addHead()
{
  int x = head->getX();
  int y = head->getY();

  if(head == NULL)
  {
    return;
  }

  switch (head->getDir())
  {
    case UP:
      y -= MOVE;
      break;

    case DOWN:
      y += MOVE;
      break;

    case LEFT:
      x -= MOVE;
      break;  
    
    case RIGHT:
      x += MOVE;
      break;

    default:
      break;
  }

  Segment *newSegment = new Segment(x, y, dir);
  newSegment->setX(x);
  newSegment->setY(y);
  newSegment->setDir(head->getDir());
  newSegment->next = head;
  head = newSegment;
  
}


// FONCTION QUI AJOUTE UN SEGMENT A LA QUEUE DU SERPENT QUAND IL MANGE UN FRUIT

void Snake::addBack(){}




void Snake::turn()
{
  head->setDir(dir);
}

// FONCTION GRANDISSEMENT DU SERPENT

/*void Snake::grow(){

  if ( keystates[SDL_SCANCODE_SPACE] ) {
    Segment *newSegment = new Segment(xpos, ypos);
  }
}*/



// FONCTION COLLISION DU SERPENT

bool Snake::coll()
{
  if( ypos > 720 || ypos < 0 || xpos > 1080 || xpos < 0  ) {
    return true;
  }
  else {
    return false;
  }
}
