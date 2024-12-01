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
        printf("Ошибка при распределении памяти\n");
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
        printf("Очередь пуста\n");
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

void BFS(const vector<vector<int>>& G, int start) {
    int n = G.size();
    vector<bool> visited(n, false);

    enqueue(start);
    visited[start] = true;

    while (!isQueueEmpty()) {
        int v = dequeue();
        cout << v + 1 << " ";

        for (int i = 0; i < n; i++) {
            if (G[v][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = true;
            }
        }
    }
}



vector<vector<int>> generateG(int versh) {
    vector<vector<int>> G(versh, vector<int>(versh, 0));

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

void printG(const vector<vector<int>>& G) {
    printf("Матрица смежности: \n");
    for (const auto& row : G) {
        for (int val : row) {
            printf("%d ", val);
        }
        printf("\n");
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(5435234623462343726);

    int versh;
    printf("Введите количество вершин графа: ");
    scanf("%d", &versh);

    vector<vector<int>> G = generateG(versh);
    printG(G);

    cout << endl << "Обход в ширину (Очередь на основе списка из лабы 3):" << endl;
    clock_t start, end;

    start = clock();
    BFS(G, 0);
    end = clock();

    float bfs = (double)(end - start) / CLOCKS_PER_SEC;
    cout << endl << "Время выполнения (Очередь на основе списка из лабы 3): " << bfs << "секунд" << endl;

    cout << endl << "Обход в ширину (Queue):" << endl;

    start = clock();
    BFSqueue(G, 0);
    end = clock();

    float bfsQ = (double)(end - start) / CLOCKS_PER_SEC;
    cout << endl << "Время выполнения (Queue): " << bfsQ << "секунд" << endl;
    cout << endl << "Время выполнения (Queue: " << bfsQ << ") - (Очередь на основе списка из лабы 3: " << bfs << "): " << bfsQ - bfs << " секунд"<< endl;
}
