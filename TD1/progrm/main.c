#include <stdio.h>
#include "../header/headrs_type.h"

int main( void )
{
    printf("ok\n");
    char filename[19] = "data/eye_s_asc.bin";
    pgm *image = pgm_read_bin(filename);
    //pgm_write_bin(image,"non.pgm");
    
    return 0;
}