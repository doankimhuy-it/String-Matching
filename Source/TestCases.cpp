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

void Gen_Random_Test(FILE* fin, int n) {
	if (fin) {
		int W = n;
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
			//fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		for (int i = 0; i < W / 3; ++i) {
			int startPos = random(0, W - 2);
			int len = random(2, W - startPos);
			int rowNum = random(1, H);
			for (int j = startPos; j < startPos + len; ++j) {
				fprintf(fin, "%c", table[rowNum - 1][j]);
			}
			//fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		for (int i = 0; i < W / 3; ++i) {
			int startPos = random(0, H - 2);
			int len = random(2, H - startPos);
			int colNum = random(1, W);
			for (int j = startPos; j < startPos + len; ++j) {
				fprintf(fin, "%c", table[j][colNum - 1]);
			}
			//fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		for (int i = 0; i < W - W / 3 * 2; ++i) {
			int randLen = random(2, W - 1);
			for (int j = 0; j <= randLen; ++j) {
				fprintf(fin, "%c", random(65, 90));
			}
			//fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
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

void Gen_Naive_Worst_Case_Test(FILE* fin, int n) {
	if (fin) {
		int W = n;
		//int H = random(1, 10);
		int H = W;
		fprintf(fin, "%d %d\n", W, H);
		char ch = random(65, 90); // generate a table with full ch char
		char ch1 = random(65, 90); // only last row and col will be filled with 
		for (int i = 0; i < H; ++i) {
			if (i == H - 1) {
				for (int j = 0; j < W - 1; ++j) {
					fprintf(fin, "%c ", ch1);
				}
				fprintf(fin, "%c", ch1);
				fprintf(fin, "\0");
				fprintf(fin, "\n");
			}
			else {
				for (int j = 0; j < W - 1; ++j) {
					fprintf(fin, "%c ", ch);
				}
				fprintf(fin, "%c", ch1);
				fprintf(fin, "\0");
				fprintf(fin, "\n");
			}
		}
		for (int i = 0; i < W - 1; ++i) {
			for (int j = 0; j <= i; ++j) {
				fprintf(fin, "%c", ch);
			}
			fprintf(fin, "%c", ch1);
			fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		fprintf(fin, "#");
	}
	else {
		printf("Cannot open input file!!!");
	}
}

void Gen_RK_Worst_Case_Test(FILE* fin, int n) {
	if (fin) {
		int W = n;
		//int H = random(1, 10);
		int H = W;
		fprintf(fin, "%d %d\n", W, H);
		char ch = random(65, 90); // generate a table with full ch char
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W - 1; ++j) {
				fprintf(fin, "%c ", ch);
			}
			fprintf(fin, "%c", ch);
			fprintf(fin, "\0");
			fprintf(fin, "\n");

		}
		for (int i = 0; i < W - 1; ++i) {
			int randLen = random(2, W);
			for (int j = 0; j < randLen; ++j) {
				fprintf(fin, "%c", ch);
			}
			fprintf(fin, "%c", random(65, 90));
			fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		fprintf(fin, "#");
	}
	else {
		printf("Cannot open input file!!!");
	}
}

void Gen_KMP_Worst_Case_Test(FILE* fin, int n) {
	if (fin) {
		int W = n;
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
			fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		for (int i = 0; i < W - 1; ++i) { // random words for NF cases
			int randLen = random(2, W - 1);
			char ch = random(65, 90);
			for (int j = 0; j <= randLen; ++j) {
				fprintf(fin, "%c", ch);
			}
			fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		fprintf(fin, "#");
	}
	else {
		printf("Cannot open input file!!!");
	}
}