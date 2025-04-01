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


double B0(double x){
    if(fabs(x)>0.5){
        return 0;
    }else if (fabs(x)<0.5){
        return 1;
    }else {//else if( fabs(x)<0.5){
        return 0.5;
    }
}

double B1(double x){
    if(fabs(x)>1){
        return 0;
    }else if(-1<= x && x<=0){
        return x+1;
    }else{//else if(0<= x && x<=1){
        return 1-x;
    }
}

double B2(double x){
    if(fabs(x)>1.5){
        return 0;
    }else if(-1.5 <= x && x<= -0.5){
        return 0.5*(x+1.4)*(x+1.4);
    }else if(-0.5 <= x && x <=0.5){
        return 0.75 - x*x; 
    }else{//else if(0.5 <= x && x <= 1.5){
        return 0.5*(x-1.5)*(x-1.5);
    }
}

double B3(double x){
    if(fabs(x)>2){
        return 0;
    }else if(0 <= fabs(x) && fabs(x) <= 1){
        return 1/2 * fabs(x)*fabs(x)*fabs(x) - x*x + 2/3;
    }else{ //else if(1 <= fabs(x) && fabs(x) <= 2){
        return 1/6 * (2-fabs(x))*(2-fabs(x))*(2-fabs(x));
    }
}


/* 
Q-1.2:
Créer une fonction unsigned char interpolation_pgm(pgm_t *image, double x, double y) 
qui renvoie la valeur interpolée du pixel en nuance de gris de coordonnées (x,y) dans l’image
image.
*/
unsigned char interpolation_pgm(pgm *image, double x, double y) {
    double sum = 0, weight = 0;
    
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            double w = B0(x - i) * B0(y - j);
            sum += w * image->pixel[i][j];
            weight += w;
        }
    }
    
    return (weight > 0) ? (unsigned char)(sum / weight) : 0;
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
                double w = B0(x - xi) * B0(y - yj);
                temp.r += w * image->pixel[xi][yj].r;
                temp.g += w * image->pixel[xi][yj].g;
                temp.b += w * image->pixel[xi][yj].b;
                weight += w;
            }
        }
    }
    if (weight > 0) {
        temp.r = (unsigned char)fmin(255, fmax(0, temp.r / weight));
        temp.g = (unsigned char)fmin(255, fmax(0, temp.g / weight));
        temp.b = (unsigned char)fmin(255, fmax(0, temp.b / weight));
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
            
            double x=x0 + (i - x0 )* cos(RAD) -(j - y0) * sin(RAD);
            double y = y0 + (i - x0) * sin(RAD) + (j - y0) * cos(RAD);
            temp->pixel[i][j] = interpolation_pgm(image, x, y);
        }
    }
    pgm_write_asc(temp,"ptn.pgm");   
    return temp; 
}
