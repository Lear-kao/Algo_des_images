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
    fprintf(fichier,"%d %d", save->width,save->height);
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
    fprintf(fichier, "P6\n%d %d\n%d\n", save->width, save->height, save->max_value);
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


/* 
Q-2.8:
Écrire la fonction ppm_negative qui prendra en paramètre un pointeur scr sur une structure
ppm contenant l’image source et un pointeur dst sur une structure ppm contenant le négatif de
l’image source.
*/
ppm *ppm_negative(ppm *entree)
{
    ppm *sortie;
    sortie = ppm_alloc(entree->height,entree->width,entree->max_value);
    for (int i = 0;  i < entree->height; i++)
    {
        for (int j = 0; j < entree->width; j++)
        {
            sortie->pixel[i][j].r = entree->max_value-entree->pixel[i][j].r;
            sortie->pixel[i][j].g = entree->max_value-entree->pixel[i][j].g;
            sortie->pixel[i][j].b = entree->max_value-entree->pixel[i][j].b;
        }
    }
    return  sortie;
}


/* 
Q-2.9:
Écrire la fonction ppm_extract qui en paramètre un pointeur sur une chaine de caractères
contenant le nom du fichier de sortie (fname), une structure ppm_t, les coordonnées dx et dy
indiquant le point de départ de l’image à extraire et les dimensions de l’image à extraire width et
height. La fonction écrira dans le fichier fname une “sous-image” extraite de l’image principale.
*/
void ppm_extract( char *fname, ppm *image, int dx, int dy, int width, int  height)
{
    int cmptx = 0, cmpty = 0;
    ppm *image_extr = ppm_alloc(height,width,image->max_value);
    for( int i = dy; i < dy+height; i++)
    {
        for( int j = dx; j < dx+width; j++)
        {
            image_extr->pixel[cmptx][cmpty].r = image->pixel[j][i].r;
            image_extr->pixel[cmptx][cmpty].g = image->pixel[j][i].g;
            image_extr->pixel[cmptx][cmpty].b = image->pixel[j][i].b;
            cmptx+=1;
        }
        cmpty +=1;
        cmptx = 0;
    }
    ppm_write_bin(image_extr,fname);
}

/* 
Q-2.10:
Écrire la fonction ppm_get_histrogram qui prendra en paramètre un pointeur sur une structure
ppm et qui retournera un pointeur sur un tableu à deux dimensions (3,=maxvalue =) contenant les
histogrammes des trois composantes RGB des pixels de l’image.
*/
int **ppm_get_histogramme(ppm *image)
{
    int **tab = (int**)malloc(sizeof(int*)*image->max_value);
    for(  int i = 0; i < image->max_value; i++)
    {
        tab[i] = (int*)malloc(sizeof(int)*3);
    }
    for(int i = 0; i < image->max_value; i++)
    {
        tab[i][0] = 0;
        tab[i][1] = 0;
        tab[i][2] = 0;
    }
    for( int i = 0; i < image->height; i++){
        for(int j = 0; j < image->width; j++)
        {
            tab[image->pixel[i][j].r][0]++;
            tab[image->pixel[i][j].g][1]++;
            tab[image->pixel[i][j].b][2]++;
        }
    }
    return tab;
}


/* 
Trouve les valeurs maximales d'un tableau 2d.
*/
int *max_tab_2d( int **tab, int max_ind)
{
    int *max = malloc(sizeof(int)*3);
    max[0] = tab[0][0];
    max[1] = tab[0][2];
    max[2] = tab[0][2];
    for(int i = 0; i < max_ind ; i++)
    {
        if ( max[0] < tab[i][0]) max[0] = tab[i][0];
        if ( max[1] < tab[i][1]) max[1] = tab[i][1];
        if ( max[2] < tab[i][2]) max[2] = tab[i][2];
        
    }
    return max;
}

/* 
Q-2.11:
Écrire la fonction ppm_write_histogram qui prendra en paramètre un pointeur sur une structure
ppm, un pointeur sur une chaine de caractère fname. La fonction devra créer le fichier fname et
l’histogramme de l’image sous la forme de quatre colonnes (la première colonne contiendra les
valeurs de 0 à max_value, les trois colonnes suivantes les données de l’histogramme des trois
composantes correspondant).
*/
void ppm_write_histogram( ppm *image,  char *fname)
{
    int **tab = ppm_get_histogramme(image);
    int *max = max_tab_2d(tab, image->max_value);
    int max_tab_max = max_tab(max,3);
    ppm *histo = ppm_alloc(max_tab_max,image->max_value*3,1);
    for(int i = (image->max_value-1)*3; i >=0; i--)
    {
        for(int j = max_tab_max-1; j >= 0;j-- )
        {
            if (i < image->max_value )
            {
                if (tab[i][0] >= j)
                {
                    histo->pixel[j][i].r = image->max_value;
                }
                else histo->pixel[j][i].r = 0;
                histo->pixel[j][i].g = 0;
                histo->pixel[j][i].b = 0;
            }
            else if ( i <  image->max_value * 2)
            {
                if (tab[i-image->max_value][1] >= j)
                {
                    histo->pixel[j][i].g = image->max_value;
                }
                else histo->pixel[j][i].g = 0;
                histo->pixel[j][i].r = 0;
                histo->pixel[j][i].b = 0;
            }
            else
            {
                if (tab[i-image->max_value*2][2] >= j)
                {
                    histo->pixel[j][i].b = image->max_value;
                }
                else histo->pixel[j][i].b = 0;
                histo->pixel[j][i].g = 0;
                histo->pixel[j][i].r = 0; 
            }
        }
    }
    ppm_write_bin(histo,fname);
}

/* 
Moyenne de 3 entiers.
*/
int moy3(int a, int b, int c)
{
    return (a+b+c)/3;
}


/* 
Q-2.12:
Écrire la fonction ppm_to_pgm qui prendra en paramètre un pointeur sur une structure ppm et un
pointeur sur une structure pgm. La fonction convertira l’image ppm en image pgm.
*/
void ppm_to_pgm(ppm *image, pgm *conv)
{    
    conv = pgm_alloc( image->height,image->width, image->max_value);
    for(int i = 0; i < image->height; i++)
    {
        for(  int j = 0; j < image->width; j++)
        {
            conv->pixel[i][j] = moy3(image->pixel[i][j].r,image->pixel[i][j].g,image->pixel[i][j].b);
        }
    }
    pgm_write_bin(conv,"suuuuu.pgm");
}