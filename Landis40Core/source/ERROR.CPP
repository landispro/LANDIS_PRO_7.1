#include <stdlib.h>

#include <stdio.h>

#include "error.h"



/////////////////////////////////////////////////////////////////////////////

//				EXTERNAL FUNCTIONS			   //

/////////////////////////////////////////////////////////////////////////////



void errorSys(const char* str, int condition)

//This prints an error message on the CRT screen and then either halts, or

//returns control to the program depending on the state of the second

//parameter.  The first parameter is the error message.  The second parameter

//is either set to STOP or CONTINUE.   



{

printf("ERROR:\n\n%s\n\n",str);

fflush(stdout);

if (condition==CONTINUE)

    printf("CONTINUING PROGRAM RUN.\n");  

else

    {

     printf("EXITING PROGRAM.\n");

     exit(255);

    }

}

