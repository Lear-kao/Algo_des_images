#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

int main( void )
{
    pgm *image2 = pgm_read_asc("data/eye_s_asc.pgm");
    naive_x(image2);
    gaussian_blur(image2,1.4,5);   
    return 0;
}