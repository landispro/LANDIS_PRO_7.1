#ifndef SITES_H

#define SITES_H



#include <stdio.h>

#include <math.h>

#include "site.h"

#include "landus.h"



//<Add By Qia on Oct 08 2008>

#include <vector>

#include <list>

//</Add By Qia on Oct 08 2008>



//<Add By Qia on May 03 2010>

#define NumTypes70Output 8 //add DBH output option on Oct 19 2010

#define NumTypesAgeRange70 8

#define NumTypes70OutputUsing 7

#define NumTypesAgeRange70Using 6







//</Add By Qia on May 03 2010>



#ifdef LANDIS40CORE_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



//<Add By Qia on Oct 08 2008>

typedef std::vector<SITE *>  SortedSITE;

//</Add By Qia on Oct 08 2008>





class DLLCLASS SITES



{

public:



SITES(int, int, int);             //Constructor.  The first parameter is the

                                  //number of species in the model.  The other

                                  //parameters dimension the number of

                                  //rows and columns on the map.

SITES();                          //Constructor.  Initial values must be

                                  //set later by the dim method.  This is

                                  //useful so that a SITES object may be

                                  //declared statically but set up

                                  //dynamically.

~SITES();                         //Destructor.

void dim(int,int,int);            //This will set the number of species,

                                  //rows and columns in the map.

SITE*  operator() (int, int);      //This will return a pointer to a singular //need to change by Qia Oct 07 2008

                                  //site.  It is referrenced by row and column

                                  //number.

void read(FILE*);                 //Read in all site data. //need to change by Qia Oct 07 2008

void write(FILE*);                //Write out all site data. //need to change by Qia Oct 07 2008

void dump();                      //Dump set of site data to the CRT.



//<Add by Qia on Oct 07 2008>

int SITE_compare(SITE *site1, SITE *site2);

int SITE_compare(int site1_x, int site1_y, int site2_x, int site2_y);

                                   // Compare two sites to see the relation between them

                                   // return 0:equal; return 1: site1 is bigger; return 2: site2 is bigger; -1: error

                               

int SITE_sort();				  // sort the pointers to sites



int SITE_insert(int pos_sortIndex, SITE *site, int i, int j);					// insert a site in to list



int SITE_delete(int pos_sortIndex, SITE *site, int i, int j);				// remove a site from list



//<Add by Qia on Oct 09 2008>

int SITE_LocateinSortIndex(SITE *site, int *pos, int *ifexist);

//</Add by Qia on Oct 09 2008>



//</Add by Qia on Oct 07 2008>



//<Add by Qia on Oct 08 2008>

void fillinSitePt(int i, int j, SITE *site);

SITE * locateSitePt(int i, int j);

void fillinLanduPt(int i, int j, LANDUNIT *landUnitPt);

LANDUNIT * locateLanduPt(int i, int j);

//</Add by Qia on Oct 08 2008>



//<Add by Qia on Oct 20 2008>

void BefStChg(int i, int j);

void AftStChg(int i,int j);

//</Add By Qia on Oct 20 2008>

/* J.Yang side-effect of del. the composite rel.

void attach(LANDUNITS*);          //This attaches a set of land units to all

                                  //sites.

*/

void setHeader(unsigned long []); //Set the header info for sites

unsigned long* getHeader();		 //Copy the header info of sites.

int number();			  				 //This will return the total number of sites.

int numRows();                    //Returns number of rows of sites.

int numColumns();                 //Returns number of columns of sites.

int numActive();                  //Returns number of active sites on the map.

//#ifdef __HARVEST__

int inBounds(int r, int c);

//#endif

//<Add By Qia on June 24 2009>

void SiteDynamics(int RDflag, int Row, int Col);

void GetRDofSite(int Row, int Col);

void MaxAgeofSite(SITE *siteptr);

void GetSeedNumberOnSite(int Row, int Col);

void NaturalMortality(SITE *siteptr, int Row, int Col,int StartAge);

//</Add By Qia on June 24 2009>

//<Add By Qia on June 29 2009>

void GetSeedDispersalProbability(char* fileSeedDispersal, int seedflag);

void GetSpeciesGrowthRates(char* fileGrowthRates, int growthrateflag);

void GetSpeciesMortalityRates(char* fileMortalityRates, int mortalityrateflag);

void GetVolumeRead(char* , int );

//</Add By Qia on June 29 2009>

//<Add By Qia on June 30 2009>

float GetSeedRain(int spec,int Distance);

float GetGrowthRates(int spec,int year, int landtype_index);

float GetMortalityRates(int spec,int year, int landtype_index);

float GetVolume(int spec,int year, int landtype_index);

//</Add By Qia on June 30 2009>

//<Add By Qia on July 1 2009>

void SetSeedRain(int spec,int Distance,float value);

void SetGrowthRates(int flag, int spec,int year,float value,int index_landtype);

void SetMortalityRates(int flag, int spec,int year,float value, int index_landtype);

void SetVolume(int growthrate_flag, int spec,int year,float value, int index_landtyp);



//</Add By Qia on July 1 2009>

//<Add By Qia on July 7 2009>

float GetBiomassData(int i, int j);

void SetBiomassData(int i, int j, float value);

void SetBiomassNum(int num);

void SetBiomassThreshold(float num);

float GetBiomassThreshold();

void BiomassRead(FILE *fp);

//</Add By Qia on July 7 2009>

void GetMatureTree();//Add on July 10 2009

int GetMaxShadeTolerance();

void Selfthinning(SITE* siteptr, LANDUNIT *l, int row, int col);

void SeedGermination(SITE* siteptr, LANDUNIT *l,int RDFlag);

void NaturalMortality_killbytargetRD(SITE * siteptr,int Row,int Col,double targetRD);


public: 

SortedSITE SortedIndex;

//<Add By Qia on Aug 1 2012>
double stocking_x_value;
double stocking_y_value;
double stocking_z_value;
//</Add By Qia on Aug 1 2012>
//<Add By Qia on June 29 2009>

int SeedRainFlag;

int GrowthFlag;

int MortalityFlag;

int VolumeFlag;

//</Add By Qia on June 29 2009>

//<Add By Qia on July 1 2009>

int CellSize;

int MaxDistofAllSpec;

int specNum;

//</Add By Qia on July 1 2009>

//<Add By Qia on Jan 13 2009>

int TimeStep;

int TimeStep_Harvest;

int TimeStep_Fuel;

int TimeStep_BDA;

int TimeStep_Wind;

int TimeStep_Fire;

//</Add By Qia on Jan 13 2009>

//<Add By Qia on March 2009>

int Pro0or401;

//</Add By Qia on March 2009>

int MaxShadeTolerance;

int countWenjuanDebug;

int flag_cut_GROUP_CUT[200]; //add by Qia on Nov 10 2011

int flag_plant_GROUP_CUT[200];

int num_TreePlant_GROUP_CUT[200];

int flag_cut_GROUP_CUT_copy[200]; //add by Qia on June 02 2012

int flag_plant_GROUP_CUT_copy[200];

int num_TreePlant_GROUP_CUT_copy[200];

//<Add By Qia on July 14 2009>

float xLLCorner;

float yLLCorner;

//</Add By Qia on July 14 2009>



//<Add By Qia on Dec 28 2010>

int Flag_AgeDistStat;

int *AgeDistStat_Year;

int *AgeDistStat_AgeRange;



//<Add By Qia on Dec 29 2010>

void SetAgeDistStat_YearVal(int specindex, int count, int value1);



int GetAgeDistStat_YearVal(int specindex, int count, int *value1);





int GetAgeDistStat_YearCount(int specindex);



int SetAgeDistStat_YearValCount(int specindex, int count);



/////////////////

void SetAgeDistStat_AgeRangeVal(int specindex, int count, int value1, int value2);

int GetAgeDistStat_AgeRangeVal(int specindex, int count, int *value1, int *value2);



int GetAgeDistStat_AgeRangeCount(int specindex);



int SetAgeDistStat_AgeRangeCount(int specindex, int count);



//</Add By Qia on Dec 28 2010>



//<Add By Qia on Feb 09 2010>

void Wind70outputdim();

void Harvest70outputdim();

void Fire70outputdim();

void Fuel70outputdim();

void BDA70outputdim();



double Wind70outputGetBiomassvalue(int i, int j);

double Harvest70outputGetBiomassvalue(int i, int j);

double Fire70outputGetBiomassvalue(int i, int j);

double Fuel70outputGetBiomassvalue(int i, int j);

double BDA70outputGetBiomassvalue(int i, int j);



double Wind70outputGetCarbonvalue(int i, int j);

double Harvest70outputGetCarbonvalue(int i, int j);

double Fire70outputGetCarbonvalue(int i, int j);

double Fuel70outputGetCarbonvalue(int i, int j);

double BDA70outputGetCarbonvalue(int i, int j);



void Wind70outputIncreaseBiomassvalue(int i, int j, double value);

void Harvest70outputIncreaseBiomassvalue(int i, int j, double value);

void Fire70outputIncreaseBiomassvalue(int i, int j, double value);

void Fuel70outputIncreaseBiomassvalue(int i, int j, double value);

void BDA70outputIncreaseBiomassvalue(int i, int j, double value);



void Wind70outputIncreaseCarbonvalue(int i, int j, double value);

void Harvest70outputIncreaseCarbonvalue(int i, int j, double value);

void Fire70outputIncreaseCarbonvalue(int i, int j, double value);

void Fuel70outputIncreaseCarbonvalue(int i, int j, double value);

void BDA70outputIncreaseCarbonvalue(int i, int j, double value);



//</Add By Qia on Feb 09 2010>

//<Add By Qia on Feb 03 2010>

double *BiomassFireCost;

double *CarbonFireCost;

int Fireflag;

double *BiomassHarvestCost;

double *CarbonHarvestCost;

int Harvestflag;

double *BiomassFuelCost;

double *CarbonFuelCost;

int Fuelflag;

double *BiomassBDACost;

double *CarbonBDACost;

int BDAflag;

double *BiomassWindCost;

double *CarbonWindCost;

int Windflag;



//</Add By Qia on Feb 03 2010>

//<Add By Qia on April 23 2010>

int *OutputGeneralFlagArray;

int flagAgeRangeOutput;

int *OutputAgerangeFlagArray;

int  *SpeciesAgerangeArray;



void SetOutputGeneralFlagArray(int i, int j, int value);

int GetOutputGeneralFlagArray(int i, int j);



void SetflagAgeOutput(int value);

int GetflagAgeOutput();



void SetOutputAgerangeFlagArray(int i, int j, int value);

int GetOutputAgerangeFlagArray(int i, int j);



void SetSpeciesAgerangeArray(int specindex, int count, int value1, int value2);

int GetSpeciesAgerangeArray(int specindex, int count, int *value1, int *value2);

int GetAgerangeCount(int specindex);

int SetAgerangeCount(int specindex, int count);



void Read70OutputOption(char *FileName);

//</Add By Qia on April 23 2010>

private:

//SITE* map;     //This is the internal represenation of the //commented by Qia Oct 07 2008 

                                  //sites map.



//<Add By Qia on June 29 2009>

float **SeedRain;

float *GrowthRates;
float *MortalityRates;
std::vector<float *> GrowthRates_file;
std::vector<float *> MortalityRates_file;
std::vector<float *> Volume_file;

float *Volume;

//</Add By Qia on June 29 2009>



//<Add By Qia on March 04 2011>

void ListbubbleSort();



std::vector<float> AreaList;

std::vector<int>	SpecIndexArray;

std::vector<int>	AgeIndexArray;



//</Add By Qia on March 04 2011>



//<Add by Qia Oct 07 2008>

SITE **map;

SITE *map70;

LANDUNIT **map_landtype;

SITE *sitetouse;

//</Add by Qia on Oct 07 2008>

//<Add By Qia on July 7 2009>

float *biomassData;

int biomassNum;

float BiomassThreshold;

//</Add By Qia on July 7 2009>

int rows, columns;                //Number of rows and columns contained in the

                                  //whole map.

unsigned long header[32];			 //Upperleft coordinates of sites



};



#undef DLLCLASS



#endif

