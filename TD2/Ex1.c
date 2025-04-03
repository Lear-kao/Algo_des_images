#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define N 1
#define pi 3.1415

/* 
Q-1.1:
Créer des fonctions double B0(double x), double B1(double x), double B2(double x)
et double B3(double x) qui renvoient les valeurs respectives de 𝛽0 (𝑥), 𝛽1 (𝑥), 𝛽2 (𝑥) et 𝛽3 (𝑥).
On définit en variable globale un tableau de pointeurs sur fonctions B de sorte à pouvoir appeler
la bonne fonction 𝜔 selon la valeur de 𝑁.
*/


double B0(double x)
/* 
Expression de poid de B0 pour l'interpolation
*/
{
    if(fabs(x)>0.5){
        return 0;
    }else if (fabs(x)<0.5){
        return 1;
    }else {//else if( fabs(x)<0.5){
        return 0.5;
    }
}

double B1(double x)
/* 
Expression de poid de B1 pour l'interpolation
*/
{
    if (fabs(x) > 1) return 0.0;
    return (x >= -1 && x <= 0) ? (x + 1) : (1 - x);
}

double B2(double x)
/* 
Expression de poid de B2 pour l'interpolation
*/
{
    x = fabs(x);
    if (x > 1.5) return 0.0;
    if (x > 0.5) return 0.5 * (x - 1.5) * (x - 1.5);
    return 0.75 - x * x;
}


double B3( double x )
/* 
Expression de poid de B3 pour l'interpolation
*/
{
    x = fabs(x);
    if (x > 2.0) return 0.0;
    if (x <= 1.0) return (1.0 / 2.0) * x * x * x - x * x + (2.0 / 3.0);
    return (1.0 / 6.0) * pow(2.0 - x, 3);
}


/* 
Q-1.2:
Créer une fonction unsigned char interpolation_pgm(pgm_t *image, double x, double y) 
qui renvoie la valeur interpolée du pixel en nuance de gris de coordonnées (x,y) dans l’image
image.
*/
unsigned char interpolation_pgm(pgm *image, double x, double y) {
    double sum = 0;
    int tempx = (int)x;
    int tempy = (int)y;
    int xi;
    int yj;
    for (int i = -1; i <= 2; i++) {
        for (int j = -1; j <= 2; j++) {
            xi = tempx + i;
            yj = tempy + j;
            if (xi >= 0 && xi < image->height && yj >= 0 && yj < image->width)
                sum += B0(x - xi) * B0(y - yj) * image->pixel[xi][yj];
        }
    }
    return (unsigned char)sum;
}

/* 
Q-1.3:
Créer une fonction rgb interpolation_ppm(ppm_t *image, double x, double y) qui renvoie
la valeur interpolée du pixel en rgb de coordonées (x,y) dans l’image image.
*/
rgb interpolation_ppm(ppm *image, double x, double y) {
    rgb temp = {0, 0, 0};
    double weight = 0;

    int ix = (int)x, iy = (int)y;
    for (int i = -1; i <= 2; i++) {
        for (int j = -1; j <= 2; j++) {
            int xi = ix + i, yj = iy + j;
            if (xi >= 0 && xi < image->height && yj >= 0 && yj < image->width) {
                double w = B2(x - xi) * B2(y - yj);
                temp.r += w * image->pixel[xi][yj].r;
                temp.g += w * image->pixel[xi][yj].g;
                temp.b += w * image->pixel[xi][yj].b;
            }
        }
    }
    return temp;
}


/* 
Q-1.4:
Créer des fonctions pgm_t *rotation_pgm(pgm_t *image, double theta, int x0, int
y0) et ppm_t *rotation_ppm(ppm_t *image, double theta, int x0, int y0) qui calculent
les rotations d’angle theta et de centre le point de coordonnées (x0,y0) des images au format pgm
et ppm passées en paramètres.
*/
pgm *rotation_pgm(pgm *image, double theta, int x0, int y0)
{
    double RAD = theta * pi/180;
    
    pgm *temp = pgm_alloc(image->height,image->width, image->max_value);
    for( int i = 0; i < temp->height; i++)
    {
        for( int j = 0; j < temp->width; j++)
        {
            double x = x0 + (i - x0 )* cos(RAD) -(j - y0) * sin(RAD);
            double y = y0 + (i - x0) * sin(RAD) + (j - y0) * cos(RAD);
            temp->pixel[i][j] = interpolation_pgm(image, x, y);
        }
    }
    pgm_write_bin(temp,"ptn.pgm");   
    return temp; 
}

ppm *rotation_ppm(ppm *image, double theta, int x0, int y0)
{
    double RAD = theta * pi/180;
    
    ppm *temp = ppm_alloc(image->height,image->width, image->max_value);
    for( int i = 0; i < temp->height; i++)
    {
        for( int j = 0; j < temp->width; j++)
        {
            double x = x0 + (i - x0 )* cos(RAD) -(j - y0) * sin(RAD);
            double y = y0 + (i - x0) * sin(RAD) + (j - y0) * cos(RAD);
            rgb temprgb = interpolation_ppm(image, x, y);
            temp->pixel[i][j].r = temprgb.r;
            temp->pixel[i][j].g = temprgb.g;
            temp->pixel[i][j].b = temprgb.b;
        }
    }
    ppm_write_asc(temp,"ptn2.ppm");   
    return temp; 
}


/* 
Q-1.5.1:
Crée ppm_t *zoom(ppm_t *image, double lambda, int x0, int y0, int Dx, int Dy) qui
crée une image de taille Dx x Dy correspondant au zoom de facteur lambda autour du point
de coordonnées (x0,y0) de l’image passée en paramètre.
*/
ppm *zoom(ppm *image, double lambda, int x0, int y0, int Dx, int Dy)
{
    // Allouer une nouvelle image de taille Dx x Dy
    ppm *temp = ppm_alloc(Dx, Dy, image->max_value);
    
    for (int i = 0; i < Dx; i++) {
        for (int j = 0; j < Dy; j++) {
            // Transformer chaque pixel de l'image d'entrée
            int xpr = x0 + lambda * (i - x0);
            int ypr = y0 + lambda * (j - y0);
            temp->pixel[i][j] = interpolation_ppm(image,xpr,ypr);
        }
    }
    // Sauvegarde de l'image zoomée
    ppm_write_asc(temp, "zoom.ppm");
    
    return temp;
}

ppm *zoom_bis_CGPT(ppm *image, double lambda, int x0, int y0, int Dx, int Dy)
{
    ppm *temp = ppm_alloc(Dx, Dy, image->max_value);
    int x, y;
    for (int i = 0; i < Dx; i++) {
        for (int j = 0; j < Dy; j++) {
            // Trouver la position correspondante dans l'image originale
            int x = x0 + (i - Dx / 2) / lambda;
            int y = y0 + (j - Dy / 2) / lambda;

            // Vérifier si la position est dans les limites de l'image originale
            if (x >= 0 && x < image->height && y >= 0 && y < image->width) {
                temp->pixel[i][j] = image->pixel[x][y];
            } else {
                // Option : mettre un pixel noir si hors limites
                temp->pixel[i][j].r = 0;
                temp->pixel[i][j].g = 0;
                temp->pixel[i][j].b = 0;
            }
        }
    }
    ppm_write_asc(temp,"zoom.ppm");
    return temp;
}



/* 
Q-1.5.2:
Crée ppm_t *shear(ppm_t *image, double cx, double cy, int Dx, int Dy) qui crée une
image de taille Dx x Dy correspondant au cisaillement de facteur cx, cy de l’image passée en
paramètre.
*/
ppm *shear(ppm *image, double cx, double cy, int Dx, int Dy)
{
    ppm *temp = ppm_alloc(Dx,Dy,image->max_value);
    for( int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
        {
            int x = i+cx*j;
            int y = j+cy*i;
            temp->pixel[x][y] = image->pixel[i][j];
        }
    }
    ppm_write_asc(temp,"cis.ppm");
    return temp;
}