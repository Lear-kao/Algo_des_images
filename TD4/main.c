#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

int main( void )
{
    ppm *image2 = ppm_read_asc("data/eye_s_asc.ppm");
    highlight_rectangle_ppm(image2,15,50,12,12);
    ppm_write_asc(image2,"cut.ppm");
    return 0;
}