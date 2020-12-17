#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "StringMatching.h"
#include "TestCases.h"

using namespace std;
using namespace std::chrono;

#define MAXCHAR 100
const char FileIn[] = "INPUT.txt";
const char FileOut[] = "OUTPUT.txt";

#define d 256

int main() {
	srand((int)time(NULL));
	FILE* fin, *ftmp;
	fin = fopen(FileIn, "w");
	//Gen_Random_Test(fin);
	//Gen_Naive_Worst_Case_Test(fin);
	//Gen_RK_Worst_Case_Test(fin);
	Gen_KMP_Worst_Case_Test(fin);
	fclose(fin);

	fin = fopen(FileIn, "r");
	ftmp = fopen("TMP.txt", "w");
	int W, H;
	fscanf(fin, "%d %d", &W, &H);
	char** table = (char**)malloc(H * sizeof(char*));
	for (int i = 0; i < H; ++i) {
		table[i] = (char*)malloc(W * sizeof(char));
	}
	while (fgetc(fin) != '\n');
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			fscanf(fin, "%c", &table[i][j]);
			fgetc(fin);
		}
	}

	char** Transpose_table = (char**)malloc(W * sizeof(char*));
	for (int i = 0; i < W; ++i) {
		Transpose_table[i] = (char*)malloc(H * sizeof(char));
	}

	for (int i = 0; i < W; ++i) {
		for (int j = 0; j < H; ++j) {
			Transpose_table[i][j] = table[j][i];
		}
	}

	char* word = (char*)malloc(MAXCHAR * sizeof(char));
	int found = 0;
	auto start = high_resolution_clock::now();
	do {
		if ((fgets(word, 100, fin) != "\0")) {
			if (strcmp(word, "#") != 0) {
				word[strlen(word) - 1] = '\0';
				bool found_horizontal = 1;
				int cntNF = 0;

				int prime = 101;
				for (int i = 0; i < H; ++i) {
					//int pos = Rabin_Karp_string_match(word, table[i], prime, d);
					//int pos = Brute_force_string_match(word, table[i]);
					int pos = KMP_String_match(word, table[i]);
					if (pos != -1) {
						found++;
						printf("%s (%d,%d) LR\n", word, i + 1, pos + 1);
						fprintf(ftmp, "%s (%d,%d) LR\n", word, i + 1, pos + 1);
					}
					else {
						cntNF++;
						if (cntNF == H)
							found_horizontal = 0;
					}
				}
				cntNF = 0;
				for (int j = 0; j < W; ++j) {
					//int pos = Rabin_Karp_string_match(word, Transpose_table[j], prime, d);
					//int pos = Brute_force_string_match(word, Transpose_table[j]);
					int pos = KMP_String_match(word, Transpose_table[j]);

					if (pos != -1) {
						found++;
						printf("%s (%d,%d) TD\n", word, j + 1, pos + 1);
						fprintf(ftmp, "%s (%d,%d) TD\n", word, j + 1, pos + 1);
					}
					else {
						cntNF++;
						if (cntNF == W && found_horizontal == 0) {
							printf("%s (0,0) NF\n", word);
							fprintf(ftmp, "%s (0,0) NF\n", word);
						}
					}
				}
			}
		}
	} while (strcmp(word, "#") != 0);
	auto end = high_resolution_clock::now();
	double Stime = (double)(duration_cast<microseconds>(end - start).count());
	fclose(ftmp);
	ftmp = fopen("TMP.txt", "r");

	FILE* fout = fopen(FileOut, "w");
	fprintf(fout, "%d\n", found);

	fseek(ftmp, 0, SEEK_SET);
	char c = fgetc(ftmp);
	while (c != EOF)
	{
		fputc(c, fout);
		c = fgetc(ftmp);
	}

	FILE* ftime = fopen("TIME.txt", "w");
	fprintf(ftime, "Execution time: %fmicrosec", Stime);
	for (int i = 0; i < H; ++i) {
		free(table[i]);
	}
	free(table);

	for (int i = 0; i < W; ++i) {
		free(Transpose_table[i]);
	}
	free(Transpose_table);

	free(word);
	fclose(fin);
	fclose(ftime);
	fclose(ftmp);
	fclose(fout);
	return 0;
}

























