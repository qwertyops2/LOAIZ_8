#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
#include <cstdlib>
#include <windows.h>

using namespace std;

struct node {
    int inf;
    struct node* next;
};

struct node* head = NULL, * last = NULL;

void BFSqueue(vector<vector<int>> G, int start) {
    int n = G.size();
    vector<bool> visited(n, false);
    queue<int> Q;

    Q.push(start);
    visited[start] = true;

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        cout << v + 1 << " ";

        for (int i = 0; i < n; ++i) {
            if (G[v][i] == 1 && !visited[i]) {
                Q.push(i);
                visited[i] = true;
            }
        }
    }
}



void enqueue(int value) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    if (p == NULL) {
        printf("������ ��� ������������� ������\n");
        exit(1);
    }
    p->inf = value;
    p->next = NULL;

    if (last == NULL) {
        head = p;
        last = p;
    }
    else {
        last->next = p;
        last = p;
    }
}

int isQueueEmpty(void) {
    return head == NULL;
}

int dequeue(void) {
    if (isQueueEmpty()) {
        printf("������� �����\n");
        return -1;
    }
    struct node* temp = head;
    int value = temp->inf;
    head = head->next;
    if (head == NULL) {
        last = NULL;
    }
    free(temp);
    return value;
}

void BFS(int** G, int n, int start) {
    int* visited = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) visited[i] = 0;

    enqueue(start);
    visited[start] = 1;

    while (!isQueueEmpty()) {
        int v = dequeue();
        printf("%d ", v + 1);

        for (int i = 0; i < n; i++) {
            if (G[v][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    free(visited);
}



int** generateG(int versh) {
    int** G = (int**)malloc(versh * sizeof(int*));
    for (int i = 0; i < versh; i++) {
        G[i] = (int*)malloc(versh * sizeof(int));
        for (int j = 0; j < versh; j++) {
            G[i][j] = 0;
        }
    }

    for (int i = 0; i < versh; i++) {
        for (int j = i + 1; j < versh; j++) {
            if (rand() % 2 == 1) {
                G[i][j] = 1;
                G[j][i] = 1;
            }
        }
    }
    return G;
}

void printG(int** G, int versh) {
    printf("������� ���������: \n");
    for (int i = 0; i < versh; i++) {
        for (int j = 0; j < versh; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(5435234623462343726);

    int versh;
    printf("������� ���������� ������ �����: ");
    scanf("%d", &versh);

    int** G = NULL;
    G = generateG(versh);
    printG(G, versh);

    printf("\n����� � ������ (������� �� ������ ������ �� ���� 3):\n");
    clock_t start, end;

    start = clock();
    BFS(G, versh, 0);
    end = clock();

    float bfs = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n����� ���������� (������� �� ������ ������ �� ���� 3): %f ������\n", bfs);
    

    vector<vector<int>> G1(versh, vector<int>(versh, 0));
    for (int i = 0; i < versh; i++) {
        for (int j = 0; j < versh; j++) {
            G1[i][j] = G[i][j];
        }
    }

    cout << endl << "����� � ������ (Queue):" << endl;

    start = clock();
    BFSqueue(G1, 0);
    end = clock();

    float bfsQ = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n����� ���������� (Queue): %f ������\n", bfsQ);
    printf("\n����� ���������� (Queue: %f) - (������� �� ������ ������ �� ���� 3: %f): %f ������\n", bfsQ, bfs, bfsQ - bfs);
}
