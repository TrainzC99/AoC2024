#include <stdio.h>

#define MAX_LIST_LENGTH 1000
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

int main ()
{
	int a, b;
	int len;
	int A[MAX_LIST_LENGTH], B[MAX_LIST_LENGTH];
	int ai, bi, i;
	int max;
	long long sum;

	ai = 0;
	bi = 0;

	// Read length
	(void) scanf("%d", &len);

	// Read numbers
	while(scanf("%d %d", &a, &b) != EOF)
	{
		A[ai++] = a;
		B[bi++] = b;
	}

	// Get maximum between the lists
	max = 0;
	for(i = 0; i < len; i ++)
	{
		max = MAX(B[i], max);
		max = MAX(A[i], max);
	}

	(void) printf("Max of both lists = %d\n", max);

	// Number frequency in the right list
	int FQ[max + 1];
	for(i = 0; i <= max; i ++)
		FQ[i] = 0;
	for(i = 0; i < len; i ++)
		FQ[B[i]]++;

	sum = 0;
	for(i = 0; i < len; i ++)
		sum = sum + A[i] * FQ[A[i]];

	(void) printf("Similarity score is -> %lld\n", sum);

	return 0;
}

