#include "Screen.h"

const int width = 640;
const int height = 640;

int main(int argc, char ** argv)
{

    Screen s;
    Screen *ptr = &s;

    Init(ptr,width,height);

    SDL_FPoint p[] = {

                {100.0,100.0},
                {200.0,100.0},
                {200.0,200.0},
                {100.0,200.0}
    };

    SDL_FPoint p2[] = {

                {150.0,150.0},
                {250.0,150.0},
                {250.0,250.0},
                {150.0,250.0}

    };

    Pairs c[] = {

                {0,1},
                {1,2},
                {2,3},
                {3,0},

                {4,5},
                {5,6},
                {6,7},
                {7,4},

                {4,0},
                {5,1},
                {6,2},
                {7,3}

    };

    addPoints(ptr,p,sizeof(p)/sizeof(SDL_FPoint));

    addPoints(ptr,p2,sizeof(p2)/sizeof(SDL_FPoint));

    addConnections(ptr,c,sizeof(c)/sizeof(Pairs));

    drawLines(ptr);

    //Quit on X pressed
    while (1)
    {
 
        drawLines(ptr);

        rotate(0.1,ptr);

        SDL_Delay(50);

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
