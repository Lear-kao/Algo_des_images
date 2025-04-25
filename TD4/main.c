#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

int main( void )
{
    ppm *image1 = ppm_read_bin("data/charlie_p2.ppm");
    ppm *image2 = ppm_read_bin("data/puzzle2.ppm");
    pgm *ah = compute_NCC(image2,image1);
    pgm_write_bin( ah,"ahhhh.pgm");
    return 0;
}