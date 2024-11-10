//#define _CRT_SECURE_NO_WARNINGS
//
//#include "stdio.h"
//#include "cstdlib"
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
//	printf("\n");
//	return;
//}
//
//int** delV(int** G, int size, int v) {
//	int** Gtemp = createG(size - 1);
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < size; j++) {
//			if (i < v && j < v) Gtemp[i][j] = G[i][j];
//			if (i > v && j > v) Gtemp[i - 1][j - 1] = G[i][j];
//			if (i > v && j < v) Gtemp[i - 1][j] = G[i][j];
//			if (i < v && j > v) Gtemp[i][j - 1] = G[i][j];
//		}
//	}
//	for (int i = 0; i < size; i++) {
//		free(G[i]);
//	}
//	free(G);
//	G = NULL;
//
//	return Gtemp;
//}
//
//int** unionV(int** G, int size, int v1, int v2) {
//	for (int i = 0; i < size; i++) {
//		if (G[v2][i] == 1) {
//			G[v1][i] = G[v2][i];
//			G[i][v1] = G[i][v2];
//		}
//	}
//
//	G = delV(G, size, v2);
//	return G;
//}
//
//int** contrE(int** G, int size, int v1, int v2) {
//	if (G[v1][v2] != 1) {
//		printf("reb no");
//		return G;
//	}
//	else {
//		G[v1][v2] = 0;
//		G[v2][v1] = 0;
//
//		for (int i = 0; i < size; i++) {
//			if (G[v2][i] == 1) {
//				G[v1][i] = G[v2][i];
//				G[i][v1] = G[i][v2];
//
//			}
//		}
//		G = delV(G, size, v2);
//
//		return G;
//
//	}
//}
//
//int** splitV(int** G, int size, int v) {
//	int** Gtemp = createG(size + 1);
//	for (int i = 0; i < size; i++) {
//		Gtemp[i][size] = G[i][v];
//		Gtemp[size][i] = G[v][i];
//	}
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < size; j++) {
//			Gtemp[i][j] = G[i][j];
//		}
//	}
//	for (int i = 0; i < size; i++) {
//		free(G[i]);
//	}
//	free(G);
//	G = NULL;
//
//	return Gtemp;
//}
//
//
//int main(void) {
//	int sizeG1 = 0, sizeG2 = 0, sizeG4 = 0, sizeG5 = 0;
//	int** G1 = NULL;
//	int** G2 = NULL;
//	int** G3 = NULL;
//
//	int** G4 = NULL;
//	int** G44 = NULL;
//
//	int** G5 = NULL;
//	int** G55 = NULL;
//
//	printf("-=-=-=-=-=-ZADANIE 1-=-=-=-=-=-=\n");
//	printf("Vvedite kol-vo versh 1 grafa: ");
//	scanf("%d", &sizeG1);
//	printf("Vvedite kol-vo versh 2 grafa: ");
//	scanf("%d", &sizeG2);
//
//	G1 = createG(sizeG1);
//	printf("1 graf\n");
//	printG(G1, sizeG1);
//
//	G2 = createG(sizeG2);
//	printf("2 graf\n");
//	printG(G2, sizeG2);
//
//	
//
//	printf("-=-=-=-=-=-ZADANIE 2-=-=-=-=-=-=\n");
//	int v1, v2;
//	printf("Versh dlya otoj grafa 1: ");
//	scanf("%d %d", &v1, &v2);
//	G3 = unionV(G1, sizeG1, v1 - 1, v2 - 1);
//	printf("3 graf otoj\n");
//	printG(G3, sizeG1 - 1);
//
//	int v3, v4;
//	printf("Vvedite kol-vo versh 4 grafa: ");
//	scanf("%d", &sizeG4);
//
//	G4 = createG(sizeG4);
//	printf("4 graf: \n");
//	printG(G4, sizeG4);
//
//	printf("Versh dlya udaleniya mejdu rebro: ");
//	scanf("%d %d", &v3, &v4);
//	G44 = contrE(G4, sizeG4, v3 - 1, v4 - 1);
//	printf("4 graf contrE^\n");
//	printG(G44, sizeG4-1);
//
//	int v5;
//	printf("Vvedite kol-vo versh 5 grafa: ");
//	scanf("%d", &sizeG5);
//
//	G5 = createG(sizeG5);
//	printf("5 graf: \n");
//	printG(G5, sizeG5);
//
//	printf("Versh dlya copirky: ");
//	scanf("%d", &v5);
//	G55 = splitV(G5, sizeG5, v5 - 1);
//	printf("5 graf split\n");
//	printG(G55, sizeG5+1);
//}