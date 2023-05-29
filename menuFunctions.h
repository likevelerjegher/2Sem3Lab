#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

#ifndef INC_3LAB_FUNCTIONS_H
#define INC_3LAB_FUNCTIONS_H
void getStr(char **string);
void menuInterface(BMPImage *image);

int methodOfInput(int size);
double methodOfInputGamma();
int methodOfInputMedian();

void functionsSelection(const BMPImage *image, int choice);
#endif
