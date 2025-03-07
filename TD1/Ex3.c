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
void pgm_extract_blk(pgm *inpgm, double ***blk, int i, int j)
{
    for( int x = 0; x < 8; x++ )
    {
        for( int y = 0; y < 8; y++)
        {
            /* if (inpgm->pixel[i+x][j+y] == NULL ) 
                (*blk)[x][y] = 0; */
            (*blk)[x][y] = inpgm->pixel[i][j];
            //inpgm->pixel[i+x][j+y].r * 0.298 + inpgm->pixel[i+x][j+y].g * 0.587 + inpgm->pixel[i+x][j+y].b * 0.114;
            //a utiliserpour pgm
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
void pgm_dct(double ***bloc)
{
    double **tmp_tab = malloc(sizeof( double*)*8);

    for( int i = 0; i < 8;i++) 
        tmp_tab[i] = malloc( sizeof(double) * 8 );
    for( int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            double tmp = 0.0;
            for( int u = 0; u < 8; u++ )
            {
                for( int v = 0; v < 8; v++ )
                {
                    tmp +=  ((*bloc)[u][v]) * 
                            cos(((2 * u+ 1) * i * PI) / 16 ) *
                            cos(((2 * v + 1) * j * PI) / 16);
                }
            }
            tmp_tab[i][j] = C(i) * C(j) * tmp;
        }
    }
    for (int i = 0; i < 8; i++) {
        free((*bloc)[i]);
    }
    free(*bloc);
    *bloc = tmp_tab;   
}


/* 
Q-3.3:
Créer la fonction void pgm_quantify(double blk[8][8], double Q[8][8]) qui quantifie
le bloc blk passé en paramètre avec la matrice de quantification 𝑄 passée en paramètre.
*/
void pgm_quantify( double ***blk, double Q[8][8])
{
    for( int i = 0; i < 8; i++)
    {
        for( int j = 0; j < 8; j++)
        {
            (*blk)[i][j] = (*blk)[i][j]/Q[i][j];
        }
    }
}


/* 
Q-3.4:
Créer la fonction void pgm_zigzag_extract(double blk[8][8], int zgzg[64]) qui ex-
trait les 64 nombres contenus dans le bloc blk de taille 8 × 8 dans l’ordre donné par la figure 1. Les
valeurs de blk seront arrondies à l’entier le plus proche avant d’être stockées dans le tableau zgzg
passé en paramètre.
*/

void pgm_zigzag_extract(double blk[8][8], int zgzg[64]) {
    int cmpt = 0;

    for (int i = 0; i < 15; i++) {
        int start_x = (i < 8) ? i : 7;
        int start_y = (i < 8) ? 0 : i - 7;
        if (i % 2 == 1) { // Si la diagonale est "montante"
            for (int j = start_x, h = start_y; j >= 0 && h < 8; j--, h++) {
                zgzg[cmpt++] = round(blk[h][j]);
            }
        } else { // Si la diagonale est "descendante"
            for (int j = start_y, h = start_x; j < 8 && h >= 0; j++, h--) {
                zgzg[cmpt++] = round(blk[h][j]);
            }
        }
    }
}


/* 
Q-3.5:
Créez la fonction void pgm_rle(FILE *fd, double zgzg[64]) qui écrit les entiers contenus
dans le tableau zgzg dans le fichier pointé par fd. On supposera que le flux donné par fd aura été
ouvert préalablement. Chaque entier sera écrit sur une ligne différente et une séquence de 𝑛 0 sera
codée par @$n$ dès que 𝑛 ≥ 2.
*/
void pgm_rle(FILE *fd, int zgzg[64]) {
    int i = 0;
    while (i < 64) {
        if (zgzg[i] == 0) { // Détection d'une séquence de 0
            int count = 0;
            while (i < 64 && zgzg[i] == 0)
            {
                count++;
                i++;
            }
            if (count >= 2) {
                fprintf(fd, "@$%d$\n", count);
            } 
            else 
            {
                fprintf(fd, "0\n"); 
            }
        } else { 
            fprintf(fd, "%d\n", zgzg[i]);
            i++;
        }
    }
}

/* 
Q-3.6:
À l’aide des fonctions précédentes, créer une fonction void pgm_to_jpeg(pgm_t *in_pgm,
char *fname) qui compresse l’image pgm pointée par in_pgm en utilisant l’algorithme de com-
pression JPEG et qui stocke le résultat dans un fichier dont le nom est donné par fname. Le fichier
compressé respectera le format suivant :
1|    JPEG
2|    widht height
3|    val 0
4|    val 1
5|    val 2
...
*/
void  pgm_to_jpeg(pgm *in_pgm,char *fname)
{

    FILE *jpg = fopen(fname,"w");
    if  (jpg == NULL) exit(1);
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

    fprintf(jpg,"JPEG\n");
    fprintf(jpg,"%d %d\n",in_pgm->width,in_pgm->height);
    int tab_2[64];
    for( int i = 0; i < 32;i++)
    {
        for( int j = 0; j < 32; j++){
            pgm_extract_blk(in_pgm,&tab,i * 8,j * 8);
            pgm_dct(&tab);
            pgm_quantify(&tab,Q);
            pgm_zigzag_extract(tab,tab_2);
            pgm_rle(jpg,tab_2);
        }
    }
}


//TD4: Même  fonction à l'inverse:

/* 
Q-4.1:
Réaliser toutes les fonctions inverses du processus de compression.
*/
void blk_extract_pgm(pgm *inpgm, double ***blk, int i, int j)
{
    for( int x = 0; x < 8; x++ )
    {
        for( int y = 0; y < 8; y++)
        {
            /* if (inpgm->pixel[i+x][j+y] == NULL ) 
                (*blk)[x][y] = 0; */
            inpgm->pixel[i][j] = (int)(*blk)[x][y];
            //inpgm->pixel[i+x][j+y].r * 0.298 + inpgm->pixel[i+x][j+y].g * 0.587 + inpgm->pixel[i+x][j+y].b * 0.114;
            //a utiliserpour pgm
        }
    }
}

void pgm_dct_rev(double ***bloc)
{
    double **tmp_tab = malloc(sizeof( double*)*8);

    for( int i = 0; i < 8;i++) 
        tmp_tab[i] = malloc( sizeof(double) * 8 );
    for( int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            double tmp = 0.0;
            for( int u = 0; u < 8; u++ )
            {
                for( int v = 0; v < 8; v++ )
                {
                    tmp +=  ((*bloc)[u][v]) * 
                            cos(((2 * u+ 1) * i * PI) / 16 ) *
                            cos(((2 * v + 1) * j * PI) / 16);
                }
            }
            tmp_tab[i][j] = tmp;
        }
    }
    for (int i = 0; i < 8; i++) {
        free((*bloc)[i]);
    }
    free(*bloc);
    *bloc = tmp_tab;   
}

void pgm_quantify_rev( double ***blk, double Q[8][8])
{
    for( int i = 0; i < 8; i++)
    {
        for( int j = 0; j < 8; j++)
        {
            (*blk)[i][j] = (*blk)[i][j]*Q[i][j];
        }
    }
}

void pgm_zigzag_extract_rev(double blk[8][8], int zgzg[64])
{
    int cmpt = 0;

    for (int i = 0; i < 15; i++) {
        int start_x = (i < 8) ? i : 7;
        int start_y = (i < 8) ? 0 : i - 7;
        if (i % 2 == 1) { // Si la diagonale est "montante"
            for (int j = start_x, h = start_y; j >= 0 && h < 8; j--, h++)
            {
                blk[h][j] = (double)zgzg[cmpt++];
            }
        } else { // Si la diagonale est "descendante"
            for (int j = start_y, h = start_x; j < 8 && h >= 0; j++, h--)
            {
                blk[h][j]= (double)zgzg[cmpt++];

            }
        }
    }
    for( int i = 0; i < 8; i++)
    {
        for( int j = 0; j < 8; j++)
        {
            printf("%f ",blk[i][j]);
        }
        printf("\n");
    }
}

void pgm_rle_rev(FILE *fd, int zgzg[64])
{
    // Récupere le 64 premier entier compressé en RLE, pour le mettre dans un tableau de 64 entiers.
    int n=0;
    char tmp;
    int nb_zero, valeur;

    while(n<64)
    {
        fscanf(fd,"%c",&tmp);
        if(tmp == '@')
        {
            fscanf(fd,"%d",&nb_zero);
            for(int i=0; i<nb_zero; ++i)
            {
                zgzg[n+i]=0;
            }
            n+=nb_zero;
        }
        else
        {
            fseek(fd,-sizeof(char),SEEK_CUR);
            fscanf(fd,"%d",&valeur);
            zgzg[n]=valeur;
            ++n;
        }
        fscanf(fd,"%c",&tmp);
    }
}

void jpeg_to_pgm(pgm *in_pgm, char *fname)
{
    FILE *jpg = fopen(fname, "r");
    if (jpg == NULL)
    {
        perror("Erreur ouverture fichier");
        exit(1);
    }

    double Q[8][8] = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };

    int width, height;
    fscanf(jpg, "JPEG\n%d %d\n", &width, &height);
    in_pgm->width = width;
    in_pgm->height = height;
    printf("clear 1st part\n");
    int tab_2[64];
    double **tab = malloc(sizeof(double*) * 8);
    for (int i = 0; i < 8; i++)
        tab[i] = malloc(sizeof(double) * 8);

    for (int i = 0; i < width / 8; i++)
    {
        for (int j = 0; j < height / 8; j++)
        {
            pgm_rle_rev(jpg, tab_2);
            printf("rle passed\n");
            pgm_zigzag_extract_rev(tab, tab_2);
            printf("zig passed\n");
            pgm_quantify_rev(&tab, Q);
            printf("quant passed\n");
            pgm_dct_rev(&tab);
            printf("dct passed\n");
            blk_extract_pgm(in_pgm, &tab, i * 8, j * 8);
            printf("extract passed\n");
        }
    }

    // Fermeture du fichier
    fclose(jpg);

    // Libération mémoire
    for (int i = 0; i < 8; i++)
        free(tab[i]);
    free(tab);
}
