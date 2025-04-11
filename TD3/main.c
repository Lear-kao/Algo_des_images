#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

int main( void )
{
    pgm *image2 = pgm_read_asc("data/eye_s_asc.pgm");
    naive_x(image2);
    gaussian_blur(image2,1.4,5);  
    pgm *grad_x = naive_x(image2);
    pgm *grad_y = naive_y(image2);
    pgm *norm = pgm_alloc(image2->height,image2->width,image2->max_value);
    double **tab_grad = gradiant_angle(grad_x,grad_y);

    return 0;
}