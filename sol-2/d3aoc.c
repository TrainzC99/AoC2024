#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "d3aoc.h"

#define FSEEK_OFFSET 0
#define MAX_MATCH 5
#define DO_CHAR_COUNT 4
#define DONT_CHAR_COUNT 7

int main (int argc, const char* argv[])
{
    /* File variables */
    FILE *inFile;
    unsigned long long fileSize;
    char *fileText, *fileTextBegin;
    int pLength;

    /* Match and related variables */
    regex_t matchex;
    regmatch_t matches[MAX_MATCH];
    char *mStr, *pChrNum;
    const char *nums = "0123456789";
    int mCount;
    bool math;

    /*Math operations variables*/
    int no1, no2;
    unsigned long long sum;

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
    // This returns +1 as ftell returns the current value of the pos. indicator
    // which inturn itself points to the next character to be read or
    // written in the next I/O operation.

    // File details
    (void) printf("File name -> %s\n", argv[1]);
    (void) printf("File size -> %llu\n", fileSize);

    // Read and store file in memory
    fileText = malloc(sizeof(*fileText) * fileSize);
    if(fileText == NULL)
    {
        (void) fprintf(stderr, "Error while allocating memory!\n");
        fclose(inFile);
        exit(EXIT_FAILURE);
    }
    fileTextBegin = fileText;
    if(fread(fileText, sizeof(*fileText), fileSize, inFile) != fileSize)
    {
        (void) fprintf(stderr, "Error file not read correctly!\n");
        fclose(inFile);
        free(fileText);
        exit(EXIT_FAILURE);
    }
    fileText[fileSize] = '\0';

    // Display read contents
    // (void) printf("Read contents:\n");
    // (void) printf("%s\n", fileText);

    // Process using RegEx
    if(regcomp(&matchex, \
               "\\(do()\\|don't()\\)\\|\\(mul([0-9]\\{1,3\\},[0-9]\\{1,3\\})\\)", \
               REG_ICASE | REG_NEWLINE) != 0)
    {
        (void) printf("Error when processing regex\n");
        exit(EXIT_FAILURE);
    }

    sum = 0;
    mCount = 0;
    math = TRUE;
    // Match regex patter on input text
    while((regexec(&matchex, fileText, MAX_MATCH, matches, 0) == 0) \
            && (*fileText != '\0'))
    {
        (void) printf("Match found: %.*s\n",
                      matches[0].rm_eo - matches[0].rm_so,
                      fileText + matches[0].rm_so);
        mCount++;

        // Get string of match
        mStr = fileText + matches[0].rm_so;
        if(strncmp("do()", mStr, DO_CHAR_COUNT) == 0)
            math = TRUE;
        else if(strncmp("don't()", mStr, DONT_CHAR_COUNT) == 0)
            math = FALSE;
        else if(math == TRUE)
        {
            // Parse string
            // Procedure:
            // Look for numbers
            // pChrNum & pLength get the whole number
            // Extract digits and turn them into numbers

            // First number
            pChrNum = strpbrk(mStr, nums);
            pLength = strspn(pChrNum, nums);
            no1 = atoi(pChrNum);
            // this stops at the first non-numerical char.
            // see glibc (strtol_l) impl. for details

            // Second number
            pChrNum = pChrNum + pLength;
            pChrNum = strpbrk(pChrNum, nums);
            no2 = atoi(pChrNum);

            // Multiply and Add numbers together
            sum += (no1 * no2);
        }
        // Move past the match
        fileText = fileText + matches[0].rm_eo;

        // In case of 0-length matches, avoiding infinite loop
        if(matches[0].rm_eo == matches[0].rm_so)
            fileText++;

    }

    printf("Matches found -> %d\n", mCount);
    printf("Sum of all mul instructions is -> %llu\n", sum);

    // Free file and regex from memory
    free(fileTextBegin);
    fclose(inFile);
    regfree(&matchex);

    return EXIT_SUCCESS;
}

inline int mul(int X, int Y) {
    return X * Y;
}

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

