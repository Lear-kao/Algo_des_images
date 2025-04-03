#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

int main( void )
{
    ppm *image2 = ppm_read_bin("data/eye_s_asc.ppm");
    ppm_write_bin(image2,"aled.ppm");
    rotation_ppm(image2,30,211,256);
    shear(image2,0.4,0.6,800,800);
    /*zoom_bis_CGPT(image2,2,211,256,image2->height*2,image2->width*2);*/
    return 0;
}
