#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {

    size_t start;
    size_t end;

}Pairs;

typedef struct {

    SDL_Window *win;
    SDL_Renderer *rend;

    SDL_FPoint *points;
    size_t num_points;

    Pairs *connections;
    size_t num_connections;

    SDL_Event event;

}Screen;

void Init(Screen*,int,int);
void setPoints(SDL_FPoint*,size_t);
void drawPoints(SDL_Renderer*,SDL_FPoint*,size_t);
void drawLines(SDL_Renderer*,SDL_FPoint*,size_t,size_t);
void Close(Screen *);


void Init(Screen *s,int width,int height) {


    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit(-1);
        }

    SDL_CreateWindowAndRenderer
        (width,height,0,&s->win,&s->rend);

    if(s->win == NULL || s->rend == NULL) {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit(-1);
        }

    s->num_points = 8;
    s->points = (SDL_FPoint*)calloc(s->num_points,sizeof(SDL_FPoint));

    if(s->points == NULL) {
        fprintf(stderr, "Can't allocate points");
        }

    for (size_t i=0;i<s->num_points;i++) {
        
            s->points[i].x = 1.0 + i*2;
            s->points[i].y = 1.0 + i*5;
        
        }

    s->num_connections = 8;
    s->connections = (Pairs*)calloc(s->num_connections,sizeof(Pairs));

    if(s->connections == NULL) {
        fprintf(stderr, "Can't allocate points");
        }

}

void drawPoints(SDL_Renderer *r,SDL_FPoint *p,size_t l) {

    SDL_SetRenderDrawColor(r,0,0,0,255);
    SDL_RenderClear(r);

    SDL_SetRenderDrawColor(r,255,255,255,255);

    for (size_t i=0;i<l;i++) {
        
            SDL_RenderDrawPointF(r,p[i].x,p[i].y);
        
        }

    SDL_RenderPresent(r);

}

void drawLines(SDL_Renderer *r,SDL_FPoint *p,size_t l,size_t c) {

}

void Close(Screen *s) {

    free(s->points);
    free(s->connections);
    SDL_Quit();

}

