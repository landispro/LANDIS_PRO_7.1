#include "defines.h"

#include "system1.h"

#include "error.h"

#include "point.h"

#include "pile.h"



PILE::PILE()

//Constructor.



{

numItems=0;

}



int PILE::isEmpty()

//This returns true if the pile is empty, false otherwise.



{

return !numItems;

}



int PILE::push(LDPOINT p)

//Pushes p onto the pile.  Returns true if unsuccesful, false otherwise.



{

if (numItems<(MAXPILE-1))

   {

    items[numItems++]=p;

    return false;

   }

else

   {

    errorSys("MAXIMUM PILE SPACE EXCEEDED!.",CONTINUE);

    return true;

   } 

}



LDPOINT PILE::pull()

//Pulls p off of the pile.



{

LDPOINT p;

int pos=(int)(frand()*(float)numItems);

if (pos<0 || pos>=numItems)

    pos=0;

p=items[pos];

for (int i=pos;i<numItems-1;i++)

   items[i]=items[i+1];

numItems--;   

return p;

}



void PILE::reset()

//This will reset the pile to an empty state.



{

numItems=0;

}

