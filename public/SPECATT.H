#ifndef SPECIESATTR_H

#define SPECIESATTR_H



#ifdef LANDIS40CORE_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



class DLLCLASS SPECIESATTR



{

public:



char* name;           //Species Name.

int   longevity,      //Maximum age.

      maturity,       //Sexual Maturity.

      shadeTolerance, //Shade Tolerance.

      fireTolerance,  //Fire Tolerance.

      effectiveD,     //Effective seeding distance.

      maxD;           //Maximum seeding distance.

float  alpha,// alpha for propability disperpal

		vegProb;        //Probability of vegetative seeding.

int   maxSproutAge;   //Maximum sprouting age.

float reclassCoef;    //Reclassification coefficient.

//<Add By Qia on June 29 2009>

int SpType;

int BioMassCoef;

int MaxDQ;

int SDImax;

int TotalSeed;

float MaxAreaOfSTDTree;

float CarbonCoEfficient;

int MinSproutAge;

//</Add By Qia on June 29 2009>

SPECIESATTR();        //Constructor.

~SPECIESATTR();       //Destructor.

void read(FILE*, int);     //Read species attributes from a file.

void write(FILE*);    //Write species attributes to a file.

void dump();          //Dump species attributes to the CRT.

float prob(float x);

//Given a distance this will return a seeding probability for a species.

                      

};



#undef DLLCLASS



#endif



