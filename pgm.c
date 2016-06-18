#include<stdio.h>
#include<stdlib.h>

#include "pgm.h"

PGMImage *readPGM(const char *filename)
{
  char buff[16];
  PGMImage *img;
  FILE *fp;
  int c, max_greyscale_value;

  fp = fopen(filename, "rb");
  if (!fp)
  {
       fprintf(stderr, "Unable to open file '%s'\n", filename);
       return NULL;
  }

  /* read image format */
  if (!fgets(buff, sizeof(buff), fp))
  {
       perror(filename);
       return NULL;
  }

  /* check the image format */
  if (buff[0] != 'P' || buff[1] != '5')
  {
       fprintf(stderr, "Invalid PGM image format (must be 'P5')\n");
       return NULL;
  }

  /* alloc memory for image */
  img = (PGMImage *)malloc(sizeof(PGMImage));
  if (!img)
  {
       fprintf(stderr, "Unable to allocate memory\n");
       return NULL;
  }

  /* check for comments */
  c = getc(fp);
  while (c == '#')
  {
    while (getc(fp) != '\n') ;
    c = getc(fp);
  }

  ungetc(c, fp);
  /* read image size information */
  if (fscanf(fp, "%d %d", &img->x, &img->y) != 2)
  {
    free(img);
    fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
    return NULL;
  }

  /* read max greyscal value */
  if (fscanf(fp, "%d", &max_greyscale_value) != 1)
  {
    fprintf(stderr, "Invalid max greyscale value(error loading '%s')\n", filename);
    free(img);
    return NULL;
  }

  /* check for 8 bit format */
  if (max_greyscale_value != MAX_GREYSCALE_VALUE)
  {
    fprintf(stderr, "'%s' does not have 8 bits greyscale \n", filename);
    free(img);
    return NULL;
  }

  while (fgetc(fp) != '\n') ;

  /* memory allocation for pixel data */
  img->data = (unsigned char*)malloc(img->x * img->y * sizeof(unsigned char));

  if (!img->data)
  {
    fprintf(stderr, "Unable to allocate memory\n");
    free(img);
    return NULL;
  }

  /* read pixel data from file */
  if (fread(img->data, 1 * img->x, img->y, fp) != img->y)
  {
    fprintf(stderr, "Error loading image '%s'\n", filename);
    free(img);
    free(img->data);
    return NULL;
  }

  fclose(fp);
  return img;
}

int writePGM(const char *filename, PGMImage *img)
{
  FILE *fp;

  fp = fopen(filename, "wb");
  if (!fp)
  {
    fprintf(stderr, "Unable to open file '%s'\n", filename);
    return -1;
  }

  if (!img)
  {
    fprintf(stderr, "write failed invalid data\n");
    return -1;
  }

  if (!img->data)
  {
    fprintf(stderr, "write failed invalid data\n");
    return -1;
  }

  /* write the header file
   * image format */
  fprintf(fp, "P5\n");

  /* image size */
  fprintf(fp, "%d %d\n",img->x,img->y);

  /* max greyscale value */ 
  fprintf(fp, "%d\n",MAX_GREYSCALE_VALUE);

  /* write pixel data */
  fwrite(img->data, 1 * img->x, img->y, fp);
  fclose(fp);

  return 0;
}


void freePGM(PGMImage *img)
{
  if (img)
  {
    if (img->data)
    {
      free(img->data);
    }
    free(img);
  }
}
