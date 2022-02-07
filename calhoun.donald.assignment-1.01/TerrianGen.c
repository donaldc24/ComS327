#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define true 1
#define false 0

char world[21][80][399][399];

void genNorthSouthPath(int worldX, int worldY) {
    int start = (rand() % 12) + 4;
    world[start][0][worldX][worldY] = '#';

    int loc[] = {start, 1};
    world[loc[0]][loc[1]][worldX][worldY] = '#';

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
        world[loc[0]][loc[1]][worldX][worldY] = '#';
    }
}

void genEastWestPath(int worldX, int worldY) {
    int start = (rand() % 70) + 4;
    world[0][start][worldX][worldY] = '#';

    int loc[] = {1, start};
    world[loc[0]][loc[1]][worldX][worldY] = '#';

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
        world[loc[0]][loc[1]][worldX][worldY] = '#';
    }
}

int isEmpty(int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4, int type, int worldX, int worldY) {
    int count = 0;
    if (type == 1) {
        int surronding[] = {
        world[r1-1][c1][worldX][worldY], world[r1][c1-1][worldX][worldY],
        world[r2+1][c1][worldX][worldY], world[r2][c1-1][worldX][worldY],
        world[r1-1][c2][worldX][worldY], world[r1][c2+1][worldX][worldY],
        world[r2+1][c2][worldX][worldY], world[r2][c2+1][worldX][worldY]
        };

        for (int k = 0; k < 12; k++) {
            if (surronding[k] == '#') {
                count++;     
            }
        }
    }


    for (int i = 1; i < 21; i++) {
        for (int j = 1; j < 80; j++) {
            if (world[r1][c1][worldX][worldY] != '.' || world[r2][c2][worldX][worldY] != '.' || world[r3][c3][worldX][worldY] != '.' || world[r4][c4][worldX][worldY] != '.') {
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

void genTallGrass(int worldX, int worldY) {
    int row = (rand() % 10) + 5;
    int col = (rand() % 70) + 5;
    int origCol = col;
    int rows[8];
    int count = 0;

    while (count <= 5 && world[row][col][worldX][worldY] == '.' && row > 4 && row < 16) {
        rows[count] = row;
        world[row][col][worldX][worldY] = ':';
        row = row + 1;
        int count2 = 0;
        col = origCol;
        while (count2 < 8 && world[row][col][worldX][worldY] == '.' && col > 4 && row < 76) {
            if (world[row][col][worldX][worldY] == '.' && col > 4 && col < 76) {
                world[row][col][worldX][worldY] = ':';
            }
            col = col + 1;
            count2++;
        }
        count++;
    }

    if (count < 3) {
        for (int i = 0; i < 8; i++) {
            if (rows[i] != 0 && rows[i] > 4 && rows[i] < 16) {
                world[rows[i]][col][worldX][worldY] = '.'; 
            } else {
                break;
            }
        }
        genTallGrass(worldX, worldY);
      }
}

void genCenterAndMart(int worldX, int worldY) {
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
        check = isEmpty(centerR1, centerC1, centerR2, centerC1, centerR1, centerC2, centerR2, centerC2, 1, worldX, worldY);
    }

    world[centerR1][centerC1][worldX][worldY] = 'C';
    world[centerR2][centerC1][worldX][worldY] = 'C';
    world[centerR1][centerC2][worldX][worldY] = 'C';
    world[centerR2][centerC2][worldX][worldY] = 'C';

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
        check = isEmpty(martR1, martC1, martR2, martC1, martR1, martC2, martR2, martC2, 1, worldX, worldY);
    }

    world[martR1][martC1][worldX][worldY] = 'M';
    world[martR2][martC1][worldX][worldY] = 'M';
    world[martR1][martC2][worldX][worldY] = 'M';
    world[martR2][martC2][worldX][worldY] = 'M';
}

void genRandomObj(int worldX, int worldY) { 
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j < 79; j++) {
            if (world[i][j][worldX][worldY] == '.') {
                int num = rand() % 50;
                if (num == 3) {
                    world[i][j][worldX][worldY] = '"';
                } else if (num == 8) {
                    world[i][j][worldX][worldY] = '%';
                }
            }
        }
    }
}

void genSeed(int worldX, int worldY) {
    int i, j;

    for (i = 0; i < 21; i++) {
        world[i][0][worldX][worldY] = '%';
        for (j = 0; j < 80; j++) {
            world[20][j][worldX][worldY] = '%';
            world[0][j][worldX][worldY] = '%';
        }
        world[i][79][worldX][worldY] = '%';
    }
    
    genTallGrass(worldX, worldY);
    genTallGrass(worldX, worldY);
    genTallGrass(worldX, worldY);
    genTallGrass(worldX, worldY);
    genNorthSouthPath(worldX, worldY);
    genEastWestPath(worldX, worldY);
    genCenterAndMart(worldX, worldY);
    genRandomObj(worldX, worldY);
}

void printSeed(int worldX, int worldY) {
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 80; j++) {
            if (world[i][j][worldX][worldY] == '"') {
                printf("\033[0;33m%c", world[i][j][worldX][worldY]);
            } else if (world[i][j][worldX][worldY] == '#') {
                printf("\033[0;31m%c", world[i][j][worldX][worldY]);
            } else if (world[i][j][worldX][worldY] == ':' || world[i][j][worldX][worldY] == '.') {
                printf("\033[0;32m%c", world[i][j][worldX][worldY]);
            } else if (world[i][j][worldX][worldY] == 'C' || world[i][j][worldX][worldY] == 'M') {
                printf("\033[0;35m%c", world[i][j][worldX][worldY]);
            } else {
                printf("\033[0;37m%c", world[i][j][worldX][worldY]);
            }
        }
        printf("\033[0;37m\n");
    }
}

int main(void) {
    char emptySeed[21][80];
    for (int i = 0; i < 399; i++) {
        for (int j = 0; j < 399; j++) {
            for (int k = 0; k < 21; k++) {
                for (int l = 0; l < 80; l++) {
                    world[k][l][i][j] = '.';
                }
            }
        }
    }

    int x = 199;
    int y = 199;
    srand(time(0));
    genSeed(x, y);
    printSeed(x, y);
    char input;

    while (input != 'q') {
        scanf("%c", &input);
        switch(input) {
            case 'n':
                //printf("Hello N\n");
                y++;
                printSeed(x, y);
                break;
            case 's':
                y--;
                //printf("Hello S\n");
                printSeed(x, y);
                break;
            case 'e':
                x++;
                //printf("Hello E\n");
                printSeed(x, y);
                break;
            case 'w':
                x--;
                //printf("Hello W\n");
                printSeed(x, y);
                break;
            case 'f':
                scanf("%d %d", &x, &y);
                printSeed(x, y);
                break;
        }
    }
    return 0;
}