#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
--------------------------
--------Exercice 2--------
--------------------------
*/

/* 
Q-2.1:
Créer une fonction void gaussian_blur(pgm_t *image, double sigma, int n) qui ap-
plique un filtre gaussien de taille 𝑛 = 2𝑝 + 1 et d’écart type 𝜎 à l’image image passée en paramètre.
*/
void gaussian_blur(pgm *image, double sigma, int n)
{
    double **kernel = malloc(sizeof(double*)*n);
    for( int i = 0; i < n; i++)
    {
        kernel[i] = (double*)malloc(sizeof(double)*n);
    }

    double sum = 0.0;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            int dx = x - n/2;
            int dy = y - n/2;
            kernel[x][y] = exp(-(dx * dx + dy * dy) / (2 * sigma * sigma));
            sum += kernel[x][y];
        }
    }
    // Normalisation (pour que la somme = 1)
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            kernel[x][y] /= sum;
        }
    }

    pgm *temp = pgm_alloc(image->height, image->width,image->max_value);
    char t = max_pgm(image);
    int mod;
    for( int i = 1; i < image->height-2; i++)
    {
        for( int j = 1;  j < image->width-2; j++)
        {
            temp->pixel[i][j] = gaussian_filter(image, i, j, kernel,n);
        }  
    }
    image = temp;
}


int gaussian_filter(pgm *image, int x, int y, double **kernel, int n)
{
    int offset = n / 2;
    double sum = 0.0;

    for (int i = -offset; i <= offset; i++) {
        for (int j = -offset; j <= offset; j++) {
            int xi = x + i;
            int yj = y + j;

            // Vérification des bords
            if (xi >= 0 && xi < image->height && yj >= 0 && yj < image->width) {
                sum += image->pixel[xi][yj] * kernel[i + offset][j + offset];
            }
        }
    }

    // Clamp final
    if (sum < 0) sum = 0;
    if (sum > 255) sum = 255;

    return (int)(sum + 0.5); // arrondi
}

/* 
Q-2.2:
Créer une fonction double **gradiant_angle(pgm_t *grad_x, pgm_t *grad_y) qui prend
en paramètre les deux composantes du gradient et renvoie l’angle de celui ci avec la tangeante
horizontale. On utilisera la fonction atan2 de la bibliothèque math.h.
*/
double **gradiant_angle(pgm *grad_x, pgm *grad_y, pgm *norm)
{
    double **tab = malloc(sizeof(double*)*grad_x->height);
    for( int i = 0; i  < grad_x->height; i++ )
    {
        tab[i] = malloc(sizeof(double)*grad_x->width);
    }
    for( int i = 0;  i < grad_x->height; i++)
    {
        for(int j = 0; j < grad_x->width; j++)
        {
            tab[i][j] = atan2(grad_x->pixel[i][j],grad_y->pixel[i][j]);
            norm->pixel[i][j] = sqrt(grad_x->pixel[i][j]*grad_x->pixel[i][j]+grad_y->pixel[i][j]*grad_y->pixel[i][j]);
        }
    }
    return tab;    
}

/* 
Q-2.3:
Créer une fonction void non_maxima_suppression(pgm_t *norm, double **angle), la fonc-
tion prendra en paramètre une image correspondant à la norme du gradient, et un tableau 2D de
double contenant l’angle du gradient avec la droite horizontale pour chaque pixel de l’image (sauf
les bords).
*/
void non_maxima_suppression(pgm *norm, double **angle, pile **edges)
{
    *edges = NULL; // Initialisation

    pgm *temp = pgm_alloc(norm->height, norm->width, norm->max_value);
    for (int i = 0; i < norm->height; i++) {
        for (int j = 0; j < norm->width; j++) {
            temp->pixel[i][j] = norm->pixel[i][j];
        }
    }

    for (int y = 1; y < norm->height - 1; y++) {
        for (int x = 1; x < norm->width - 1; x++) {
            double theta = angle[y][x] * 180.0 / PI;
            if (theta < 0) theta += 180;

            int q = 0, r = 0;
            if ((0 <= theta && theta < 22.5) || (157.5 <= theta && theta <= 180)) {
                q = temp->pixel[y][x + 1];
                r = temp->pixel[y][x - 1];
            } else if (22.5 <= theta && theta < 67.5) {
                q = temp->pixel[y + 1][x - 1];
                r = temp->pixel[y - 1][x + 1];
            } else if (67.5 <= theta && theta < 112.5) {
                q = temp->pixel[y + 1][x];
                r = temp->pixel[y - 1][x];
            } else if (112.5 <= theta && theta < 157.5) {
                q = temp->pixel[y - 1][x - 1];
                r = temp->pixel[y + 1][x + 1];
            }

            if (temp->pixel[y][x] < q || temp->pixel[y][x] < r) {
                norm->pixel[y][x] = 0;
            } else {
                norm->pixel[y][x] = temp->pixel[y][x];
                if (norm->pixel[y][x] >= 100) {
                    empiler(edges, x, y);
                }
            }
        }
    }

    pgm_free(temp); // Libération mémoire
}


void hysteresis_thresholding(pgm *image, float seuil_haut, float seuil_bas) {
    int w = image->width;
    int h = image->height;
    unsigned char max_val = max_pgm(image);

    // Calcul des seuils réels
    unsigned char seuil_haut_val = (unsigned char)(seuil_haut * max_val);
    unsigned char seuil_bas_val  = (unsigned char)(seuil_bas * max_val);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (image->pixel[y][x] >= seuil_haut_val) {
                image->pixel[y][x] = STRONG_EDGE;
            } else if (image->pixel[y][x] >= seuil_bas_val) {
                image->pixel[y][x] = WEAK_EDGE;
            } else {
                image->pixel[y][x] = 0;
            }
        }
    }

    // Étape 3 : traquage des pixels faibles
    int dx[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    int dy[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    int change = 1;
    while (change) {
        change = 0;
        for (int y = 1; y < h - 1; y++) {
            for (int x = 1; x < w - 1; x++) {
                if (image->pixel[y][x] == WEAK_EDGE) {
                    for (int k = 0; k < 8; k++) {
                        int nx = x + dx[k];
                        int ny = y + dy[k];
                        if (image->pixel[ny][nx] == STRONG_EDGE) {
                            image->pixel[y][x] = STRONG_EDGE;
                            change = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}
