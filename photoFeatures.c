#include "photoFeatures.h"
#include "menuFunctions.h"
#include "structures.h"
void convertNegative(const BMPImage *image, unsigned int height, unsigned int width){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            Pixel pixel = image->pixels[i][j];
            pixel.red = 255 - pixel.red;
            pixel.green = 255 - pixel.green;
            pixel.blue = 255 - pixel.blue;
            image->pixels[i][j] = pixel;
        }
    }
}
void convertBlackAndWhite(const BMPImage *image, unsigned int height, unsigned int width){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            Pixel pixel = image->pixels[i][j];
            char grayscalePixel = (char)((0.3 * pixel.red) + pixel.blue * 0.11 + pixel.green * 0.59);
            pixel.red = grayscalePixel;
            pixel.green = grayscalePixel;
            pixel.blue = grayscalePixel;
            image->pixels[i][j] = pixel;
        }
    }
}
void gammaCorrection(const BMPImage *image, unsigned int height, unsigned int  width, double gamma){
    double invertedGamma = gamma;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            Pixel pixel = image->pixels[i][j];
            double red = pow((double)image->pixels[i][j].red / 255.0, invertedGamma) * 255.0;
            double green = pow((double)image->pixels[i][j].green / 255.0, invertedGamma) * 255.0;
            double blue = pow((double)image->pixels[i][j].blue / 255.0, invertedGamma) * 255.0;
            pixel.red = (char)red;
            pixel.green = (char)green;
            pixel.blue = (char)blue;
            image->pixels[i][j] = pixel;
        }
    }
}
int compareForMedian(const void *a, const void *b){
    const int *firstObj = (const int *)a;
    const int *secondObj = (const int *)b;
    return (*firstObj > *secondObj) - (*firstObj < *secondObj);
}
void medianFilter(const BMPImage *image, int frame, unsigned int height, unsigned int width){
    if (frame % 2 == 0) {
        frame++;
    }
    int padding = frame / 2;

    Pixel **paddingPixels = malloc(sizeof(Pixel *) * (height + (2 * padding)));
    for (int i = 0; i < height + 2 * padding; i++) {
        paddingPixels[i] = malloc(sizeof(Pixel) * (width + (2 * padding)));
    }
    //copying pixels
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            paddingPixels[i + padding][j + padding] = image->pixels[i][j];
        }
    }
    //pad edges with border pixels
    for (int i = 0; i < padding; i++) {
        for (int j = 0; j < width + 2 * padding; j++) {
            paddingPixels[i][j] = paddingPixels[padding][j];
            paddingPixels[height + 2 * padding - i - 1][j] = paddingPixels[height + padding - 1][j];
        }
    }
    for (int i = 0; i < height + 2 * padding; i++) {
        for (int j = 0; j < padding; j++) {
            paddingPixels[i][j] = paddingPixels[i][padding];
            paddingPixels[i][width + 2 * padding - j - 1] = paddingPixels[i][width + padding - 1];
        }
    }
    //median filter for each color
    int frameSize = frame * frame;

    for (int i = padding; i < height + padding; i++) {
        for (int j = padding; j < width + padding; j++) {
            unsigned int r[frameSize];
            unsigned int g[frameSize];
            unsigned int b[frameSize];
            memset(r, 0, frameSize * sizeof(unsigned int));
            memset(g, 0, frameSize * sizeof(unsigned int));
            memset(b, 0, frameSize * sizeof(unsigned int));

            int iterator = 0;
            for (int seci = -padding; seci <= padding; seci++) {
                for (int secj = -padding; secj <= padding; secj++) {
                    r[iterator] = paddingPixels[i + seci][j + secj].red;
                    g[iterator] = paddingPixels[i + seci][j + secj].green;
                    b[iterator] = paddingPixels[i + seci][j + secj].blue;
                    iterator++;
                }
            }
            //sort pixels
            qsort(r, frameSize, sizeof(unsigned int), compareForMedian);
            qsort(g, frameSize, sizeof(unsigned int), compareForMedian);
            qsort(b, frameSize, sizeof(unsigned int), compareForMedian);
            //set median values
            image->pixels[i - padding][j - padding].red = r[frameSize / 2];
            image->pixels[i - padding][j - padding].green = g[frameSize / 2];
            image->pixels[i - padding][j - padding].blue = b[frameSize / 2];
        }
    }

    for (int i = 0; i < height + 2 * padding; i++) {
        free(paddingPixels[i]);
    }
    free(paddingPixels);
}