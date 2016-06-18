#ifndef PGM_H
#define PGM_H

#define MAX_GREYSCALE_VALUE 255

typedef struct {
     int            x, y;
     unsigned char *data;
} PGMImage;


PGMImage *readPGM(const char *filename);
int       writePGM(const char *filename, PGMImage *img);
void      freePGM(PGMImage *img);

#endif
