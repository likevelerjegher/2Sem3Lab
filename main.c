#include "menuFunctions.h"
#include "fileFunctions.h"
#include "structures.h"

int main() {
    printf("\033[0;34mEnter BMP image path: \033[0m");
    char *filePath = NULL;
    getStr(&filePath);
    BMPImage *image = readBMPFile(filePath);
    menuInterface(image);
    return 0;
}
