#include <stdio.h>
#include <stdlib.h>
#include "/home/axel/Documents/GitHub/Algo_des_images/TD1/header/headrs_type.h"

/*
Q-1.1:
Ecrire une structure pgm qui contiendra la hauteur (height), la largeur (width) la valeur maximale
de codage des pixels (max_value) ainsi qu’un pointeur sur un tableau à deux dimensions de caractères
non-signés (pixels).

VOIR FICHIER HEADER
*/



/*
Q-1.2:
Écrire une fonction pgm_alloc qui prend en paramètre la hauteur (height), la largeur (width)
la valeur maximale de codage des pixels (max_value) et qui retourne une structure pgm contenant
les données d’une image de taille height x width de pixels initialisés à la valeur max_value.
*/
pgm* pgm_alloc(int  height, int width, int max_value)
{
    pgm *image = (pgm*)malloc(sizeof(pgm));
    image->height = height;
    image->width  = width;
    image->max_value = max_value;
    image->pixel = malloc(sizeof(unsigned char*)*height);
    for(int i = 0; i < height; i++)
    {
        image->pixel[i] = malloc(sizeof(unsigned char)*width);
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image->pixel[i][j] = max_value;
        }
    }
    return image;
}

/*
Q-1.3:
Écrire une fonction pgm_free qui prend en paramètre un pointeur sur une structure pgm et libère
l’espace mémoire occupé par cette structure.
*/

void pgm_free(pgm *image)
{
    for (int i = 0; i < image->height; i++) free(image->pixel[i]);
    free(image->pixel);
    free(image);
}


/*
Q-1.4:
Écrire la fonction pgm_read_asc qui prendra en paramètre un pointeur sur une chaine de
caractères contenant le nom du fichier au format ASCII à lire (fname) et retournant un pointeur sur
une structure pgm contenant les informations relatives à l’image contenue dans le fichier fname.
*/

pgm* pgm_read_asc(char *fname)
{
    int height;
    int width;
    int max_value;
    char temp;
    printf("au village sans prétention\n");
    FILE *file = fopen(fname,"r");
    printf("j'ai mauvaise réputation\n");
    if(file == NULL)
    {
        printf("erreur fichier\n");
        return NULL;
    }
    fscanf(file, "%s",&temp);
    fscanf(file,"%d",&width);
    fscanf(file,"%d",&height);
    fscanf(file,"%d",&max_value);
    pgm *image = pgm_alloc(height,width,max_value);
    for(int i = 0; i < height; i++)
    {
        for( int j =0; j < width; j++)
        {
            fscanf(file, "%hhu",&(image->pixel[i][j]));
            printf("%hhu\n",(image->pixel[i][j]));
        }
        printf("\n");
    }
    return image;
}

/*
Q-1.5:
Écrire la fonction pgm_write_asc qui prendra en paramètre un pointeur sur une chaine de
caractères contenant le nom du fichier (fname) à écrire (au format ASCII) ainsi qu’un pointeur sur
une structure pgm. La fonction retournera un entier égale à 0 si tout s’est bien passé et à 1 sinon.
*/

int pgm_write_asc( pgm *save, char *fname)
{
    FILE *fichier = fopen(fname, "w");
    if (fichier == NULL) return  0;
    fprintf(fichier,"P2\n");
    fprintf(fichier,"%d\n", save->width);
    fprintf(fichier,"%d\n", save->height);
    fprintf(fichier,"%d\n", save->max_value);
    for(int i = 0; i < save -> height; i++)
    {
        for( int j =0; j < save  -> width; j++)
        {
            fprintf(fichier, "%d\n",save->pixel[i][j]);
            fprintf(fichier,"\n");
        }
    }
    return 1;
}

/*
Q-1.6:
Écrire la fonction pgm_read_bin qui prendra en paramètre un pointeur sur une chaine de
caractères contenant le nom du fichier au format BINAIRE à lire (fname) et retournant un pointeur
sur une structure pgm contenant les informations relatives à l’image contenue dans le fichier fname.
*/

struct pgm* pgm_read_bin(char *fname)
{
    FILE *fichier = fopen(fname,"rb");
    if (fichier == NULL){
        printf("ok");
        return NULL;
    }
    char trash[2];
    fread(trash,sizeof(char),2,fichier);
    int width;
    fread(&width,sizeof(int),1,fichier);
    int height;
    fread(&height,sizeof(int),1,fichier);
    int max_value;
    fread(&max_value,sizeof(int),1,fichier);
    pgm *image = pgm_alloc(height,width,max_value);
    for(int i = 0; i < height; i++)
    {
        for( int j =0; j < width; j++)
        {
            fread(&(image->pixel[i][j]),sizeof(unsigned  char),1,fichier);
            printf("%u",image->pixel[i][j]);
        }
    }
    return image;
}

/*
Q-1.7:
Écrire la fonction pgm_write_bin qui prendra en paramètre un pointeur sur une chaine de
caractères contenant le nom du fichier (fname à écrire (au format BINAIRE) ainsi qu’un pointeur sur
une structure pgm. La fonction retournera un entier égale à 0 si tout s’est bien passé et à 1 sinon.
*/
int pgm_write_bin( pgm *save, char *fname)
{
    FILE *fichier = fopen(fname, "w");
    if (fichier == NULL) return  0;
    fwrite(fichier,"P5\n");
    fprintf(save->width,sizeof(int), 1, fichier);
    fprintf(save->height,sizeof(int),1,fichier);
    fprintf(save->max_value, sizeof(int), 1, fichier);
    for(int i = 0; i < save -> height; i++)
    {
        fwrite(save->pixel[i],sizeof(unsigned  char),save->width,fichier);
    }
    return 1;
}

