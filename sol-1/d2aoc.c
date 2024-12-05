#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_512B 512
#define ABS(X) ((X) < 0 ? -(X) : (X))

int main (int argc, const char* argv[])
{
	FILE *inFile;
	char line[BUFF_512B], *no;
	int a, b, c;
	int delta;
	int safeCount, safeReportCount, countPairs;

	// Check for enough args were provided
	if (argc < 2)
	{
		(void) printf("Please provide input file!\n");
		exit(EXIT_FAILURE);
	}

	// File setup
	inFile = fopen(argv[1], "rb");
	if(inFile == NULL)
	{
		fprintf(stderr, "The file is unopenable!\n");
		exit(EXIT_FAILURE);
	}

	// File details
	(void) printf("File name is -> %s\n", argv[1]);

	// Read and process file line by line
	safeCount = 0;
	safeReportCount = 0;
	countPairs = 0;
	while(fgets(line, BUFF_512B, inFile) != NULL)
	{
		(void) printf("%s", line);
		no = strtok(line, " \n");
		a = atoi(no);
		no = strtok(NULL, " \n");
		b = atoi(no);
		no = strtok(NULL, " \n");
		while(no != NULL && countPairs == safeCount)
		{
			c = atoi(no);
			(void) printf("%d %d %d\n", a, b, c);

			delta = ABS(b - a);
			if(!(delta < 1 || delta > 3)) // delta >= 1 && delta <= 3
				safeCount++;
			else
				safeCount = 0;

			if((a > b && b > c) || (a < b && b < c))
				countPairs++;
			else
				countPairs = 0;

			a = b;
			b = c;
			no = strtok(NULL, " \n");
		}
		if(safeCount != 0  && safeCount == countPairs)
		{
			safeReportCount++;
			printf("after while %d %d\n", safeCount, countPairs);
		}
		safeCount = 0;
		countPairs = 0;
	}

	(void) printf("Number of safe reports -> %d\n", safeReportCount);

	return EXIT_SUCCESS;
}

