#include "Screen.h"

const int width = 640;
const int height = 640;



int main(int argc, char ** argv)
{

    Screen s;

    Init(&s,width,height);

    drawPoints(s.rend,s.points,s.num_points);

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
