#ifndef GLOBALFUNCTIONS_H

#define GLOBALFUNCTIONS_H



#include "point.h"

#include "map8.h"

#include "Stand.h"

//#include "SiteHarvester.h"

#include "point.h"

#include "stands.h"

#include "sites.h"

//begin add by vera

#include "harvesteventqueue.h"  //add by Vera

//#include "MANAGEMENTAREAS.h"

#include "PDP.h"



#ifdef HARVESTDLL_EXPORTS

#define DLLFUNC   __declspec( dllexport )

#else

#define DLLFUNC   __declspec( dllimport )

#endif



void DLLFUNC HarvestprocessEvents(int);

void DLLFUNC HarvestPassCurrentDecade(int);

//void DLLFUNC HarvestPassFile(FILE*, FILE*);



void DLLFUNC HarvestPass(SITES* psi, SPECIESATTRS*);  //add by Vera

void DLLFUNC setUpdateFlags(int r, int c);

void DLLFUNC createHarvestTypeMap(MAP8 &m);

void DLLFUNC PutOutput_harvestBACut(char *fn);

void DLLFUNC PutOutput_harvestBACut(char *fn, char *fn1);

void DLLFUNC PutOutput_harvestBACut_spec(char *fn,int spec);//Add By Qia

void DLLFUNC PutOutput_harvestBACut_spec(char *fn, char *fn1, int spec);//*

void DLLFUNC createHarvestDecadeMap(MAP8 &m);

void DLLFUNC writeStandReport();

void DLLFUNC CleanHarvest();

void DLLFUNC output_harvest_Dec_Type(int itr, char str_htyp[200], char str_dec[200]);

void DLLFUNC output_harvest_Dec_Type(int itr, char str_htyp[200], char str_htyp1[200], char str_dec[200], char str_dec1[200]);

void DLLFUNC HarvestPassInit(SITES*, int, char*, char*, PDP*);  //add by Vera



int getRandomHarvestablePoint(Stand* theStand, LDPOINT& thePoint);

int canBeHarvested(LDPOINT& thePoint);

void dumpHarvestMap();

int inBounds(int r, int c);





float gasdev();

float gasdev(float mean, float sd);



#undef DLLFUNC



#endif



