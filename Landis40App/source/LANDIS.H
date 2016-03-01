#ifndef LANDIS_H

#define LANDIS_H



#include "params.h"

#include "specatts.h"

#include "landus.h"

#include "sites.h"

//#include "stocc.h"



#include "BDA.h"

#include "BDAS.h"



extern PARAMETERS    parameters;       //System paramters.

extern SPECIESATTRS  speciesAttrs;     //Species attributes.

extern LANDUNITS     landUnits;        //Land units.

extern SITES         sites;            //Map of all landis sites.

//<Add By Qia on Jan 06 2009>

extern timestep	  time_step;

//</Add By Qia on Jan 06 2009>



//extern StochasticLib stochastic;





extern BDAS*		 pBDAS;



#endif



