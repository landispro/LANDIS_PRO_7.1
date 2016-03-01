#ifndef SITE_H

#define SITE_H



#include "species.h"

#include "landu.h"

#include "landus.h"



#ifdef LANDIS40CORE_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



class DLLCLASS SITE : public SPECIES



{

public:



//short lastFire;                   //Number of years since last fire.

 //     lastWind,                   //Number of years since last windthrow.

//      lastTimber;                 //Number of years since last timber harvest.



//<delete By Qia on Oct 08 2008>

//LANDUNIT *landUnit;               //Pointer to the land unit the site is //need to change by Qia Oct 07 2008

                                  //present on.

//</delete By Qia on Oct 08 2008>



//<Add By Qia on Oct 08 2008>

int numofsites;

//</Add By Qia on Oct 08 2008>

SITE(int n);                      //Constructor.      NOTE:  Apply same rules

SITE();                           //Constructor.      as for class SPECIES.

~SITE();                          //Destructor.



/* J.Yang side-effect of deleting the composite relationship

static void attach(LANDUNITS*);   //This attaches a set of land units to

                                  //all sites.

*/

void read(FILE*);                 //Read in all site data.

void write(FILE*);                //Write out all site data.

void dump();                      //Dump set of site data to the CRT.

//SITE& operator=(const SITE&);

//<Add By Qia on June 29 2009>

float RD;

int HighestShadeTolerance;

float MaxAge;



//</Add By Qia on June 29 2009>



private:





};



#undef DLLCLASS



#endif

