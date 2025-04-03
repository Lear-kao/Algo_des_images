#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



// Fonction de multiplication de matrices 6x6 * 6x1
void multiply_matrices(double A[6][6], double B[6], double result[6]) {
    for (int i = 0; i < 6; i++) {
        result[i] = 0;
        for (int j = 0; j < 6; j++) {
            result[i] += A[i][j] * B[j];
        }
    }
}

// Algorithme de pseudo-inverse (Moore-Penrose simplifié)
void pseudo_inverse(double X[6][6], double X_inv[6][6]) {
    double Xt[6][6], XtX[6][6], XtX_inv[6][6];

    // Calcul de la transposée de X (Xt)
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            Xt[j][i] = X[i][j];

    // Calcul de Xt * X
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            XtX[i][j] = 0;
            for (int k = 0; k < 6; k++)
                XtX[i][j] += Xt[i][k] * X[k][j];
        }

    // Approximation de l'inverse de XtX (ajout d'un petit terme pour éviter division par zéro)
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            XtX_inv[i][j] = (i == j) ? 1.0 / (XtX[i][j] + 1e-9) : 0;

    // Pseudo-inverse : (XtX)^-1 * Xt
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            X_inv[i][j] = 0;
            for (int k = 0; k < 6; k++)
                X_inv[i][j] += XtX_inv[i][k] * Xt[k][j];
        }
}

// Fonction principale pour trouver la transformation affine
void get_affine_transformation(point A[3], point B[3]) {
    double X[6][6] = {
        {A[0].x, A[0].y, 1, 0, 0, 0},
        {0, 0, 0, A[0].x, A[0].y, 1},
        {A[1].x, A[1].y, 1, 0, 0, 0},
        {0, 0, 0, A[1].x, A[1].y, 1},
        {A[2].x, A[2].y, 1, 0, 0, 0},
        {0, 0, 0, A[2].x, A[2].y, 1}
    };

    double Y[6] = {B[0].x, B[0].y, B[1].x, B[1].y, B[2].x, B[2].y};

    double X_inv[6][6], coeffs[6];

    // Calcul de la pseudo-inverse
    pseudo_inverse(X, X_inv);

    // Multiplication X_inv * Y pour obtenir les coefficients
    multiply_matrices(X_inv, Y, coeffs);

    // Affichage du résultat
    printf("Transformation affine trouvée :\n");
    printf("a00 = %lf, a01 = %lf, a02 = %lf\n", coeffs[0], coeffs[1], coeffs[2]);
    printf("a10 = %lf, a11 = %lf, a12 = %lf\n", coeffs[3], coeffs[4], coeffs[5]);
}



/* 
Q-2.2:
Généraliser les questions précédentes en créant une fonction ppm_t *affine_transformation(ppm_-
t *image, double *coeff_transformation) qui renvoie l’image correspondante à la transfor-
mation affine donnée par les coefficients coeff_transformation de l’image image passée en
paramètre.
*/

ppm *affine_transformation(ppm *image, double *coeff_transformation)
{
    int new_size_x[4];
    new_size_x[0] = coeff_transformation[0] * 0 + coeff_transformation[1] * 0 + coeff_transformation[2];
    new_size_x[1] = coeff_transformation[0] * image->height-1 + coeff_transformation[1] * 0 + coeff_transformation[2];
    new_size_x[2] = coeff_transformation[0] * 0 + coeff_transformation[1] * image->width-1 + coeff_transformation[2];
    new_size_x[3] = coeff_transformation[0] * image->height-1 + coeff_transformation[1] * 0 + coeff_transformation[2];
    int new_size_y[4];
    new_size_y[0] = coeff_transformation[0] * 0 + coeff_transformation[1] * 0 + coeff_transformation[2];
    new_size_y[1] = coeff_transformation[0] * image->height-1 + coeff_transformation[1] * 0 + coeff_transformation[2];
    new_size_y[2] = coeff_transformation[0] * 0 + coeff_transformation[1] * image->width-1 + coeff_transformation[2];
    new_size_y[3] = coeff_transformation[0] * image->height-1 + coeff_transformation[1] * image->width-1 + coeff_transformation[2];

    int max_x = new_size_x[0];
    int max_y = new_size_y[0];
    int min_x = new_size_x[0];
    int min_y = new_size_y[0];
    for(int i = 1; i < 4; i++)
    {
        if ( max_x < new_size_x[i]) max_x = new_size_x[i];
        if ( max_y < new_size_y[i]) max_y = new_size_y[i];
        if ( min_x > new_size_x[i]) min_x = new_size_x[i];
        if ( min_y > new_size_y[i]) min_y = new_size_y[i];
    }
    if(min_x < 0)
    {
        max_x -= min_x;
        min_x = 0;
    }
    if(min_y < 0)
    {
        max_y -= min_y;
        min_y = 0;
    }
    ppm *temp = ppm_alloc(max_x,max_y,image->max_value);

    for( int i = 0; i < max_x; i++)
    {
        for( int j = 0; j < max_y; j++)
        {
            int newX = (coeff_transformation[0] * i + coeff_transformation[1] * j + coeff_transformation[3]);
            int newY = (coeff_transformation[3] * i + coeff_transformation[4] * j + coeff_transformation[3]);
            rgb temprgb = interpolation_ppm(image,newX,newY);
            temp->pixel[i][j] = temprgb;
        }
    }
    ppm_write_asc(temp,"non.ppm");
    return temp;
}