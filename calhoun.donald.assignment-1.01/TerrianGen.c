#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define true 1
#define false 0

char world[21][80][399][399];
int pathNS[4];
int pathEW[4];

void genEastWestPath(int worldX, int worldY, int pathLoc[3]) {
    int start = (rand() % 12) + 4;

    if (pathLoc[2] == 3) {
        start = pathLoc[1];
        pathEW[0] = start;
        pathEW[1] = 0;

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
        pathEW[2] = loc[1];
        pathEW[3] = loc[0];
    } else if (pathLoc[2] == 2) {
        start = pathLoc[0];
        pathEW[0] = start;
        pathEW[1] = 79;

        world[start][79][worldX][worldY] = '#';

        int loc[] = {start, 78};
        world[loc[0]][loc[1]][worldX][worldY] = '#';

        while (loc[1] > 0) {
            int num = rand() % 10;

            if (num < 6) {
                loc[1] = loc[1] - 1;
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
        pathEW[2] = loc[1];
        pathEW[3] = loc[0];
    } else {
        pathEW[0] = start;
        pathEW[1] = 0;
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
        pathEW[2] = loc[1];
        pathEW[3] = loc[0];
    }
}

void genNorthSouthPath(int worldX, int worldY, int pathLoc[3]) {
    int start = (rand() % 70) + 4;
    if (pathLoc[2] == 1) {
        start = pathLoc[1];
        pathNS[0] = start;
        pathNS[1] = 0;
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
        pathNS[2] = loc[0];
        pathNS[3] = loc[1];
    } else if (pathLoc[2] == 0) {
        start = pathLoc[0];
        pathNS[0] = start;
        pathNS[1] = 20;
        world[20][start][worldX][worldY] = '#';

        int loc[] = {19, start};
        world[loc[0]][loc[1]][worldX][worldY] = '#';

        while (loc[0] > 0) {
            int num = rand() % 10;

            if (num < 6) {
                loc[0] = loc[0] - 1;
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
        pathNS[2] = loc[0];
        pathNS[3] = loc[1];
    } else {
        pathNS[0] = start;
        pathNS[1] = 0;
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
        pathNS[2] = loc[0];
        pathNS[3] = loc[1];
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

void genCenterAndMart(int worldX, int worldY, int manhatDist) {
    int centerR1 = 0;
    int centerC1 = 0;
    int centerR2 = 0;
    int centerC2 = 0;
    int check = false;

    if (manhatDist == 0.0) {
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
    } else {
        int num = (rand() % manhatDist);
        int num2 = (rand() % manhatDist/2);

        //printf("%d, %d, %d\n", num, num2, manhatDist);
        if (num <= 14 || num == manhatDist || num == manhatDist/2) {
            genCenterAndMart(worldX, worldY, 0);
        } else if (manhatDist >= 20 && num < (manhatDist-(num2+(num2/2)+(num2/3)))) {
            genCenterAndMart(worldX, worldY, 0);
        } 
        // else if (manhatDist >= 61 && manhatDist <= 122 && num ) {
        //     genCenterAndMart(worldX, worldY, 0);
        // } else if (manhatDist >= 125) {
        //     genCenterAndMart(worldX, worldY, 0);
        // }
        //double placeMarket = (((-45.0 * manhatDist) / 200.0) + 50.0);
        //printf("%f, %f\n", placeMarket, manhatDist);
        // if (placeMarket < 100) {
        //     genCenterAndMart(worldX, worldY, 0.0);
        // }
    }
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

void genSeed(int worldX, int worldY, int pathLoc[3], int manhatDist) {
    int i, j;
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 80; j++) {
            world[i][j][worldX][worldY] = '.';
        }
    }

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
    genNorthSouthPath(worldX, worldY, pathLoc);
    genEastWestPath(worldX, worldY, pathLoc);
    genCenterAndMart(worldX, worldY, manhatDist);
    genRandomObj(worldX, worldY);

    for (i = 0; i < 21; i++) {
        if (world[i][0][worldX][worldY] != '%' && world[i][0][worldX][worldY] != '#') {
            world[i][0][worldX][worldY] = '%';
        }
        if (world[i][79][worldX][worldY] != '%' && world[i][79][worldX][worldY] != '#') {
            world[i][79][worldX][worldY] = '%';
        }
    }

    for (i = 0; i < 80; i++) {
        if (world[0][i][worldX][worldY] != '%' && world[0][i][worldX][worldY] != '#') {
            world[0][i][worldX][worldY] = '%';
        }
        if (world[20][i][worldX][worldY] != '%' && world[20][i][worldX][worldY] != '#') {
            world[20][i][worldX][worldY] = '%';
        }
    }
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
    int x = 199;
    int y = 199;

    int pathLoc[3];
    int manhatDist = 0;
    pathLoc[0] = -1;
    pathLoc[1] = -1;
    // 0 is North, 1 is South, 2 is East, 3 is West
    pathLoc[2] = -1;

    srand(time(0));
    genSeed(x, y, pathLoc, manhatDist);
    printSeed(x, y);
    char input;

    while (input != 'q') {
        scanf(" %c", &input);
        switch(input) {
            case 'n':
                y++;
                if (y > 398) {
                    printf("Out of bounds\n");
                    y--;
                }
                if (world[0][0][x][y] != '%') {
                    manhatDist = abs(199 - x) + abs(199 - y);
                    pathLoc[0] = pathNS[0];
                    pathLoc[1] = pathNS[1];
                    pathLoc[2] = 0;
                    genSeed(x, y, pathLoc, manhatDist);
                }
                printSeed(x, y);
                break;
            case 's':
                y--;
                if (y < 0) {
                    printf("Out of bounds\n");
                    y++;
                }
                if (world[0][0][x][y] != '%') {
                    manhatDist = abs(199 - x) + abs(199 - y);
                    pathLoc[0] = pathNS[2];
                    pathLoc[1] = pathNS[3];
                    pathLoc[2] = 1;
                    genSeed(x, y, pathLoc, manhatDist);
                }
                printSeed(x, y);
                break;
            case 'w':
                x++;
                if (x > 398) {
                    printf("Out of bounds\n");
                    x--;
                }
                if (world[0][0][x][y] != '%') {
                    manhatDist = abs(199 - x) + abs(199 - y);
                    pathLoc[0] = pathEW[0];
                    pathLoc[1] = pathEW[1];
                    pathLoc[2] = 2;
                    genSeed(x, y, pathLoc, manhatDist);
                }
                printSeed(x, y);
                break;
            case 'e':
                x--;
                if (x < 0) {
                    printf("Out of bounds\n");
                    x++;
                }
                if (world[0][0][x][y] != '%') {
                    manhatDist = abs(199 - x) + abs(199 - y);
                    pathLoc[0] = pathEW[2];
                    pathLoc[1] = pathEW[3];
                    pathLoc[2] = 3;
                    genSeed(x, y, pathLoc, manhatDist);
                }
                printSeed(x, y);
                break;
            case 'f':
                scanf("%d %d", &x, &y);
                if (x > 398 || y > 398 || x < 0 || y < 0) {
                    printf("Out of bounds, returned to start\n");
                    x = 199;
                    y = 199;
                }
                if (world[0][0][x][y] != '%') {
                    manhatDist = abs(199 - x) + abs(199 - y);
                    genSeed(x, y, pathLoc, manhatDist);
                }
                printSeed(x, y);
                break;
            default:
                printf(" Not a valid input, please try n, s, e, w, or f x y!\n");
                printSeed(x, y);
                break;
        }
    }
    return 0;
}