#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/headrs_type.h"

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
    char temp[3];
    char c;
    printf("au village sans prétention\n");
    FILE *file = fopen(fname,"r");
    printf("j'ai mauvaise réputation\n");
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
pgm* pgm_read_bin(char *fname)
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
    pgm *image = pgm_alloc(height,width,max_value);
    for( int i = 0;  i < height;  i++)
    {
        for(int j = 0; j < width; j++)
        {
            fread( &image->pixel[i][j], sizeof( unsigned char), 1, file);
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
    FILE *fichier = fopen(fname, "wb");
    if (fichier == NULL) return  0;
    fprintf(fichier, "P5\n%d %d\n%d\n", save->width, save->height, save->max_value);
    for( int i = 0; i < save -> height; i++)
    {
        for( int j = 0;  j < save->width; j++) fwrite(&save->pixel[i][j],sizeof(unsigned char),1,fichier);
    }
    fclose(fichier);
    return 1;
}


/*
Q-1.8:
Écrire la fonction pgm_negative qui prendra en paramètre un pointeur scr sur une structure
pgm contenant l’image source et un pointeur dst sur une structure pgm contenant le négatif de
l’image source.
*/
//retrouver la musique neon nightlife
pgm *pgm_negative(pgm *entree)
{
    pgm *sortie;
    sortie = pgm_alloc(entree->height,entree->width,entree->max_value);
    for (int i = 0;  i < entree->height; i++)
    {
        for (int j = 0; j < entree->width; j++)
        {
            sortie->pixel[i][j] = entree->max_value-entree->pixel[i][j];
        }
    }
    return  sortie;
}


/* 
Q-1.9:
Ecrire la fonction pgm_extract qui en paramètre un pointeur sur une chaine de caractères
contenant le nom du fichier de sortie (fname), une structure pgm_t, les coordonnées dx et dy
indiquant le point de départ de l’image à extraire et les dimensions de l’image à extraire width et
height. La fonction écrira dans le fichier fname une “sous-image” extraite de l’image principale.
*/
void pgm_extract( char *fname, pgm *image, int dx, int dy, int width, int  height)
{
    int cmptx = 0, cmpty = 0;
    pgm *image_extr = pgm_alloc(height,width,image->max_value);
    for( int i = dy; i < dy+height; i++)
    {
        for( int j = dx; j < dx+width; j++)
        {
            image_extr->pixel[cmptx][cmpty] = image->pixel[j][i];
            cmptx+=1;
        }
        cmpty +=1;
        cmptx = 0;
    }
    pgm_write_bin(image_extr,fname);
}


/* 
Q-1.10:
Écrire la fonction pgm_get_histrogram qui prendra en paramètre un pointeur sur une structure
pgm et qui retournera un pointeur sur un tableu de max_value contenant l’histogramme des pixels
de l’image.
*/
int * pgm_get_histogramme(pgm *image)
{
    int *tab = (int*)malloc(sizeof(int)*image->max_value);
    for(int i = 0; i < image->max_value; i++)
    {
        tab[i] = 0;
    }
    for( int i = 0; i < image->height; i++){
        for(int j = 0; j < image->width; j++)
        {
            tab[image->pixel[i][j]]++;
        }
    }
    return tab;
}


/* 
Trouve la valeur maximale d'un tableau 1d.
*/
int max_tab( int *tab, int max_ind)
{
    int max = tab[0];
    for(int i = 0; i < max_ind ; i++)
    {
        if ( max  < tab[i]) max = tab[i];
    }
    return max;
}


/* 
Q-1.11:
Ecrire la fonction pgm_write_histogram qui prendra en paramètre un pointeur sur une structure
pgm, un pointeur sur une chaine de caractère fname. La fonction devra créer le fichier fname et
l’histogramme de l’image sous la forme de deux colonnes (la première colonne contiendra les valeurs
de 0 à max_value, la seconde les données de l’histogramme correspondant).
*/
void pgm_write_histogram( pgm *image,  char *fname)
{
    int *tab = pgm_get_histogramme(image);
    int max = max_tab(tab, image->max_value);
    pgm *histo = pgm_alloc(max,image->max_value,1);
    printf("%d",max);
    for(int i = image->max_value-1; i >=0; i--)
    {
        for(int j = max-1; j >= 0;j-- )
        {
            if (tab[i] >= j)
            {
                histo->pixel[j][i] = 1;
            }
            else histo->pixel[j][i] = 0;
        }
    }
    pgm_write_bin(histo,fname);
}