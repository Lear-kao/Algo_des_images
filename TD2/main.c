#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

int main( void )
{
    pgm *image = pgm_read_bin("data/eye_s_asc.pgm");
    rotation_pgm(image,20,256,256);
    return 0;
}
