//#define _CRT_SECURE_NO_WARNINGS 
//
//#include "stdio.h" 
//#include "cstdlib" 
//#include "time.h" 
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
//int** unionG(int** G1, int** G2, int size1, int size2) {
//	int sizemax = (size1 > size2) ? size1 : size2;
//	int sizemin = (size1 < size2) ? size1 : size2;
//	int** Gmax = (size1 > size2) ? G1 : G2;
//	int** Gmin = (size1 < size2) ? G1 : G2;
//	int** Gtemp = createG(sizemax);
//	for (int i = 0; i < sizemin; i++) {
//		for (int j = 0; j < sizemin; j++) {
//			Gtemp[i][j] = Gmin[i][j] | Gmax[i][j];
//		}
//	}
//	for (int i = 0; i < sizemax; i++) {
//		for (int j = sizemin; j < sizemax; j++) {
//			Gtemp[i][j] = Gmax[i][j];
//			Gtemp[j][i] = Gtemp[i][j];
//		}
//	}
//	return Gtemp;
//}
//
//int** intersectoinG(int** G1, int** G2, int size1, int size2) {
//	int sizemin = (size1 < size2) ? size1 : size2;
//	int** Gtemp = createG(sizemin);
//	for (int i = 0; i < sizemin; i++) {
//		for (int j = 0; j < sizemin; j++) {
//			Gtemp[i][j] = G1[i][j] & G2[i][j];
//		}
//	}
//	return Gtemp;
//}
//int** xorG(int** G1, int** G2, int size1, int size2) {
//	int sizemax = (size1 > size2) ? size1 : size2;
//	int sizemin = (size1 < size2) ? size1 : size2;
//	int** Gmax = (size1 > size2) ? G1 : G2;
//	int** Gmin = (size1 < size2) ? G1 : G2;
//	int** Gtemp = createG(sizemax);
//	for (int i = 0; i < sizemax; i++) {
//		for (int j = 0; j < sizemax; j++) {
//			if (i < sizemin && j < sizemin) {
//				Gtemp[i][j] = Gmax[i][j] ^ Gmin[i][j];
//			}
//			else {
//				Gtemp[i][j] = Gmax[i][j];
//			}
//		}
//	}
//	return Gtemp;
//}
//
//int main(void) {
//
//	srand(673453875);
//	int sizeG1 = 0, sizeG2 = 0, sizeG3, sizeG4;
//	int** G1 = NULL;
//	int** G2 = NULL;
//	int** G3 = NULL;
//	int** G4 = NULL;
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
//	sizeG3 = (sizeG1 > sizeG2) ? sizeG1 : sizeG2;
//	G3 = unionG(G1, G2, sizeG1, sizeG2);
//	printf("Obed:\n");
//	printG(G3, sizeG3);
//
//	sizeG3 = (sizeG1 < sizeG2) ? sizeG1 : sizeG2;
//	G3 = intersectoinG(G1, G2, sizeG1, sizeG2);
//	printf("Peresech:\n");
//	printG(G3, sizeG3);
//
//	sizeG4 = (sizeG1 > sizeG2) ? sizeG1 : sizeG2;
//	G4 = xorG(G1, G2, sizeG1, sizeG2);
//	printf("Kolc summa:\n");
//	printG(G4, sizeG4);
//}