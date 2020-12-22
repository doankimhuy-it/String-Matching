#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <string>
#include <vector>

// We use these functions to generate test 
int random(int l, int r);
void Gen_Random_Test(FILE* fin);
void Gen_Naive_Worst_Case_Test(FILE* fin);
void Gen_RK_Worst_Case_Test(FILE* fin);
void Gen_KMP_Worst_Case_Test(FILE* fin);

// Pre-Declare for String-Matching Algorithm
int Brute_force_string_match(char pat[], char txt[]);
int Rabin_Karp_string_match(char pat[], char txt[], int q, int d);
int KMP_String_match(char pat[], char txt[]);
void computeLPSArray(char pat[], int M, int lps[]);


using namespace std;
using namespace std::chrono;

#define MAXCHAR 100
const char FileIn[] = "INPUT.txt";
const char FileOut[] = "OUTPUT.txt";

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

// StringMatching Algorithm
int Brute_force_string_match(char pat[], char txt[])
{
	int M = strlen(pat);
	int N = strlen(txt);

	/* A loop to slide pat[] one by one */
	for (int i = 0; i <= N - M; i++) {
		int j;

		/* For current index i, check for pattern match */
		for (j = 0; j < M; j++)
			if (txt[i + j] != pat[j])
				break;

		if (j == M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
			return i;
	}
	return -1;
}

int Rabin_Karp_string_match(char pat[], char txt[], int q, int d) 
{
	int M = strlen(pat);
	int N = strlen(txt);
	int i, j;
	int p = 0; // hash value for pattern  
	int t = 0; // hash value for txt  
	int h = 1;

	// The value of h would be "pow(d, M-1)%q"  
	for (i = 0; i < M - 1; i++)
		h = (h * d) % q;

	// Calculate the hash value of pattern and first  
	// window of text  
	for (i = 0; i < M; i++)
	{
		p = (d * p + pat[i]) % q;
		t = (d * t + txt[i]) % q;
	}

	// Slide the pattern over text one by one  
	for (i = 0; i <= N - M; i++)
	{

		// Check the hash values of current window of text  
		// and pattern. If the hash values match then only  
		// check for characters on by one  
		if (p == t)
		{
			/* Check for characters one by one */
			for (j = 0; j < M; j++)
			{
				if (txt[i + j] != pat[j])
					break;
			}

			// if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]  
			if (j == M)
				//cout << "Pattern found at index " << i << endl;
				return i;
		}

		// Calculate hash value for next window of text: Remove  
		// leading digit, add trailing digit  
		if (i < N - M)
		{
			t = (d * (t - txt[i] * h) + txt[i + M]) % q;

			// We might get negative value of t, converting it  
			// to positive  
			if (t < 0)
				t = (t + q);
		}
	}
	return -1;
}

// Prints occurrences of txt[] in pat[] 
int KMP_String_match(char pat[], char txt[])
{
	int M = strlen(pat);
	int N = strlen(txt);

	// create lps[] that will hold the longest prefix suffix 
	// values for pattern 
	int* lps = new int[M];

	// Preprocess the pattern (calculate lps[] array) 
	computeLPSArray(pat, M, lps);

	int i = 0; // index for txt[] 
	int j = 0; // index for pat[] 
	while (i < N) {
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == M) {
			//printf("Found pattern at index %d ", i - j);
			return i - j;
			//j = lps[j - 1];
		}

		// mismatch after j matches 
		else if (i < N && pat[j] != txt[i]) {
			// Do not match lps[0..lps[j-1]] characters, 
			// they will match anyway 
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
	delete[]lps;
	return -1;
}

// Fills lps[] for given patttern pat[0..M-1] 
void computeLPSArray(char pat[], int M, int lps[])
{
	// length of the previous longest prefix suffix 
	int len = 0;

	lps[0] = 0; // lps[0] is always 0 

	// the loop calculates lps[i] for i = 1 to M-1 
	int i = 1;
	while (i < M) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else // (pat[i] != pat[len]) 
		{
			// This is tricky. Consider the example. 
			// AAACAAAA and i = 7. The idea is similar 
			// to search step. 
			if (len != 0) {
				len = lps[len - 1];

				// Also, note that we do not increment 
				// i here 
			}
			else // if (len == 0) 
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

// Function for generate test

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