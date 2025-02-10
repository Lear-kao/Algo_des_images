#include <stdio.h>
#include "../header/headrs_type.h"

int main( void )
{
    printf("ok\n");
    char filename[19] = "data/eye_s_asc.pgm";
    pgm *image = pgm_read_bin(filename);
    pgm *img = pgm_negative(image);
    pgm_write_bin(img,"non.pgm");
    
    return 0;
}