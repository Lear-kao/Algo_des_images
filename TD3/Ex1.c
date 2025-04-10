#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
Q-1.1:
Créer une fonction unsigned char max_pgm(pgm_t *image) qui renvoie la valeur maximale
des pixels de l’image image passée en paramètre.
*/
unsigned char max_pgm(pgm *image)
{
    unsigned char v_max = image->pixel[0][0];
    for  (int i = 0; i < image->height; i++){
        for (int j = 0; j < image->width; j++)
        {
            if( v_max < image->pixel[i][j] )v_max = image->pixel[i][j];
        }
    }
    return v_max;
}

/* 
Q-1.2:
Créer des fonctions pgm_t *naive_x(pgm_t *image) et pgm_t *naive_y(pgm_t *image)
qui renvoient l’image correspondant respectivement au détecteur de contours horizontaux et verti-
caux.
*/
pgm *naive_x(pgm *image)
{
    pgm *temp = pgm_alloc(image->height, image->width,image->max_value);
    char t = max_pgm(image);
    int mod;
    for( int i = 1; i < image->height; i++)
    {
        for( int j = 1;  j < image->width; j++)
        {
            mod = image->pixel[i][j] - image->pixel[i][j-1];
            if (mod < 0) mod = 0;
            temp->pixel[i][j] = mod;
        }
    }
    pgm_write_asc(temp,"T_T.pgm");
    return temp;
}

pgm *naive_y(pgm *image)
{
    pgm *temp = pgm_alloc(image->height, image->width,image->max_value);
    char t = max_pgm(image);
    int mod;
    for( int i = 1; i < image->height; i++)
    {
        for( int j = 1;  j < image->width; j++)
        {
            mod = image->pixel[i][j] - image->pixel[i-1][j];
            if (mod < 0) mod = 0;
            temp->pixel[i][j] = mod;
        }
    }
    pgm_write_asc(temp,"^_^.pgm");
    return temp;
}

/* 
Q-1.3:
Créer une fonction pgm_t *naive_edge_detector(pgm_t *image) permettant d’implanter le
détecteur de contours naïf.
*/
pgm *naive_edge_detector(pgm *image)
{
    pgm *temp = pgm_alloc(image->height, image->width,image->max_value);
    char t = max_pgm(image);
    int mod;
    for( int i = 1; i < image->height; i++)
    {
        for( int j = 1;  j < image->width; j++)
        {
            mod = image->pixel[i][j] - image->pixel[i-1][j];
            if (mod < 0) mod = 0;
            if (mod >= 8 ) mod = 255;
            temp->pixel[i][j] = mod;
        }
    }
    for( int i = 1; i < image->height; i++)
    {
        for( int j = 1;  j < image->width; j++)
        {
            mod = image->pixel[i][j] - image->pixel[i][j-1];
            if (mod < 0) mod = 0;
            if (mod > 8 ) mod = 255;
            temp->pixel[i][j] = mod;
        }
    }
    pgm_write_asc(temp,"aled.pgm");
    return temp;
}


/* 
Q-1.4:
    En suivant le même raisonnement créer des fonctions pgm_t *sobel_edge_detector(pgm_t
*image) implantant le filtre de Sobel.
*/
int sobel_x(pgm *image, int x, int y)
{
    int tab_sob_x[3][3] = 
    {
        {-1, 0, 1},
        { -2, 0, 2},
        { -1, 0, 1}
    };
    int mod = 0;
    for( int i = -1; i < 2; i++)
    {
        for( int j = -1; j < 2; j++)
        {
            mod  += tab_sob_x[i+1][j+1] * image->pixel[i+x][j+y];
        }
    }
    if ( mod < 0 ) mod = 0;
    if ( mod > 255 ) mod = 255;
    return mod;
}

int sobel_y(pgm *image, int x, int y)
{
    int tab_sob_y[3][3] = 
    {
        {-1, -2, -1},
        { 0, 0, 0},
        { 1, 2, 1}
    };
    int mod = 0;
    for( int i = -1; i < 2; i++)
    {
        for( int j = -1; j < 2; j++)
        {
            mod  += tab_sob_y[i+1][j+1] * image->pixel[i+x][j+y];
        }
    }
    if ( mod < 0 ) mod = 0;
    if ( mod > 255 ) mod = 255;
    return mod;
}

/*


*/
pgm *sobel_edge_detector(pgm *image)
{
    pgm *temp = pgm_alloc(image->height, image->width,image->max_value);
    char t = max_pgm(image);
    int mod;
    for( int i = 1; i < image->height-2; i++)
    {
        for( int j = 1;  j < image->width-2; j++)
        {
            int Gx = sobel_x(image,i,j);
            int Gy = sobel_y(image,i,j);
            mod = sqrt(Gx*Gx + Gy*Gy);
            if ( mod < 0 ) mod = 0;
            if ( mod > 255 ) mod = 255;
            temp->pixel[i][j] = mod;
        }  
    }
    pgm_write_asc(temp,"0_0.pgm");
    return temp;
}

