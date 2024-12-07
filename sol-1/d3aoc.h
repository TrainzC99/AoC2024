#pragma once

// ---> ENUMERATIONS <--- // // §- Declarations -§ //
/*------------------------------------------------*/
enum boolean{
	FALSE,
	TRUE
};
typedef enum boolean bool;
/*------------------------------------------------*/

// ---> FUNCTIONS <--- // // §- Declarations -§ //
/*---------------------------------------------*/
int mul(int X, int Y);
void checkFileOpen(FILE *ifp);
unsigned long long getFileSize(FILE* fp);
/*---------------------------------------------*/

