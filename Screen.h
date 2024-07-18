#include <SDL2/SDL.h>
#include <math.h>
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
bool addConnections(Screen*,Pairs*,size_t);

//Draw functions
void clear(Screen*);

void drawPoints(Screen*);
void drawLines(Screen*);

void rotate(float,Screen*);


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

        //Add values at the end of the list
        size_t j = 0;

        for(i = screen->num_points; i < (screen->num_points + num_points); i++){

            screen->points[i].x = points[j].x;
            screen->points[i].y = points[j].y;

            j++;

        }
         
    //Set new number of points
    screen->num_points += num_points;

    return true;

    }

}

bool addConnections(Screen *screen,Pairs *connections,size_t num_conn) {

    //If there are no connections to add
    if(connections == NULL){
        fprintf(stderr, "No connections to add");
        return false;
    }

    size_t i;

    //If there are no connections
    if(screen->connections == NULL){

        //Allocate memory to save the connections
        screen->connections = (Pairs*)calloc(num_conn,sizeof(Pairs));

        //Catch error
        if(screen->connections == NULL){
            fprintf(stderr, "Can't allocate memory");
            return false;
        }

        //Set values
        for (i=0; i < num_conn; i++) {
            screen->connections[i].start = connections[i].start;
            screen->connections[i].end = connections[i].end;
        }

        //Set number of connections
        screen->num_connections = num_conn;

        return true;


    }

    //If there are already values
    else {
        
        Pairs *temp;

        temp = screen->connections;

        //Expand memory allocated if possible
        screen->connections = (Pairs*)realloc(screen->connections,sizeof(Pairs)*(screen->num_connections+num_conn));

        //If not abort and rollback
        if(temp == NULL){
            fprintf(stderr, "Can't add elements");
            screen->connections = temp;
            return false;
        }

        screen->connections = temp;

        //Add values at the end of the list
        size_t j = 0;

        for(i = screen->num_connections; i < (screen->num_connections + num_conn); i++){

            screen->connections[i].start = connections[j].start;
            screen->connections[i].end = connections[j].end;

            j++;

        }
         
    //Set new number of connections
    screen->num_connections += num_conn;

    return true;

    }
}

/// @brief Clear the screen
/// @param screen The screen to clear
void clear(Screen *screen) {

    SDL_SetRenderDrawColor(screen->renderer,0,0,0,255);
    SDL_RenderClear(screen->renderer);

}

/// @brief Draw all the points saved in the screen
/// @param screen The screen whose points must be drawn
void drawPoints(Screen *screen) {

    clear(screen);

    SDL_SetRenderDrawColor(screen->renderer,255,255,255,255);

    for (size_t i=0;i<screen->num_points;i++) {
        
            SDL_RenderDrawPointF(screen->renderer,screen->points[i].x,screen->points[i].y);
        
        }

    SDL_RenderPresent(screen->renderer);

}

/// @brief Draw the lines between the points in connections
/// @param screen The screen to draw to
void drawLines(Screen *screen) {

    clear(screen);

    SDL_SetRenderDrawColor(screen->renderer,255,255,255,255);

    int a,b;

    for (size_t i=0;i<screen->num_connections;i++) {
        
            a = screen->connections[i].start;
            b = screen->connections[i].end;

            SDL_RenderDrawLineF(screen->renderer,screen->points[a].x,screen->points[a].y,screen->points[b].x,screen->points[b].y);

        }

    SDL_RenderPresent(screen->renderer);

}

/// @brief Used to rotate points
/// @param x The velocity on x axys
/// @param y The velocity on y axys
/// @param screen The screen containing the points
void rotate(float x,Screen *screen) {

    for (size_t i = 0; i < screen->num_points; i++)
    {
        screen->points[i].x = cos(x) * screen->points[i].x - sin(x) * screen->points[i].y;

        screen->points[i].y = cos(x) * screen->points[i].y + sin(x) * screen->points[i].x;
    }

    

}

/// @brief Close the library and free the memory occupied by the screen
/// @param s The screen to close
void Close(Screen *screen) {

    if(screen->points != NULL){free(screen->points);}
    if(screen->connections != NULL){free(screen->connections);}
    SDL_Quit();

}

