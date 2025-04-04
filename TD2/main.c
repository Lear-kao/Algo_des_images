#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

int main( void )
{
    pgm *image2 = pgm_read_asc("data/eye_s_asc.pgm");
    affine_transformation(image2,tab);
    /*zoom_bis_CGPT(image2,2,211,256,image2->height*2,image2->width*2);*/
    return 0;
}
