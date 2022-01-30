#include <stdio.h>

char seed[21][80];

void genNorthSouthPath() {

}

void genSeed() {
    int i, j;

    for (i = 0; i < 22; i++) {
        seed[i][0] = '%';
        if (i == 0 || i == 21) {
            for (j = 1; j < 80; j++) {
                seed[i][j] = '%';
            } 
        } else {
            for (j = 1; j < 80; j++) {
                seed[i][j] = '.';
            }
        }
        seed[i][80] = '%';
    }
}

void printSeed() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 81; j++) {
            printf("%c", seed[i][j]);
        }
        printf("\n");
    }
}

void main() {
    genSeed();
    printSeed();
}