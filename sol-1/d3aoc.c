#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "d3aoc.h"

#define FSEEK_OFFSET 0
#define MAX_MATCH 5

int main (int argc, const char* argv[])
{
	FILE *inFile;
	unsigned long long fileSize;
	char *fileText;
	regex_t matchex;
	regmatch_t matches[MAX_MATCH];

	// Check for enough args were provided
	if (argc < 2)
	{
		(void) printf("Please provide input file!\n");
		exit(EXIT_FAILURE);
	}

	// File setup
	inFile = fopen(argv[1], "rb");
	checkFileOpen(inFile);
	fileSize = getFileSize(inFile);

	// File details
	(void) printf("File name is -> %s\n", argv[1]);

	// Read and store file in memory
	fileText = malloc(sizeof(*fileText) * fileSize);
	(void) fgets(fileText, fileSize, inFile);

	// Display read contents
	(void) printf("Read contents:\n");
	(void) printf("%s\n", fileText);

	// Process using RegEx
	if(regcomp(&matchex, \
				"mul([0-9]\\{1,3\\},[0-9]\\{1,3\\})", \
				REG_ICASE | REG_NEWLINE) != 0)
	{
		(void) printf("Error when processing regex\n");
		exit(EXIT_FAILURE);
	}

	// Match regex patter on input text
	while((regexec(&matchex, fileText, MAX_MATCH, matches, 0) == 0) \
			|| (*fileText == '\0'))
	{
		(void) printf("Match\n");
		(void) printf("Match found:\n %.*s\n", \
				matches[0].rm_eo - matches[0].rm_so, \
				fileText + matches[0].rm_so);

		fileText = fileText + matches[0].rm_eo;
	}
	// Free file from memory
	free(fileText);
	regfree(&matchex);

	return EXIT_SUCCESS;
}

inline int mul(int X, int Y) { return X * Y; }

/**
 * @brief This function obtains the size of a given file
 *
 * @param fp A pointer to the file
 * @return ULL The no. of bytes i.e. chars/elements/obj. in the file
 */
unsigned long long getFileSize(FILE* fp)
{
	unsigned long long size = 0;
	 //This moves the FP (file pointer) to the EOF (end of file)
	//which can be made use of later in the program
	fseek(fp, FSEEK_OFFSET, SEEK_END);
	//This return the pointer's position in the file
	size = ftell(fp);
	//This moves back the FP to the start of the file (SOF)
	rewind(fp);

	return size;
}

/**
 * @brief This function verifies if a file is open,
 *        if not it ends execution with an appropiate message
 *
 * @param ifp A pointer to the file
 */
void checkFileOpen(FILE *ifp)
{
	if(ifp == NULL)
	{
		fprintf(stderr, "The file is unopenable!\n");
		exit(EXIT_FAILURE);
	}
}

