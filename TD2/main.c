#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

int main( void )
{
    ppm *image2 = ppm_read_bin("data/eye_s_asc.ppm");
    double  tab[6] = {1,1,1,1,1,1};
    affine_transformation(image2,tab);
    /*zoom_bis_CGPT(image2,2,211,256,image2->height*2,image2->width*2);*/
    return 0;
}
