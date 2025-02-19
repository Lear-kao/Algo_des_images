#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header/headrs_type.h"

#define PI 3.1415
/* 
Q-3.1:
Créer une fonction void pgm_extract_blk(pgm_t *inpgm, double blk[8][8], int i, int
j) qui extrait le bloc 8 × 8 formé de la composante Y de l’image ppm pointée par image dont le coin
supérieur gauche se trouve aux coordonnées (𝑖, 𝑗). Ce bloc sera sauvegardé dans le tableau de double
bloc passé en paramètre.
*/
void pgm_extract_blk(ppm *inpgm, double *blk[8][8], int i, int j)
{
    for( int x = 0; i  < 8; i++ )
    {
        for( int y = 0; j < 8; j++)
        {
            *blk[x][y] = inpgm->pixel[i+x][j+y].r * 0.298 + inpgm->pixel[i+x][j+y].g * 0.587 + inpgm->pixel[i+x][j+y].b * 0.114;
        }
    }
}



double C( int nu )
{
    if (nu == 0) return sqrt(1.0/8);
    return sqrt(2.0/8);
}
/* 
Q-3.2:
Créer une fonction void pgm_dct(double bloc[8][8]) qui applique la transformée en cosinus
discrète bi-dimensionnelle à un tableau bloc de taille 8 × 8. Pensez à vérifier le bon fonctionnement
de votre fonction avec l’exemple du cours. 
*/
void pgm_dct(double *bloc[8][8])
{
    double tmp_tab[8][8] = {0.0};
    for( int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            double tmp = 0.0;
            for( int u = 0; u < 8; u++ )
            {
                for( int v; u < 8; v++ )
                {
                    tmp +=  bloc[u][v] * 
                            cos((2 * u+ 1) * i * PI / 16 ) * 
                            cos((2 * v + 1) * i * PI / 16);
                }
            }
            tmp_tab[i][j] = C(i) * C(j) * tmp;
        }
    }
    (*bloc) = tmp_tab;   
}

/* 
Q-3.4:

*/