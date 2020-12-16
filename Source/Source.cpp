#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "StringMatching.h"
#include "TestCases.h"

using namespace std;

#define MAXCHAR 100
const char FileIn[] = "INPUT.txt";
const char FileOut[] = "OUTPUT.txt";

#define d 256

int main() {
    srand((int)time(NULL));
    FILE* fin, *fout;
    fin = fopen(FileIn, "w");
    Gen_Random_Test(fin);
    fclose(fin);
    
    fin = fopen(FileIn, "r");
    fout = fopen(FileOut, "w");
	int W, H;
	fscanf(fin, "%d%d", &W, &H);
	char** table = (char**)malloc(H * sizeof(char*));
	for (int i = 0; i < H; ++i) {
		table[i] = (char*)malloc(W * sizeof(char));
	}
	while (fgetc(fin) != '\n');
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			fscanf(fin, "%c", &table[i][j], (unsigned int)sizeof(char));
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
	

	char* word = (char*)malloc(MAXCHAR*sizeof(char));
	do {
		fgets(word, 20, fin);
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
                    printf("%s (%d,%d) LR\n", word, i + 1, pos + 1);
                    fprintf(fout, "%s (%d,%d) LR\n", word, i + 1, pos + 1);
                }
                else {
                    cntNF++;
                    if (cntNF == W)
                        found_horizontal = 0;
                }
            }
            cntNF = 0;
            for (int j = 0; j < W; ++j) {
                //int pos = Rabin_Karp_string_match(word, Transpose_table[j], prime, d);
                //int pos = Brute_force_string_match(word, Transpose_table[j]);
                int pos = KMP_String_match(word, Transpose_table[j]);

                if (pos != -1) {
                    printf("%s (%d,%d) TD\n", word, j + 1, pos + 1);
                    fprintf(fout,"%s (%d,%d) TD\n", word, j + 1, pos + 1);

                }
                else {
                    cntNF++;
                    if (cntNF == H && found_horizontal == 0) {
                        printf("%s (0,0) NF\n", word);
                        fprintf(fout, "%s (0,0) NF\n", word);
                    }
                }
            }
            
        }


	} while (strcmp(word, "#") != 0);
	
	
    for (int i = 0; i < H; ++i) {
        free(table[i]);
    }
    free(table);

    for (int i = 0; i < W; ++i) {
        free(Transpose_table[i]);
    }
    free(Transpose_table);
    
    free(word);
    fclose(fout);
	fclose(fin);
    return 0;
}

























