#ifndef _STRINGMATCHING_H_
#define _STRINGMATCHING_H_



int Brute_force_string_match(char pat[], char txt[]);
int Rabin_Karp_string_match(char pat[], char txt[], int q, int d);

void computeLPSArray(char pat[], int M, int lps[]);
int KMP_String_match(char pat[], char txt[]);


#endif // _STRINGMATCHING_H_