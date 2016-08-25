#ifndef GLOBALVARIABLES_H

#define GLOBALVARIABLES_H



#include <stdio.h>

#include "map8.h"

#include "STANDS.h"

#include "ManagementAreas.h"

//#include "harvest\List.h"

#include "HarvestEventQueue.h"



/*add by Vera*/

#include "Sites.h"

#include "HarvestSites.h"

/*end add by Vera*/

#include "PDP.h"





extern int currentDecade;

extern int numberOfSpecies;



/*Jian Yang 02/24/02

comment following two sentences:

  	extern MAP16 standMap;

	extern MAP16 managementAreaMap;



*/

extern MAP16 standMap;

extern MAP16 managementAreaMap;



/*Jian Yang 02/24/02

above is added

*/



extern MANAGEMENTAREAS managementAreas;

extern HarvestEventQueue harvestEvents;



extern FILE* harvestOutputFile1;

extern FILE* harvestOutputFile2;



extern unsigned short currentHarvestEventId;



/* begin Add by Vera Oct. 30 2003*/

extern STANDS*			pstands;

extern SITES*			pCoresites;

extern HARVESTSites*	pHarvestsites;

extern int				giRow;

extern int				giCol;



//parameters for harvest

extern int				iParamstandAdjacencyFlag;

extern int				iParamharvestDecadeSpan;

extern float			fParamharvestThreshold;



extern SPECIESATTRS*	pspeciesAttrs;

/*end add by Vera*/



extern PDP*		m_pPDP; //added by Vera





//#ifdef __HARVEST__ //Jian Yang 02/24/02 add this line

extern MAP16 visitationMap;

//#endif //Jian Yang 02/24/02 add this line



#endif

