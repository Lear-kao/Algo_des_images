#include <stdio.h>
#include "/home/axel/Documents/GitHub/Algo_des_images/TD1/header/headrs_type.h"

int main( void )
{
    char filename[19] = "data/eye_s_asc.bin";
    pgm *image = pgm_read_bin(filename);
    //pgm_write_asc(image,"oui.pgm");
    
    return 0;
}