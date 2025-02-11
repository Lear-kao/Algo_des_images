#ifndef _test_h_
#define _test_h_

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
/* 
---------------------------
------prog principal-------
---------------------------
*/

int main( void  );

#endif // _test_h_