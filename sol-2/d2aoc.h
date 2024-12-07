#pragma once

// ---> ENUMERATIONS <--- // // §- Declarations -§ //
/*------------------------------------------------*/
enum boolean{
	FALSE,
	TRUE
};
typedef enum boolean bool;
enum progression{
	INCREASING,
	DECREASING
};
typedef enum progression prog;
/*------------------------------------------------*/

// ---> STRUCTURES <--- // // §- Declarations -§ //
/*----------------------------------------------*/
struct result{
	bool safe;
	int failIndex; // if any, if not is -1
};
typedef struct result result;
/*----------------------------------------------*/

// ---> FUNCTIONS <--- // // §- Declarations -§ //
/*---------------------------------------------*/
result safe_report(int num[], int n);
/*---------------------------------------------*/

