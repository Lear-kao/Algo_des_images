#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
Q-2.1:
Créer les fonctions double average_pixels_pgm(pgm_t *image) et double_rgb average_-
pixels_ppm(ppm_t *image) qui permettent de calculer la valeur moyenne des pixels de
l’image pgm ou ppm passée en paramètre.
*/
d_rgb *average_pixels_ppm(ppm *image)
{
    double d_sum_r = 0,d_sum_g = 0,d_sum_b = 0;
    for( int i = 0; i < image->height; i++)
    {
        for( int j = 0; j < image->width; j++)
        {
            d_sum_r += image->pixel[i][j].r;
            d_sum_g += image->pixel[i][j].g;
            d_sum_b += image->pixel[i][j].b;
        }
    }
    d_rgb *moy_rgb = malloc(sizeof(d_rgb));
    moy_rgb->r = d_sum_r/(image->height * image->width); 
    moy_rgb->g = d_sum_g/(image->height * image->width); 
    moy_rgb->b = d_sum_b/(image->height * image->width); 
    return moy_rgb;
}




/* 
Q-2.2:
Créer les fonctions double std_dev_pgm(picture *image, double average) et double_-
rgb std_dev_ppm(picture *image, double_rgb average) qui permettent de calculer la
fonction std_dev, définie ci-desssous, de l’image pgm ou ppm passée en paramètre.
*/

d_rgb *std_dev_ppm(ppm *image, d_rgb *average)
{
    double sum_r,sum_g = 0,sum_b = 0;
    for( int i = 0; i < image->height; i++)
    {
        for ( int j = 0; j < image->width; j++)
        {
            sum_r += (image->pixel[i][j].r-average->r)*(image->pixel[i][j].r-average->r);
            sum_g += (image->pixel[i][j].g-average->g)*(image->pixel[i][j].g-average->g);
            sum_b += (image->pixel[i][j].b-average->b)*(image->pixel[i][j].b-average->b);
        }
    }
    d_rgb *result = malloc(sizeof(d_rgb));
    result->r = sqrt(sum_r);
    result->g = sqrt(sum_g);
    result->b = sqrt(sum_b);
    return result;
}

/* 
Q-2.3:
Créer les fonctions, dont la signature est donnée ci-dessous, et qui permettent de calculer
la CCN de la sous-image d’indice (𝑥, 𝑦) de image et du motif pattern. La fonction prendra
également en paramètre la moyenne des valeurs des pixels du motif average_pattern et leur
déviation standard std_dev_pattern. 
• unsigned char NCC_pgm(pgm_t *image, pgm_t *pattern, int x, int y, double
average_pattern, double std_dev_pattern)
• unsigned char NCC_ppm(ppm_t *image, ppm_t *pattern, int x, int y, double_-
rgb average_pattern, double_rgb std_dev_pattern)
*/
unsigned char NCC_ppm(ppm *image, ppm *pattern, int x, int y, d_rgb *average_pattern, d_rgb *std_dev_pattern)
{
    //calcul pour l'image
    double d_sum_r = 0,d_sum_g = 0,d_sum_b = 0;
    for( int i = 0; i < pattern->height; i++)
    {
        for( int j = 0; j < pattern->width; j++)
        {
            d_sum_r += image->pixel[i+x][j+y].r;
            d_sum_g += image->pixel[i+x][j+y].g;
            d_sum_b += image->pixel[i+x][j+y].b;
        }
    }
    d_rgb *average = malloc(sizeof(d_rgb));
    average->r = d_sum_r/(pattern->height * pattern->width); 
    average->g = d_sum_g/(pattern->height * pattern->width); 
    average->b = d_sum_b/(pattern->height * pattern->width); 

    //calcul pour la formule
    d_rgb temp_bot, temp_top;    
    double sum_r = 0, sum_g = 0, sum_b = 0;
    for( int i = 0; i < pattern->height; i++)
    {
        for ( int j = 0; j < pattern->width; j++)
        {
            sum_r += (image->pixel[i+x][j+y].r-average->r)*(image->pixel[i+x][j+y].r-average->r);
            sum_g += (image->pixel[i+x][j+y].g-average->g)*(image->pixel[i+x][j+y].g-average->g);
            sum_b += (image->pixel[i+x][j+y].b-average->b)*(image->pixel[i+x][j+y].b-average->b);

            temp_top.r += (pattern->pixel[i][j].r - average_pattern->r) * (image->pixel[i+x][j+y].r-average->r);
            temp_top.g += (pattern->pixel[i][j].g - average_pattern->g) * (image->pixel[i+x][j+y].g-average->g);
            temp_top.b += (pattern->pixel[i][j].b - average_pattern->b) * (image->pixel[i+x][j+y].b-average->b);

        }
    }
    temp_bot.r = sqrt(sum_r)*std_dev_pattern->r;
    temp_bot.g = sqrt(sum_g)*std_dev_pattern->g;
    temp_bot.b = sqrt(sum_b)*std_dev_pattern->b;
    
    unsigned char ccn  = sqrt
    (
        (temp_top.r/temp_bot.r)*(temp_top.r/temp_bot.r) + 
        (temp_top.g/temp_bot.g)*(temp_top.g/temp_bot.g) + 
        (temp_top.r/temp_bot.r)*(temp_top.r/temp_bot.r)
    ) / sqrt(3);

    return ccn;
}

/* 
Q-2.4:
Créer la fonction pgm_t *compute_NCC(pgm_t *image, pgm_t *pattern) qui renvoie
l’image pgm de taille (𝑀 − 𝑚) × (𝑁 − 𝑛) dont le pixel d’indice (𝑖, 𝑗) contient la valeur de la
NCC entre pattern et la sous image d’indice (𝑖, 𝑗) de image.
*/

pgm *compute_NCC(ppm *image, ppm *pattern)
{
    d_rgb *pat_moy = average_pixels_ppm(pattern);
    d_rgb *pat_std = std_dev_ppm(pattern,pat_moy);
    pgm *temp = malloc(sizeof(ppm));
    temp->height = image->height;
    temp->width = image->width;
    temp->max_value = image->max_value;
    for( int i = 0; i < image->height-20;i++)
    {
        for(int  j = 0; j < image->width-20; j++)
        {
            temp->pixel[i][j] = NCC_ppm(image,pattern,i,j,pat_moy,pat_std);
        }
    }
    return temp;
}

