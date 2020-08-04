#ifndef PARAMETERS_H

#define PARAMETERS_H



#define NO_DISPERSAL  0     //No seed dispersal.

#define UNIFORM       1     //Uniform seed dispersal.

#define NEIGHBORS     2     //Seed to immediate neighbors.

#define DISPERSAL     3     //Seed within effective distance.

#define RAND_ASYM     4     //Seed using interpolated chaotic distances.

#define MAX_DIST      5     //RAND_ASYM up to maximum distances.

#define SIM_RAND_ASYM 6     //RAND_ASYM up to maximum distances, Simulated

									//random asymptopic after maximum distance.

#include <stdio.h>



class  PARAMETERS

{

public:

  char

	*specAttrFile,		//Species Attributes input file name.

	*landUnitFile,		//Landtype attribute file name.

	//*landUnitMapFile,	//landtype map file name.     

	*landImgMapFile,    //* landtype.img 

	*siteInFile,		//Site input file name.

	*siteImgFile,        //* speciesmap3.img

	*reclassInFile,  	//Reclassification input file name.

	//*reclassOutFile, 	//Reclassification output file name.

	*outputDir,    	  	//Output directory.

	*disturbance,		//Disturbance regime file name.

	*default_plt,		//For map output

	*freq_out_put,		//Output map frequency file

	//*ageIndexFile,		//species age output index file

	*OutputOption70,	//landis 7.0 output option

	//<Add By Qia on Jan 21 2009>

	*varianceSECFile;	//Customized By user year variances

	int flagforSECFile; // 0,1,2, 3

					//0 is no change, 1 is pulse, 2 is random, 3 read from file 

	FILE *FpSECfile;

	//</Add By Qia on Jan 21 2009>

	//<Add By Qia on June 29 2009>

	int SeedRainFlag;

	int GrowthFlag;

	int MortalityFlag;

	int VolumeFlag;

	

	char *SeedRainFile;

	char *GrowthFlagFile;

	char *MortalityFile;

	char *VolumeFile;

	char *Biomassfile;

	const char *pszSRS_WKT = NULL;

	//</Add By Qia on June 29 2009>



//#ifdef _FUEL_

   char

	  *strFuelInitName;		//add by Wei Li

   int

	  fuel,

	  fuelFlag;



   int	fuelManagement;    //for fuel management

   FILE* fuelManageFile;

   FILE* fuelManOutStand;

//#endif

//<Add By Qia on Jan 05 2009>

int timestep;

int timestep_BDA;

int timestep_Harvest;

int timestep_Fuel;

int timestep_Fire;

int timestep_Wind;

//</Add By Qia on Jan 05 2009>

//<Add By Qia on Aug 1 2012>
double stocking_x_value;
double stocking_y_value;
double stocking_z_value;
//</Add By Qia on Aug 1 2012>



  int

	fire,				//Turn fire disturbances on/off.

//	timber,				//Turn timber disturbances on/off.

//#ifdef __HARVEST__

     harvest,           //Turn harvest events on/off.

     standAdjacencyFlag,//Turn stand adjacency flag on/off.

     harvestDecadeSpan, //Sites harvested within this time span are considered

                        //"recently harvested".

//#endif

	numberOfIterations, //Number of iterations in model.

	numberOfReplicates, //Number of replicates in model.

	randSeed,           //Random number seed.

	cellSize,           //Length of side of cell in meters.

	dispRegime;         //Seeding regime: NO_DISPERSAL, UNIFORM, NEIGHBORS,

			      		//DISPERSAL, or INTERPOLATE.

//#ifdef __HARVEST__ 

  float 

     harvestThreshold;  //If the number of "recently harvested" sites on a

                        //divided by the number of active sites on a stand

                        //is greater than or equal to this value, consider

                        //the stand "recently harvested".

//#endif



  //Wind

  char*	strWindInitName;				//Turn wind disturbances on/off.



  //BDA

  char*	strBDAInitName;  //BDAInit.dat directory and file name

  //Harvest

  char*	strHarvestInitName;



  char* strFireInitName;



	PARAMETERS();		//Constructor.

	~PARAMETERS();		//Destructor.

	int read(FILE*, int*);	//Read in all parameters from a file.

	void write(FILE*);	//Write all parameters to a file.

	void dump();		//Dump all parameters to the CRT.

};



#endif



