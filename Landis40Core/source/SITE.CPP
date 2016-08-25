#ifdef __HARVEST__

#include <assert.h>

#include "agelist.h"

//#include "landis.h"

//#include "GlobalVariables.h"

#endif

#include <stdlib.h>

#include <stdio.h>

#include "system1.h"

#include "error.h"

#include "species.h"

#include "landus.h"

#include "site.h"



/* J.Yang side-effect of del the composite rel.

LANDUNITS *SITE::landUnits=NULL;

*/



///////////////////////////////////////////////////////////////////////////////

//				SITE CLASS CODE				                                      //

///////////////////////////////////////////////////////////////////////////////



SITE::SITE(int n) : SPECIES(n)

//Constructor.

{

//lastFire=0;

//lastTimber=0;

numofsites=0;

}



SITE::SITE() : SPECIES()

//Constructor.

{

//lastFire=0;

//lastWind=0;

//lastTimber=0;

//<Delete By Qia On Oct 08 2008>

//</Delete By Qia On Oct 08 2008>

numofsites=0;



}



SITE::~SITE()

{

//<Delete By Qia On Oct 08 2008>

//if(landUnit)

//	landUnit=NULL;

//</Delete By Qia On Oct 08 2008>

	

}



/* J.Yang side-effect of del the composite rel.

void SITE::attach(LANDUNITS *l)

{

landUnits=l;

}

*/

void SITE::read(FILE *infile)

//Read in site data.

{

SPECIES::read(infile);

}



void SITE::write(FILE *outfile)

//Write out site data.

{

//fprintf(outfile,"%s %d %d %d\n",landUnit->name,lastFire, lastWind, lastTimber);

//	fprintf(outfile,"%s  %d %d\n",landUnit->name,lastFire, lastTimber);

SPECIES::write(outfile);

printf("\n\n");

}



void SITE::dump()

//Dump site data to the CRT screen.

{

//printf("%s %d %d %d\n",landUnit->name,lastFire, lastWind, lastTimber);

SPECIES::dump();

printf("\n\n");

}



