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
		int W = random(1, 10);
		int H = random(1, 10);
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
			fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		for (int i = 0; i < 10; ++i) { // generate 10 LR words
			int startPos = random(0, W - 2);
			int len = random(2, W - startPos);
			int rowNum = random(1, H);
			for (int j = startPos; j < startPos + len; ++j) {
				fprintf(fin, "%c", table[rowNum - 1][j]);
			}
			fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		for (int i = 0; i < 10; ++i) { // generate 10 TD words
			int startPos = random(0, H - 2);
			int len = random(2, H - startPos);
			int colNum = random(1, W);
			for (int j = startPos; j < startPos + len; ++j) {
				fprintf(fin, "%c", table[j][colNum - 1]);
			}
			fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		for (int i = 0; i < 5; ++i) { // random words for NF cases
			int randLen = random(2, W - 1);
			for (int j = 0; j <= randLen; ++j) {
				fprintf(fin, "%c", random(65, 90));
			}
			fprintf(fin, "\0");
			fprintf(fin, "\n");
		}
		fprintf(fin, "#");
		for (int i = 0; i < H; ++i) {
			free(table[i]);
		}
		free(table);
		fclose(fin);
	}
	else {
		printf("Cannot open input file!!!");
	}
}