#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
Q-1.1:
Créer une fonction pgm_t *empty_image(int value_max, int height, int width) qui
crée une image de type pgm_t de taille height × width dont la valeur des pixels peut être au
maximum égale à value_max. On mettra la valeur de tous les pixels à 0.
*/
pgm *empty_image(int value_max, int height, int width)
{
    pgm *image = (pgm*)malloc(sizeof(pgm));
    image->height = height;
    image->width  = width;
    image->max_value = value_max;
    image->pixel = malloc(sizeof(unsigned char*)*height);
    for(int i = 0; i < height; i++)
    {
        image->pixel[i] = malloc(sizeof(unsigned char)*width);
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image->pixel[i][j] = 0;
        }
    }
    return image;
}

ppm* empty_ppm(int  height, int width, int max_value)
{
    ppm *image = (ppm*)malloc(sizeof(ppm));
    image->height = height;
    image->width  = width;
    image->max_value = max_value;
    image->pixel =(rgb**)malloc(sizeof(rgb*)*height);
    for(int i = 0; i < height; i++)
    {
        image->pixel[i] =(rgb*)malloc(sizeof(rgb)*width);
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image->pixel[i][j].r = 0;
            image->pixel[i][j].g = 0;
            image->pixel[i][j].b = 0;
        }
    }
    return image;
}

/* 
Q-1.2:
Créer les fonctions void highlight_rectangle_pgm(pgm_t *image, int x, int y, int
height, int width) et void highlight_rectangle_ppm(ppm_t *image, int x, int
y, int height, int width) qui mettent en évidence un rectangle de taille height × width
dont le coin supérieur gauche est situé sur le pixel d’indice (𝑥, 𝑦). La fonction assombrira tous
les pixels qui ne sont pas dans le rectangle en divisant leur valeur par trois. La valeur des pixels
à l’intérieur du rectangle restera inchangée.
*/
void highlight_rectangle_pgm(pgm *image, int x, int y, int height, int width)
{
    for( int i = 0; i < image->height; i++)
    {
        for( int j = 0; j < image->width; j++)
        {
            if( i < x || j < y || i > x+height || j > y+width )
            {
                image->pixel[i][j] /= 3;
            }
        }
    }
}

void highlight_rectangle_ppm(ppm *image, int x, int y, int height, int width)
{
    for( int i = 0; i < image->height; i++)
    {
        for( int j = 0; j < image->width; j++)
        {
            if( i < x || j < y || i > x+height || j > y+width )
            {
                image->pixel[i][j].r /= 3;
                image->pixel[i][j].g /= 3;
                image->pixel[i][j].b /= 3;
            }
        }
    }
}