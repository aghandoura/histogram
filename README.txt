DESCRITPTION:

  pgm file format is used for an 8 bit grey scale image maniputlaion

  test program use input.pgm file placed in current directory and generate
  an image with equalised histogram output.pgm file

  both input and output pgm image files can be viewed on (Linux) Ubuntu
  using image viewer or gimp, in windows using openseeit image viewer
  https://sourceforge.net/projects/openseeit/

CODE:
  pgm.c and pgm.h are used for pgm file manipulation
and hist_eq.c contains code for histogram equalization

BUILD and RUN:
  test application is compiled using make
to run it ./test
  generated file is named output.pgm.


TEST:
  application is tested on X86_64 ubuntu machine
  compilation: gcc version 4.9.2 (Ubuntu 4.9.2-10ubuntu13)
  histograms of both input and output images are visualised using gimp

References:
 -pgm file description:
  http://netpbm.sourceforge.net/doc/pgm.html

 -reference code for ppm file manipulation modified to work with pgm
  http://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c

 -online tool to conver pgm files:
  https://convertio.co/jpg-pgm/

 -information about histogram equalization and input image file
   https://en.wikipedia.org/wiki/Histogram_equalization
