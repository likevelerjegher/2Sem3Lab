#include "menuFunctions.h"
#include "photoFeatures.h"
#include "structures.h"
#include "fileFunctions.h"

void functionsSelection(const BMPImage *image, int choice){
    unsigned int height = image->imageHeader.height;
    unsigned int width = image->imageHeader.width;
    switch (choice) {
        case 1:
            convertNegative(image, height, width);
            break;
        case 2:
            convertBlackAndWhite(image, height, width);
            break;
        case 3: {
            int median;
            printf("\nEnter the FRAME size (ONE positive integer number): ");
            median = methodOfInputMedian();
            medianFilter(image, median, height, width);
        }
            break;
        case 4: {
            double gamma;
            printf("\nEnter the GAMMA value (more of equal to zero): ");
            gamma = methodOfInputGamma();
            gammaCorrection(image, height, width, gamma);
        }
            break;
        default: {
            printf("");
        }
    }
}
void menuInterface(BMPImage *image){
    if (image == NULL && !image){
        printf("\n\033[0;31mFinishing the program.\n\033[0m");
        free(image);
        exit(0);
    }
    printf("\n\033[0;31mChoose what to do with the IMAGE:\033[0m"
           "\n1. Converting to negative."
           "\n2. Converting to monochrome."
           "\n3. Implementing median filtering."
           "\n4. Implementing gamma correction."
           "\n\033[0;33m(Type 99 to exit the program)\033[0m\n"
           "\n\033[0;32mDecision: \033[0m");
    int choice;
    choice = methodOfInput(4);
    if (choice == 99){
        printf("\n\033[0;31mFinishing the program.\n\033[0m");
        freeStructure(image);
        exit(0);
    }
    functionsSelection(image, choice);
    writeBMP(image);
    printf("\n\033[0;34mThe feature has been implemented.\033[0m\n");

}
int methodOfInput(int size){
    int num;
    while (scanf("%d", &num) != 1 || (!(num >=1 && num <=size)&& num != 99) || getchar() != '\n') {
        printf("Try better:\n");
        rewind(stdin);
    }
    return num;
}
double methodOfInputGamma(){
    double gammaVal;
    while (!scanf("%lf", &gammaVal) || gammaVal <= 0.0 || getchar() != '\n') {
        printf("Try better (more or equal to zero):\n");
        rewind(stdin);
    }
    return gammaVal;
}
int methodOfInputMedian(){
    int medianVal;
    while (!scanf("%d", &medianVal)|| medianVal <= 0 || getchar() != '\n') {
        printf("Try better (choose positive INTEGER number):\n");
        rewind(stdin);
    }
    return medianVal;
}
void getStr(char **string){
    int size = 0;
    int realSize = 16;
    *string = (char *)malloc(realSize * sizeof(char));
    rewind(stdin);
    char check;
    while (1) {
        check = (char)getchar();
        if (check == '\n') {
            if (size + 1 < realSize) {
                *string = (char *) realloc(*string, (size + 1) * sizeof(char));
            }
            (*string)[size] = '\0';
            return;
        }
        (*string)[size] = check;
        size++;
        if (size + 1 == realSize) {
            realSize *= 2;
            *string = (char *) realloc(*string, realSize * sizeof(char));
        }
    }
}