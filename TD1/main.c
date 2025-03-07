#include <stdio.h>
#include <stdlib.h>
#include "../header/headrs_type.h"


int main( void )
{
    int a;
    printf("jpeg ou autre?\n");
    scanf("%d",&a);
    if(a == 0)
    {
        char filename[19] = "data/eye_s_asc.pgm";
        pgm *image = pgm_read_bin(filename);
        jpeg_to_pgm(image,"data/ahhhhhhhhhhhhh.jpeg");
        return 0;
    }
    else
    {
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
           ppm *neg = ppm_negative(image);
           ppm_extract("bonjour.ppm",neg,100,100,200,200);
           ppm_write_bin(neg,"non.ppm");
           printf("je suis un connard\n");
           ppm_write_histogram(image,"aled.ppm");
           pgm *conv;
           ppm_to_pgm(image,conv);
       }
       else return 1;
    }
    return 0;
}