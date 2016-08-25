#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include <math.h>

//#include "mem.h"

#include "system1.h"

#include "error.h"

//#include "landis.h"

#include "specatt.h"



////////////////////////////////////////////////////////////////////////////

//				SPECIESATTR CLASS			  //

////////////////////////////////////////////////////////////////////////////



SPECIESATTR::SPECIESATTR()

//Constructor.



{

name=NULL;

longevity=0;

maturity=0;

shadeTolerance=0;

fireTolerance=0;

effectiveD=0;

maxD=0;

alpha = 0.0;

vegProb=0.0;

maxSproutAge=0;

reclassCoef=0.0;

}



SPECIESATTR::~SPECIESATTR()

//Destructor.



{

//free(name);

// Nim: add the next line if SPECIESATTR owns name

	//J.Yang 

	if(name)

		delete [] name;

	

//delete [] name;

}



//_0909_ add cellSize by Li Wei

void SPECIESATTR::read(FILE* infile, int cellSize)

//Read species attributes from a file.



{

char instring[25];



if (fscanc(infile,"%s",instring)!=1)

	 errorSys("Read error in spec. attr. file.",STOP);

//Nim: deleted next two lines

//if ((name=(char*)malloc((strlen(instring)+1)*sizeof(char)))==NULL)

//	 errorSys("SPECIESATTR::read(FILE*)-> Out of memory error.",STOP);



name=new char[strlen(instring)+1]; //Nim: added this line

strcpy(name,instring);



if (fscanc(infile,"%d",&longevity)!=1)

	 errorSys("Error reading in longevity from spec. attr. file.",STOP);

if (fscanc(infile,"%d",&maturity)!=1)

	 errorSys("Error reading in maturity from spec. attr. file.",STOP);

if (fscanc(infile,"%d",&shadeTolerance)!=1)

	 errorSys("Error reading in shadeTolerance from spec. attr. file.",STOP);

if (fscanc(infile,"%d",&fireTolerance)!=1)

	 errorSys("Error reading in fireTolerance from spec. attr. file.",STOP);

if (fscanc(infile,"%d",&effectiveD)!=1)

	 errorSys("Error reading in effectiveD from spec. attr. file.",STOP);

/* J.Yang

DELETE them

*/

//DEL if (effectiveD!=-1) 

//DEL 	effectiveD = effectiveD * cellSize / 30;

if (fscanc(infile,"%d",&maxD)!=1)

    errorSys("Error reading in maxD from spec. attr. file.",STOP);

if (fscanc(infile, "%f", &alpha) != 1)

	errorSys("Error reading in vegClass from spec. attr. file.", STOP);

if (fscanc(infile,"%f",&vegProb)!=1)

    errorSys("Error reading in vegClass from spec. attr. file.",STOP);

if (fscanc(infile,"%d",&MinSproutAge)!=1)

    errorSys("Error reading in MinSproutAge from spec. attr. file.",STOP);

if (fscanc(infile,"%d",&maxSproutAge)!=1)

    errorSys("Error reading in maxSproutAge from spec. attr. file.",STOP);

if (fscanc(infile,"%f",&reclassCoef)!=1)

    errorSys("Error reading in reclassCoef from spec. attr. file.",STOP);  

//<Add By Qia on July 2 2009>

if (fscanc(infile,"%d",&SpType)!=1)

    errorSys("Error reading in SpType from spec. attr. file.",STOP);

if (fscanc(infile,"%d",&BioMassCoef)!=1)

    errorSys("Error reading in BioMassCoef from spec. attr. file.",STOP);

if (fscanc(infile,"%d",&MaxDQ)!=1)

    errorSys("Error reading in MaxDQ from spec. attr. file.",STOP);

if (fscanc(infile,"%d",&SDImax)!=1)

    errorSys("Error reading in SDImax from spec. attr. file.",STOP);

MaxAreaOfSTDTree=10000.0/(float)SDImax;

if (fscanc(infile,"%d",&TotalSeed)!=1)

    errorSys("Error reading in TotalSeed from spec. attr. file.",STOP);  

if (fscanc(infile,"%f",&CarbonCoEfficient)!=1)

    errorSys("Error reading in CarbonCoEfficient from spec. attr. file.",STOP); 

 



//</Add By Qia on July 2 2009>

}



void SPECIESATTR::write(FILE* outfile)

//Write species attributes to a file.



{

fprintf(outfile,"%s\t",name);

fprintf(outfile,"%d\t",longevity);

fprintf(outfile,"%d\t",maturity);

fprintf(outfile,"%d\t",shadeTolerance);

fprintf(outfile,"%d\t",fireTolerance);

fprintf(outfile,"%d\t",effectiveD);

fprintf(outfile,"%d\t",maxD);

fprintf(outfile, "%f\t", alpha);

fprintf(outfile,"%f\t",vegProb);

fprintf(outfile,"%d\t",maxSproutAge);

fprintf(outfile,"%f\n",reclassCoef);

}



void SPECIESATTR::dump()

//Dump species attributes to CRT.



{

printf("name:           %s\n",name);

printf("longevity:      %d\n",longevity);

printf("maturity:       %d\n",maturity);

printf("shadeTolerance: %d\n",shadeTolerance);

printf("fireTolerance:  %d\n",fireTolerance);

printf("effectiveD:     %d\n",effectiveD);

printf("maxD:           %d\n",maxD);

printf("alpha:        %f\n", alpha);

printf("vegProb:        %f\n",vegProb);

printf("maxSproutAge:   %d\n",maxSproutAge);

printf("reclassCoef:    %f\n",reclassCoef);

}



float SPECIESATTR::prob(float x)

//Given a distance this will return a seeding probability for a species.



{

double a=.95;

double b=0.001;  

double md = maxD;

double ed = effectiveD;



if (x <= ed) return (float) a;

if (x > md) return (float) b;



double alpha;

alpha = log(a/b)/(md-ed);



double prob;

prob = a * exp(-1* alpha * (x-ed));

return (float) prob;



}

