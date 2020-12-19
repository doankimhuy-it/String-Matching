#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <string>
#include <vector>
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
	FILE* fin;
	//fin = fopen(FileIn, "w");
	//Gen_Random_Test(fin);
	//Gen_Naive_Worst_Case_Test(fin);
	//Gen_RK_Worst_Case_Test(fin);
	//Gen_KMP_Worst_Case_Test(fin);
	//fclose(fin);

	fin = fopen(FileIn, "r");
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
	vector<string> words;
	vector<pair<int, int>> positions;
	vector<bool> isFound;
	vector<bool> isLR;

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
					int pos = Brute_force_string_match(word, table[i]);
					//int pos = KMP_String_match(word, table[i]);
					if (pos != -1) {
						found++;
						string word1(word);
						words.push_back(word1);
						positions.push_back(make_pair(i + 1, pos + 1));
						isFound.push_back(true);
						isLR.push_back(true);
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
					int pos = Brute_force_string_match(word, Transpose_table[j]);
					//int pos = KMP_String_match(word, Transpose_table[j]);

					if (pos != -1) {
						found++;
						string word1(word);
						words.push_back(word1);
						positions.push_back(make_pair(j + 1, pos + 1));
						isFound.push_back(true);
						isLR.push_back(false);
					}
					else {
						cntNF++;
						if (cntNF == W && found_horizontal == 0) {
							string word1(word);
							words.push_back(word1);
							positions.push_back(make_pair(0, 0));
							isFound.push_back(false);
							isLR.push_back(false);
						}
					}
				}
			}
		}
	} while (strcmp(word, "#") != 0);
	auto end = high_resolution_clock::now();
	double Stime = (double)(duration_cast<microseconds>(end - start).count());

	//FILE* ftime = fopen("TIME.txt", "w");
	//fprintf(ftime, "Execution time: %fmicrosec", Stime);

	printf("%d\n", found);
	int len = (int)words.size();
	for (int i = 0; i < len; ++i) {
		printf("%s (%d,%d) ", words.at(i).c_str(), positions.at(i).first, positions.at(i).second);
		if (isFound.at(i)) {
			if (isLR.at(i)) {
				printf("LR\n");
			}
			else {
				printf("TD\n");
			}
		}
		else {
			printf("NF\n");
		}
	}
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
	//fclose(ftime);
	return 0;
}
