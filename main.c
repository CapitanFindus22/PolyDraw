#include "Screen.h"

const int width = 640;
const int height = 640;



int main(int argc, char ** argv)
{

    Screen s;
    Screen *ptr = &s;

    Init(ptr,width,height);

    SDL_FPoint p[] = {

                {10.0,60.0},
                {20.0,50.0},
                {30.0,40.0},
                {40.0,30.0},
                {50.0,20.0},
                {60.0,10.0}
    };

    SDL_FPoint p2[] = {

                {100.0,60.0},
                {200.0,50.0},
                {300.0,40.0},
                {400.0,30.0}

    };

    addPoints(ptr,p,sizeof(p)/sizeof(SDL_FPoint));

    addPoints(ptr,p2,sizeof(p2)/sizeof(SDL_FPoint));

    drawPoints(ptr);

    //Quit on X pressed
    while (1)
    {
 
        while (SDL_PollEvent(&s.event)) {

            switch(s.event.type) {

            case SDL_QUIT:
                goto end;

            }

        }

    }

    end:

    Close(&s);
 
    return 0;
}
