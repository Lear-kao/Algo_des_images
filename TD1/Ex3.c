#include <stdio.h>
#include <stdlib.h>
#include "../header/headrs_type.h"

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