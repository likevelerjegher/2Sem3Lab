#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#ifndef INC_3LAB_FILEFUNCTIONS_H
#define INC_3LAB_FILEFUNCTIONS_H

BMPImage *readBMPFile(const char *filePath);
void writeBMP(const BMPImage *image);

void freeStructure(BMPImage *image);
#endif
