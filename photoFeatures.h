#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structures.h"
#ifndef INC_3LAB_PHOTOFEATURES_H
#define INC_3LAB_PHOTOFEATURES_H

void convertBlackAndWhite(const BMPImage *image, unsigned int  height, unsigned int  width);
void convertNegative(const BMPImage *image, unsigned int  height, unsigned int  width);

int compareForMedian(const void *a, const void *b);
void medianFilter(const BMPImage *image, int frame, unsigned int height, unsigned int width);

void gammaCorrection(const BMPImage *image, unsigned int  height, unsigned int  width, double gamma);

#endif
