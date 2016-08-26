#ifndef FIRE_H

#define FIRE_H



#include "defines.h"

#include "point.h"

#include "map8.h"



#include "PDP.h"

#include "Sites.h"

#include "stocc.h"



#include "FireRegimeUnits.h"



#include "FinneyCell.h"

#include <list>		// list class library

#include <algorithm>

using namespace std;



#ifdef FIREDLL_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif





#define MAX_TRY 255



typedef struct StructFireParam {

	//output files

	char yearlyFn[FNSIZE], // the base name for output iterationly information

	     finalFn[FNSIZE],  // the base name for output final information

	     logFn[FNSIZE];    // log fire where each row record one fire event

	

	//input files

	char fireRegimeAttrFn[FNSIZE],  //name of the file having attributes for each fire regime

		 fireRegimeDataFn[FNSIZE],  //the gis file having fire regime index for each site, if flag of using independent fire regime is 0, this item has to be N/A

		 FinneyParamFN[FNSIZE],

		 DEMDataFn[FNSIZE],         //#the gis file having elevation value for each site. it is 16 bit. if flag of using DEM data is 0, this item has to be N/A
		File_regime_change[FNSIZE];			//#fire regime changing input
		 

	//fire spread parameters

	float fSpreadProb;              //Base probability for fuel class 3	

	float fCoeff1,fCoeff2,fCoeff3;  //Wind coefficient,Topography coefficient,Predefined fire size distribution coefficient



	//prevailing wind regime (across landscape)

	int iNonWindPercent;

	int iCummWindClass[40];

/*	

	int iWindIntensity;	

	int iWindDirectionIndex;		//Prevailing wind direction Index, 0-NW; 1-W; 2-SW; 3-S; 4-SE; 5-E; 6-NE; 7-N

*/	



	//Flags

	int iWindFlag;

	int iFuelFlag; //if it turned off, use old fire initiation and spread routines.

	int iDEMFlag;

	int iFireRegimeFlag;

	int iTSLFFlag;

	

	float fInitiationProb[5];



	int cellSize;

	int m_nFNOI;
	


	int rows, cols;

	//<Add By Qia on Oct 9 2012>
	//Fire mortality parameters
	float fire_betavalues[5][3];
	float fire_X2values[5];
	//</Add By Qia on Oct 9 2012>

} fireParam;



typedef struct StructFinneyParam {

	float ellipseAxisRatio[6]; //w.r.t wind class

	float fuelWeight,windWeight,TopoWeight;

	float a,b,c;

	float spreadRate[6][6]; //ROS for flat area. slope class 0

	float ROS_low[6][6]; //slope class 1

	float ROS_moderate[6][6]; //slope class 2

	float ROS_high[6][6]; //slope class 3

	float ROS_extreme[6][6]; //slope class 4

} finneyParam;



typedef struct StructBurnningSite {

	int row;

	int col;

	int burnningTime;

	int burnningLimit;

} fireFront;



class DLLCLASS CFIRE  

{

public:

	void WriteCummInitiationMap(int snr, int snc, int itr);

	void WriteInitiationMap(int snr, int snc, int itr);

	float fireDuration(float mean,float std);

	LDPOINT Retrieve(int index);

	void InitilizeBurnedCells();

	void FinneyExpandCostList(int row, int col);

	int FinneyIsValid(int row, int column);

	void FinneyInitilizeActiveCostList();

	void FinneyCalculateMinTime();

	void FinneyCalculateFinalCost();

	void FinneyCalculateWindCost();

	void FinneyEucDirection();

	void FinneyCalculateFuelCost();

	long FinneySpread();

	float fireSizeHa(float MFS,float STD);

	void FinneyCalculateDimensions();

	void FinneyFreeMemory();

	void FinneyInitilization();

	void updateFRU(int itr);
	void updateFire_Regime_Map(int itr);

	CFIRE();

	//where is the settings to tell which module is on or off? is it in PDP?

	//nFNOI is number of iterarions

	CFIRE(char*	strfn, int mode, SITES* outsites, 

		LANDUNITS* outlus, SPECIESATTRS*  outsa, PDP* ppdp, int nFNOI,

		char * strOutput,int randSeed);

	void Activate(int itr, int freq[], double wAdfGeoTransform[]);

	virtual ~CFIRE();
	int flag_regime_update;
private:

	float FinneyCalculateAcceleration(int from_x, int from_y, int to_x, int to_y, float weight);

	double ProductLog(double kernel);

	void FinneyInsertList(CFinneyCell inCell);

	int m_itr; //current iteration

	FILE * m_LogFP;

	char m_strTSLF[255];

	char m_strFireOutputDirectory[255];

	int isValid(int row, int col, int * landOnFire);

	long fireSpread(int row, int col);

	void ReadDEM(char * fileName);	

	void CalculateFSFactor(long lCurrentFS, long lFS);

	void CalculateSlope(int row1, int col1, int row2, int col2);

	void CalculateWind(int index);

	double m_dFSFactor;

	float m_fSlope;

	float m_fWind;

	int m_iOriginRow, m_iOriginColumn;

	int m_iMapRow, m_iMapColumn;	

	long m_lPredefinedFireSize; //in pixels

	float m_fPredefinedDuration; //in minutes

	float m_fFireSize; //in ha

	long burnedCells[MAX_LANDUNITS];

	int m_FinneyDebugOutput;



	double modifiedSpreadProb(int row, int col);

	void ReadParam(FILE *infile); // read fire parameter file

	void AttachLandUnitGIS(SITES* outsites);

	void DrawWindEvent();

	void PrintWindLog();

	void WriteTSLF(int snr, int snc, int itr);

	

	//data at the site level

	//data at the fire regime level

	//data at the landscape level

	fireParam m_fireParam;

	finneyParam m_finneyParam;

	CFireSites * m_pFireSites;

	CFireRegimeUnits * m_pFireRegimeUnits;

	int m_DLLMode;

	class MAP8 m_Map,        //Map of damage for iteration.

		       m_cummMap;  //Map of damage for model run.

	class MAP8 m_InitiationMap,

		m_cummInitiationMap;

	long * m_lptrIgnitionOccurance;

	int * m_iptrValidLandUnits;

	int m_iNumLU;

	int m_iWindIntensity;

	int m_iWindDirectionIndex;

	int m_iWindEventsLog[42]; 

	long FinneynumCohorts;

	double m_maxWindRate;



	float m_fRatio;

	float m_fA; //minor axis length

	float m_fB; //major axis length

	float m_fC; //Squar root of B^2 - A^2

	

	// long length_CostList; // the length of cost list (i.e., how many non-background cells have been calculated of its accumulative travel time)

	// long length_ActiveList;//the length of active point list (i.e., how many cells left to be counted as spreading souces)

	long length_BurnedCells;

	bool m_FinneyCutoff;

	

	int ** m_checkMap;

	float ** m_fuelCostMap;

	float ** m_windCostMap;

	float ** m_minTimeMap;

	float ** m_actualROSMap;



	char * m_pIgnitionStatusArray;	

	long m_FRUAvailableCells[255];



	StochasticLib * m_pStochastic;

	PDP * m_pPDP;

	SPECIESATTRS *  m_pSPECIESATTRS;

	SITES * m_pLAND;	

	long fireSize(float MFS,float STD);

	int disturb(int row, int col, int totArea, class MAP8 &m, FILE *logfile,

		double x, int itr);

	int damage(LDPOINT p, int &fireClass);



	list<CFinneyCell> FinneyList;
	//<Add By Qia on July 31 2012>
	vector<string> Fire_regime_files;
	vector<string> Fire_regime_gisfiles;
	//</Add By Qia on July 31 2012>
};



#endif

