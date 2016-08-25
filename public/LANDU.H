#ifndef LANDUNIT_H

#define LANDUNIT_H



#include "specatt.h"

#include "specatts.h"



#ifdef LANDIS40CORE_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



#define PASSIVE 0

#define ACTIVE  1

#define WATER   2

#define WETLAND 3

#define BOG     4

#define LOWLAND 5

#define NONFOREST 6

#define GRASSLAND 7



class DLLCLASS LANDUNIT

{

public:

int		index;		//Add by Qia on Jan 22 2009

					//This is used for luReclass

char*  name;               //Land unit name.

int    minShade,           //This is the minimum number of shade years that

                           //must be present before shade 5 species may seed

                           //in on this site.

 /*      fireInterval,       //Mean interval between fires measured in years.

       probCoef,				//Fire probability coefficient   

       initialLastFire,		//initial last fire disturbance 

       fireCurve[5],       //Elements 0-4 correpsond to fire class 1-5.  Each

                           //element stores the number of years fuel must

                           //accumulate for the LANDUNIT to accomodate a fire

                           //of a given severity.

       fireClass[5],       //This holds fire classes in conjunction with fire

                           //curve.

       windCurve[5],       //Same as fireCurve and fireClass but used for fire

       windClass[5],       //fuel after windthrow.

       ignitionCoef;			//Fire ignition coefficient		



*/  // deleted by Wei, April 8, 2004



       initialLastWind,		//initial last wind disturbance

       

		ltID;				//Landtype ID for fuel by Vera

		//<Add By Qia on July 2 2009>

		float MaxRDArray[4];

		float MaxRD;

		//</Add By Qia on July 2 2009>

		float *probReproduction;   //Set of probabilities of reproduction of all

                           //elements of s where s is of type SPECATTRIBS.

                           //Each probability is the chance of reproduction

                           //given that seeds are present and there is no

                           //competition.



		//<Add By Qia on Jan 15 2009>

		float *probReproductionOriginalBackup;

		//</Add By Qia on Jan 15 2009>

		



LANDUNIT();                //Constructor.

~LANDUNIT();               //Destructor.

void read(FILE*);          //Read a land unit from a file.

void write(FILE*);         //Write a land unit to a file.

void dump();               //Dump contents of land unit to the CRT.

void attach(SPECIESATTRS*);//Attaches a set of species attributes to the

                           //land unit.  Must be performed following

                           //construction.

float probRepro(int);      //Returns the probability of reproduction of the

                           //given species on the land unit.  Species is

                           //referrenced by number.

float probRepro(char*);    //Returns the probability of reproduction of the

                           //given species on the land unit.  Species is

                           //referrenced by name.

float probRepro(SPECIESATTR*);//Returns the probability of reproduction of the

                           //given species on the land unit.  Species is

                           //referrenced by species attribute class.

int active();              //A landunit type is either active or inactive.

                           //Inactive land units are not processed.

int water();               //Returns true if a land unit type is water, false

                           //otherwise.

int lowland();             //Returns true if a land unit type is lowland,

                           //false otherwise

int Get_status();

private:



SPECIESATTRS *speciesAttrs;//Pointer to an attached set of species attributes.

                           //Allows species attributes to be referrenced by

                           //name.

int status;                //Either ACTIVE, PASSIVE, or WATER.

};



#undef DLLCLASS



#endif



