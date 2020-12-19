#include "TestCases.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define MAXCHAR 100

const char FileIn[] = "INPUT.txt";
const char FileOut[] = "OUTPUT.txt";

int random(int l, int r) {
	if (r > l) {
		return rand() % (r - l + 1) + l;
	}
	return r;
}

void Gen_Random_Test(FILE* fin) {
	if (fin) {
		int W = 50;
		//int H = random(1, 10);
		int H = W;
		char** table = (char**)malloc(H * sizeof(char*));
		for (int i = 0; i < H; ++i) {
			table[i] = (char*)malloc(W * sizeof(char));
		}
		fprintf(fin, "%d %d\n", W, H);
		for (int i = 0; i < H; ++i) {
			int j;
			for (j = 0; j < W - 1; ++j) {
				char ch = random(65, 90);
				fprintf(fin, "%c ", ch);
				table[i][j] = ch;
			}
			char ch = random(65, 90);
			fprintf(fin, "%c", ch);
			table[i][j] = ch;
			fprintf(fin, "\n");
		}
		int startPos = random(1, W / 2);
		int len = W / 2;
		int randRow = random(0, W - 1);
		for (int i = 0; i < len; ++i) {
			fprintf(fin, "%c", table[randRow][startPos + i]);
		}
		fprintf(fin, "\n");
		fprintf(fin, "#");
		for (int i = 0; i < H; ++i) {
			free(table[i]);
		}
		free(table);
	}
	else {
		printf("Cannot open input file!!!");
	}
}

void Gen_Naive_Worst_Case_Test(FILE* fin) {
	if (fin) {
		int W = 50;
		//int H = random(1, 10);
		int H = W;
		fprintf(fin, "%d %d\n", W, H);
		char ch = random(65, 90); // generate a table with full ch char
		char ch1 = random(65, 90); // only last row and col will be filled with ch1
		for (int i = 0; i < H; ++i) {
			if (i == H - 1) {
				for (int j = 0; j < W - 1; ++j) {
					fprintf(fin, "%c ", ch1);
				}
				fprintf(fin, "%c", ch1);
				fprintf(fin, "\n");
			}
			else {
				for (int j = 0; j < W - 1; ++j) {
					fprintf(fin, "%c ", ch);
				}
				fprintf(fin, "%c", ch1);
				fprintf(fin, "\n");
			}
		}
		for (int i = 0; i < W / 2 - 1; ++i) {
			fprintf(fin, "%c", ch);
		}
		fprintf(fin, "%c", ch1);
		fprintf(fin, "\n");
		
		fprintf(fin, "#");
	}
	else {
		printf("Cannot open input file!!!");
	}
}

void Gen_RK_Worst_Case_Test(FILE* fin) {
	if (fin) {
		int W = 50;
		//int H = random(1, 10);
		int H = W;
		fprintf(fin, "%d %d\n", W, H);
		char ch = random(65, 90); // generate a table with full ch char
		char ch1 = random(65, 90);
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W - 1; ++j) {
				fprintf(fin, "%c ", ch);
			}
			fprintf(fin, "%c", ch);
			fprintf(fin, "\n");

		}
		fprintf(fin, "%c", ch1);
		for (int i = 0; i < W / 2 - 1; ++i) {
			fprintf(fin, "%c", ch);
		}
		fprintf(fin, "\n");
		fprintf(fin, "#");
	}
	else {
		printf("Cannot open input file!!!");
	}
}

void Gen_KMP_Worst_Case_Test(FILE* fin) {
	if (fin) {
		int W = 50;
		//int H = random(1, 10);
		int H = W;
		fprintf(fin, "%d %d\n", W, H);
		for (int i = 0; i < H; ++i) {
			int j;
			for (j = 0; j < W - 1; ++j) {
				char ch = random(65, 90);
				fprintf(fin, "%c ", ch);
			}
			char ch = random(65, 90);
			fprintf(fin, "%c", ch);
			fprintf(fin, "\n");
		}
		char ch = random(65, 90);
		for (int i = 0; i < W / 2; ++i) {
			fprintf(fin, "%c", ch);
		}
		fprintf(fin, "\n");
		fprintf(fin, "#");
	}
	else {
		printf("Cannot open input file!!!");
	}
}