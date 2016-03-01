#include <stdlib.h>

#include <stdio.h>

#include "system1.h"

#include "error.h"

#include "specatt.h"

#include "specatts.h"

#include "specie.h"

#include "species.h"



int SPECIES::numSpec=0;

SPECIESATTRS *SPECIES::speciesAttrs=NULL;



//////////////////////////////////////////////////////////////////////////////

//			    SPECIES CLASS CODE				    //

//////////////////////////////////////////////////////////////////////////////



SPECIES::SPECIES(int n)

//Constructor.  This constructor can only be used on the first creation

//instance of class SPECIES.  It sets the number of different varieties of

//species in the model.



{ 

	species=NULL;



if (numSpec==0)

   {

    species=new SPECIE[n];

    numSpec=n;

    currentSpec=0;

   }

else

   errorSys("SPECIES::SPECIES(int)-> Number of species may only be set\
             once at construction.",STOP);

}



SPECIES::SPECIES()

//Constructor.  Should be used on all instance constructions other than the 

//first.  This may be used on the first instance of construction but should 

//be followed by a call to setNumber before the second construction instance.



{

	species=NULL;



if (numSpec==0)

   {

    species=NULL;

    currentSpec=0;

   }

else

   {

    species=new SPECIE[numSpec];

    currentSpec=0;

	for(int i=0;i<numSpec;i++)

		{

		species[i].AGELISTAllocateVector(i);

		}

   } 

}



SPECIES::~SPECIES()

//Destructor.

//changed By Qia on March 04 2009

{

	//printf("~SPECIES()\n");



if(species) 

  delete [] species; //Nim: added []

	

}



void SPECIES::setNumber(int n)

//Sets the number of species.  Must be called after the first instance of 

//construction and before the second.



{

if (numSpec==0)

    numSpec=n;

else

    errorSys("SPECIES::setNumber()-> Number of species already set.",STOP);    

}



void SPECIES::reset()

//If all instances of class SPECIES are destructed then the reset function 

//may be called.  After it has been called instances may be constructed with

//a different number of species present.



{

numSpec=0;

} 



void SPECIES::read(FILE *infile)

//Read a set of species from a file.



{

for (int i=0;i<numSpec;i++)

    {

     species[i].readTreeNum(infile,i);

	 /*J.Yang 

	 Initilize disPropagulus for seed dispersal

	 at the 1st iteration

	 */

	 species[i].initilizeDisPropagules(

		 this->specAtt(i+1)->maturity,

		 this->specAtt(i+1)->name);

	 

    }

}



void SPECIES::write(FILE *outfile)

//Write a set of species to a file.



{

for (int i=0;i<numSpec;i++)

    {

     species[i].write(outfile);

     fprintf(outfile,"\n");

    }

}



void SPECIES::dump()

//Write a set of species to the CRT.



{

if (speciesAttrs==NULL)

    errorSys("SPECIES::dump()-> Species attributes not attached to SPECIES.",

              STOP);



for (int i=0;i<numSpec;i++)

    {

     printf("%s\t",(*speciesAttrs)(i+1)->name);

     species[i].dump();

    }

}



SPECIE* SPECIES::operator () (int n)

//Referrences a species by number.



{

if (n>numSpec || n<0)

    return NULL;

else

   {

    currentSpec=(unsigned char)(n-1);

    return &species[n-1];

   }

}



SPECIE* SPECIES::first()

//Referrence first species.



{

currentSpec=0;

return &species[currentSpec];

}

//<Add By Qia on June 30 2009>

SPECIE* SPECIES::SpecieIndex(int n)

{

	n=n-1;

	if (n>=numSpec || n<0)

		errorSys("Specie Index Error out Bound",STOP);

	else

		{

			return &species[n];

		}

}

//</Add By Qia on June 30 2009>



SPECIE* SPECIES::current(int n)   

{

if (n>numSpec || n<0)

    return NULL;

else

   {

    currentSpec=(unsigned char)n;

    return &species[n];

   }

}



SPECIE* SPECIES::next()

//Referrence next species.



{

currentSpec++;

if (currentSpec>=numSpec)

   return NULL;

else

   return &species[currentSpec];

}



SPECIESATTR* SPECIES::specAtt()

//Referrence the current species attribute.



{

if (speciesAttrs==NULL)

    errorSys("SPECIES::specAtt()-> Species attributes not attached to\
              SPECIES.",STOP);



if (currentSpec>=numSpec)

     return NULL;

else

     return (*speciesAttrs)(currentSpec+1);

}



SPECIESATTR* SPECIES::specAtt(int i)

//Referrence the current species attribute.



{

if (speciesAttrs==NULL)

    errorSys("SPECIES::specAtt()-> Species attributes not attached to\
              SPECIES.",STOP);



if (i>numSpec||i==0){

	errorSys("specAtt out of bound",STOP);

     return NULL;

}

else

     return (*speciesAttrs)(i);

}





void SPECIES::attach(SPECIESATTRS *s)

//This attaches a set of species attributes to all instances of species.



{

speciesAttrs=s;

}



int SPECIES::number()

//This returns the number of species.



{

return numSpec;

}



int SPECIES::youngest()

//This returns the youngest age.



{

int y=10000;



for (int i=0;i<numSpec;i++)

    {

     y=min(y,species[i].youngest());

    }

return y;    

}



int SPECIES::oldest()

//This returns the oldest age among the youngest.



{

int o=0;



for (int i=0;i<numSpec;i++)

    {

     o=max(o,species[i].oldest());

    }

return o;    

}



SPECIES& SPECIES::operator=(const SPECIES& s)



{

for (int i=0;i<number();i++)

   {

    species[i]=s.species[i];

	//<add by Qia on Dec 2 2008>

	species[i].disPropagules=s.species[i].disPropagules;

	species[i].vegPropagules=s.species[i].vegPropagules;

	//</Add By Qia on Dec 2 2008>

   }

currentSpec=0;   

return *this;

}

