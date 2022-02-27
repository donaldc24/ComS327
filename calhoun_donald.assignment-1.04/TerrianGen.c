// For the Priority Queue used I used the one I found on https://www.geeksforgeeks.org/priority-queue-using-linked-list/
// Functions that are not my own and were found on this website are: struct node, newNode, peek, pop, push, isEmptyQ

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#define true 1
#define false 0

// Structure that I found on https://www.geeksforgeeks.org/priority-queue-using-linked-list/
typedef struct node {
    int data;
 
    // Lower values indicate higher priority
    int priority;
 
    struct node* next;
 
} Node;
 
// Function to Create A New Node, found on https://www.geeksforgeeks.org/priority-queue-using-linked-list/
Node* newNode(int d, int p) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
 
    return temp;
}
 
// Return the value at head, found on https://www.geeksforgeeks.org/priority-queue-using-linked-list/
int peek(Node** head) {
    return (*head)->data;
}
 
// Removes the element with the
// highest priority form the list, found on https://www.geeksforgeeks.org/priority-queue-using-linked-list/
void pop(Node** head) {
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}
 
// Function to push according to priority, found on https://www.geeksforgeeks.org/priority-queue-using-linked-list/
void push(Node** head, int d, int p) {
    Node* start = (*head);
 
    // Create new Node
    Node* temp = newNode(d, p);
 
    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > p) {
 
        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {
 
        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
            start->next->priority < p) {
            start = start->next;
        }
 
        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}
 
// Function to check is list is empty, found on https://www.geeksforgeeks.org/priority-queue-using-linked-list/
int isEmptyQ(Node** head) {
    return (*head) == NULL;
}

//[0] is WE, [1] is NS
int entry[8];
int exitt[8];
int pathResult[4];

int pc[2];
int weightMap[21][80];

char world[21][80][399][399];
int pathNS[4];
int pathEW[4];

//store locations of NPCs
int hLoc[100];
int rLoc[100];
int bLoc[100];
int pLoc[100];
int wLoc[100];
int sLoc[100];
int nLoc[100];

int hLocNew[100];
int rLocNew[100];
int bLocNew[100];
int pLocNew[100];
int wLocNew[100];
int sLocNew[100];
int nLocNew[100];

int hLocPrev[100];
int rLocPrev[100];
int bLocPrev[100];
int pLocPrev[100];
int wLocPrev[100];
int sLocPrev[100];
int nLocPrev[100];
Node* pqNPC; 

void dijkstra(int graph[21][80], int src) {
    int dist[80*21];
    int prev[80*21];

    for (int i = 0; i < 80*21; i++) {
        dist[i] = INT_MAX;
        prev[i] = INT_MAX;
    }

    dist[src] = 0;
    Node* pq = newNode(src, 0);

    while (!isEmptyQ(&pq)) {
        int u = peek(&pq);
        src = u;

        int neighbors[8] = {src-80, src+80, src+1, src-1, src-81, src-79, src+79, src+81};
        for (int i = 0; i < 8; i++) {
            int v = neighbors[i];
            int alt = dist[u] + graph[0][v];

            if (v < 1680 && v >= 0 && alt < dist[v] && alt > 0) {
                dist[v] = alt;
                prev[v] = u;
                push(&pq, v, alt);
            }
        }
        pop(&pq);
    }

    for (int i = 0; i < (80*21); i++) {
        weightMap[0][i] = dist[i];
    }
}

void genEastWestPath(int worldX, int worldY, int pathLoc[4]) {
    int start = (rand() % 12) + 4;

    if (pathLoc[0] == 1) {
        start = entry[0];
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
    } else if (pathLoc[1] == 1) {
        start = exitt[2];
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
    if (worldX == 398) {
        world[pathEW[3]][79][worldX][worldY] = '%';
    }
    if (worldX == 0) {
        world[start][0][worldX][worldY] = '%';
    }
}

void genNorthSouthPath(int worldX, int worldY, int pathLoc[4]) {
    int start = (rand() % 70) + 4;

    if (pathLoc[3] == 1) {
        start = entry[7];
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
    } else if (pathLoc[2] == 1) {
        start = exitt[5];
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
    if (worldY == 398) {
        world[0][start][worldX][worldY] = '%';
    }
    if (worldY == 0) {
        world[20][pathNS[3]][worldX][worldY] = '%';
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

void genWater(int worldX, int worldY) {
    int row = (rand() % 10) + 5;
    int col = (rand() % 70) + 5;
    int origCol = col;
    int rows[8];
    int count = 0;

    while (count <= 5 && world[row][col][worldX][worldY] == '.' && row > 4 && row < 16) {
        rows[count] = row;
        world[row][col][worldX][worldY] = ',';
        row = row + 1;
        int count2 = 0;
        col = origCol;
        while (count2 < 8 && world[row][col][worldX][worldY] == '.' && col > 4 && row < 76) {
            if (world[row][col][worldX][worldY] == '.' && col > 4 && col < 76) {
                world[row][col][worldX][worldY] = ',';
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
        genWater(worldX, worldY);
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

        if (num <= 14 || num == manhatDist || num == manhatDist/2) {
            genCenterAndMart(worldX, worldY, 0);
        } else if (manhatDist >= 20 && num < (manhatDist-(num2+(num2/2)+(num2/3)))) {
            genCenterAndMart(worldX, worldY, 0);
        } 
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

void genSeed(int worldX, int worldY, int pathLoc[4], int manhatDist) {
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
    genWater(worldX, worldY);
    genWater(worldX, worldY);
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
                printf("\033[0;36m%c", world[i][j][worldX][worldY]);
            } else if (world[i][j][worldX][worldY] == '@') {
                printf("\033[0;35m%c", world[i][j][worldX][worldY]);
            } else if (world[i][j][worldX][worldY] == ',') {
                printf("\033[0;34m%c", world[i][j][worldX][worldY]);
            } else if (world[i][j][worldX][worldY] == '%') {
                printf("\033[0;37m%c", world[i][j][worldX][worldY]);
            } else {
                printf("\033[0;35m%c", world[i][j][worldX][worldY]);
            }
        }
        printf("\033[0;37m\n");
    }
}

void checkMap(int x, int y) {
    pathResult[0] = 0;
    pathResult[1] = 0;
    pathResult[2] = 0;
    pathResult[3] = 0;

    if (world[0][0][x+1][y] == '%') {
        for (int i = 0; i < 21; i++) {
            if (world[i][0][x+1][y] == '#') {
                entry[0] = i;
            }
            if (world[i][79][x+1][y] == '#') {
                exitt[0] = i;
            }
        }

        for (int i = 0; i < 80; i++) {
            if (world[0][i][x+1][y] == '#') {
                entry[1] = i;
            }
            if (world[20][i][x+1][y] == '#') {
                exitt[1] = i;
            }
        }
        pathResult[0] = 1;
    }

    if (world[0][0][x-1][y] == '%') {
        for (int i = 0; i < 21; i++) {
            if (world[i][0][x-1][y] == '#') {
                entry[2] = i;
            }
            if (world[i][79][x-1][y] == '#') {
                exitt[2] = i;
            }
        }

        for (int i = 0; i < 80; i++) {
            if (world[0][i][x-1][y] == '#') {
                entry[3] = i;
            }
            if (world[20][i][x-1][y] == '#') {
                exitt[3] = i;
            }
        }
        pathResult[1] = 1;
    }

    if (world[0][0][x][y+1] == '%') {
        for (int i = 0; i < 21; i++) {
            if (world[i][0][x][y+1] == '#') {
                entry[4] = i;
            }
            if (world[i][79][x][y+1] == '#') {
                exitt[4] = i;
            }
        }

        for (int i = 0; i < 80; i++) {
            if (world[0][i][x][y+1] == '#') {
                entry[5] = i;
            }
            if (world[20][i][x][y+1] == '#') {
                exitt[5] = i;
            }
        }
        pathResult[2] = 1;
    }

    if (world[0][0][x][y-1] == '%') {
        for (int i = 0; i < 21; i++) {
            if (world[i][0][x][y-1] == '#') {
                entry[6] = i;
            }
            if (world[i][79][x][y-1] == '#') {
                exitt[6] = i;
            }
        }

        for (int i = 0; i < 80; i++) {
            if (world[0][i][x][y-1] == '#') {
                entry[7] = i;
            }
            if (world[20][i][x][y-1] == '#') {
                exitt[7] = i;
            }
        }
        pathResult[3] = 1;
    }
}

void setPlayer(int x, int y) {
    pc[0] = (rand() % 18) + 1;
    for (int i = 1; i < 80; i++) {
        if (world[pc[0]][i][x][y] == '#') {
            world[pc[0]][i][x][y] = '@';
            pc[1] = i;
            return;
        }
    }
}

void fillWeightMap(int x, int y, int type) {
    // Hiker, Rival, Boater, Player
    //   0      1       2      3  
    int tallG[4] = {15, 20, 20, 20};
    int clearing[4] = {10, 12, 12, 12};
    int path[4] = {10, 10, 10, 10};
    int water[4] = {INT_MAX, INT_MAX, 20, INT_MAX};

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 80; j++) {
            char c = world[i][j][x][y];
            switch(c) {
                case ':':
                    weightMap[i][j] = tallG[type];
                    break;
                case '#':
                    weightMap[i][j] = path[type];
                    break;
                case ',':
                    weightMap[i][j] = water[type];
                    break;
                case '.':
                    weightMap[i][j] = clearing[type];
                    break;
                default:
                    weightMap[i][j] = INT_MAX;
                    break;
            }
            weightMap[0][j] = INT_MAX;
            weightMap[20][j] = INT_MAX;
        }
        weightMap[i][0] = INT_MAX;
        weightMap[i][79] = INT_MAX;
    }
}

void printWM(void) {
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 80; j++) {
            int n = weightMap[i][j];
            if (n == INT_MAX || n == -INT_MAX) {
                printf("  ");
            } else {
                printf("%02d ", abs(n) % 100);
            }
        }
        printf("\n");
    }
}

void moveNPC(int x, int y, int time, int mapH[21][80], int mapR[21][80], int mapB[21][80]) {
    //'h', 'r', 'b', 'p', 'w', 's', 'n'
    int cost = 0;
    int i = 0;
    while (hLoc[i] != 0 || rLoc[i] != 0 || bLoc[i] != 0) {
        if (hLoc[i] != 0) {
            int src = hLoc[i];
            int neighbors[8] = {src-80, src+80, src+1, src-1, src-81, src-79, src+79, src+81};
            int sml = neighbors[0];
            for (int j = 1; j < 8; j++) {
                int n = neighbors[j];
                if ((n > 80 && n < 1600 && mapH[0][n] < mapH[0][sml] && world[0][n][x][y] != '@') || sml <= 0) {
                    sml = n;
                }
            }
            cost = time + mapH[0][sml];
            hLocNew[i] = sml;
            push(&pqNPC, sml, cost);
        } 
        if (rLoc[i] != 0) {
            int src = rLoc[i];
            int neighbors[8] = {src-80, src+80, src+1, src-1, src-81, src-79, src+79, src+81};
            int sml = neighbors[0];
            for (int j = 1; j < 8; j++) {
                int n = neighbors[j];
                if ((n > 80 && n < 1600 && mapR[0][n] < mapR[0][sml]) || sml <= 0) {
                    sml = n;
                }
            }
            cost = time + mapR[0][sml];
            rLocNew[i] = sml;
            push(&pqNPC, sml, cost);
        } 
        if (bLoc[i] != 0) {
            int src = bLoc[i];
            int neighbors[8] = {src-80, src+80, src+1, src-1, src-81, src-79, src+79, src+81};
            int sml = neighbors[0];
            for (int j = 1; j < 8; j++) {
                int n = neighbors[j];
                if ((n > 80 && n < 1600 && mapB[0][n] < mapB[0][sml] && world[0][n][x][y] != '@') || sml <= 0) {
                    sml = n;
                }
            }
            cost = time + mapB[0][sml];
            bLocNew[i] = sml;
            push(&pqNPC, sml, cost);
        }
        i++;
    }
}

void getDistMaps(int x, int y, int time) {
    // Hiker
    fillWeightMap(x, y, 0);
    int num = 80*pc[0] + pc[1];
    dijkstra(weightMap, num);
    int hikerMap[21][80];
    memcpy(hikerMap, weightMap, sizeof(hikerMap));
    // printWM();
    // printf("\n");

    // Rival
    fillWeightMap(x, y, 1);
    dijkstra(weightMap, num);
    int rivalMap[21][80];
    memcpy(rivalMap, weightMap, sizeof(rivalMap));
    // printWM();
    // printf("\n");

    // Boater
    fillWeightMap(x, y, 2);
    dijkstra(weightMap, num);
    int boaterMap[21][80];
    memcpy(boaterMap, weightMap, sizeof(boaterMap));
    // printWM();
    // printf("\n");

    moveNPC(x, y, time, hikerMap, rivalMap, boaterMap);
}

void placeNPCs(int amt, int x, int y) {
    int i = 0;
    char types[7] = {'h', 'r', 'b', 'p', 'w', 's', 'n'};
    int tallG[7] = {15, 20, 20, 20, INT_MAX, INT_MAX, 20};
    int clearing[7] = {10, 12, 12, 12, INT_MAX, INT_MAX, 12};
    int path[7] = {10, 10, 10, 10, INT_MAX, INT_MAX, 10};
    int water[7] = {INT_MAX, INT_MAX, 20, INT_MAX, INT_MAX, INT_MAX, INT_MAX};
    int hc = 0;
    int rc = 0;
    int bc = 0;
    int pc = 0;
    int wc = 0;
    int nc = 0;

    while (i < amt) {
        int row = (rand() % 15) + 2;
        int col = (rand() % 75) + 2;
        int t = (rand() % 6);

        if (i < 7) {
            t = i;
        }

        if (world[row][col][x][y] != 'M' && world[row][col][x][y] != 'C' && world[row][col][x][y] != '#' && world[row][col][x][y] != '%' && world[row][col][x][y] != 'h' && world[row][col][x][y] != 'r' && world[row][col][x][y] != 'p' && world[row][col][x][y] != 'w' && world[row][col][x][y] != 's' && world[row][col][x][y] != 'n' && world[row][col][x][y] != 'b' && world[row][col][x][y] != '@') {
            if (t == 4) {
                switch(world[row][col][x][y]) {
                    case ':':
                        tallG[t] = 5;
                        break;
                    case ',':
                        water[t] = 5;
                        break;
                    case '.':
                        clearing[t] = 5;
                        break;
                }
                wLocPrev[wc] = world[row][col][x][y];
                world[row][col][x][y] = types[t];
                wLoc[wc] = 80*row + col;
                wc++;
                i++;
            } else if (t == 5) {
                if (world[row][col][x][y] != ',') {
                    world[row][col][x][y] = types[t];
                    i++;
                }
            } else {
                char c = world[row][col][x][y];
                switch(c) {
                    case ':':
                        if (tallG[t] != INT_MAX) {
                            char prev = world[row][col][x][y];
                            world[row][col][x][y] = types[t];
                            switch(t) {
                                case 0:
                                    hLocPrev[hc] = prev;
                                    hLoc[hc] = 80*row + col;
                                    hc++;
                                    break;
                                case 1:
                                    rLocPrev[rc] = prev;
                                    rLoc[rc] = 80*row + col;
                                    rc++;
                                    break;
                                case 2:
                                    bLocPrev[bc] = prev;
                                    bLoc[bc] = 80*row + col;
                                    bc++;
                                    break;
                                case 3:
                                    pLocPrev[pc] = prev;
                                    pLoc[pc] = 80*row + col;
                                    pc++;
                                    break;
                                case 6:
                                    nLocPrev[nc] = prev;
                                    nLoc[nc] = 80*row + col;
                                    nc++;
                                    break;
                            }
                            i++;
                        }
                        break;
                    case ',':
                        if (water[t] != INT_MAX) {
                            world[row][col][x][y] = types[t];
                            switch(t) {
                                case 0:
                                    hLoc[hc] = 80*row + col;
                                    hc++;
                                    break;
                                case 1:
                                    rLoc[rc] = 80*row + col;
                                    rc++;
                                    break;
                                case 2:
                                    bLoc[bc] = 80*row + col;
                                    bc++;
                                    break;
                                case 3:
                                    pLoc[pc] = 80*row + col;
                                    pc++;
                                    break;
                                case 6:
                                    nLoc[nc] = 80*row + col;
                                    nc++;
                                    break;
                            }
                            i++;
                        }
                        break;
                    case '.':
                        if (clearing[t] != INT_MAX) {
                            world[row][col][x][y] = types[t];
                            switch(t) {
                                case 0:
                                    hLoc[hc] = 80*row + col;
                                    hc++;
                                    break;
                                case 1:
                                    rLoc[rc] = 80*row + col;
                                    rc++;
                                    break;
                                case 2:
                                    bLoc[bc] = 80*row + col;
                                    bc++;
                                    break;
                                case 3:
                                    pLoc[pc] = 80*row + col;
                                    pc++;
                                    break;
                                case 6:
                                    nLoc[nc] = 80*row + col;
                                    nc++;
                                    break;
                            }
                            i++;
                        }
                        break;
                }
            }

        }
    }
}

void changeNPCLoc(int x, int y, int u) {
    for (int i = 0; i < 100; i++) {
        if (hLocNew[i] == u) {
            world[0][hLoc[i]][x][y] = hLocPrev[i];
            char prev = world[0][u][x][y];
            world[0][u][x][y] = 'h';
            hLocPrev[i] = prev;
            hLoc[i] = u;
        }
        if (rLocNew[i] == u) {
            world[0][rLoc[i]][x][y] = rLocPrev[i];
            char prev = world[0][u][x][y];
            world[0][u][x][y] = 'r';
            rLocPrev[i] = prev;
            rLoc[i] = u;
        }
        if (bLocNew[i] == u) {
            world[0][bLoc[i]][x][y] = bLocPrev[i];
            char prev = world[0][u][x][y];
            world[0][u][x][y] = 'b';
            bLocPrev[i] = prev;
            bLoc[i] = u;
        }
    }
}

void runMaps(int x, int y, int numT) {
    placeNPCs(numT, x, y);
    printSeed(x, y);
    pqNPC = newNode(INT_MAX, INT_MAX);
    int time = 0;
    while (1 == 1) {
        usleep(250000);
        int i = 0;
        getDistMaps(x, y, time);
        while (i < 6 && !isEmptyQ(&pqNPC)) {
            int u = peek(&pqNPC);
            if (u == INT_MAX) {
                break;
            }
            changeNPCLoc(x, y, u);
            pop(&pqNPC);
            usleep(250000);
            printSeed(x, y);
            i++;
        }
        time++;
    }
}

int main(void) {
    int x = 199;
    int y = 199;
    int numTrainers = 10;
    int manhatDist = 0;

    srand(time(0));
    genSeed(x, y, pathResult, manhatDist);
    setPlayer(x, y);
    //getDistMaps(x, y);
    runMaps(x, y, numTrainers);
    char input[100];

    while (input[0] != 'q') {
        scanf(" %s", &input);
        switch(input[0]) {
            case 'n':
                y++;
                if (y > 398) {
                    printf("Out of bounds\n");
                    y--;
                }
                if (world[0][0][x][y] != '%') {
                    checkMap(x, y);
                    manhatDist = abs(199 - x) + abs(199 - y);
                    genSeed(x, y, pathResult, manhatDist);
                    setPlayer(x, y);
                }
                //getDistMaps(x, y);
                runMaps(x, y, numTrainers);
                break;
            case 's':
                y--;
                if (y < 0) {
                    printf("Out of bounds\n");
                    y++;
                }
                if (world[0][0][x][y] != '%') {
                    checkMap(x, y);
                    manhatDist = abs(199 - x) + abs(199 - y);
                    genSeed(x, y, pathResult, manhatDist);
                    setPlayer(x, y);
                }
                //getDistMaps(x, y);
                runMaps(x, y, numTrainers);
                break;
            case 'e':
                x++;
                if (x > 398) {
                    printf("Out of bounds\n");
                    x--;
                }
                if (world[0][0][x][y] != '%') {
                    checkMap(x, y);
                    manhatDist = abs(199 - x) + abs(199 - y);
                    genSeed(x, y, pathResult, manhatDist);
                    setPlayer(x, y);
                }
                //getDistMaps(x, y);
                runMaps(x, y, numTrainers);
                break;
            case 'w':
                x--;
                if (x < 0) {
                    printf("Out of bounds\n");
                    x++;
                }
                if (world[0][0][x][y] != '%') {
                    checkMap(x, y);
                    manhatDist = abs(199 - x) + abs(199 - y);
                    genSeed(x, y, pathResult, manhatDist);
                    setPlayer(x, y);
                }
                //getDistMaps(x, y);
                runMaps(x, y, numTrainers);
                break;
            case 'f':
                scanf("%d %d", &x, &y);
                if (x > 398 || y > 398 || x < 0 || y < 0) {
                    printf("Out of bounds, returned to start\n");
                    x = 199;
                    y = 199;
                }
                if (world[0][0][x][y] != '%') {
                    checkMap(x, y);
                    manhatDist = abs(199 - x) + abs(199 - y);
                    genSeed(x, y, pathResult, manhatDist);
                    setPlayer(x, y);
                }
                //getDistMaps(x, y);
                runMaps(x, y, numTrainers);
                break;
            case '-':
                int tempTrainers = numTrainers;
                scanf("%d", &tempTrainers);
                for (int k = 0; k < 13; k++) {
                    if (input[1] == '-' && input[2] == 'n' && input[3] == 'u' && input[4] == 'm' && input[5] == 't' && input[6] == 'r' && input[7] == 'a' && input[8] == 'i' && input[9] == 'n' && input[10] == 'e' && input[11] == 'r' && input[12] == 's') {
                        numTrainers = tempTrainers;
                    }
                }
                break;
            default:
                printf(" Not a valid input, please try n, s, e, w, or f x y!\n");
                printSeed(x, y);
                break;
        }
    }
    return 0;
}