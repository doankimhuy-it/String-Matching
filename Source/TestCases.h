#ifndef _TESTCASES_H_
#define _TESTCASES_H_

#include <stdio.h>

int random(int l, int r);
void Gen_Random_Test(FILE* fin);
void Gen_Naive_Worst_Case_Test(FILE* fin);
void Gen_RK_Worst_Case_Test(FILE* fin);
void Gen_KMP_Worst_Case_Test(FILE* fin);

#endif // !_TESTCASES_H_