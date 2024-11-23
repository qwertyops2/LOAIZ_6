#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <locale.h>


typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

struct Graph {
	int numVertices;
	struct node** adjLists;
};

int** createG(int size) {
    int** G = NULL;
    G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            G[i][j] = 0;
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int edge = rand() % 2;
            G[i][j] = edge;
            G[j][i] = edge;
        }
    }
    return G;
}

int** printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
    return G;
}


Node** createAdjList(int** G, int size) {
    Node** adjList = (Node**)malloc(size * sizeof(Node*));

    for (int i = 0; i < size; i++) {
        adjList[i] = NULL;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (G[i][j] == 1) {
                addEdge(&adjList[i], j);
            }
        }
    }

    return adjList;
}

void sortAdjList(Node* list) {
    if (list == NULL || list->next == NULL) {
        return;
    }

    for (Node* i = list; i != NULL; i = i->next) {
        for (Node* j = i->next; j != NULL; j = j->next) {
            if (i->vertex > j->vertex) {
                int temp = i->vertex;
                i->vertex = j->vertex;
                j->vertex = temp;
            }
        }
    }
}

void printAdjList(Node** adjList, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d: ", i + 1);
        Node* temp = adjList[i];

        sortAdjList(temp);

        while (temp != NULL) {
            printf("%d ", temp->vertex + 1);
            temp = temp->next;
        }
        printf("\n");
    }
}

int** unionG(int** G1, int** G2, int size1, int size2) {
    int sizemax = (size1 > size2) ? size1 : size2;
    int sizemin = (size1 < size2) ? size1 : size2;

    int** Gmax = (size1 > size2) ? G1 : G2;
    int** Gmin = (size1 < size2) ? G1 : G2;

    int** Gtemp = createG(sizemax);

    for (int i = 0; i < sizemin; i++) {
        for (int j = 0; j < sizemin; j++) {
            Gtemp[i][j] = Gmin[i][j] | Gmax[i][j];
        }
    }
    for (int i = 0; i < sizemax; i++) {
        for (int j = sizemin; j < sizemax; j++) {
            Gtemp[i][j] = Gmax[i][j];
            Gtemp[j][i] = Gtemp[i][j];
        }
    }

    return Gtemp;

}

int** intersectoinG(int** G1, int** G2, int size1, int size2) {
    int sizemin = (size1 < size2) ? size1 : size2;

    int** Gtemp = createG(sizemin);

    for (int i = 0; i < sizemin; i++) {
        for (int j = 0; j < sizemin; j++) {
            Gtemp[i][j] = G1[i][j] & G2[i][j];
        }
    }
    return Gtemp;
}

int** xorG(int** G1, int** G2, int size1, int size2) {
    int sizemax = (size1 > size2) ? size1 : size2;
	int sizemin = (size1 < size2) ? size1 : size2;
	int** Gmax = (size1 > size2) ? G1 : G2;
	int** Gmin = (size1 < size2) ? G1 : G2;
	int** Gtemp = createG(sizemax);
	for (int i = 0; i < sizemax; i++) {
		for (int j = 0; j < sizemax; j++) {
			if (i < sizemin && j < sizemin) {
				Gtemp[i][j] = Gmax[i][j] ^ Gmin[i][j];
			}
			else {
				Gtemp[i][j] = Gmax[i][j];
			}
		}
	}
	return Gtemp;
}


void addEdge(Node** adjacencyList, int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = *adjacencyList;
    *adjacencyList = newNode;
}

Node** unionAdjLists(Node** adjList1, Node** adjList2, int size1, int size2) {
    int size = (size1 > size2) ? size1 : size2;
    Node** result = (Node**)malloc(size * sizeof(Node*));


    for (int i = 0; i < size; i++) {
        result[i] = NULL;
    }

    for (int i = 0; i < size1; i++) {
        Node* temp1 = adjList1[i];
        while (temp1 != NULL) {
            addEdge(&result[i], temp1->vertex);
            temp1 = temp1->next;
        }
    }

    for (int i = 0; i < size2; i++) {
        Node* temp2 = adjList2[i];
        while (temp2 != NULL) {
            bool found = false;
            Node* tempResult = result[i];
            while (tempResult != NULL) {
                if (tempResult->vertex == temp2->vertex) {
                    found = true;
                    break;
                }
                tempResult = tempResult->next;
            }
            if (!found) {
                addEdge(&result[i], temp2->vertex);
            }
            temp2 = temp2->next;
        }
    }

    return result;
}

Node** intersectionAdjLists(Node** adjList1, Node** adjList2, int size1, int size2) {
    int size = (size1 < size2) ? size1 : size2;
    Node** result = (Node**)malloc(size * sizeof(Node*));

    for (int i = 0; i < size; i++) {
        result[i] = NULL;
    }

    for (int i = 0; i < size; i++) {
        Node* temp1 = (size1 < size2) ? adjList2[i] : adjList1[i];
        while (temp1 != NULL) {
            Node* temp2 = (size1 < size2) ? adjList1[i] : adjList2[i];
            while (temp2 != NULL) {
                if (temp1->vertex == temp2->vertex) {
                    addEdge(&result[i], temp1->vertex);
                    break;
                }
                temp2 = temp2->next;
            }
            temp1 = temp1->next;
        }
    }

    return result;
}

Node** xorAdjLists(Node** adjList1, Node** adjList2, int size1, int size2) {
    int maxSize = (size1 > size2) ? size1 : size2;
    Node** result = (Node**)malloc(maxSize * sizeof(Node*));

    for (int i = 0; i < maxSize; i++) {
        Node* list1 = (i < size1) ? adjList1[i] : NULL;
        Node* list2 = (i < size2) ? adjList2[i] : NULL;
        Node* temp1 = list1;
        Node* temp2 = list2;
        Node* xorResult = NULL;

        while (temp1 != NULL) {
            Node* check = list2;
            bool found = false;
            while (check != NULL) {
                if (check->vertex == temp1->vertex) {
                    found = true;
                    break;
                }
                check = check->next;
            }
            if (!found) {
                addEdge(&xorResult, temp1->vertex);
            }
            temp1 = temp1->next;
        }

        while (temp2 != NULL) {
            Node* check = list1;
            bool found = false;
            while (check != NULL) {
                if (check->vertex == temp2->vertex) {
                    found = true;
                    break;
                }
                check = check->next;
            }
            if (!found) {
                addEdge(&xorResult, temp2->vertex);
            }
            temp2 = temp2->next;
        }

        result[i] = xorResult;
    }

    return result;
}

int main(void) {
    int sizeG1 = 3, sizeG2 = 5;
    setlocale(LC_ALL, "");

    printf("Введите количество вершин графа 1: ");
    scanf("%d", &sizeG1);
    printf("Введите количество вершин графа 2: ");
    scanf("%d", &sizeG2);

    int** G1 = createG(sizeG1);
    int** G2 = createG(sizeG2);

    printf("граф 1\n");
    printG(G1, sizeG1);
    printf("граф 2\n");
    printG(G2, sizeG2);

    int** G3 = unionG(G1, G2, sizeG1, sizeG2);
    int sizeG3 = (sizeG1 > sizeG2) ? sizeG1 : sizeG2;
    printf("\nОбъединение графов\n");
    printG(G3, sizeG3);

    int** G4 = intersectoinG(G1, G2, sizeG1, sizeG2);
    int sizeG4 = (sizeG1 < sizeG2) ? sizeG1 : sizeG2;
    printf("\nПересечение графов\n");
    printG(G4, sizeG4);

    int** G5 = xorG(G1, G2, sizeG1, sizeG2);
    printf("\nКольцевая сумма графов (матрица смежности):\n");
    printG(G5, (sizeG1 > sizeG2) ? sizeG1 : sizeG2);

    printf("\nСписок смежности для 1 графа:\n");
    Node** graph1 = createAdjList(G1, sizeG1);
    printAdjList(graph1, sizeG1);

    printf("\nСписок смежности для 2 графа:\n");
    Node** graph2 = createAdjList(G2, sizeG2);
    printAdjList(graph2, sizeG2);

    printf("\nОбъединение списков смежности:\n");
    Node** unionList = unionAdjLists(graph1, graph2, sizeG1, sizeG2);
    printAdjList(unionList, sizeG1);

    printf("\nПересечение списков смежности:\n");
    Node** intersectionList = intersectionAdjLists(graph1, graph2, sizeG1, sizeG2);
    int sizeInterList = (sizeG1 < sizeG2) ? sizeG1 : sizeG2;
    printAdjList(intersectionList, sizeInterList);

    printf("\nКольцевая сумма списков смежности:\n");
    int sizeXorList = (sizeG1 > sizeG2) ? sizeG1 : sizeG2;
    Node** xorList = xorAdjLists(graph1, graph2, sizeG1, sizeG2);
    printAdjList(xorList, sizeXorList);
}
