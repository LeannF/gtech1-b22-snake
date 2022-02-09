#pragma once


#include "segment.hpp"

class Snake{
    public:
        Snake(int length, int direction);
        ~Snake();
        void move();
        void create(SDL_Renderer* renderer);
        void grow();
        void movement();
        void addBack();
        void turn();
        int direction();
        Segment getHead();
        bool coll();
        bool eaten();

    private:
        Segment* head = NULL;
        int ypos = 300;
        int xpos = 300;
        int dir;
};