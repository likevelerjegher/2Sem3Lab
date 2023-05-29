#ifndef INC_3LAB_STRUCTURES_H
#define INC_3LAB_STRUCTURES_H
#pragma pack(1)
typedef struct Pixel{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
}Pixel;
typedef struct BMPFileHeader{
    char ID[2];
    unsigned int fileSize;
    unsigned char unUsed[4];
    unsigned int pixelOffset;
}BMPFileHeader;

typedef struct BMPImageHeader{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short colorPlanes;
    unsigned short bitsPerPixel;
    unsigned int pixelCompression;
    unsigned int dataSize;
    unsigned int pWidth;
    unsigned int pHeight;
    unsigned int numberOfColors;
    unsigned int importantColors;
}BMPImageHeader;

typedef struct BMPImage{
    BMPFileHeader fileHeader;
    BMPImageHeader imageHeader;
    Pixel **pixels;
}BMPImage;
#pragma pop
#endif
