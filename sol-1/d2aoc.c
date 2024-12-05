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
	int no;
	int R[MAX_REPORT_LENGTH], RCount;
	int safeReportCount;

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
	RCount = 0;
	safeReportCount = 0;
	while(fgets(line, BUFF_512B, inFile) != NULL)
	{
		(void) printf("%s", line);
		strno = strtok(line, " \n");
		do{
			no = atoi(strno);
			R[RCount++] = no;
		}while((strno = strtok(NULL, " \n")));
		safeReportCount = (safe_report(R, RCount) == TRUE) ? \
						  safeReportCount + 1 : safeReportCount;
		RCount = 0;
	}

	(void) printf("Number of safe reports -> %d\n", safeReportCount);
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
		level = (num[i - 1] > num[i]) ? DECREASING : \
				(num[i - 1] < num[i]) ? INCREASING : \
				level;
		if(lastLevel != level)
			return FALSE;

		delta = ABS(num[i - 1] - num[i]);
		if(delta < 1 || delta > 3)
			return FALSE;

		lastLevel = level;
	}

	return TRUE;
}

