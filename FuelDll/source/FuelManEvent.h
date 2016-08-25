// FuelManEvent.h: interface for the FuelManEvent class.

//

//////////////////////////////////////////////////////////////////////

#ifndef _FUELMANE_

#define _FUELMANE_



#include "DEFINES.H"

#include <stdio.h>

#include "IntArray.h"

#include "Stand.h"



#include "FuelTreatmentRank.h"



//<Add By Qia on May 19 2009>

static const float  lifespan[5]={(float)0.0,(float).2,(float).5,(float).7,(float).85};

//</Add By Qia on May 19 2009>

class FuelManEvent  

{

public:

	

	char

		*Label;

	int manageAreaIdentify,		// management area identify

		rankAlgorithm,			// ranking algorithm

		entryDecade,			// first entry decade

		finalDecade,			// final entry decade

		reentryInterval,		// re-entry interval

		minClass;				// mimum potential fire risk class

	float proportion;			// treatment proportion



	//int useFireForTreatment;

	int *FineFuelManagement,	// fine fuel management prescription

		*CoarseFuelManagement;	// coarse fuel management prescription



	// store fuel treatment efforts

	int *FFTreat, *CFTreat;

	

	FuelTreatmentRank

		*itRankAlgorithm;		// new a ranking algorithm



	FuelManEvent();

	virtual ~FuelManEvent();

	void read (FILE*);			// read in management prescription

	int FineFuelManager(int);	// function to treat the fine fuels

	int CoarseFuelManager(int);	// function to treat the coarse fuels

	void Treatment(int, FILE*, FILE*, int);	// fuel treatment records //Changed By Qia to Change Fuel

	//<Add By Qia on May 19 2009>

	int damage_FireinFuel(LDPOINT p, int fireClass);

	//</Add By Qia on May 19 2009>

};



#endif

