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
  body = {seg->getX(),seg->getY(),35,35};
  SDL_RenderFillRect(renderer, &body);
  SDL_RenderDrawRect(renderer, &body); // Dessine la tête du serpent
  seg = seg->next;
  
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
  direction();
  turn();
  movement();
}



// FONCTION GRANDISSEMENT DU SERPENT

void Snake::grow()
{
  int x = head->getX();
  int y = head->getY();
  Segment *newSegment = new Segment(x, y, dir);

  if ( keystates[SDL_SCANCODE_SPACE] ) {
    if(head == NULL){
      std::cout << "head null";
      head = newSegment;
      return;
    }
    
    newSegment->setX(x);
    newSegment->setY(y);
    newSegment->setDir(head->getDir());
    newSegment->next = head;
    head = newSegment;
  }
}

// FONCTION QUI BOUGE LE SERPENT

void Snake::movement()
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

void Snake::addBack(){
  Segment *seg = head;

  while (seg->next != NULL)
  {
    seg = seg->next;
  }

  int x = seg->getX();
  int y = seg->getY();

  switch (seg->getDir())
  {
  case UP:
      y += MOVE;
      break;
  case DOWN:
      y -= MOVE;
      break;
  case RIGHT:
      x -= MOVE;
      break;
  case LEFT:
      x += MOVE;
      break;
  default:
    break;
  }
  Segment *newSegment  = new Segment(x, y, seg->getDir());
  newSegment->setX(x);
  newSegment->setY(y);
  newSegment->setDir(head->getDir());
  seg->next = newSegment;
}




void Snake::turn()
{
  head->setDir(dir);
}


// FONCTION COLLISION DU SERPENT

bool Snake::coll()
{
  if( head->getY() > 720 || head->getY() < 0 || head->getX() > 1080 || head->getX() < 0  ) {
    return true;
  }
  else {
    return false;
  }
}
