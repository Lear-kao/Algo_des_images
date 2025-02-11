#include <stdio.h>
#include "../header/headrs_type.h"

int main( void )
{
    int a;
    printf("pgm(0) ou ppm(1)\n");
    scanf("%d",&a);
    if(a == 0)
    {
        char filename[19] = "data/eye_s_asc.pgm";
        pgm *image = pgm_read_bin(filename);
        pgm *img = pgm_negative(image);
        pgm_write_bin(img,"non.pgm");
        pgm_extract("bonjour.pgm",img,100,100,200,200);
        pgm_write_histogram(img,"bjr.pgm");
    }
    else if(a == 1)
    {
        char filename[19] = "data/eye_s_asc.ppm";
        ppm *image = ppm_read_bin(filename);
        ppm_write_bin(image,"non.ppm");
        printf("%d",a);
    }
    else return 1;
    return 0;
}