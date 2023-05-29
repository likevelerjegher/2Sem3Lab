#include "fileFunctions.h"
BMPImage *readBMPFile(const char *filePath){
    BMPImage *image = malloc(sizeof(BMPImage));
    FILE *initialFile = fopen(filePath, "rb");
    if (initialFile == NULL || !initialFile){
        printf("Can't open the file.\n");
        free(image);
        return NULL;
    }
    fread(&image->fileHeader, sizeof(BMPFileHeader), 1, initialFile);
    if (image->fileHeader.ID[0] != 'B' || image->fileHeader.ID[1] != 'M') {
        printf("Error, invalid format.\n");
        fclose(initialFile);
        free(image);
        return NULL;
    }
    fread(&image->imageHeader, sizeof(BMPImageHeader), 1, initialFile);
    unsigned int width = image->imageHeader.width;
    unsigned int height = image->imageHeader.height;
    if(image->imageHeader.bitsPerPixel != 24){
        printf("Cannot process the file: not 24 bpp.");
        free(image);
        fclose(initialFile);
        return NULL;
    }
    if (image->imageHeader.pixelCompression) {
        printf("Cannot process the file: Compression not supported.");
        free(image);
        fclose(initialFile);
        return NULL;
    }
    image->pixels = malloc(sizeof(Pixel *) * height);
    for (int i = 0; i < height; i++) {
        image->pixels[i] = malloc(sizeof(Pixel) * width);
    }

    unsigned int offset = image->fileHeader.pixelOffset;
    fseek(initialFile, offset, SEEK_SET);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fread(&image->pixels[i][j], sizeof(Pixel), 1, initialFile);
        }
    }
    fclose(initialFile);
    return image;
}
void writeBMP(const BMPImage *image){
    FILE *outputFile = fopen("editedFile.bmp", "wb");
    if (outputFile == NULL) {
        printf("Error: Failed to open output file.");
        return;
    }
    unsigned int width = image->imageHeader.width;
    unsigned int height = image->imageHeader.height;
    fwrite(&image->fileHeader, sizeof(image->fileHeader), 1, outputFile);
    fwrite(&image->imageHeader, sizeof(image->imageHeader), 1, outputFile);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fwrite(&image->pixels[i][j], sizeof(Pixel), 1, outputFile);
        }
    }
    unsigned int padding = (4 - (width * 3) % 4) % 4;
    for (int j = 0; j < padding; j++) {
        fputc(0x00, outputFile);
    }
    fclose(outputFile);
}
void freeStructure(BMPImage *image){
    if (image->pixels)
        free(image->pixels);
    free(image);
}