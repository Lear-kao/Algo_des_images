#include <stdio.h>
#include <stdlib.h>


/*
Q-1.1:
Ecrire une structure pgm qui contiendra la hauteur (height), la largeur (width) la valeur maximale
de codage des pixels (max_value) ainsi qu’un pointeur sur un tableau à deux dimensions de caractères
non-signés (pixels).
*/
typedef struct pgm
{
    int height;
    int width;
    int max_value;
    unsigned char **pixel;
} pgm;


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
    image->pixel = malloc(sizeof(unsigned char*)*width);
    for(int i = 0; i < width; i++)
    {
        image->pixel[i] = malloc(sizeof(unsigned char)*height);
    }
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
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
    fscanf(file,"%d",&height);
    fscanf(file,"%d",&width);
    fscanf(file,"%d",&max_value);
    pgm *image = pgm_alloc(height,width,max_value);
    for(int i = 0; i < width; i++)
    {
        for( int j =0; j < height; j++)
        {
            fscanf(file, "%s",&(image->pixel[i][j]));
            printf("%s",*(image->pixel[i][j]));
        }
        printf("\n");
    }
    return image;
}

int main( void )
{
    char filename[14] = "eye_s_asc.pgm";
    pgm *image = pgm_read_asc(filename);
    printf("%d",image->height);
    
    return 0;
}