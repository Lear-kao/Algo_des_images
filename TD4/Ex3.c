#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
Q-3.1:
Créer une fonction pgm_t *thresholding(pgm_t *image, int threshold) qui effectue
le seuillage de l’image pgm image par la valeur threshold.
*/
pgm *thresholding(pgm *image, int threshold)
{
    pgm *temp = empty_image(image->height,image->width, image->max_value);
    for( int i =0; i < image->height; i++)
    {
        for ( int j = 0; j < image->width; j++)
        {
            if ( temp->pixel[i][j] < threshold ) temp->pixel[i][j] = 255;
            else temp->pixel[i][j] = 0;
        }
    }
    return temp;
}

/* 
Q-3.2:
Créer une fonction pgm_t *local_maxima(picture *image) qui prend en paramètre une
image pgm et qui renvoie une nouvelle image res de même type et de même taille que image.
*/
pgm *local_maxima(pgm *image)
{
    pgm *temp = empty_image(image->height,image->width, image->max_value);
    printf("%d-%d\n",temp->height,temp->width);
    for( int i =2; i < temp->height-2; i++)
    {
        for ( int j = 2; j < temp->width-2; j++)
        {
            
            for( int k = -1; k < 2; k++)
            {
                
                for( int l = -1; l < 2; l++)
                {
                    
                    if (image->pixel[i][j] < image->pixel[i+k][j+l]) temp->pixel[i][j] = 0;
                    else temp->pixel[i][j] = 255;
                }
            }
        }
    }
    
    return temp;
}

/* 
Q-3.3:
Créer une fonction pgm_t *pattern_matching(pgm_t *image, pgm_t *pattern) qui ren-
voie une copie de l’image pgm image dans laquelle le motif pattern est mis en évidence à
l’aide de la fonction highlight_rectangle.
*/
pgm *pattern_matching(ppm *image, ppm *pattern)
{
    pgm *ah = compute_NCC(image,pattern);
    printf("1\n");
    pgm *max_loc = local_maxima(ah);
    printf("2\n");
    pgm *tresh = thresholding(ah,200);
    printf("3\n");
    pgm *temp = pgm_alloc(image->height,image->width,image->max_value);
    for( int i =0; i < image->height; i++)
    {
        for ( int j = 0; j < image->width; j++)
        {
            if ( max_loc->pixel[i][j] == 255 && tresh->pixel[i][j] == 255) temp->pixel[i][j] = 255;
        }
    }
    printf("4\n");
    pgm_write_asc(temp,"non.pgm");
}