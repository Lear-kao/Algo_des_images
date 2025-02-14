#include <stdio.h>
#include <stdlib.h>
#include "../header/headrs_type.h"

/* 
Q-2.1:
Écrire une structure ppm qui contiendra la hauteur (height), la largeur (width), une valeur
maximale (max_value) et un pointeur sur un tableau à deux dimensions de structure rgb (pixels).

Voir headers.
*/

/* 
Q-2.2:
Écrire une fonction ppm_alloc qui prend en paramètre la hauteur (height), la largeur (width)
la valeur maximale de codage des pixels (max_value) et qui retourne une structure ppm contenant
les données d’une image de taille height x width de pixels initialisés à la valeur max_value.
*/
ppm* ppm_alloc(int  height, int width, int max_value)
{
    ppm *image = (ppm*)malloc(sizeof(ppm));
    image->height = height;
    image->width  = width;
    image->max_value = max_value;
    image->pixel =(rgb**)malloc(sizeof(rgb*)*height);
    for(int i = 0; i < height; i++)
    {
        image->pixel[i] =(rgb*)malloc(sizeof(rgb)*width);
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image->pixel[i][j].r = 0;
            image->pixel[i][j].g = 0;
            image->pixel[i][j].b = 0;
        }
    }
    return image;
}

/* 
Q-2.3:
Écrire une fonction ppm_free qui prend en paramètre un pointeur sur une structure ppm et libère
l’espace mémoire occupé par cette structure.
*/

void ppm_free(ppm *image)
{
    for (int i = 0; i < image->height; i++) free(image->pixel[i]);
    free(image->pixel);
    free(image);
}

/* 
Q-2.4:
Écrire la fonction ppm_read_asc qui prendra en paramètre un pointeur sur une chaine de
caractères contenant le nom du fichier au format ASCII à lire (fname) et retournant un pointeur sur
une structure ppm contenant les informations relatives à l’image contenue dans le fichier fname.
*/

ppm* ppm_read_asc(char *fname)
{
    int height;
    int width;
    int max_value;
    char temp;

    FILE *file = fopen(fname,"r");
    if(file == NULL)
    {
        printf("erreur fichier\n");
        return NULL;
    }

    fscanf(file, "%3c",&temp);
    do
    {
        fscanf(file, "%c",&temp);
        printf("%c",temp);
        
    } while( temp != '\n');

    fscanf(file,"%d",&width);
    fscanf(file,"%d",&height);
    fscanf(file,"%d",&max_value);
    ppm *image = ppm_alloc(height,width,max_value);
    for(int i = 0; i < height; i++)
    {
        for( int j =0; j < width; j++)
        {
            fscanf(file, "%hhu",&(image->pixel[i][j].r));
            fscanf(file, "%hhu",&(image->pixel[i][j].g));
            fscanf(file, "%hhu",&(image->pixel[i][j].b));
            printf
            (
                "%hhu-%hhu-%hhu\n",
                image->pixel[i][j].r,
                image->pixel[i][j].g,
                image->pixel[i][j].b
            );
        }
        printf("\n");
    }
    return image;
}

/* 
Q-2.5:
Écrire la fonction ppm_write_asc qui prendra en paramètre un pointeur sur une chaine de
caractères contenant le nom du fichier (fname) à écrire (au format ASCII) ainsi qu’un pointeur sur
une structure ppm. La fonction retournera un entier égale à 0 si tout s’est bien passé et à 1 sinon.
*/

int ppm_write_asc( ppm *save, char *fname)
{
    FILE *fichier = fopen(fname, "w");
    if (fichier == NULL) return  1;
    fprintf(fichier,"P3\n");
    fprintf(fichier,"%d\n", save->width);
    fprintf(fichier,"%d\n", save->height);
    fprintf(fichier,"%d\n", save->max_value);
    for(int i = 0; i < save -> height; i++)
    {
        for( int j =0; j < save  -> width; j++)
        {
            fprintf(fichier, "%d\n",save->pixel[i][j].r);
            fprintf(fichier, "%d\n",save->pixel[i][j].g);
            fprintf(fichier, "%d\n",save->pixel[i][j].b);
            fprintf(fichier,"\n");
        }
    }
    return 0;
}

/* 
Q-2.6:
Écrire la fonction ppm_read_bin qui prendra en paramètre un pointeur sur une chaine de
caractères contenant le nom du fichier au format BINAIRE à lire (fname) et retournant un pointeur
sur une structure ppm contenant les informations relatives à l’image contenue dans le fichier fname.
*/

ppm* ppm_read_bin(char *fname)
{
    int height;
    int width;
    int max_value;
    char temp[3];
    char c;
    FILE *file = fopen(fname,"rb");
    if(file == NULL)
    {
        printf("erreur fichier\n");
        return NULL;
    }
    
    fscanf(file, "%3c",temp);
    do
    {
        fscanf(file, "%c",&c);
        printf("%c",c);
        
    } while( c != '\n');
    fscanf(file, "%d",&width);
    fscanf(file, "%d",&height);
    fscanf(file, "%d",&max_value);
    printf("%d-%d-%d\n",height,width,max_value);
    ppm *image = ppm_alloc(height,width,max_value);
    for( int i = 0;  i < height;  i++)
    {
        for(int j = 0; j < width; j++)
        {
            fread( &image->pixel[i][j].r, sizeof( unsigned char), 1, file);
            fread( &image->pixel[i][j].g, sizeof( unsigned char), 1, file);
            fread( &image->pixel[i][j].b, sizeof( unsigned char), 1, file);
        }
    }
    
    return image;
}

/* 
Q-2.7:
Écrire la fonction ppm_write_bin qui prendra en paramètre un pointeur sur une chaine de
caractères contenant le nom du fichier (fname à écrire (au format BINAIRE) ainsi qu’un pointeur sur
une structure ppm. La fonction retournera un entier égale à 0 si tout s’est bien passé et à 1 sinon.
*/

int ppm_write_bin( ppm *save, char *fname)
{
    FILE *fichier = fopen(fname, "wb");
    if (fichier == NULL) return 1;
    fprintf(fichier, "P6\n%d %d\n%d", save->width, save->height, save->max_value);
    for( int i = 0; i < save -> height; i++)
    {
        for( int j = 0;  j < save->width; j++)
        {
            fwrite(&save->pixel[i][j].r,sizeof(unsigned char),1,fichier);
            fwrite(&save->pixel[i][j].g,sizeof(unsigned char),1,fichier);
            fwrite(&save->pixel[i][j].b,sizeof(unsigned char),1,fichier);
        }
    }
    
    fclose(fichier);
    return 0;
}
