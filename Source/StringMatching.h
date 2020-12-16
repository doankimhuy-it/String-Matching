#ifndef _STRINGMATCHING_H_
#define _STRINGMATCHING_H_



int Brute_force_string_match(string pat, string txt);
int Rabin_Karp_string_match(string pat, string txt, int q,int d);

void computeLPSArray(string pat, int M, int lps[]);
int KMP_String_match(string pat, string txt);


#endif // _STRINGMATCHING_H_