#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

int main( void )
{
    ppm *image1 = ppm_read_bin("data/charlie_p2.ppm");
    ppm *image2 = ppm_read_bin("data/puzzle2.ppm");
    pattern_matching(image2,image1);
    return 0;
}