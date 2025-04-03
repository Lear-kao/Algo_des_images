#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double *get_affine_transformation(point X_start[3], point X_end[3])
{
    double tab[6][6] = 
    {
        {X_start[0].x,X_start[0].y,1,0,0,0},
        {0,0,0,X_start[0].x,X_start[0].y,1},
        {X_start[1].x,X_start[1].y,1,0,0,0},
        {0,0,0,X_start[1].x,X_start[1].y,1},
        {X_start[2].x,X_start[0].y,1,0,0,0},
        {0,0,0,X_start[2].x,X_start[2].y,1}
    };
    double **tab_inv;
    inverse_matrice(6,tab,tab_inv);
    double tab_start[6][1] = 
    {
        {X_start[0].x},
        {X_start[0].y},
        {X_start[1].x},
        {X_start[1].y},
        {X_start[2].x},
        {X_start[2].y}
    };
    int C[6][1];

    multiplication_matrice(6,6,1,tab_inv,tab_start,C);
    double *ret = malloc(sizeof(double))
}

void multiplication_matrice(int n, int m, int p, double **A, double B[m][p], int C[n][p])
{
    // Initialisation de la matrice résultat C à 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
            for (int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int inverse_matrice(int n,double A[n][n], double ***A_inv)
{
    *A_inv = (double**)malloc(sizeof(double*)*n);
    for(int i = 0;i < n; i++)
    {
        *A_inv[i] = (double*)malloc(sizeof(double)*n);
    }
    // Création d'une matrice identité
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *A_inv[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Appliquer la méthode de Gauss-Jordan
    for (int i = 0; i < n; i++) {
        // Vérifier si l'élément diagonal est nul (impossible d'inverser)
        if (A[i][i] == 0.0) {
            return 0;  // La matrice n'est pas inversible
        }

        double pivot = A[i][i];

        // Normaliser la ligne courante (mettre un 1 sur la diagonale)
        for (int j = 0; j < n; j++) {
            A[i][j] /= pivot;
            *A_inv[i][j] /= pivot;
        }

        // Annuler les autres éléments de la colonne
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double facteur = A[k][i];
                for (int j = 0; j < n; j++) {
                    A[k][j] -= facteur * A[i][j];
                    *A_inv[k][j] -= facteur * *A_inv[i][j];
                }
            }
        }
    }
    return 1;
}