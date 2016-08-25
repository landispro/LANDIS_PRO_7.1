#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include "system1.h"

#include "error.h"

#include "specatt.h"

#include "specatts.h"



////////////////////////////////////////////////////////////////////////////

//			     SPECIESATTRS CLASS			  	  //

////////////////////////////////////////////////////////////////////////////



SPECIESATTRS::SPECIESATTRS(int n)

//Constructor.  N is equal to maximum array size for number of species. 



{

numAttrs=0;

specAttrs=new SPECIESATTR[n];

currentAttr=0;

maxAttrs=n;

}



SPECIESATTRS::~SPECIESATTRS()

//Destructor.



{

if(specAttrs)

delete[] specAttrs;

}



void SPECIESATTRS::read(FILE* infile, int cellSize)

//Read set of species attributes from a file.



{

while (!LDeof(infile))

   {

    if (numAttrs<maxAttrs)

       specAttrs[numAttrs++].read(infile, cellSize);

    else

       errorSys("SPECIESATTRS::read(FILE*)-> Array bounds error.",STOP);

   }

printf("number of species attributes: %d\n",numAttrs);

//<Add By Qia on July 2 2009>

MaxDistanceofAllSpecs=0;

for(int i=0;i<numAttrs;i++)

{

	if(specAttrs[i].maxD>=MaxDistanceofAllSpecs)

		{

		MaxDistanceofAllSpecs=specAttrs[i].maxD;

		}

}

MaxShadeTolerance=0;

for(int i=0;i<numAttrs;i++)

{

	if(specAttrs[i].shadeTolerance>=MaxShadeTolerance&&specAttrs[i].SpType>=0)

		{

		MaxShadeTolerance=specAttrs[i].shadeTolerance;

		}

}



//</Add By Qia on July 2 2009>

}



void SPECIESATTRS::write(FILE* outfile)

//Write set of species attributes to a file.



{

for (int i=0;i<numAttrs;i++)

   {

    specAttrs[i].write(outfile);

   }

}



void SPECIESATTRS::dump()

//Dump set of species attributes to the CRT.



{

for (int i=0;i<numAttrs;i++)

   {

    specAttrs[i].dump();

    printf("==================================\n");

   }

}



SPECIESATTR* SPECIESATTRS::operator ()(char* name)

//Referrence an attribute by species name.



{

for (int i=0;i<numAttrs;i++)

   if (strcmp(name,specAttrs[i].name)==0)

       return &specAttrs[i];



return NULL;

}



int SPECIESATTRS::current (char* name)

//Return the number of sequence of a given species name

{

for (int i=0;i<numAttrs;i++)

   if (strcmp(name,specAttrs[i].name)==0)

       return i;



return NULL;

}



SPECIESATTR* SPECIESATTRS::operator ()(int n)

//Referrence an attribute by species number.



{

if (n>numAttrs||n==0){

   errorSys("Specie Attributes out bound",STOP);

   return NULL;

}

else

   return &specAttrs[n-1];

}



SPECIESATTR* SPECIESATTRS::first()

//Referrence first species attribute.



{

currentAttr=0;

if (numAttrs==0)

   return NULL;

else

   return &specAttrs[currentAttr];

}



SPECIESATTR* SPECIESATTRS::next()

//Referrence next species attribute.



{

currentAttr++;

if (currentAttr>=numAttrs)

   return NULL;

else

   return &specAttrs[currentAttr];

}



int SPECIESATTRS::number()

//Returns number of species.



{

return numAttrs;

}

