#include "Screen.h"

const int width = 640;
const int height = 640;

int main(int argc, char **argv)
{

    Screen s;
    Screen *ptr = &s;

    InitScreen(ptr, width, height);

    Polygon p;
    Polygon *ptr2 = &p;

    InitPolygon(ptr2);

    SDL_FPoint p1[] = {

        {100.0, 100.0},
        {200.0, 100.0},

    };

    SDL_FPoint p2[] = {

        {200.0, 200.0},
        {100.0, 200.0}

    };

    Pairs c[] = {

        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},

    };

    addPoints(ptr2, p1, sizeof(p1) / sizeof(SDL_FPoint));

    addPoints(ptr2, p2, sizeof(p2) / sizeof(SDL_FPoint));

    CalculateCentroid(ptr2);

    addlines(ptr2, c, sizeof(c) / sizeof(Pairs));

    drawLines(ptr, ptr2);

    // Quit on X pressed
    while (1)
    {

        rotatePoints(0.001, ptr2);

        drawLines(ptr, ptr2);

        SDL_Delay(50);

        while (SDL_PollEvent(&s.event))
        {

            switch (s.event.type)
            {

            case SDL_QUIT:
                goto end;
            }
        }
    }

end:

    ClearPolygon(ptr2);
    CloseScreen();

    return 0;
}
