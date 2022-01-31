#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define true 1
#define false 0

char seed[21][80];

void genNorthSouthPath() {
    int start = (rand() % 12) + 4;
    seed[start][0] = '#';

    int loc[] = {start, 1};
    seed[loc[0]][loc[1]] = '#';

    while (loc[1] < 79) {
        int num = rand() % 10;

        if (num < 6) {
            loc[1] = loc[1] + 1;
        } else if (num >= 6 && num <= 7) {
            loc[0] = loc[0] - 1;
            if (loc[0] < 3) {
                loc[0] = loc[0] + 1;
            }
        } else {
            loc[0] = loc[0] + 1;
            if (loc[0] > 17) {
                loc[0] = loc[0] - 1;
            }
        }
        seed[loc[0]][loc[1]] = '#';
    }
}

void genEastWestPath() {
    int start = (rand() % 70) + 4;
    seed[0][start] = '#';

    int loc[] = {1, start};
    seed[loc[0]][loc[1]] = '#';

    while (loc[0] < 20) {
        int num = rand() % 10;

        if (num < 6) {
            loc[0] = loc[0] + 1;
        } else if (num >= 6 && num <= 7) {
            loc[1] = loc[1] - 1;
            if (loc[1] < 3) {
                loc[1] = loc[1] + 1;
            }
        } else {
            loc[1] = loc[1] + 1;
            if (loc[1] > 73) {
                loc[1] = loc[1] - 1;
            }
        }
        seed[loc[0]][loc[1]] = '#';
    }
}

int isEmpty(int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4, int type) {
    int count = 0;
    if (type == 1) {
        int surronding[] = {
        seed[r1-1][c1], seed[r1][c1-1],
        seed[r2+1][c1], seed[r2][c1-1],
        seed[r1-1][c2], seed[r1][c2+1],
        seed[r2+1][c2], seed[r2][c2+1]
        };

        for (int k = 0; k < 12; k++) {
            if (surronding[k] == '#') {
                count++;     
            }
        }
    }


    for (int i = 1; i < 21; i++) {
        for (int j = 1; j < 80; j++) {
            if (seed[r1][c1] != '.' || seed[r2][c2] != '.' || seed[r3][c3] != '.' || seed[r4][c4] != '.') {
                return false;
            }
        }
    }

    if (type == 1 && count > 0) {
        return true;
    } else {
        return false;
    }

}

void genTallGrass() {
    // int row = (rand() % 10) + 5;
    // int col = (rand() % 70) + 5;
    // int check = false;

    // int posRow[] = {1, 0, -1};
    // int posCol[] = {1, 0, -1};

    // int area = (rand() % 5) + 2;

    // while (seed[row][col] != '.') {
    //     row = (rand() % 10) + 5;
    //     col = (rand() % 70) + 5;
    // }
    // seed[row][col] = ':';

    // //for (int k = 0; k < 3; k++) {
    //     for (int i = 0; i < 3; i++) {
    //         for (int j = 0; j < 3; j++) {
    //             int row1 = row + posRow[i];
    //             int col1 = col + posCol[j];

    //             while (seed[row1][col1] != '.') {
    //                 row1 = row + posRow[i];
    //                 col1 = col + posCol[j];
    //             }
    //             row = row1;
    //             col = col1;
    //             seed[row][col] = ':';
    //             break;
    //         }
    //     }
    // //}
}

void genCenterAndMart() {
    int centerR1 = 0;
    int centerC1 = 0;
    int centerR2 = 0;
    int centerC2 = 0;
    int check = false;

    while (check == false) {
        centerR1 = (rand() % 10) + 5;
        centerC1 = (rand() % 70) + 5;
        centerR2 = centerR1 + 1;
        centerC2 = centerC1 + 1;
        check = isEmpty(centerR1, centerC1, centerR2, centerC1, centerR1, centerC2, centerR2, centerC2, 1);
    }

    seed[centerR1][centerC1] = 'C';
    seed[centerR2][centerC1] = 'C';
    seed[centerR1][centerC2] = 'C';
    seed[centerR2][centerC2] = 'C';

    int martR1 = 0;
    int martC1 = 0;
    int martR2 = 0;
    int martC2 = 0;
    check = false;

    while (check == false) {
        martR1 = (rand() % 10) + 5;
        martC1 = (rand() % 70) + 5;
        martR2 = martR1 + 1;
        martC2 = martC1 + 1;
        check = isEmpty(martR1, martC1, martR2, martC1, martR1, martC2, martR2, martC2, 1);
    }

    seed[martR1][martC1] = 'M';
    seed[martR2][martC1] = 'M';
    seed[martR1][martC2] = 'M';
    seed[martR2][martC2] = 'M';
}

void genSeed() {
    int i, j;

    for (i = 0; i < 21; i++) {
        seed[i][0] = '%';
        if (i == 0 || i == 20) {
            for (j = 1; j < 80; j++) {
                seed[i][j] = '%';
            } 
        } else {
            for (j = 1; j < 80; j++) {
                seed[i][j] = '.';
            }
        }
        seed[i][79] = '%';
    }

    int num = rand() % 20;
    if (num == 3 || num == 7) {
        genNorthSouthPath();
        genNorthSouthPath();
    } else {
        genNorthSouthPath();
    }

    num = rand() % 20;
    if (num == 3 || num == 12) {
        genEastWestPath();
        genEastWestPath();
    } else if (num == 7) {
        genEastWestPath();
        genEastWestPath();
        genEastWestPath();
    } else {
        genEastWestPath();
    }
    
    genCenterAndMart();
    genTallGrass();
}

void printSeed() {
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 80; j++) {
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