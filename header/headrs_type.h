#ifndef _test_h_
#define _test_h_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
/* 
-------------------------
---structure générale----
-------------------------
*/
typedef struct pgm
{
    int height;
    int width;
    int max_value;
    unsigned char **pixel;
} pgm;

typedef struct rgb
{
    unsigned char r, g, b;
} rgb;

typedef struct ppm
{
    int height, width, max_value;
    rgb **pixel;
} ppm;

typedef struct point
{
int x,y;
}point;

typedef struct pile
{
    int x, y;
    struct pile *suite;
} pile;

/* 
-------------------------
----Fonction générale----
-------------------------
*/
int max_tab( int *tab, int max_ind);
int *max_tab_2d( int **tab, int max_ind);
int moy3(int a, int b, int c);

/* 
---------------------------
------------TD1------------
---------------------------
*/
/* 
-------------------------
-------Exercice 1--------
-------------------------
*/
pgm* pgm_alloc(int  height, int width, int max_value);

void pgm_free(pgm *image);

pgm* pgm_read_asc(char *fname);

int pgm_write_asc( pgm *save, char *fname);

pgm* pgm_read_bin(char *fname);

int pgm_write_bin( pgm *save, char  *fname);

pgm *pgm_negative(pgm *entree);

void pgm_extract( char *fname, pgm *image, int dx, int dy, int width, int  height);

int * pgm_get_histogramme(pgm *image);

void pgm_write_histogram( pgm *image,  char *fname);

/* 
---------------------------
--------Exercice 2---------
---------------------------
*/
ppm* ppm_alloc(int  height, int width, int max_value);

void ppm_free(ppm *image);

ppm* ppm_read_asc(char *fname);

int ppm_write_asc( ppm *save, char *fname);

ppm* ppm_read_bin(char *fname);

int ppm_write_bin( ppm *save, char  *fname);

ppm *ppm_negative(ppm *entree);

void ppm_extract( char *fname, ppm *image, int dx, int dy, int width, int  height);

int **ppm_get_histogramme(ppm *image);

void ppm_write_histogram( ppm *image,  char *fname);

void ppm_to_pgm(ppm *image, pgm *conv);



/* 
---------------------------
--------Exercice 3---------
---------------------------
*/
void pgm_extract_blk(pgm *inpgm, double ***blk, int i, int j);

double C( int nu );

void pgm_dct(double ***bloc);

void pgm_quantify( double **blk, double Q[8][8]);

void pgm_zigzag_extract(double **blk, int zgzg[64]);

void pgm_rle(FILE *fd, int zgzg[64]);

void pgm_to_jpeg(pgm  *in_pgm, char *fname);

/* 
---------------------------
--------Exercice 4---------
---------------------------
*/

void blk_extract_pgm(pgm *inpgm, double **blk, int i, int j);

void pgm_dct_rev(double ***bloc);

void pgm_quantify_rev( double **blk, double Q[8][8]);

void pgm_zigzag_extract_rev(double **blk, int zgzg[64]);

void pgm_rle_rev(FILE *fd, int zgzg[64]);

void  jpeg_to_pgm(pgm *in_pgm,char *fname);





/* 
---------------------------
------------TD2------------
---------------------------
*/

/* 
---------------------------
--------Exercice 1---------
---------------------------
*/
double B0( double x );
double B1( double x );
double B2( double x );
double B3( double x );

unsigned char interpolation_pgm( pgm *image, double x, double y );
rgb interpolation_ppm(ppm *image, double x, double y);
pgm *rotation_pgm(pgm *image, double theta, int x0, int y0);
ppm *rotation_ppm(ppm *image, double theta, int x0, int y0);
ppm *zoom(ppm *image, double lambda, int x0, int y0, int Dx, int Dy);
ppm *zoom_bis_CGPT(ppm *image, double lambda, int x0, int y0, int Dx, int Dy);
ppm *shear(ppm *image, double cx, double cy, int Dx, int Dy);

/* 
---------------------------
--------Exercice 2---------
---------------------------
*/
void multiply_matrices(double A[6][6], double B[6], double result[6]);
void pseudo_inverse(double X[6][6], double X_inv[6][6]);
void get_affine_transformation(point A[3], point B[3]);
ppm *affine_transformation(ppm *image, double *coeff_transformation);


/* 
---------------------------
------------TD3------------
---------------------------
*/

/* 
---------------------------
--------Exercice 1---------
---------------------------
*/
unsigned char max_pgm(pgm *image);
pgm *naive_x(pgm *image);
pgm *naive_y(pgm *image);
pgm *naive_edge_detector(pgm *image);
pgm *sobel_edge_detector(pgm *image);
void gaussian_blur(pgm *image, double sigma, int n);
int gaussian_filter(pgm *image, int x, int y, double **kernel, int n);
double **gradiant_angle(pgm *grad_x, pgm *grad_y, pgm *norm);


/* 
---------------------------
--------prog pile----------
---------------------------
*/
pile* empiler(pile **p, int x, int y);
pile* depiler(pile *p, int **valeur_retour);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
int rechercher(pile *p, int x,  int y);
void afficher_pile(pile *p);

/*                                                          
---------------------------
------prog principal-------
---------------------------
*/

int main( void  );

#endif // _test_h_