#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "d2aoc.h"


int main (int argc, const char* argv[])
{
	FILE *inFile;



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



	return EXIT_SUCCESS;
}

