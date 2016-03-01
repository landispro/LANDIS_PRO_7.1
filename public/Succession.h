#ifndef SUCCESSION_H

#define SUCCESSION_H



#include <stdlib.h>

#include <stdio.h>

#include "specatt.h"

#include "landu.h"

#include "specie.h"

#include "site.h"

#include "sites.h"

#include "optim.h"



#ifdef SUCCESSION_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



class DLLCLASS SUCCESSION



{

public:

	int			cellSize;

	SITES*		psites;

	LANDUNITS*	plandUnits;

	OPTIM*		poptim;

	//<Add By Qia on Jan 14 2009>

	int Totaliteration,CurrentIteration,timestep;

	char *VectorIteration;

	void initiateVariableVector(int , int );

	//</Add By Qia on Jan 14 2009>

	SUCCESSION(SITES*, LANDUNITS*, OPTIM*, int);//Changed By Qia on Jan 14 2009

	~SUCCESSION();





//	void singularLandisIteration(int, int, int, int, int, int);

	void seed(SPECIESATTR*, LANDUNIT*, SPECIE *, int, int, int, int, int);

	void noDisp(SPECIESATTR*, LANDUNIT*, SPECIE*, int, int);

	void uniDisp(SPECIESATTR*, LANDUNIT*, SPECIE*, int, int);

	void neighDisp(SPECIESATTR*, LANDUNIT*, SPECIE*, int, int, int, int);

	void seedDisp(SPECIESATTR*, LANDUNIT*, SPECIE*, int, int, int, int);

	void intSeedDisp(SPECIESATTR*, LANDUNIT*, SPECIE*, int, int, int, int);

	void randDisp(SPECIESATTR*, LANDUNIT*, SPECIE*, int, int, int, int);

	void maxDisp(SPECIESATTR*, LANDUNIT*, SPECIE*, int, int, int, int);

	void extraSeed(int, int, int, int);

	void vegProp(SPECIE*, SPECIESATTR*, int);

	void grow(SPECIE*, SPECIESATTR*);

	void kill(SPECIE*, SPECIESATTR*);

	void birth(SPECIE*);

	void envChange(int,int, char*);

	void updateLandtype(FILE*,int);

	float probBirth(LANDUNIT*, int);

	int enoughLight(SPECIESATTR*, int);

	int findShade(SITE*);

	void findX1X2(int &x1, int &x2, int x, int y, int y1, int r);



};

#endif

