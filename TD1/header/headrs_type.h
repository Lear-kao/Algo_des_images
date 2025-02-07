#ifndef _test_h_
#define _test_h_

typedef struct pgm
{
    int height;
    int width;
    int max_value;
    unsigned char **pixel;
} pgm;

pgm* pgm_alloc(int  height, int width, int max_value);

void pgm_free(pgm *image);

int pgm_write_asc( pgm *save, char *fname);

pgm* pgm_read_bin(char *fname),


int main( void  );

#endif // _test_h_