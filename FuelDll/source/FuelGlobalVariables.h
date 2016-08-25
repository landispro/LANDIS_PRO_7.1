#ifndef _FUELGLOBALVAR_

#define _FUELGLOBALVAR_



#include "fuelstands.h"

#include "sites.h"

#include "FuelSites.h"

#include "FuelRule.h"

#include "Map8.h"

#include "ManagementAreas.h"

#include "PDP.h"

#include "FuelManage.h"

#include "Fueltrack.h"

//#include "FireRegimes.h"



extern FUELSTANDS*		fuelpstands;//change by Qia on Nov 20 2008

extern SITES*			pfuelcoresites;

extern FuelSites		fuelsites;

extern FuelRule			fuelrule;

extern float			harvestThreshold;



extern MAP16			standMap;

extern MAP16			managementAreaMap;

extern MANAGEMENTAREAS	managementAreas;

extern char*			fueloutputDir;

extern int				gDLLMode;

extern PDP*				pPDP;

extern int				numberOfSpecies;

extern FuelManage		fuelManager;

extern FuelTrack		fueltrack;



extern FILE*			fuelout;

extern FILE*			fuelManageFile;

extern FILE*			fuelManOutStand;



//extern FireRegimes		fireRegimes;

#endif