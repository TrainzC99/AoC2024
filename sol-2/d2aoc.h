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

// ---> FUNCTIONS <--- // // §- Declarations -§ //
/*---------------------------------------------*/
bool safe_report(int num[], int n);
/*---------------------------------------------*/

