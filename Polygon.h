#include <SDL2/SDL.h>
#include <stdbool.h>
#include <malloc.h>

#define PI 3.14159265359;

/// @brief A pair of numbers
typedef struct
{

    size_t start;
    size_t end;

} Pairs;

/// @brief A polygon
typedef struct
{

    SDL_FPoint *points;
    size_t num_points;

    Pairs *lines;
    size_t num_lines;

    SDL_FPoint centroid;

} Polygon;

void InitPolygon(Polygon *);
void ClearPolygon(Polygon *);

bool addPoints(Polygon *, SDL_FPoint *, size_t);
bool addConnections(Polygon *, Pairs *, size_t);

void CalculateCentroid(Polygon *);
void rotatePoints(float, Polygon *);

/// @brief Set the start values for the variables of the polygon
/// @param polygon The polygon itself
inline void InitPolygon(Polygon *polygon)
{
    polygon->lines = NULL;
    polygon->points = NULL;
    polygon->num_lines = 0;
    polygon->num_points = 0;
    polygon->centroid.x = 0;
    polygon->centroid.y = 0;
}

/// @brief Free the memory occupied by the polygon variables
/// @param polygon The polygon itself
inline void ClearPolygon(Polygon *polygon)
{
    if (polygon->lines != NULL)
    {
        free(polygon->lines);
    }

    if (polygon->points != NULL)
    {
        free(polygon->points);
    }
}

/// @brief Add points to the polygon
/// @param polygon The polygon where to add the points
/// @param points The points to add
/// @param num_points The number of points to add
/// @return Whether or not the points have been added
bool addPoints(Polygon *polygon, SDL_FPoint *points, size_t num_points)
{

    // If there are no points to add
    if (points == NULL || num_points <= 0)
    {
        fprintf(stderr, "No points to add");
        return false;
    }

    size_t i;

    // If there are no points in the struct
    if (polygon->points == NULL)
    {

        // Allocate memory to save the points
        polygon->points = (SDL_FPoint *)calloc(num_points, sizeof(SDL_FPoint));

        // Catch error
        if (polygon->points == NULL)
        {
            fprintf(stderr, "Can't allocate memory");
            return false;
        }

        // Set values
        for (i = 0; i < num_points; i++)
        {
            polygon->points[i].x = points[i].x;
            polygon->points[i].y = points[i].y;
        }

        // Set number of points
        polygon->num_points = num_points;

        return true;
    }

    // If there are already values
    else
    {

        SDL_FPoint *temp;

        temp = polygon->points;

        // Expand memory allocated if possible
        polygon->points = (SDL_FPoint *)realloc(polygon->points, sizeof(SDL_FPoint) * (polygon->num_points + num_points));

        // If not abort and rollback
        if (temp == NULL)
        {
            fprintf(stderr, "Can't add elements");
            polygon->points = temp;
            return false;
        }

        memcpy(polygon->points, temp, sizeof(SDL_FPoint) * polygon->num_points);

        // Add values at the end of the list
        size_t j = 0;

        for (i = polygon->num_points; i < (polygon->num_points + num_points); i++)
        {

            polygon->points[i].x = points[j].x;
            polygon->points[i].y = points[j].y;

            j++;
        }

        // Set new number of points
        polygon->num_points += num_points;

        return true;
    }
}

/// @brief Add lines to the polygon between the points
/// @param polygon The polygon where to add the lines
/// @param lines The lines to add
/// @param num_lines The number of lines to add
/// @return Whether or not the lines have been added
bool addlines(Polygon *polygon, Pairs *lines, size_t num_lines)
{

    // If there are no lines to add
    if (lines == NULL)
    {
        fprintf(stderr, "No lines to add");
        return false;
    }

    size_t i;

    // If there are no lines
    if (polygon->lines == NULL)
    {

        // Allocate memory to save the lines
        polygon->lines = (Pairs *)calloc(num_lines, sizeof(Pairs));

        // Catch error
        if (polygon->lines == NULL)
        {
            fprintf(stderr, "Can't allocate memory");
            return false;
        }

        // Set values
        for (i = 0; i < num_lines; i++)
        {
            polygon->lines[i].start = lines[i].start;
            polygon->lines[i].end = lines[i].end;
        }

        // Set number of lines
        polygon->num_lines = num_lines;

        return true;
    }

    // If there are already values
    else
    {

        Pairs *temp;

        temp = polygon->lines;

        // Expand memory allocated if possible
        polygon->lines = (Pairs *)realloc(polygon->lines, sizeof(Pairs) * (polygon->num_lines + num_lines));

        // If not abort and rollback
        if (temp == NULL)
        {
            fprintf(stderr, "Can't add elements");
            polygon->lines = temp;
            return false;
        }

        memcpy(polygon->lines, temp, sizeof(Pairs) * polygon->num_lines);

        // Add values at the end of the list
        size_t j = 0;

        for (i = polygon->num_lines; i < (polygon->num_lines + num_lines); i++)
        {

            polygon->lines[i].start = lines[j].start;
            polygon->lines[i].end = lines[j].end;

            j++;
        }

        // Set new number of lines
        polygon->num_lines += num_lines;

        return true;
    }
}

/// @brief Calculate the centroid of the polygon
/// @param polygon The polygon itself
void CalculateCentroid(Polygon *polygon)
{

    if (polygon->num_points <= 0)
    {
        return;
    }

    for (size_t i = 0; i < polygon->num_points; i++)
    {

        polygon->centroid.x += polygon->points[i].x;
        polygon->centroid.y += polygon->points[i].y;
    }

    polygon->centroid.x /= polygon->num_points;
    polygon->centroid.y /= polygon->num_points;
}

/// @brief Used to rotate points
/// @param angle The rotation angle
/// @param screen The screen containing the points
void rotatePoints(float angle, Polygon *polygon)
{

    angle = angle * 180 / PI;

    float oldx, oldy;

    for (size_t i = 0; i < polygon->num_points; i++)
    {
        oldx = polygon->points[i].x - polygon->centroid.x;
        oldy = polygon->points[i].y - polygon->centroid.y;

        polygon->points[i].x = (cos(angle) * oldx) - (sin(angle) * oldy) + polygon->centroid.x;
        polygon->points[i].y = (cos(angle) * oldy) + (sin(angle) * oldx) + polygon->centroid.y;
    }
}