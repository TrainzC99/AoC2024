#include <stdio.h>

#define MAX_LIST_LENGTH 1000
#define ABS(X) ((X) < 0 ? -(X) : (X))

int main ()
{
	int a, b;
	int len;
	int A[MAX_LIST_LENGTH], B[MAX_LIST_LENGTH];
	int ai, bi;
	int i, j;
	int aux;
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

	// Sort numbers - Exchange sort
	for(i = 0; i < len - 1; i ++)
		for(j = i + 1; j < len; j ++)
		{
			if(A[i] > A[j])
			{
				aux = A[i];
				A[i] = A[j];
				A[j] = aux;
			}
			if(B[i] > B[j])
			{
				aux = B[i];
				B[i] = B[j];
				B[j] = aux;
			}
		}

	for(i = 0; i < len; i ++)
		(void) printf("%d %d\n", A[i], B[i]);

	sum = 0;
	for(i = 0; i < len; i ++)
		sum = sum + ABS(A[i] - B[i]);

	(void) printf("Total distance between the lists is -> %lld\n", sum);

	return 0;
}

