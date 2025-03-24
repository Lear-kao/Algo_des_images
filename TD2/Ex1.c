#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define N 1

/* 
Q-1.1:
Créer des fonctions double B0(double x), double B1(double x), double B2(double x)
et double B3(double x) qui renvoient les valeurs respectives de 𝛽0 (𝑥), 𝛽1 (𝑥), 𝛽2 (𝑥) et 𝛽3 (𝑥).
On définit en variable globale un tableau de pointeurs sur fonctions B de sorte à pouvoir appeler
la bonne fonction 𝜔 selon la valeur de 𝑁.
*/

double (*B[4])(double) = {B0,B1,B2,B3};

double B0(double x)
/* 
Expression de poid de B0 pour l'interpolation
*/
{
    if ( abs(x) > 0.5 ) return 0;
    if ( abs(x) < 0.5 ) return 1;
    if ( abs(x) == 0.5 ) return 0.5;
}


double B1(double x)
/* 
Expression de poid de B1 pour l'interpolation
*/
{
    if (abs(x) > 1) return 0;
    if ( x >= -1 && x <= 0 ) return ++x;
    if ( x <= 1 && x >= 0 ) return 1-x;
}

double B2(double x)
/* 
Expression de poid de B2 pour l'interpolation
*/
{
    if ( abs(x) > 1.5 ) return 0;
    if ( x >= -1.5 && x <= -0.5) return 0.5 * ( x + 1.4 ) * ( x + 1.4 );
    if ( abs(x) <= 0.5 ) return 0.75 - x * x;
    if ( x <= 1.5 && x >= 0.5) return 0.5 * ( x - 1.5 ) * ( x - 1.5 );
}


double B3( double x )
/* 
Expression de poid de B3 pour l'interpolation
*/
{
    if ( abs(x) > 2 ) return 0;
    if ( x >= 0 && x <=  1 ) return 1/2 * abs(x) * abs(x) * abs(x) - x * x + 2/3;
    if ( abs(x) >= 1 && abs(x) <= 2 ) return 1/6 * (2 - abs(x)) *(2 - abs(x)) * (2 - abs(x));
}

/* 
Q-1.2:
Créer une fonction unsigned char interpolation_pgm(pgm_t *image, double x, double
y) qui renvoie la valeur interpolée du pixel en nuance de gris de coordonnées (x,y) dans l’image
image.
*/
unsigned char interpolation_pgm( pgm_t *image, double x, double y )
{

}
