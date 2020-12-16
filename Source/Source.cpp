#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
#include "StringMatching.h"
#include "TestCases.h"

using namespace std;

#define MAXCHAR 100
const string FileIn = "INPUT.txt";
const string FileOut = "OUTPUT.txt";

#define d 256

int main() {
    srand((int)time(NULL));
    ifstream(FileIn);
    ofstream(FileOut);

    Gen_Random_Test(fin);
	int W, H;
    FileIn >> W >> H;
	
	char** table = new char*[H * sizeof(char*)];
	for (int i = 0; i < H; ++i) {
		table[i] = new char[W * sizeof(char)];
	}
    
	FileIn.get();
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			FileIn >> table[i][j];
		}
	}
	FileIn.get();
    
    char** Transpose_table = new char*[H * sizeof(char*)];
    for (int i = 0; i < W; ++i) {
        Transpose_table[i] = new char[W * sizeof(char)];
    }
    
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            Transpose_table[i][j] = table[j][i];
        }
    }
	

	string word;
	do {
		getline(FileIn, word);
        if (word[0] != '#') {
            
            word[word.size() - 1] = '\0';
            bool found_horizontal = 1;
            int cntNF = 0;

            int prime = 101;
            for (int i = 0; i < H; ++i) {
                //int pos = Rabin_Karp_string_match(word, table[i], prime, d);
                //int pos = Brute_force_string_match(word, table[i]);
                int pos = KMP_String_match(word, table[i]);
                if (pos != -1) {
                    FileOut << word << " (" << i + 1 << ", " << pos + 1 << " LR\n";
                    cout << word << " (" << i + 1 << ", " << pos + 1 << " LR\n";
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
                    FileOut << word << " (" << j + 1 << ", " << pos + 1 << " TD\n";
                    cout << word << " (" << j + 1 << ", " << pos + 1 << " TD\n";

                }
                else {
                    cntNF++;
                    if (cntNF == H && found_horizontal == 0) {
                        FileOut << word << " NF\n";
                        cout << word << " NF\n";
                    }
                }
            }
            
        }


	} while (word[0] != '#');
	
	
    for (int i = 0; i < H; ++i) {
        delete[] table[i];
    }
    delete[] table;

    for (int i = 0; i < H; ++i) {
        delete[] Transpose_table[i];
    }
    delete[] Transpose_table;
    FileIn.close();
    FileOut.close();
}
