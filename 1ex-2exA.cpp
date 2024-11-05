#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "cstdlib"

struct node {
	int vertex;
	struct node* next;
};

struct Graph {
	int numVertices;
	struct node** adjLists;
};

struct node* createNode(int v) {
	struct node* newNode = (node*)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createAGraph(int vertices) {
	struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
	graph->numVertices = vertices;

	graph->adjLists = (node**)malloc(vertices * sizeof(struct node*));

	for (int i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
	}

	return graph;
}

void addEdge(struct Graph* graph, int s, int d) {
	struct node* temp = graph->adjLists[s];
	while (temp) {
		if (temp->vertex == d) {
			return;
		}
		temp = temp->next;
	}

	struct node* newNode = createNode(d);
	newNode->next = graph->adjLists[s];
	graph->adjLists[s] = newNode;

	temp = graph->adjLists[d];
	while (temp) {
		if (temp->vertex == s) {
			return;
		}
		temp = temp->next;
	}

	newNode = createNode(s);
	newNode->next = graph->adjLists[d];
	graph->adjLists[d] = newNode;
}

struct Graph* edges(int** G, int size) {
	struct Graph* graph = createAGraph(size);

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (G[i][j] == 1) {
				addEdge(graph, i, j);
			}
		}
	}
	return graph;
}

void printGraph(struct Graph* graph) {
	for (int v = 0; v < graph->numVertices; v++) {
		struct node* temp = graph->adjLists[v];
		printf("\nVertex %d: ", v + 1);
		while (temp) {
			printf("%d -> ", temp->vertex + 1);
			temp = temp->next;
		}
		printf("\n");
	}
	printf("\n");
}

int** createG(int size) {
	int** G = NULL;
	G = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		G[i] = (int*)malloc(size * sizeof(int));
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			G[i][j] = rand() % 2;
			if (i == j) G[i][j] = 0;
			G[j][i] = G[i][j];
		}
	}
	return G;
}

void printG(int** G, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void unionV(struct Graph* graph, int v1, int v2) {
	if (v1 == v2) return;

	struct node* temp = graph->adjLists[v2];
	while (temp) {
		addEdge(graph, v1, temp->vertex);
		temp = temp->next;
	}

	for (int i = 0; i < graph->numVertices; i++) {
		struct node* adj = graph->adjLists[i];
		struct node* p = NULL;

		while (adj) {
			if (adj->vertex == v2) {
				if (p) {
					p->next = adj->next;
				}
				else {
					graph->adjLists[i] = adj->next;
				}
				struct node* del = adj;
				adj = adj->next;
				free(del);
			}
			else {
				p = adj;
				adj = adj->next;
			}
		}
	}

	graph->adjLists[v2] = NULL;

	for (int i = v2 + 1; i < graph->numVertices; i++) {
		graph->adjLists[i - 1] = graph->adjLists[i];
	}
	graph->adjLists[graph->numVertices - 1] = NULL;

	graph->numVertices--;

	for (int i = 0; i < graph->numVertices; i++) {
		struct node* adj = graph->adjLists[i];
		while (adj) {
			if (adj->vertex > v2) {
				adj->vertex--;
			}
			adj = adj->next;
		}
	}
}

int main(void) {
	int sizeG1 = 0, sizeG2 = 0;
	int** G1 = NULL;
	int** G2 = NULL;

	printf("-=-=-=-=-=-ZADANIE 1 * -=-=-=-=-=-=\n");
	printf("Vvedite kol-vo versh 1 grafa: ");
	scanf("%d", &sizeG1);
	printf("Vvedite kol-vo versh 2 grafa: ");
	scanf("%d", &sizeG2);

	G1 = createG(sizeG1);
	printf("1 graf\n");
	printG(G1, sizeG1);

	struct Graph* graph1 = edges(G1, sizeG1);
	printGraph(graph1);

	G2 = createG(sizeG2);
	printf("2 graf\n");
	printG(G2, sizeG2);

	struct Graph* graph2 = edges(G2, sizeG2);
	printGraph(graph2);

	printf("-=-=-=-=-=-ZADANIE 2 * -=-=-=-=-=-=\n");
	int v1, v2;
	printf("Vvedite vershiny dlya sliyaniya: ");
	scanf("%d %d", &v1, &v2);
	unionV(graph1, v1 - 1, v2 - 1);
	printf("Graf posle sliyaniya:\n");
	printGraph(graph1);
}