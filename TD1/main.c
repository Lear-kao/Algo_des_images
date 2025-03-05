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
        double Q[8][8] = 
        {
            {16,11,10,16,24,40,51,61},
            {12,12,14,19,26,58,60,55},
            {14,13,16,24,40,57,69,56},
            {14,17,22,29,51,87,80,62},
            {18,22,37,56,68,109,103,77},
            {24,35,55,64,81,104,113,92},
            {49,64,78,87,103,121,120,101},
            {72,92,95,98,112,100,103,99}
        };
        double **tab = malloc(sizeof(double*) * 8);
        for( int i = 0; i < 8; i++ )
        {
            tab[i] = malloc(sizeof(double) * 8);
            
        }
        char filename[19] = "data/eye_s_asc.ppm";
        ppm *image = ppm_read_bin(filename);
        pgm_extract_blk(image, &tab,0,0);
        printf("premières parties passées \n");
        for(int i = 0;  i < 8; i++)
        {
            for(  int j = 0; j < 8; j++ )
            {
                printf("%f ",tab[i][j]);
            }
            printf("\n");
        }
        pgm_dct(&tab);
        printf("check\n");
        pgm_quantify(&tab,Q);
        printf("second check\n");
        double *tab_2[64];
        pgm_zigzag_extract(Q,tab_2);
        for( int i = 0; i < 64; i++) printf("%f\n",*tab_2[i]);
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