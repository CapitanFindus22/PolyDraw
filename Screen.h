#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

/// @brief A pair of numbers
typedef struct {

    size_t start;
    size_t end;

}Pairs;
 
/// @brief Encapsulate a window 
typedef struct {

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_FPoint *points;
    size_t num_points;

    Pairs *connections;
    size_t num_connections;

    SDL_Event event;

}Screen;

//Start and end functions
void Init(Screen*,int,int);
void Close(Screen*);

//Setter functions
bool addPoints(Screen*,SDL_FPoint*,size_t);

/*
bool setConnections(Screen*,int*,size_t);
bool addConnections(Screen*,int*,size_t);
 */
//Draw functions
void drawPoints(Screen*);
void drawLines(SDL_Renderer*,SDL_FPoint*,size_t,size_t);



/// @brief Initializa the library and create the screen and the renderer
/// @param screen The screen to initialize
/// @param width The width of the screen to create
/// @param height The height of the screen to create
void Init(Screen *screen, int width, int height) {


    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit(-1);
        }

    SDL_CreateWindowAndRenderer
        (width,height,0,&screen->window,&screen->renderer);

    if(screen->window == NULL || screen->renderer == NULL) {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit(-1);
        }

    screen->points = NULL;
    screen->connections = NULL;

/*    
    screen->num_connections = 8;
    screen->connections = (Pairs*)calloc(screen->num_connections,sizeof(Pairs));

    if(screen->connections == NULL) {
        fprintf(stderr, "Can't allocate points");
        } */

}

/// @brief Add points to the screen list
/// @param screen The screen where to add the points
/// @param points The points to add
/// @param num_points The number of points to add
/// @return Whether or not the points have been added
bool addPoints(Screen *screen, SDL_FPoint *points, size_t num_points) {

    //If there are no points to add
    if(points == NULL){
        fprintf(stderr, "No points to add");
        return false;
    }

    size_t i;

    //If there are no points
    if(screen->points == NULL){

        //Allocate memory to save the points
        screen->points = (SDL_FPoint*)calloc(num_points,sizeof(SDL_FPoint));

        //Catch error
        if(screen->points == NULL){
            fprintf(stderr, "Can't allocate memory");
            return false;
        }

        //Set values
        for (i=0; i < num_points; i++) {
            screen->points[i].x = points[i].x;
            screen->points[i].y = points[i].y;
        }

        //Set number of points
        screen->num_points = num_points;

        return true;


    }

    //If there are already values
    else {
        
        SDL_FPoint *temp;

        temp = screen->points;

        //Expand memory allocated if possible
        screen->points = (SDL_FPoint*)realloc(screen->points,sizeof(SDL_FPoint)*(screen->num_points+num_points));

        //If not abort and rollback
        if(temp == NULL){
            fprintf(stderr, "Can't add elements");
            screen->points = temp;
            return false;
        }

        screen->points = temp;

        //Add values
        for(size_t j = 0, i = num_points; i < screen->num_points + num_points || j < num_points;i++,j++){

            screen->points[i].x = points[j].x;
            screen->points[i].y = points[j].y;

        }
         
    //Set new number of points
    screen->num_points += num_points;

    return true;

    }

}

/// @brief Draw all the points saved in the screen
/// @param screen The screen whose points must be drawn
void drawPoints(Screen *screen) {

    SDL_SetRenderDrawColor(screen->renderer,0,0,0,255);
    SDL_RenderClear(screen->renderer);

    SDL_SetRenderDrawColor(screen->renderer,255,255,255,255);

    for (size_t i=0;i<screen->num_points;i++) {
        
            SDL_RenderDrawPointF(screen->renderer,screen->points[i].x,screen->points[i].y);
        
        }

    SDL_RenderPresent(screen->renderer);

}

void drawLines(SDL_Renderer *renderer,SDL_FPoint *points,size_t l,size_t c) {

}

/// @brief Close the library and free the memory occupied by the screen
/// @param s The screen to close
void Close(Screen *screen) {

    if(screen->points != NULL){free(screen->points);}
    if(screen->connections != NULL){free(screen->connections);}
    SDL_Quit();

}

