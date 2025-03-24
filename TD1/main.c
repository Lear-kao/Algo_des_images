#include <stdio.h>
#include <stdlib.h>
#include "../header/headrs_type.h"


int main( void )
{
    pgm *image = pgm_read_bin("data/eye_s_asc.pgm");
    pgm_to_jpeg(image,"aled.jpg");
    pgm *image_2 = malloc(sizeof(pgm));
    jpeg_to_pgm(image,"exo3.jpeg");

    double Q[8][8] = 
    {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };
    double tab[8][8]= 
    {
    {139, 144, 149, 153, 155, 155, 155, 155},
    {144, 151, 153, 156, 159, 156, 156, 156},
    {150, 155, 160, 163, 158, 156, 156, 156},
    {159, 161, 162, 160, 160, 159, 159, 159},
    {159, 160, 161, 162, 162, 155, 155, 155},
    {161, 161, 161, 161, 160, 157, 157, 157},
    {162, 162, 161, 163, 162, 157, 157, 157},
    {162, 162, 161, 161, 163, 158, 158, 158}
    };
    double **tab2 = malloc(sizeof(double*) *8);
    for(  int i = 0; i < 8; i++ )
    {
        tab2[i] = malloc(sizeof(double)*8);
    }

    for( int i = 0; i < 8; i++)
    {
        for(int j = 0;  j  < 8; j++)
        {
            tab2[i][j] = tab[i][j];
        }
        printf("\n");
    }
    pgm_dct(&tab2);
    pgm_quantify(*tab2,Q);
    pgm_quantify_rev(*tab2,Q);
    pgm_dct_rev(tab2);
    for( int i = 0; i < 8; i++)
    {
        for(int j = 0;  j  < 8; j++)
        {
            printf("%f",*tab2[i][j]);
        }
        printf("\n");
    }
    for( int i = 0; i < 8; i++)
    {
        for(int j = 0;  j  < 8; j++)
        {
            printf("%f",tab[i][j]);
        }
        printf("\n");
    }

    return 0;
}