#include <stdio.h>

#include <string.h>



#include "system1.h"

#include "agelist.h"

#include "specie.h"



//<Add By Qia On Oct 16 2008>

#include "sites.h"

//</Add By Qia On Oct 16 2008>



//////////////////////////////////////////////////////////////////////////////

//			     SPECIE CLASS CODE				    //

//////////////////////////////////////////////////////////////////////////////



SPECIE::SPECIE()

//Constructor.



{

	

vegPropagules=0;

disPropagules=0;

//AGELIST::AGELIST();

//AGELIST::clear();

}

//<Add By Qia on March 04 2009>

SPECIE::~SPECIE()			//destructor

{



}

//</Add By Qia on March 04 2009>



void SPECIE::clear()

//Clear all specie values.



{

vegPropagules=0;

disPropagules=0;

AGELIST::clear();

}



void SPECIE::kill(int l, int h)

//Kill all trees bounded by l and h.



{

int num=getTimeStep();

for (int i=l;i<=h;i+=num)

    reset(i);

}



void SPECIE::kill(int l, int h, AGELIST a)

//Kill all trees bounded by l and h if and only if the age is present in a.



{

int num=getTimeStep();

for (int i=l;i<=h;i+=num)

    if (a.query(i))

        reset(i);

}



void SPECIE::read(FILE *infile)

//Read a specie from a file.



{

int a;

//////

fscanc(infile,"%d ",&a);

//////// its the above line

////fputs("thru bug fscanc/n", stdout);

vegPropagules=(short)a;

////fputs("vegPropagules=a/n", stdout);

AGELIST::read(infile);

}

void SPECIE::readTreeNum(FILE* infile, int specIndex)

{

	int a;

	//////

	fscanc(infile,"%d ",&a);

	//////// its the above line

	////fputs("thru bug fscanc/n", stdout);

	vegPropagules=(short)a;

	////fputs("vegPropagules=a/n", stdout);

	AGELIST::readTreeNum(infile, specIndex);

	TreesFromVeg = 0;

}



void SPECIE::write(FILE *outfile)

//Write a specie to a file.



{

fprintf(outfile,"%d ",vegPropagules);

AGELIST::write(outfile);

}



void SPECIE::dump()

//Dump a specie to the CRT.



{

printf("%d\t",vegPropagules);

AGELIST::dump();

}



void SPECIE::initilizeDisPropagules(int maturity, char * name)

{

	if (oldest() >= maturity)

	{

		disPropagules = 1; //can disperse, non OS

	}  

	

}



void SPECIE::updateDispropagules(int maturity)

{

	if (oldest() >= maturity)

	{

		disPropagules = true; 

	}  

	else

	{

		disPropagules = false;

	}	



}



//<Add By Qia on Oct 17 2008>

void SPECIE::birth() {set(getTimeStep());}         //Adds trees to age ten.

void SPECIE::grow() {shiftOld();}       //Grows trees ten years.

void SPECIE::kill(int i) {reset(i);}  //Kills trees of a given age class.

//</Add By Qia on Oct 17 2008>



void SPECIE::SetMatureTreeValue(int value)

{

MatureTree=value;

}

int SPECIE::GetMatureTreeValue()

{

	return MatureTree;

}





