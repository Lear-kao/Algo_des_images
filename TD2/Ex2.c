#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>







/* 
Q-2.2:
Généraliser les questions précédentes en créant une fonction ppm_t *affine_transformation(ppm_-
t *image, double *coeff_transformation) qui renvoie l’image correspondante à la transfor-
mation affine donnée par les coefficients coeff_transformation de l’image image passée en
paramètre.
*/

ppm *affine_transformation(ppm *image, double *coeff_transformation)
{
    int new_size_x[4];
    new_size_x[0] = coeff_transformation[0] * 0 + coeff_transformation[1] * 0 + coeff_transformation[2];
    new_size_x[1] = coeff_transformation[0] * image->height-1 + coeff_transformation[1] * 0 + coeff_transformation[2];
    new_size_x[2] = coeff_transformation[0] * 0 + coeff_transformation[1] * image->width-1 + coeff_transformation[2];
    new_size_x[3] = coeff_transformation[0] * image->height-1 + coeff_transformation[1] * 0 + coeff_transformation[2];
    int new_size_y[4];
    new_size_y[0] = coeff_transformation[0] * 0 + coeff_transformation[1] * 0 + coeff_transformation[2];
    new_size_y[1] = coeff_transformation[0] * image->height-1 + coeff_transformation[1] * 0 + coeff_transformation[2];
    new_size_y[2] = coeff_transformation[0] * 0 + coeff_transformation[1] * image->width-1 + coeff_transformation[2];
    new_size_y[3] = coeff_transformation[0] * image->height-1 + coeff_transformation[1] * image->width-1 + coeff_transformation[2];

    int max_x = new_size_x[0];
    int max_y = new_size_y[0];
    int min_x = new_size_x[0];
    int min_y = new_size_y[0];
    for(int i = 1; i < 4; i++)
    {
        if ( max_x < new_size_x[i]) max_x = new_size_x[i];
        if ( max_y < new_size_y[i]) max_y = new_size_y[i];
        if ( min_x > new_size_x[i]) min_x = new_size_x[i];
        if ( min_y > new_size_y[i]) min_y = new_size_y[i];
    }
    if(min_x < 0)
    {
        max_x -= min_x;
        min_x = 0;
    }
    if(min_y < 0)
    {
        max_y -= min_y;
        min_y = 0;
    }
    ppm *temp = ppm_alloc(max_x,max_y,image->max_value);

    for( int i = 0; i < max_x; i++)
    {
        for( int j = 0; j < max_y; j++)
        {
            int newX = (coeff_transformation[0] * i + coeff_transformation[1] * j + coeff_transformation[3]);
            int newY = (coeff_transformation[3] * i + coeff_transformation[4] * j + coeff_transformation[3]);
            rgb temprgb = interpolation_ppm(image,newX,newY);
            temp->pixel[i][j] = temprgb;
        }
    }
    ppm_write_asc(temp,"non.ppm");
    return temp;
}