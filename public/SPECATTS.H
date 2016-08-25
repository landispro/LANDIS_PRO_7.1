#ifndef SPECIESATTRS_H

#define SPECIESATTRS_H



#include <stdio.h>

#include "defines.h"

#include "specatt.h"



#ifdef LANDIS40CORE_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



class DLLCLASS SPECIESATTRS



{

public:



SPECIESATTRS(int n=MAX_SPECIES);	//Constructor, sets upper limit for number of

                                 //species. 

~SPECIESATTRS();                 //Destructor.

void read(FILE*, int);                //Read set of species attributes from a file.

void write(FILE*);               //Write set of species attributes to a file.

void dump();                     //Dump set of species attributes to the CRT.

SPECIESATTR* operator()(char*);  //Referrence an attribute by species name.

SPECIESATTR* operator()(int);    //Referrence an attribute by species number.

SPECIESATTR* first();            //Referrence first species attribute.

SPECIESATTR* next();             //Referrence next species attribute.

                                 //NOTE: All four referrence functions return

                                 //NULL if attribute referrenced is illegal or

                                 //unavailable.

int number();                    //Returns number of species.

int current (char*);					//Return current number of species name 

//<Add By Qia on July 2 2009>

int MaxDistanceofAllSpecs;

int MaxShadeTolerance;

//</Add By Qia on July 2 2009>

private:



SPECIESATTR *specAttrs;          //Array holding all species attributes.

int numAttrs;                    //Number of species attributes.

int currentAttr;                 //Current species attribute being pointed to

                                 //by first and next access functions.

int maxAttrs;                    //Maximum number of attributes.  Defined upon

                                 //class construction.

};



#undef DLLCLASS



#endif

