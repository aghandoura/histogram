#include<stdio.h>
#include<stdlib.h>

#include "hist_eq.h"

#define FIXED_POINT_SHIFT  16

/* fixedpoint shift is used to avoid 
 * floating point operation overhead
 * histogram equalization is done in place */
int apply_histogram_equalization(unsigned char *data, unsigned int size)
{
  unsigned int hist[256];
  unsigned int eqHist[256];
  unsigned int histIndex = 0;
  unsigned int pixIndex = 0;
  //shifted histogram value at pos i
  unsigned long Ni = 0;
  //shifted equalized histogram value at pos i
  unsigned long Kn  = 0;


  if (!data)
  {
    printf("%s invalid data pointer \n", __FUNCTION__);
    return -1;
  }

  if (size == 0)
  {
    printf("%s invalid size\n", __FUNCTION__);
    return -1;
  }

  for (histIndex = 0; histIndex < 256; histIndex++)
  {
    hist[histIndex] = 0;
  }

  /* orginal data histogram */
  for (pixIndex = 0; pixIndex < size; pixIndex++)
  {
    hist[data[pixIndex]] += 1;
  }
  
  /* generate equalized histogram */
  for (histIndex=0; histIndex<256; histIndex++)
  {
    Ni = ((unsigned long)hist[histIndex] << FIXED_POINT_SHIFT);
    Kn += 256 * (Ni/(unsigned long)size) ;
    eqHist[histIndex] = ((unsigned long)(Kn>>FIXED_POINT_SHIFT)) & 0xff ;
  }

  /* update data */
  for (pixIndex=0; pixIndex < size; pixIndex++)
  {
    data[pixIndex] = ((unsigned char)(eqHist[data[pixIndex]])) & 0xff;
  }

  return 0;
}
