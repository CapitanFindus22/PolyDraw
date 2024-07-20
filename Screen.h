#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "Polygon.h"

/// @brief Encapsulate a window
typedef struct
{

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

} Screen;

// Start and end functions
void InitScreen(Screen *, int, int);
void CloseScreen();

// Draw functions
void clear(Screen *);
void drawPoints(Screen *, Polygon *);
void drawLines(Screen *, Polygon *);

/// @brief Initialize the library and create the screen and the renderer
/// @param screen The screen to initialize
/// @param width The width of the screen to create
/// @param height The height of the screen to create
inline void InitScreen(Screen *screen, int width, int height)
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit(-1);
    }

    SDL_CreateWindowAndRenderer(width, height, 0, &screen->window, &screen->renderer);

    if (screen->window == NULL || screen->renderer == NULL)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit(-1);
    }
}

/// @brief Close the library
inline void CloseScreen()
{

    SDL_Quit();
}

/// @brief Clear the screen
/// @param screen The screen to clear
inline void clear(Screen *screen)
{

    SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 255);
    SDL_RenderClear(screen->renderer);
}

/// @brief Draw the points of the polygon
/// @param screen The screen where to draw the points
/// @param polygon The polygon whose points must be drawn
void drawPoints(Screen *screen, Polygon *polygon)
{

    clear(screen);

    SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 255);

    for (size_t i = 0; i < polygon->num_points; i++)
    {

        SDL_RenderDrawPointF(screen->renderer, polygon->points[i].x, polygon->points[i].y);
    }

    SDL_RenderPresent(screen->renderer);
}

/// @brief Draw the lines of the polygon
/// @param screen The screen where to draw the lines
/// @param polygon The polygon whose points must be drawn
void drawLines(Screen *screen, Polygon *polygon)
{

    clear(screen);

    SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 255);

    int a, b;

    for (size_t i = 0; i < polygon->num_lines; i++)
    {

        a = polygon->lines[i].start;
        b = polygon->lines[i].end;

        SDL_RenderDrawLineF(screen->renderer, polygon->points[a].x, polygon->points[a].y, polygon->points[b].x, polygon->points[b].y);
    }

    SDL_RenderPresent(screen->renderer);
}
