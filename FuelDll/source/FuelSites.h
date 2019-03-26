// FuelSites.h: interface for the FuelSites class.

//

//////////////////////////////////////////////////////////////////////

#ifndef _FUELSITES_

#define _FUELSITES_

//#endif



#include <stdio.h>

#include "DEFINES.H"

#include "FuelDEFINES.H"

#include "gdal_priv.h"

#include "cpl_conv.h" // for CPLMalloc()

#include "cpl_string.h"

#include "ogr_spatialref.h"

//<Add By Qia on Nov 19 2008>

#include <vector>

#include <list>

//</Add By Qia on Nov 19 2008>





//#ifdef _FUEL_



// Create a structure to save the fuel site information

typedef struct

{

	// Shang 03/04 Remove FFLoad and CFLoad from fuelsite to PDP

	//char FFLoad,					// fine fuel load

	//	 CFLoad,					// coarse fuel load

	char 

		 beginCFDecompClass;		// Disturbances, e.g. harvest, windthrow, BDA, etc. will add some extra coarse fuel into the coarse fuel pool

									// Must save the information because it will be used for estimating the coarse fuel decomposition

									// Therefore, create a variable to save the begin coarse fuel load before decomposition

	int  timeOfCFAccumulation;		// Time of coarse fuel accumulation (yr)

	//char fireSeverity,				// Fire intensity class

	// Shang 03/04

	/*

	char fireIntensity,				// Fire intensity class

		 fireProbility,				// Fire probability class

		 fireRisk;					// Fire risk class

	float potentialFireProbility;	// Fire probability (0~1)

	*/

	char cFireProbabilityClass;		// Fire probability class (0~5)

	char fireRegime;				// Fire regime

	//<Add By Qia on Nov 19  2008>

	int numofsites;

	//</Add By Qia on Nov 19 2008>

}FuelSite;

//<Add By Qia on Nov 19 2008>

typedef std::vector<FuelSite *>  SortedFuelSiteSITE;

//</Add By Qia on Nov 19 2008>



typedef struct

{

		// Fuel management

	short		sTSLFUELMAN;						// Time since last fuel management

	char		cFUELMANEvent;					// Fuel management event

}FuelManSite;





typedef struct

{

	int spFFAccumulation[FUELCATEGORY];

	int spFFClass[FUELCATEGORY];

	float LiveFuelQualityCoeff;

	

}SpecieFFAccumulation;



typedef struct

{

	char LandtypeName [FNSIZE];					// land type name

	int  fineFuelLoad [FUELCATEGORY];			// fine fuel accumulation curve

	int  coarseFuelAccumulation [FUELCATEGORY];	// coarse fuel accumulation curve

	int  coarseFuelDecomposition [FUELCATEGORY];// coarse fuel decomposition curve

	float CrownFireCoeff;						// coefficient for crown fire

	

}LandtypeInfo;

/*

typedef struct

{

	int SpNum;

	float *density;

	char landtypeName[FNSIZE];

	

}SpecieDensity;



*/



typedef struct

{

	char   fireRegimeName[FNSIZE];     //Fire Regime Unit name.

	int    fireInterval,       //Mean interval between fires measured in years.         	   		       

           initialLastFire;	   //initial last fire disturbance 

	int	   status;			   //status of the fire regime



}FireRegime;





class FuelSites  

{

public:

	

	int spNum,

		landtypeNum,

		cols,

		rows,



		fireFlag,

		windFlag;

	//<Add By Qia on Nov 19 2008>

	SortedFuelSiteSITE SortedIndex;

	//</Add By Qia on Nov 19 2008>

	int numFireRegimes;



	int *fireModFF;			// fire modifier for fine fuels

	int *fireModCF;			// fire modifier for coarse fuels

	int *windModFF;			// wind modifier for fine fuels

	int *windModCF;			// wind modifier for coarse fuels

	int *BDAModFF;			// BDA modifier for fine fuels

	int *BDAModCF;			// BDA modifier for coarse fuels

	int *HarvestModFF;		// Harvest modifier for fine fuels

	int *HarvestModCF;		// Harvest modifier for coarse fuels

	int totalHarvestEvent;	// Total harvest event number

	int totalBDAType;		// Total BDA types

//	int *mortality;

	//<Add By Qia on Dec 03 2012>
	//Fire mortality parameters
	float fire_betavalues[5][3];
	float fire_X2values[5];
	//</Add By Qia on Dec 03 2012>

	SpecieFFAccumulation *spFFAccumulation;		// array of species fine fuel accumulation

	LandtypeInfo		 *landtypeInfo;			// array of land type info

//	SpecieDensity		 *spDensity;



	FuelSite			 *fuelSite;				// array of fuel site



	FuelManSite			 *fuelManSite;			// array of fuel management site



	FireRegime			 *fireRegime;			// array of fire regime



	FuelSites();

	~FuelSites();

	void init(int, int);						// initialzation, par: species num, landtype num

	void initFuelSite(int, int);				// initialization, par: row, col

	void initFuelManSite();						// initialization of fuel management site

	void read(FILE*, char*);							// read in the fuel tracking file

	int CalculateFFLoad (int, int, int, int);			// calculate the fine fule loads

//	float getSpWeight (int, int);

	int CalculateCFLoad (int, int, int, int, int);	// calculate the coarse fuel loads

	int windDisFFLoad (int, int, int);				// wind disturb the fine fuel loads

	int fireDisFFLoad (int, int, int);			// fire burn the fine fuel loads

	int windDisCFLoad (int, int, int);				// wind disturb the coarse fuel loads

	int fireDisCFLoad (int, int, int);			// fire burn the coarse fuel loads

	int HarvestDisFFLoad(int, int, int);		// harvest modify fine fuel loads

	int HarvestDisCFLoad(int, int, int);		// harvest modify coarse fuel loads

	int BDADisFFLoad(int, int, int);			// BDA modify fine fuel loads

	int BDADisCFLoad(int, int, int);			// BDA modify coarse fuel loads

//	int UpdateFireRisk(int, int);				// Update fire risk, fire intensity based on new fine and coarse fuels

	int CFAccumulation (int, int);				// calculate coarse fuel accumulation

	int getCFAccumulationTime (int, int);		// calculate the coarse fuel accumulation time

	FuelSite* operator () (int, int);			// get the fuelsite

	// Shang 03/04

	int setFFLoad (int, int, int);				// set the fine fule loads into PDP

	int setCFLoad (int, int, int);				// set the coarse fule loads into PDP

	int getFFLoad (int, int);					// get the fine fule loads into PDP

	int getCFLoad (int, int);					// get the coarse fule loads into PDP

	int setFireIntensityClass (int, int, int);	// set the Fire intensity class into PDP

	int getFireIntensityClass (int, int);		// get the fire intensity class from PDP

	int setFireProbabiltyClass (int, int, int);	// set the Fire probabilty class into PDP

	int getFireProbabiltyClass (int, int);		// get the fire probability class from PDP

	int setFireRiskClass (int, int, int);		// set the Fire risk class into PDP

	int getFireRiskClass (int, int);			// get the fire risk class from PDP

	

//	float setFireProbability (float, int, int);	// set the Fire probability into PDP

//	float getFireProbability (int, int);		// get the fire probability from PDP

	void readFireRegimeAttr(char*);				// read in the fire regime attributes

	void readFireRegimeMap(char*);				// read in the fire regime maps

	void readFireRegimeIMG(char* fn, const int giRow, const int giCol);

	void updateFuelManSite();					// add the time since last fuel management by 10 yr



	int CrownFire(int, int, int);				// live fuel change low intensity fire into crown fire



	

	//<Add by Qia on Nov 19 2008>

	int SITE_compare(FuelSite *site1, FuelSite *site2);

	int SITE_compare(int site1_x, int site1_y, int site2_x, int site2_y);

	                                   // Compare two sites to see the relation between them

	                                   // return 0:equal; return 1: site1 is bigger; return 2: site2 is bigger; -1: error

	                               

	int SITE_sort();				  // sort the pointers to sites



	int SITE_insert(int pos_sortIndex, FuelSite *site, int i, int j);					// insert a site in to list



	int SITE_delete(int pos_sortIndex, FuelSite *site, int i, int j);				// remove a site from list



	

	int SITE_LocateinSortIndex(FuelSite *site, int *pos, int *ifexist);

	

	void fillinSitePt(int i, int j, FuelSite *site);

	FuelSite * locateSitePt(int i, int j);

	

	void BefStChg(int i, int j);

	void AftStChg(int i,int j);

	//</Add By Qia on Nov 19 2008>



private:

	//<Add by Qia Nov 07 2008>

	FuelSite **map;

	//</Add by Qia on Nov 07 2008>

	FuelSite *sitetouse;//Add By Qia on Dec 19 2008



};



#endif

