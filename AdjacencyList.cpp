//#define _CRT_SECURE_NO_WARNINGS
//
//#include "stdio.h"
//#include "stdlib.h"
//#include "cstdlib"
//
//struct node {
//	int vertex;
//	struct node* next;
//};
//
//struct Graph {
//	int numVertices;
//	struct node** adjLists;
//};
//
//struct node* createNode(int v) {
//	struct node* newNode = (node*)malloc(sizeof(struct node));
//	newNode->vertex = v;
//	newNode->next = NULL;
//	return newNode;
//}
//
//struct Graph* createAGraph(int vertices) {
//	struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
//	graph->numVertices = vertices;
//
//	graph->adjLists = (node**)malloc(vertices * sizeof(struct node*));
//
//	for (int i = 0; i < vertices; i++) {
//		graph->adjLists[i] = NULL;
//	}
//
//	return graph;
//}
//
//void addEdge(struct Graph* graph, int s, int d) {
//	struct node* temp = graph->adjLists[s];
//	while (temp) {
//		if (temp->vertex == d) {
//			return; 
//		}
//		temp = temp->next;
//	}
//
//	struct node* newNode = createNode(d);
//	newNode->next = graph->adjLists[s];
//	graph->adjLists[s] = newNode;
//
//	temp = graph->adjLists[d];
//	while (temp) {
//		if (temp->vertex == s) {
//			return;
//		}
//		temp = temp->next;
//	}
//
//	newNode = createNode(s);
//	newNode->next = graph->adjLists[d];
//	graph->adjLists[d] = newNode;
//}
//
//
//struct Graph* edges(int** G, int size) {
//	struct Graph* graph = createAGraph(size);
//
//	for (int i = 0; i < size; i++) {
//		for (int j = i; j < size; j++) {
//			if (G[i][j] == 1) {
//				addEdge(graph, i, j);
//			}
//		}
//	}
//	return graph;
//}
//
//void printGraph(struct Graph* graph) {
//	for (int v = 0; v < graph->numVertices; v++) {
//		struct node* temp = graph->adjLists[v];
//		printf("\nVertex %d: ", v+1);
//		while (temp) {
//			printf("%d -> ", temp->vertex + 1);
//			temp = temp->next;
//		}
//		printf("\n");
//	}
//}
//
//
//
//int** createG(int size) {
//	int** G = NULL;
//	G = (int**)malloc(size * sizeof(int*));
//	for (int i = 0; i < size; i++) {
//		G[i] = (int*)malloc(size * sizeof(int));
//	}
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < size; j++) {
//			G[i][j] = rand() % 2;
//			if (i == j) G[i][j] = 0;
//			G[j][i] = G[i][j];
//		}
//	}
//	return G;
//}
//
//void printG(int** G, int size) {
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < size; j++) {
//			printf("%d ", G[i][j]);
//		}
//		printf("\n");
//	}
//	return;
//}
//
//
//
//void unionV(struct Graph* graph, int v1, int v2) {
//	if (v1 == v2) return;
//
//	struct node* temp = graph->adjLists[v2];
//	while (temp) {
//		addEdge(graph, v1, temp->vertex);
//		temp = temp->next;
//	}
//
//	for (int i = 0; i < graph->numVertices; i++) {
//		struct node* adj = graph->adjLists[i];
//		struct node* p = NULL;
//
//		while (adj) {
//			if (adj->vertex == v2) {
//				if (p) {
//					p->next = adj->next;
//				}
//				else {
//					graph->adjLists[i] = adj->next;
//				}
//				struct node* del = adj;
//				adj = adj->next;
//				free(del);
//			}
//			else {
//				p = adj;
//				adj = adj->next;
//			}
//		}
//	}
//
//	graph->adjLists[v2] = NULL;
//
//	for (int i = v2 + 1; i < graph->numVertices; i++) {
//		graph->adjLists[i - 1] = graph->adjLists[i];
//	}
//	graph->adjLists[graph->numVertices - 1] = NULL;
//
//	graph->numVertices--;
//
//	for (int i = 0; i < graph->numVertices; i++) {
//		struct node* adj = graph->adjLists[i];
//		while (adj) {
//			if (adj->vertex > v2) {
//				adj->vertex--;
//			}
//			adj = adj->next;
//		}
//	}
//}
//
//void styag(struct Graph* graph, int v1, int v2) {
//	if (v1 == v2) return;
//
//	int flag = 0;
//	struct node* temp = graph->adjLists[v1];
//	while (temp) {
//		if (temp->vertex == v2) {
//			flag = 1;
//		}
//		temp = temp->next;
//	}
//
//	if (flag) {
//		struct node* adj = graph->adjLists[v1];
//		struct node* p = NULL;
//
//		while (adj) {
//			if (adj->vertex == v2) {
//				if (p) {
//					p->next = adj->next;
//				}
//				else {
//					graph->adjLists[v1] = adj->next;
//				}
//				struct node* del = adj;
//				adj = adj->next;
//				free(del);
//				break;
//			}
//			else {
//				p = adj;
//				adj = adj->next;
//			}
//		}
//
//		adj = graph->adjLists[v2];
//		p = NULL;
//
//		while (adj) {
//			if (adj->vertex == v1) {
//				if (p) {
//					p->next = adj->next;
//				}
//				else {
//					graph->adjLists[v2] = adj->next;
//				}
//				struct node* del = adj;
//				adj = adj->next;
//				free(del);
//				break;
//			}
//			else {
//				p = adj;
//				adj = adj->next;
//			}
//		}
//
//		struct node* temp = graph->adjLists[v2];
//		while (temp) {
//			addEdge(graph, v1, temp->vertex);
//			temp = temp->next;
//		}
//
//		for (int i = 0; i < graph->numVertices; i++) {
//			adj = graph->adjLists[i];
//			p = NULL;
//
//			while (adj) {
//				if (adj->vertex == v2) {
//					if (p) {
//						p->next = adj->next;
//					}
//					else {
//						graph->adjLists[i] = adj->next;
//					}
//					struct node* del = adj;
//					adj = adj->next;
//					free(del);
//				}
//				else {
//					p = adj;
//					adj = adj->next;
//				}
//			}
//		}
//
//		graph->adjLists[v2] = NULL;
//
//		for (int i = v2 + 1; i < graph->numVertices; i++) {
//			graph->adjLists[i - 1] = graph->adjLists[i];
//		}
//		graph->adjLists[graph->numVertices - 1] = NULL;
//
//		graph->numVertices--;
//
//		for (int i = 0; i < graph->numVertices; i++) {
//			struct node* adj = graph->adjLists[i];
//			while (adj) {
//				if (adj->vertex > v2) {
//					adj->vertex--;
//				}
//				adj = adj->next;
//			}
//		}
//	}
//	else { return; }
//}
//
//
//void splitV(struct Graph* graph, int v) {
//	if (v < 0 || v >= graph->numVertices) return;
//
//	int newV1 = graph->numVertices;
//	int newV2 = graph->numVertices + 1;
//
//	graph->numVertices += 1;
//	graph->adjLists = (struct node**)realloc(graph->adjLists, graph->numVertices * sizeof(struct node*));
//	graph->adjLists[newV1] = NULL;
//
//	struct node* temp = graph->adjLists[v];
//	while (temp) {
//		addEdge(graph, newV1, temp->vertex);
//		temp = temp->next;
//	}
//	addEdge(graph, newV1, v);
//}
//
//int main(void) {
//	int sizeG1 = 0, sizeG2 = 0, sizeG3 = 0;
//	int** G1 = NULL;
//	int** G2 = NULL;
//	int** G3 = NULL;
//
//	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
//	printf("Vvedite kol-vo versh 1 grafa: ");
//	scanf("%d", &sizeG1);
//	G1 = createG(sizeG1);
//	printf("1 graf\n");
//	printG(G1, sizeG1);
//	struct Graph* graph1 = edges(G1, sizeG1);
//	printGraph(graph1);
//
//	int v1, v2;
//	printf("Vvedite vershiny dlya otoj v graph1: ");
//	scanf("%d %d", &v1, &v2);
//	unionV(graph1, v1-1, v2-1);
//	printf("Graf posle otoj:\n");
//	printGraph(graph1);
//
//	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
//	printf("Vvedite kol-vo versh 2 grafa: ");
//	scanf("%d", &sizeG2);
//	G2 = createG(sizeG2);
//	printf("2 graf\n");
//	printG(G2, sizeG2);
//	struct Graph* graph2 = edges(G2, sizeG2);
//	printGraph(graph2);
//
//	int vert;
//	printf("Vvedite vershinu dlya raschepleniya v graph2: ");
//	scanf("%d", &vert);
//	splitV(graph2, vert - 1);
//	printf("Graf posle raschepleniya:\n");
//	printGraph(graph2);
//
//	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
//	printf("Vvedite kol-vo versh 3 grafa: ");
//	scanf("%d", &sizeG3);
//	G3 = createG(sizeG3);
//	printf("1 graf\n");
//	printG(G3, sizeG3);
//	struct Graph* graph3 = edges(G3, sizeG3);
//	printGraph(graph3);
//
//	int v3, v4;
//	printf("Vvedite vershiny dlya stjagivaniya v graph3: ");
//	scanf("%d %d", &v3, &v4);
//	styag(graph3, v3 - 1, v4 - 1);
//	printf("Graf posle stjagivaniya:\n");
//	printGraph(graph3);
//}