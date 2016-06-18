#include<stdio.h>
#include<stdlib.h>

#include "hist_eq.h"
#include "pgm.h"


int main(int argc, const char* argv[])
{
  PGMImage *image;

  image = readPGM("input.pgm");
  if(!image)
  {
    fprintf(stderr, "read pgm file failed \n");
    exit(1);
  }

  if (apply_histogram_equalization(image->data, (image->x * image->y)) != 0)
  {
    fprintf(stderr, "histogram equalization failed \n");
    freePGM(image);
    exit(1);
  }

  if (writePGM("output.pgm",image) !=0)
  {
    fprintf(stderr, "writing pgm file failed \n");
    freePGM(image);
    exit(1);
  }

  freePGM(image);
  printf("press return to exit...");
  getchar();
  return 0;
}

