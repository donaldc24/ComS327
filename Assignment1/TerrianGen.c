#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define true 1
#define false 0

char seed[21][80];

// void genNorthSouthPath() {

// }
int isEmpty(int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4) {
    for (int i = 1; i < 21; i++) {
        for (int j = 1; j < 80; j++) {
            if (seed[r1][c1] != '.' || seed[r2][c2] != '.' || seed[r3][c3] != '.' || seed[r4][c4] != '.') {
                return false;
            }
        }
    }

    return true;
}

void genCenterAndMart() {
    int centerR = (rand() % 10) + 5;
    int centerC = (rand() % 70) + 5;

    seed[centerR][centerC] = 'C';
    seed[centerR+1][centerC] = 'C';
    seed[centerR][centerC+1] = 'C';
    seed[centerR+1][centerC+1] = 'C';

    int martR1 = 0;
    int martC1 = 0;
    int martR2 = 0;
    int martC2 = 0;
    int check = false;

    while (check == false) {
        martR1 = (rand() % 10) + 5;
        martC1 = (rand() % 70) + 5;
        martR2 = martR1 + 1;
        martC2 = martC1 + 1;
        check = isEmpty(martR1, martC1, martR2, martC1, martR1, martC2, martR2, martC2);
    }

    seed[martR1][martC1] = 'M';
    seed[martR2][martC1] = 'M';
    seed[martR1][martC2] = 'M';
    seed[martR2][martC2] = 'M';
}

void genSeed() {
    int i, j;

    for (i = 0; i < 22; i++) {
        seed[i][0] = '%';
        if (i == 0 || i == 21) {
            for (j = 1; j < 81; j++) {
                seed[i][j] = '%';
            } 
        } else {
            for (j = 1; j < 81; j++) {
                seed[i][j] = '.';
            }
        }
        seed[i][80] = '%';
    }

    genCenterAndMart();
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
    srand(time(0));
    genSeed();
    printSeed();
}