#ifndef SPECIE_H

#define SPECIE_H



#include <stdio.h>

#include "agelist.h"



#ifdef LANDIS40CORE_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



class DLLCLASS SPECIE : public AGELIST



{

friend class RECLASS;



friend int reclassificationValue(SPECIE*);



public:

	void updateDispropagules(int maturity);



short vegPropagules,      //Number of years of vegetative propagules present.

      disPropagules;      //Number of years of dispersed propagules present.

//<Add By Qia on June 29 2009>

unsigned long AvailableSeed;

int TreesFromVeg;

int flag_herb;

//</Add By Qia on June 29 2009>

int MatureTree;

void SetMatureTreeValue(int value);

int GetMatureTreeValue();

SPECIE();                 //Constructor.

//<Add By Qia on March 04 2009>

~SPECIE();			//destructor

//</Add By Qia on March 04 2009>

void clear();             //Clear all values.

void kill(int, int);      //Kill trees in a given age range.

void kill(int, int, AGELIST);  //Kill trees in a given range if and only if the

                          //ages are present in a mask were the mask is

                          //represented by type AGELIST.

void read(FILE*);         //Read a specie from a file.

void readTreeNum(FILE*, int specIndex);



void write(FILE*);        //Write a specie to a file.

void dump();              //Dump specie data to the CRT.

void initilizeDisPropagules(int maturity, char * name);





//The following functions are alternate names for accessing the members of age

//list.



//<commented By Qia Oct 17 2008>

/*void birth() {set(10);}         //Adds trees to age ten.

void grow() {shiftOld();}       //Grows trees ten years.

void kill(int i) {reset(i);}  //Kills trees of a given age class.*/

//</commented By Qia Oct 17 2008>



//<Add By Qia on Oct 17 2008>

void birth();         //Adds trees to age ten.

void grow();      //Grows trees ten years.

void kill(int i) ;  //Kills trees of a given age class.

//</Add By Qia on Oct 17 2008>

};



#undef DLLCLASS



#endif

