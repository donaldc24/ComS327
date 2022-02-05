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
    int row = (rand() % 10) + 5;
    int col = (rand() % 70) + 5;
    int origCol = col;
    int rows[8];
    int count = 0;

    while (count <= 5 && seed[row][col] == '.' && row > 4 && row < 16) {
        rows[count] = row;
        seed[row][col] = ':';
        row = row + 1;
        int count2 = 0;
        col = origCol;
        while (count2 < 8 && seed[row][col] == '.' && col > 4 && row < 76) {
            if (seed[row][col] == '.' && col > 4 && col < 76) {
                seed[row][col] = ':';
            }
            col = col + 1;
            count2++;
        }
        count++;
    }

    if (count < 3) {
        for (int i = 0; i < 8; i++) {
            if (rows[i] != 0 && rows[i] > 4 && rows[i] < 16) {
                seed[rows[i]][col] = '.'; 
            } else {
                break;
            }
        }
        genTallGrass();
      }
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

void genRandomObj() { 
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j < 79; j++) {
            if (seed[i][j] == '.') {
                int num = rand() % 50;
                if (num == 3) {
                    seed[i][j] = '"';
                } else if (num == 8) {
                    seed[i][j] = '%';
                }
            }
        }
    }
}

void genSeed() {
    int i, j;

    for (i = 0; i < 21; i++) {
        seed[i][0] = '%';
        if (i == 0 || i == 20) {
            for (j = 0; j < 80; j++) {
                seed[i][j] = '%';
            } 
        } else {
            for (j = 1; j < 80; j++) {
                seed[i][j] = '.';
            }
        }
        seed[i][79] = '%';
    }
    
    genTallGrass();
    genTallGrass();

    int num = rand() % 20;
    if (num == 3 || num == 7) {
        genNorthSouthPath();
        genNorthSouthPath();
        genNorthSouthPath();
        genTallGrass();
    } else if (num == 13) {
        genNorthSouthPath();
        genNorthSouthPath();
        genTallGrass();
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
        genTallGrass();
    } else {
        genEastWestPath();
    }
    genTallGrass();
    genCenterAndMart();
    genRandomObj();
}

void printSeed() {
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 80; j++) {
            if (seed[i][j] == '"') {
                printf("\033[0;33m%c", seed[i][j]);
            } else if (seed[i][j] == '#') {
                printf("\033[0;31m%c", seed[i][j]);
            } else if (seed[i][j] == ':' || seed[i][j] == '.') {
                printf("\033[0;32m%c", seed[i][j]);
            } else if (seed[i][j] == 'C' || seed[i][j] == 'M') {
                printf("\033[0;35m%c", seed[i][j]);
            } else {
                printf("\033[0;37m%c", seed[i][j]);
            }
        }
        printf("\033[0;37m\n");
    }
}

int main(void) {
    srand(time(0));
    genSeed();
    printSeed();
    char input;
    int x, y;

    while (input != 'q') {
        scanf("%c", &input);
        switch(input) {
            case 'n':
                printf("Hello N\n");
                break;
            case 's':
                printf("Hello S\n");
                break;
            case 'e':
                printf("Hello E\n");
                break;
            case 'w':
                printf("Hello W\n");
                break;
            case 'f':
                scanf("%d %d", &x, &y);
                printf("%d %d\n", x, y);
                break;
        }
    }

    return 0;
}