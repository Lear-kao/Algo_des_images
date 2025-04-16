#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

int main( void )
{
    pgm *image2 = pgm_read_asc("data/eye_s_asc.pgm");
    gaussian_blur(image2,1.4,5);  
    pgm *grad_x = naive_x(image2);
    pgm *grad_y = naive_y(image2);
    pgm *norm = pgm_alloc(image2->height,image2->width,image2->max_value);
    double **tab_grad = gradiant_angle(grad_x,grad_y,norm);
    pile *liste_pixels_forts = NULL;
    non_maxima_suppression(norm, tab_grad, &liste_pixels_forts);
    hysteresis_thresholding(norm, 0.2, 0.1);
    pgm_write_asc(norm,"0-0.pgm");
    return 0;
}