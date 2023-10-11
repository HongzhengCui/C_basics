#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for a point (x, y, step)
typedef struct {
    int x, y, step;
} point;

// Define a structure for a direction (incrx, incry)
typedef struct {
    int incrx;
    int incry;
} dir;

// Define a structure for a node in a queue
typedef struct node {
    point data;
    struct node* pNext;
} Node, *Pnode;

// Define a structure for a queue
typedef struct queue {
    Pnode front;
    Pnode rear;
} Q, *Pqueue;

// Function to initialize a queue
Pqueue Initq() {
    Pqueue q = (Pqueue)malloc(sizeof(Q));
    q->front = q->rear = (Pnode)malloc(sizeof(Node));
    q->front->pNext = NULL;
    q->rear->pNext = NULL;
    return q;
}

// Function to enqueue a point into the queue
void enqueue(Pqueue q, point key) {
    Pnode pnew = (Pnode)malloc(sizeof(Node));
    pnew->data.x = key.x;
    pnew->data.y = key.y;
    pnew->data.step = key.step;
    q->rear->pNext = pnew;
    pnew->pNext = NULL;
    q->rear = pnew;
}

// Function to check if the queue is empty
bool empty(Pqueue q) {
    if (q->front == q->rear)
        return true;
    else
        return false;
}

// Function to dequeue a point from the queue
void dequeue(Pqueue q) {
    if (!(empty(q))) {
        if (q->front->pNext != q->rear) {
            Pnode source = q->front->pNext;
            q->front->pNext = source->pNext;
            free(source);
        }
        else {
            free(q->rear);
            q->front->pNext = NULL;
            q->rear = q->front;
        }
    }
}

// Function to get the front point from the queue
point Getfront(Pqueue q) {
    if (!(empty(q))) {
        return q->front->pNext->data;
    }
}

// Define directions for movement
dir Dire[4] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

dir inverseDire[4] = {
    {0, -1}, {-1, 0}, {0, 1}, {1, 0}
};

// Function to find a path through a maze using BFS
bool passmaze(int SIZE, char maze[][SIZE], dir Dire[], Pqueue q, int flag[][SIZE], int Sx, int Sy, int Tx, int Ty) {
    int x, y, step;
    int row, col;
    point source = {Sx, Sy, 0};
    maze[Sx][Sy] = 'o';
    enqueue(q, source);
    while (!(empty(q))) {
        source = Getfront(q);
        x = source.x;
        y = source.y;
        step = 0;
        while (step < 4) {
            row = x + Dire[step].incrx;
            col = y + Dire[step].incry;
            if (maze[row][col] == '.' || maze[row][col] == 'T') {
                flag[row][col] = step;
                source.x = row;
                source.y = col;
                source.step = step;
                enqueue(q, source);
                maze[row][col] = 'o';
                if (row == Tx && col == Ty)
                    return true;
            }
            step++;
        }
        dequeue(q);
    }
    return false;
}

// Function to display the path found in the maze
void pathshow(int SIZE, char maze[SIZE][SIZE], dir Dire[], dir inverseDire[], Pqueue q, int flag[][SIZE], int Sx, int Sy, int Tx, int Ty) {
    if (passmaze(SIZE, maze, Dire, q, flag, Sx, Sy, Tx, Ty)) {
        int x, y, step;
        point source = Getfront(q);
        x = Tx, y = Ty;
        while (x != Sx || y != Sy) {
            printf("%d,%d ", x, y);
            step = flag[x][y];
            x = x + inverseDire[step].incrx;
            y = y + inverseDire[step].incry;
        }
    }
}

int main(int argc, char* argv[]) {

    char* file_name = argv[1];
    FILE* file = fopen(file_name, "r");
    int SIZE = 0;
    while (fgetc(file) != '\n') SIZE++;
    rewind(file);
    char maze[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fscanf(file, "%c", &maze[i][j]);
            if (maze[i][j] == '\n') j--;
        }
    }
    fclose(file);

    int Sx, Sy;
    int Tx, Ty;
    int flag[SIZE][SIZE];
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            flag[row][col] = 0;
            if (maze[row][col] == 'S') {
                Sx = row;
                Sy = col;
            }
            else if (maze[row][col] == 'T') {
                Tx = row;
                Ty = col;
            }
        }
    }

    Pqueue q = Initq();
    pathshow(SIZE, maze, Dire, inverseDire, q, flag, Sx, Sy, Tx, Ty);
    return 0;
}

