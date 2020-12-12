#include "StringMatching.h"
#include <string.h>
#include <stdio.h>

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

int Rabin_Karp_string_match(char pat[], char txt[], int q,int d) {
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