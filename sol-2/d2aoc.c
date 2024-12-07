#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "d2aoc.h"

#define BUFF_512B 512
#define MAX_REPORT_LENGTH 8
#define ABS(X) ((X) < 0 ? -(X) : (X))

int main (int argc, const char* argv[])
{
	FILE *inFile;
	char line[BUFF_512B], *strno;
	int R[MAX_REPORT_LENGTH], auxNum[MAX_REPORT_LENGTH], RCount;
	int safeReportCount, no;
	int i, j;
	bool safe;

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
	safe = FALSE;
	RCount = 0;
	safeReportCount = 0;
	while(fgets(line, BUFF_512B, inFile) != NULL)
	{
		//Parse line into numerical array
		(void) printf("%s", line);
		strno = strtok(line, " \n");
		do{
			no = atoi(strno);
			R[RCount++] = no;
		}while((strno = strtok(NULL, " \n")));

		// Check if line is safe
		if(safe_report(R, RCount) == FALSE)
		{
			// Take out one number at once
			for(i = 0; (i < RCount) && (!safe); i++)
			{
				// Remove said number
				(void) memcpy(auxNum, R, sizeof(auxNum[0]) * RCount);
				for(j = i; j < RCount - 1; j ++)
					auxNum[j] = auxNum[j + 1];

				// Assert safety
				if(safe_report(auxNum, RCount - 1))
					safe = TRUE;
			}

			// Assert if line short of one element is safe
			safeReportCount = safe ? safeReportCount + 1 : safeReportCount;
		}
		else
		{
			safeReportCount++;
		}

		safe = FALSE;
		RCount = 0;
	}

	(void) printf("\nNumber of safe reports -> %d\n", safeReportCount);
	return EXIT_SUCCESS;
}

bool safe_report(int num[], int n)
{
	int i;
	int delta;
	prog level, lastLevel;

	level = (num[0] > num[1]) ? DECREASING : \
			(num[0] < num[1]) ? INCREASING : \
			level;
	lastLevel = level;
	for(i = 1; i < n; i ++)
	{
		// Check progression between two elements
		level = (num[i - 1] > num[i]) ? DECREASING : \
				(num[i - 1] < num[i]) ? INCREASING : \
				level;
		// Calculate the difference between two elements
		delta = ABS(num[i - 1] - num[i]);

		// Assert that the progression has not changed
		// and that the difference is out of range [1, 3]
		if((lastLevel != level) || (delta < 1 || delta > 3))
			return FALSE;

		lastLevel = level;
	}
	return TRUE;
}

