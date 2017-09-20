/****************************************************************************

* LANDIS model design:                                                      *

*        David J. Mladenoff, Joel E. Boeder, Hong S. He, George E. Host     *

* LANDIS 4.0  Dynamic Linked Libraries :                                    *

*        Wei Li, Hong S. He													*

* Contact :

*						                                                    *

*        Hong S. He, Forestry Department, University of Missouri at			*

*        Columbia,                       *

*        heh@missouri.edu													*

*                                                                           *

* History:                                                                  *

*        Name           Date                  General Modification          *

* ----------------  ------------  ----------------------------------------- *

*  Jeol E. Boeder       09/93            original coding                    *

* Chris Heim           ??/94            upgrade from LANDIS 1.0 to 1.5      *

* Hong S. He         10/94-2003       upgrade to LANDIS 3.6 (VC++6.0)       *

* Wei Li			 05/2003-08/2008   LANDIS 4.0							*

* Qia Wang		08/2008-current	  LANDIS Pro

*-----------------  ------------  ----------------------------------------- *

* Last changes were made by Qia Wang 2009.									*

*                                                                           *

* Version: Pro																*

* Description:                                                              *

*        LANDIS is a raster based landscape model simulating forest         *

*        succession, wind and fire disturbances, forest management, and     *

*        the interaction among them over long period of time.               *

* Documentations:                                                           *

*																			*

*                                                                           *

****************************************************************************/

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include <time.h>

#include <afxwin.h> 

#include <string.h>

#include "defines.h"

#include "system1.h"

#include "error.h"

#include "params.h"

#include "optim.h"

#include "landu.h"

#include "landus.h"

#include "specatt.h"

#include "specatts.h"

#include "specie.h"

#include "site.h"

#include "sites.h"

#include "fire.h"

#include "wind.h"

#include "io.h"

#include "map8.h"

#include "reclass3.h"

//*gdal 

#include <iostream>

#include <cstdio>

#include <stdio.h>

#include "gdal_priv.h"

#include "cpl_conv.h" // for CPLMalloc()

#include "cpl_string.h"

#include "ogr_spatialref.h"



#include "GlobalFunctions.h"







#include "PDP.h"



#include "Succession.h"



//fuel

#include "FuelGlobalFuncs.h"





#include "BDAExport.h"

#include "FireExport.h"

//<Add By Qia on Jan 05 2009>

#include "GlobalVariables.h"

//</Add By Qia on Jan 05 2009>
#include <vector>



using namespace std;

static int red2[maxLeg] = { 0, 70, 0, 0, 0, 0, 0, 0, 200, 100, 255, 150, 200, 200, 255, 255 };

static int green2[maxLeg] = { 0, 70, 0, 0, 0, 150, 200, 255, 30, 200, 50, 50, 200, 0, 255 };

static int blue2[maxLeg] = { 0, 70, 125, 200, 255, 0, 100, 0, 30, 50, 50, 0, 0, 255 };

FILE *fpforTimeBU;//Add By Qia on Feb 20 2009
FILE *fpLogFileSEC; //Add By Qia on Apr 24 2012


/////////////////////////////////////////////////////////////////////////////

//                      FUNCTION DEFINITIONS                               //

/////////////////////////////////////////////////////////////////////////////

void singularLandisIteration(int, int, int, int, int, int, double[6], PDP*);



/////////////////////////////////////////////////////////////////////////////

//                      GLOBAL VARIABLE DECLARATION                        //

//      THESE GLOBALS MAY BE REFERRENCED IN ALL LANDIS MODULES             //

//          THEY ARE DEFINED IN THE LANDIS HEADER FILE                     //

/////////////////////////////////////////////////////////////////////////////

void Succession_Landis70(int snr, int snc, PDP* ppdp); //Add By Qia on June 29 2009

void initiateRDofSite_Landis70(int snr, int snc);

void KillTrees(int snr, int snc); // <Add By Yang on Nov 04 2014> 

PARAMETERS    parameters;       //System paramters.            SYSTEM.CPP

SPECIESATTRS  speciesAttrs(MAX_SPECIES); //Species attributes. SPECATT.CPP

LANDUNITS     landUnits(MAX_LANDUNITS);    //Land units.         LANDU.CPP

SITES         sites;            //Map of all landis sites.     SITES.CPP

//OPTIM         optim;            //Optimization structure.      OPTIM.CPP

//<Add By Qia on Jan 06 2009>

timestep	  time_step;

//</Add By Qia on Jan 06 2009>

//BDA 

BDAS*		  pBDAS;

WIND*		  pWINDdll;

HINSTANCE	  gLibBDA;

HINSTANCE	  gLibWind;

HINSTANCE	  gLibFuel;

HINSTANCE	  gLibFire;



CFIRE*		  pFire = NULL;



SUCCESSION* pSuccession = NULL;
//<Add By Qia on Mar 15 2012>
vector<string> SEC_landtypefiles;
vector<string> SEC_gisfiles;
//</Add By Qia on Mar 15 2012>

//#ifdef __HARVEST__

int freq[6];

//#else

//int freq[5];

//#endif



//#ifdef __HARVEST__

int currentDecade;

int numberOfSpecies;

 unsigned short currentHarvestEventId = 0;





MAP16 visitationMap;

//#endif Harvest



char reMethods[MAX_RECLASS][80], ageMaps[MAX_SPECIES][80];



int gDLLMode;



void putHarvestOutput(int itr, double wAdfGeoTransform[])

{



	MAP8 m(sites.getHeader());

	char str[200], str1[200];

	char str_htyp[200], str_htyp1[200], str_dec[200], str_dec1[200];

	writeStandReport();

	//if (((itr%freq[5]) == 0) && (freq[5] <= sites.TimeStep) || (itr*sites.TimeStep == freq[5]) && (freq[5] >= 0))

	//{

	//	//sprintf(str_htyp, "%s/%s/htyp%d.asc", parameters.outputDir, "Harvest", itr*sites.TimeStep_Harvest);

	//	sprintf(str_htyp1, "%s/%s/htyp%d.img", parameters.outputDir, "Harvest", itr*sites.TimeStep_Harvest);//*

	//	//sprintf(str_dec, "%s/%s/hdec%d.asc", parameters.outputDir, "Harvest", itr*sites.TimeStep_Harvest);

	//	sprintf(str_dec1, "%s/%s/hdec%d.img", parameters.outputDir, "Harvest", itr*sites.TimeStep_Harvest);//*

	//	//output_harvest_Dec_Type(itr, str_htyp, str_dec);

	//	output_harvest_Dec_Type(itr, str_htyp, str_htyp1, str_dec, str_dec1);//*

	//	for (int i = 0; i < sites.specNum; i++){

	//		//sprintf(str, "%s/%s/%s_BACut%d.asc", parameters.outputDir, "Harvest", speciesAttrs(i + 1)->name, itr*sites.TimeStep_Harvest);

	//		sprintf(str1, "%s/%s/%s_BACut%d.img", parameters.outputDir, "Harvest", speciesAttrs(i + 1)->name, itr*sites.TimeStep_Harvest);//*

	//		//PutOutput_harvestBACut_spec(str, i);

	//		PutOutput_harvestBACut_spec(str, str1, i);//*

	//	}

	if (itr * freq[3] <= parameters.numberOfIterations)
	{

		sprintf(str_htyp1, "%s/%s/htyp%d.img", parameters.outputDir, "Harvest", itr*freq[3] * sites.TimeStep_Harvest);//*

		sprintf(str_dec1, "%s/%s/hdec%d.img", parameters.outputDir, "Harvest", itr*freq[3] * sites.TimeStep_Harvest);//*

		output_harvest_Dec_Type(itr, str_htyp, str_htyp1, str_dec, str_dec1, wAdfGeoTransform);//*

		for (int i = 0; i < sites.specNum; i++)
		{

			sprintf(str1, "%s/%s/%s_BACut%d.img", parameters.outputDir, "Harvest", speciesAttrs(i + 1)->name, itr*freq[3] * sites.TimeStep_Harvest);//*

			PutOutput_harvestBACut_spec(str, str1, i, wAdfGeoTransform);//*
		}

		sprintf(str1, "%s/%s/BACut%d.img", parameters.outputDir, "Harvest", itr*freq[3] * sites.TimeStep_Harvest);//*

		PutOutput_harvestBACut(str, str1, wAdfGeoTransform);
	}


			if (parameters.numberOfIterations % freq[3] != 0)
			{

				sprintf(str_htyp1, "%s/%s/htyp%d.img", parameters.outputDir, "Harvest", parameters.numberOfIterations* sites.TimeStep_Harvest);//*

				sprintf(str_dec1, "%s/%s/hdec%d.img", parameters.outputDir, "Harvest", parameters.numberOfIterations * sites.TimeStep_Harvest);//*

				output_harvest_Dec_Type(itr, str_htyp, str_htyp1, str_dec, str_dec1, wAdfGeoTransform);//*

				for (int i = 0; i < sites.specNum; i++){

					sprintf(str1, "%s/%s/%s_BACut%d.img", parameters.outputDir, "Harvest", speciesAttrs(i + 1)->name, parameters.numberOfIterations* sites.TimeStep_Harvest);//*

					PutOutput_harvestBACut_spec(str, str1, i, wAdfGeoTransform);//*
				}
				sprintf(str1, "%s/%s/BACut%d.img", parameters.outputDir, "Harvest", parameters.numberOfIterations* sites.TimeStep_Harvest);//*

				PutOutput_harvestBACut(str, str1, wAdfGeoTransform);
			}
		////sprintf(str, "%s/%s/BACut%d.asc", parameters.outputDir, "Harvest", itr*sites.TimeStep_Harvest);

		//sprintf(str1, "%s/%s/BACut%d.img", parameters.outputDir, "Harvest", itr*sites.TimeStep_Harvest);//*

		////PutOutput_harvestBACut(str);

		//PutOutput_harvestBACut(str, str1);


	}









void updateLandtypeMap8(FILE * ltMapFile)

{

	unsigned char c;

	unsigned long dest[64];

	int

		nCols,

		nRows,

		numRead,

		coverType,

		b16or8;

	SITE* s;

	unsigned short		 intdata;

	LDfread((char*)dest, 4, 32, ltMapFile);



	if ((dest[1] & 0xff0000) == 0x020000)

		b16or8 = 16;

	else if ((dest[1] & 0xff0000) == 0)

		b16or8 = 8;

	else

	{

		b16or8 = -1;

		errorSys("Error: IO: Landtype map is neither 16 bit or 8 bit.", STOP);

	}

#ifdef __UNIX__

	ERDi4_c(&dest[4],nCols);

	ERDi4_c(&dest[5],nRows);

#else

	nCols = dest[4];

	nRows = dest[5];

#endif

	int xDim = sites.numColumns();

	int yDim = sites.numRows();

	if ((nCols != xDim) || (nRows != yDim))

		errorSys("landtype map and species map do not match.", STOP);



	if (b16or8 == 8)  //8 bit

	{

		for (int i = yDim; i > 0; i--)

		{

			for (int j = 1; j <= xDim; j++)

			{

				numRead = LDfread((char*)(&c), 1, 1, ltMapFile);

				coverType = (int)c;

				if ((numRead >= 0) && (coverType >= 0))

				{

					//s=sites(i,j); // comment By Qia Oct 10 2008

					//<Add By Qia on Oct 10 2008>

					sites.fillinLanduPt(i, j, landUnits(coverType));


					//</Add By Qia on Oct 10 2008>

					//		   s->lastWind=(short)s->landUnit->initialLastWind;  modified by Vera Dec. 30

					//		 if ((gDLLMode & G_WIND && gDLLMode & G_BDA) || (gDLLMode & G_WIND && gDLLMode & G_FUEL))

					// if (gDLLMode & G_WIND)

					//	(ppdp->sTSLWind)[i][j] = (short)sites.locateLanduPt(i,j)->initialLastWind;

					//original landis4.0: (ppdp->sTSLWind)[i][j] = (short)s->landUnit->initialLastWind;

					//changed By Qia on Oct 13 2008



					// 	   s->lastFire=(short)s->landUnit->initialLastFire;

					//		 ppdp->sTSLFire[i][j] = 

				}

				else

					errorSys("illegal landtype class found4.", STOP);

			}

		}

	}

	else if (b16or8 == 16)	//16 bit

	{

		for (int i = yDim; i > 0; i--)

		{

			for (int j = 1; j <= xDim; j++)

			{

				numRead = LDfread((char*)(&intdata), 2, 1, ltMapFile);

				coverType = (int)intdata;

				if ((numRead >= 0) && (coverType >= 0))

				{

					//s=sites(i,j);// comment By Qia Oct 10 2008

					//s->landUnit=landUnits(coverType);// comment By Qia Oct 10 2008

					//<Add By Qia on Oct 10 2008>

					sites.fillinLanduPt(i, j, landUnits(coverType));


					//</Add By Qia on Oct 10 2008>

					//		   s->lastWind=(short)s->landUnit->initialLastWind;  modified by Vera Dec. 30

					//		 if ((gDLLMode & G_WIND && gDLLMode & G_BDA) || (gDLLMode & G_WIND && gDLLMode & G_FUEL))

					// if (gDLLMode & G_WIND)

					//	(ppdp->sTSLWind)[i][j] = (short)sites.locateLanduPt(i,j)->initialLastWind;

					//original landis4.0: (ppdp->sTSLWind)[i][j] = (short)s->landUnit->initialLastWind

					//changed By Qia on Oct 13 2008

					// 	   s->lastFire=(short)s->landUnit->initialLastFire;

					//		 ppdp->sTSLFire[i][j] = 

				}

				else

					errorSys("illegal landtype class found5.", STOP);

			}

		}

	}



}

void updateLandtypeImg8(GDALDataset* ltimgFile)

{

	/*unsigned char c;

	unsigned long dest[64];*/

	int nCols, nRows, numRead, coverType;

	SITE* s;

	unsigned short		 intdata;

	float *pafScanline; //*

	GDALRasterBand  *poBand;

	/*LDfread((char*)dest, 4, 32, ltMapFile);



	if ((dest[1] & 0xff0000) == 0x020000)

		b16or8 = 16;

	else if ((dest[1] & 0xff0000) == 0)

		b16or8 = 8;

	else

	{

		b16or8 = -1;

		errorSys("Error: IO: Landtype map is neither 16 bit or 8 bit.", STOP);

	}*/

#ifdef __UNIX__

	ERDi4_c(&dest[4], nCols);

	ERDi4_c(&dest[5], nRows);

#else

	nCols = ltimgFile->GetRasterXSize(); //*

	nRows = ltimgFile->GetRasterYSize(); //*

#endif

	int xDim = sites.numColumns();

	int yDim = sites.numRows();

	if ((nCols != xDim) || (nRows != yDim))

		errorSys("landtype map and species map do not match.", STOP);

	pafScanline = (float *)CPLMalloc(sizeof(float)* (xDim * yDim));

	poBand = ltimgFile->GetRasterBand(1);

	poBand->RasterIO(GF_Read, 0, 0, xDim, yDim, pafScanline, xDim, yDim, GDT_Float32, 0, 0);

		for (int i = yDim; i > 0; i--)
		{
			for (int j = 1; j <= xDim; j++)
			{
				
				coverType = (int)*(pafScanline + (yDim - i)*xDim + j - 1);//*

				if (coverType >= 0)

				{
					sites.fillinLanduPt(i, j, landUnits(coverType));


					//</Add By Qia on Oct 10 2008>

					//		   s->lastWind=(short)s->landUnit->initialLastWind;  modified by Vera Dec. 30

					//		 if ((gDLLMode & G_WIND && gDLLMode & G_BDA) || (gDLLMode & G_WIND && gDLLMode & G_FUEL))

					// if (gDLLMode & G_WIND)

					//	(ppdp->sTSLWind)[i][j] = (short)sites.locateLanduPt(i,j)->initialLastWind;

					//original landis4.0: (ppdp->sTSLWind)[i][j] = (short)s->landUnit->initialLastWind;

					//changed By Qia on Oct 13 2008



					// 	   s->lastFire=(short)s->landUnit->initialLastFire;

					//		 ppdp->sTSLFire[i][j] = 

				}

				else

					errorSys("illegal landtype class found6.", STOP);

			}

		}

	}



void envUpdate(int i)

{

	char str[255], iterString[5];

	char tempStr[255];

	FILE * luFile, *ltMapFile;

	itoa(i, iterString, 10);

	GDALDataset  *simgFile, *ltimgFile; //*

	double        adfGeoTransform[6]; //*

	GDALAllRegister(); //*

	double wAdfGeoTransform[6];


	//update land type attribute

	//file name is landtype.dat1, landtype.dat10 etc

	strcpy(str, parameters.landUnitFile);

	strcat(str, iterString);

	if ((luFile = LDfopen(str, 1)) == NULL)

	{

		sprintf(tempStr, "Landtype attribute file %s not found.\n", str);

		errorSys(tempStr, STOP);

	}

	else

	{

		//update landtype attribute

		landUnits.read(luFile);

		LDfclose(luFile);

	}



	//update land type GIS

	//file name is landtype.gis1, landtype.gis10 etc

	//strcpy(str, parameters.landUnitMapFile);

	strcpy(str, parameters.landImgMapFile);

	strcat(str, iterString);

	if ((simgFile = (GDALDataset *)GDALOpen(parameters.landImgMapFile, GA_ReadOnly)) == NULL) //* landtype.img

	{

		sprintf(tempStr, "Landtype img file %s not found.\n", str);

		errorSys(tempStr, STOP);

	}
	else

	{

		//update landtype img

		if (simgFile->GetGeoTransform(adfGeoTransform) == CE_None){ //*

			for (int i = 0; i < 6; i++){//*

				wAdfGeoTransform[i] = adfGeoTransform[i];//*
			}//*

		}//*

		updateLandtypeImg8(simgFile);

		GDALClose((GDALDatasetH)simgFile); //*


	}



	//if ((ltMapFile = LDfopen(str, 2)) == NULL)

	//{



	//	sprintf(tempStr, "Landtype img file %s not found.\n", str);

	//	errorSys(tempStr, STOP);

	//}

	//else

	//{

	//	//update landtype GIS

	//	updateLandtypeMap8(ltMapFile);

	//	LDfclose(ltMapFile);

	//}



}

////////////////////////////////////////////////////////////////////////////

//                             MAIN ROUTINE                               //

////////////////////////////////////////////////////////////////////////////



int main(int argc, char *argv[])

//Main program.  This contains start and shut down procedures as well as the

//main iteration loop.



{
   	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FILE *infile;

	char str[100];

	int numbOfIter, snr, snc, specAtNum;

	int run_extraSeed = 0;

	int x;

	int numSitesActive, envOn = 0, reclYear = 0;

	time_t ltime, ltimeTemp;

	long ltimeDiff;

	int frequency[6] = {1,1,1,1,1,1};

	GDALDataset  *simgFile, *ltimgFile; //*

	double        adfGeoTransform[6]; //*

	GDALAllRegister(); //*


	time(&ltime);

	printf("Starting LANDIS PRO 7.1 at %s", ctime(&ltime));



	if ((argc != 2) && (argc != 3) && (argc != 4))

	{

		argHelp();

		exit(255);

	}



	if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "-H") == 0))

	{

		argHelp();

		exit(255);

	}

	else if ((strcmp(argv[1], "-p") == 0) || (strcmp(argv[1], "-P") == 0))

	{

		help();

		exit(255);

	}



	if ((strcmp(argv[1], "-e") == 0) || (strcmp(argv[1], "-E") == 0))

	{

		if (argc != 4)

			errorSys("Syntax error. For help enter: landis -h", STOP);

		envOn = (atoi(argv[2]));

		if (!envOn)

			errorSys("Invalid year value", STOP);

		else if ((infile = LDfopen(argv[3], 1)) == NULL)

			errorSys("Input file not found. For help enter: landis -h", STOP);

	}



	else if ((strcmp(argv[1], "-r") == 0) || (strcmp(argv[1], "-R") == 0))

	{

		if (argc != 4)

			errorSys("Syntax error. For help enter: landis -h", STOP);

		reclYear = atoi(argv[2]);

		if (!(reclYear%sites.TimeStep))

			errorSys("Invalid year number", STOP);

		else if ((infile = LDfopen(argv[3], 1)) == NULL)

			errorSys("Input file not found. For help enter: landis -h", STOP);

	}





	else if (((infile = LDfopen(argv[1], 1)) == NULL))

		errorSys("Input file not found. For help enter: landis -h", STOP);



	if (argc == 2)

	{

		printf("input: %s\n", argv[1]);

	}

	else

		printf("input: %s\n", argv[3]);



	printMessage("Beginning Landis 7.1 Pro Run.\n");



	if (envOn > 0)

		printf("Environment will be updated every %d iteration\n", envOn);





	int	 BDANo;

	//Get DLL mode



	gDLLMode = parameters.read(infile, &BDANo);

	time_step.gettimestep(parameters.timestep);

	sites.stocking_x_value = parameters.stocking_x_value;

	sites.stocking_y_value = parameters.stocking_y_value;

	sites.stocking_z_value = parameters.stocking_z_value;
	//<Add By Qia on Jan 13 2009>

	sites.TimeStep = parameters.timestep;

	sites.TimeStep_BDA = parameters.timestep_BDA;

	sites.TimeStep_Fire = parameters.timestep_Fire;

	sites.TimeStep_Fuel = parameters.timestep_Fuel;

	sites.TimeStep_Harvest = parameters.timestep_Harvest;

	sites.TimeStep_Wind = parameters.timestep_Wind;

	sites.CellSize = parameters.cellSize;

	//</Add By Qia on Jan 13 2009>



	for (x = 0; x < 5; x++) freq[x] = 1;

	if ((gDLLMode & G_HARVEST) != 0)

		for (x = 0; x < 6; x++) freq[x] = 1;

	else

		for (x = 0; x < 5; x++) freq[x] = 1;



	if (gDLLMode & G_BDA)

		printf("BDA ");

	if (gDLLMode & G_WIND)

		printf("Wind ");

	if (gDLLMode & G_HARVEST)

		printf("Harvest ");

	if (gDLLMode & G_FUEL)

		printf("Fuel ");

	if (gDLLMode & G_FUELMANAGEMENT)

		printf("Fuel management ");

	if (gDLLMode & G_FIRE)

		printf("Fire ");

	if (gDLLMode != 0)

		printf("are(is) on\n");



	printf("------------------------------------------------------------\n\n");

	fflush(stdout);







	//read in parameters & Init PDP---------------------------------//

	PDP* pPDP;

	double wAdfGeoTransform[6];

	getInput(infile, freq, reMethods, ageMaps, &pPDP, BDANo, wAdfGeoTransform); // Need to change in this function Qia Oct 06 2008


	//END read in parameters & Init PDP---------------------------------//

	//Harvest Init 1-----------------------------------------------//

	if ((gDLLMode & G_HARVEST) != 0)

	{

		printf("Harvest Dll loaded in...\n");

		HarvestPass(&sites, &speciesAttrs);

		sites.Harvest70outputdim();

	}



	//WIND-Init-----------------------------------------------------//

	if ((gDLLMode & G_WIND) != 0)

	{

		printf("Enabling WindThrow\n");

		typedef WIND* (*GetWINDTYPE)(char*, char*, int);



		gLibWind = LoadLibrary("WindDll.dll");

		FARPROC  pnProc = GetProcAddress(gLibWind, "GetWind");

		if (!pnProc)

		{

			DWORD m = GetLastError();

			errorSys("Wind: Error in load in Wind DLL, check if there is a Wind dll.", STOP);

		}



		GetWINDTYPE GetWind = (GetWINDTYPE)pnProc;

		pWINDdll = GetWind(parameters.strWindInitName, parameters.outputDir, gDLLMode);

		pWINDdll->m_pPDP = pPDP;

		sites.Wind70outputdim();

		//	printf("Wind Dll loaded in...\n");

	}

	//WIND Inti END------------------------------------------------//





	if ((gDLLMode & G_WIND) != 0)

		pWINDdll->m_pPDP = pPDP;

	//END read in parameters & Init PDP---------------------------------//





	//BDA Init ---------------------------------------------------------//

	if ((gDLLMode & G_BDA) != 0)

	{

		typedef BDAS* (*GetBDASTYPE)(char* str, SITES* s, int i, char*, LANDUNITS* plu, SPECIESATTRS* ps, PDP*, int, int);

		printf("Enabling BDA\n");

		gLibBDA = LoadLibrary("BDADll.dll");

		if (gLibBDA == NULL)

		{

			printf("Error in Loading BDADLL\n");

			fflush(stdin);

		}

		/*

		printf("Loading BDA DLL ...\n");

		fflush(stdin);

		long errno;

		errno = GetLastError();

		printf("error code %ld\n", errno );

		fflush(stdin);

		*/



		FARPROC  pnProc = GetProcAddress(gLibBDA, "GetBDAS");



		/*

		errno = GetLastError();

		printf("error code %ld\n", errno );

		fflush(stdin);

		*/





		if (!pnProc)

		{

			DWORD m = GetLastError();

			errorSys("BDA: Error in load in BDA DLL, check if there is a BDA dll.", STOP);

		}



		GetBDASTYPE GetBDAS = (GetBDASTYPE)pnProc;

		pBDAS = GetBDAS(parameters.strBDAInitName, &sites, parameters.cellSize, parameters.outputDir, &landUnits, &speciesAttrs, pPDP, parameters.randSeed, gDLLMode);



		printf("BDA Dll loaded in...\n");

		sites.BDA70outputdim();

	}

	//BDA Init END---------------------------------------------------------//





	//Fuel init begin-------------------------------------------------  //

	if ((gDLLMode & G_FUEL) != 0)

	{

		HINSTANCE gLibFuel;

		printf("Enabling Fuel\n");

		typedef int(*GetFUELTYPE)(PDP*, char*, int, int, char*, SITES*, int);

		gLibFuel = LoadLibrary("FuelDll.dll");

		FARPROC pnProc = GetProcAddress(gLibFuel, "FuelInit");

		if (!pnProc)

		{

			DWORD m = GetLastError();

			errorSys("Fuel: Error in load in Fuel DLL, check if there is a Fuel dll.", STOP);

		}



		GetFUELTYPE FuelInit = (GetFUELTYPE)pnProc;



		gDLLMode = FuelInit(pPDP, parameters.strFuelInitName, speciesAttrs.number(), landUnits.number(), parameters.outputDir, &sites, gDLLMode);

		sites.Fuel70outputdim();

		//	printf("FUEL Dll loaded in...\n");

	}

	//Fuel init END ----------------------------------------------- ---//





	//Fire init begin-------------------------------------------------  //

	if ((gDLLMode & G_FIRE) != 0)

	{

		printf("Start fire (version 4.3) initialization \n");

		fflush(stdout);



		typedef CFIRE* (*GetFIRETYPE)(char*, int, SITES*, LANDUNITS*, SPECIESATTRS*, PDP*, int, char*, int);

		gLibFire = LoadLibrary("FireDll.dll");

		FARPROC pnProcfire = GetProcAddress(gLibFire, "GetFire");

		if (!pnProcfire)

		{

			DWORD m = GetLastError();

			errorSys("Fire: Error in load in Fire DLL, check if there is a Fire dll.", STOP);

		}



		GetFIRETYPE GetFire = (GetFIRETYPE)pnProcfire;



		pFire = GetFire(parameters.strFireInitName, gDLLMode, &sites, &landUnits,&speciesAttrs, pPDP, parameters.numberOfIterations,parameters.outputDir, parameters.randSeed);



		printf("Finish Fire initiliation \n");

		fflush(stdout);

		sites.Fire70outputdim();



	}

	//Fire init END-------------------------------------------------  //



	printf("Finish getting input\n");



	OutputScenario();

	initiateOutput_landis70Pro();

	snr = sites.numRows();

	snc = sites.numColumns();

	numSitesActive = sites.numActive();

	specAtNum = speciesAttrs.number();

	//optim.dim(specAtNum,snr,snc, &sites, &speciesAttrs); // need to change Qia Oct 06 2008

	numbOfIter = parameters.numberOfIterations;



	//<Add By Qia on July 6 2009>



	sites.GetSeedDispersalProbability(parameters.SeedRainFile, parameters.SeedRainFlag);

	sites.GetSpeciesGrowthRates(parameters.GrowthFlagFile, parameters.GrowthFlag);

	sites.GetSpeciesMortalityRates(parameters.MortalityFile, parameters.MortalityFlag);

	sites.GetVolumeRead(parameters.VolumeFile, parameters.VolumeFlag);

	initiateRDofSite_Landis70(snr, snc);



	//</Add By Qia on July 6 2009>





	if (reclYear )

	{

		reclassify(reclYear, ageMaps);

		putOutput(reclYear / sites.TimeStep, reclYear / sites.TimeStep, freq, wAdfGeoTransform);

		putOutput_Landis70Pro(reclYear / sites.TimeStep, reclYear / sites.TimeStep, freq, wAdfGeoTransform);

		putOutput_AgeDistStat(reclYear / sites.TimeStep);

		fclose(infile);

		ioTerm();

		return 0;

	}

	else {


		putOutput(0, 0, freq, wAdfGeoTransform);

		putOutput_Landis70Pro(0, 0, freq, wAdfGeoTransform);

		putOutput_AgeDistStat(0);

	}



	if ((gDLLMode & G_FUEL) != 0)

		FuelputFuelOutput(reclYear / sites.TimeStep_Fuel, parameters.outputDir, parameters.cellSize);







	if (envOn > numbOfIter)

		errorSys("Invalid year of interpretation for updating environment", STOP);



	 if (parameters.randSeed == 0)  //random

	 {

	 	srand((unsigned)time(&ltime));

	 	parameters.randSeed = ltime;

	 	fseed(parameters.randSeed);

	 }

	 else fseed(parameters.randSeed);

	//<Add By Qia on Feb 20 2009>

	char strfilenamefortime[100];

	sprintf(strfilenamefortime, "%s/%s", parameters.outputDir, "Running Time Stat.txt");

	fpforTimeBU = fopen(strfilenamefortime, "w");

	sprintf(strfilenamefortime, "%s/%s", parameters.outputDir, "SECLog.txt");

	fpLogFileSEC = fopen(strfilenamefortime, "w");   //</Add By Qia on Feb 20 2009>





	time(&ltimeTemp);

	printf("\nFinish the initilization at %s", ctime(&ltimeTemp));
	fflush(stdout);

	ltimeDiff = (long)ltimeTemp - ltime;

	printf("it took %ld seconds\n", ltimeDiff);


	fflush(stdout);



	//<Add By Qia on Jan 20 2009>

	landUnits.initiateVariableVector(parameters.numberOfIterations, parameters.timestep, speciesAttrs.number(), parameters.flagforSECFile, parameters.varianceSECFile);

	//</Add By Qia on Jan 20 2009>

	fprintf(fpforTimeBU, "Initilization took: %ld seconds\n", ltimeDiff);//Add By Qia

	//Simulation loops////////////////////////////////////////////////

	for (int i = 1; i <= numbOfIter*sites.TimeStep; i++)

	{

		if (i%sites.TimeStep == 0){

			if ((envOn > 0) && (i%envOn == 0) && i > 1 && 0)

			{

				//performing environment change

				//should also affect fireRegimeUnit GIS and Attr 

				//for fire and fuel module



				//update landtype GIS and landtype Attr if there are any

				//let fire module update fire regime unit GIS and Attr if there are any

				envUpdate(i);

				printf("landtype attribute and gis has been updated at iteration %d\n", i);
				fflush(stdout);

				//pSuccession->envChange(i,specAtNum, parameters.landUnitFile);

				if ((gDLLMode & G_FIRE) != 0)

				{

					//update fire regime unit attr and fire regime GIS

					pFire->updateFRU(i);

					printf("fire regime unit attribute and gis has been updated at iteration %d\n", i);
					fflush(stdout);



				}

			}
			if ((gDLLMode & G_FIRE) != 0 && pFire->flag_regime_update){

				pFire->updateFire_Regime_Map(i);

				//printf("fire regime unit attribute and gis has been updated at iteration %d\n",i);
			}
			if (parameters.flagforSECFile == 3)

			{
				char SECfileNametemp[100];

				char SECfileMapGIS[100];

				if (i / sites.TimeStep == 1){

					SEC_landtypefiles.clear();

					SEC_gisfiles.clear();
					if ((parameters.FpSECfile = LDfopen(parameters.varianceSECFile, 1)) == NULL){

						errorSys("Can not open SEC variance file", STOP);
					}
					int num_of_files;

					fscanf(parameters.FpSECfile, "%d", &num_of_files);

					//while(!feof(parameters.FpSECfile))

					for (int ii_count_num = 0; ii_count_num < num_of_files; ii_count_num++){

						if (fscanc(parameters.FpSECfile, "%s %s", SECfileMapGIS, SECfileNametemp) != 1)

							errorSys("Error reading in Landunit from SEC variance file.", STOP);

						SEC_landtypefiles.push_back(string(SECfileNametemp));

						SEC_gisfiles.push_back(string(SECfileMapGIS));
					}

					LDfclose(parameters.FpSECfile);

					int index = i / sites.TimeStep - 1;

					if (index < SEC_landtypefiles.size()){

						sprintf(SECfileNametemp, "%s", SEC_landtypefiles.at(index).c_str());

						sprintf(SECfileMapGIS, "%s", SEC_gisfiles.at(index).c_str());

						FILE *luFile;

						strcpy(parameters.landUnitFile, SECfileNametemp);

						if ((luFile = LDfopen(parameters.landUnitFile, 1)) == NULL){

							printf("Landtype attribute file %s not found.\n", parameters.landUnitFile);
							fflush(stdout);

							errorSys(parameters.landUnitFile, STOP);
						}
						else{
							//update landtype attribute

							landUnits.read(luFile);

							LDfclose(luFile);
						}

						printf("\nEnvironment parameter Updated.\n");
						fflush(stdout);

						FILE *GISmap;

						//strcpy(parameters.landUnitMapFile, SECfileMapGIS);

						strcpy(parameters.landImgMapFile, SECfileMapGIS);

						//if ((GISmap = LDfopen(parameters.landUnitMapFile, 2)) == NULL){

						//	printf("Land Map file %s not found.\n", parameters.landUnitMapFile);
						//	fflush(stdout);

						//	errorSys(parameters.landUnitMapFile, STOP);
						//}
						//else{
						//	//update landtype attribute

						//	updateLandtypeMap8(GISmap);

						//	LDfclose(GISmap);
						//}

						if ((simgFile = (GDALDataset *)GDALOpen(parameters.landImgMapFile, GA_ReadOnly)) == NULL) //* landtype.img

						{

							printf("Land Map Img file %s not found.\n", parameters.landImgMapFile);
							fflush(stdout);

							errorSys(parameters.landImgMapFile, STOP);
						}
						else{
							if (simgFile->GetGeoTransform(adfGeoTransform) == CE_None){ //*

								for (int i = 0; i < 6; i++){//*

									wAdfGeoTransform[i] = adfGeoTransform[i];//*
								}//*

							}//*

							updateLandtypeImg8(simgFile);

							GDALClose((GDALDatasetH)simgFile); //*

						}

						
						printf("\nEnvironment map Updated.\n");
						fflush(stdout);


						LANDUNIT*	SECLog_use = landUnits.first();

						int ii_count = 0;

						fprintf(fpLogFileSEC, "Year: %d\n", i);

						for (SECLog_use = landUnits.first(); ii_count < landUnits.number(); ii_count++){

							fprintf(fpLogFileSEC, "Landtype%d:\n", ii_count);

							for (int jj_count = 1; jj_count <= speciesAttrs.number(); jj_count++){

								fprintf(fpLogFileSEC, "spec%d: %f, ", jj_count, SECLog_use->probRepro(jj_count));
							}

							SECLog_use = landUnits.next();

							fprintf(fpLogFileSEC, "\n");
						}
					}
				}

				if (i / sites.TimeStep > 1){

					int index = i / sites.TimeStep - 1;

					if (index < SEC_landtypefiles.size()){

						sprintf(SECfileNametemp, "%s", SEC_landtypefiles.at(index).c_str());

						sprintf(SECfileMapGIS, "%s", SEC_gisfiles.at(index).c_str());

						FILE *luFile;

						strcpy(parameters.landUnitFile, SECfileNametemp);

						if ((luFile = LDfopen(parameters.landUnitFile, 1)) == NULL){

							printf("Landtype attribute file %s not found.\n", parameters.landUnitFile);
							fflush(stdout);

							errorSys(parameters.landUnitFile, STOP);

						}
						else{

							//update landtype attribute

							landUnits.read(luFile);

							LDfclose(luFile);
						}

						printf("\nEnvironment parameter Updated.\n");
						fflush(stdout);

						FILE *GISmap;

						//strcpy(parameters.landUnitMapFile, SECfileMapGIS);

						//if ((GISmap = LDfopen(parameters.landUnitMapFile, 2)) == NULL){

						//	printf("Land Map file %s not found.\n", parameters.landUnitMapFile);
						//	fflush(stdout);
						//	errorSys(parameters.landUnitMapFile, STOP);
						//}
						//else{

						//	//update landtype attribute

						//	updateLandtypeMap8(GISmap);

						//	LDfclose(GISmap);
						//}
						strcpy(parameters.landImgMapFile, SECfileMapGIS);

						if ((ltimgFile = (GDALDataset *)GDALOpen(parameters.landImgMapFile, GA_ReadOnly)) == NULL) //* landtype.img

						{

							printf("Land Map Img file %s not found.\n", parameters.landImgMapFile);
							fflush(stdout);

							errorSys(parameters.landImgMapFile, STOP);
						}
						else{
							if (ltimgFile->GetGeoTransform(adfGeoTransform) == CE_None){ //*

								for (int i = 0; i < 6; i++){//*

									wAdfGeoTransform[i] = adfGeoTransform[i];//*
								}//*

							}//*

							updateLandtypeImg8(ltimgFile);

							GDALClose((GDALDatasetH)ltimgFile); //*

						}

						printf("\nEnvironment map Updated.\n");
						fflush(stdout);


						LANDUNIT*	SECLog_use = landUnits.first();

						int ii_count = 0;

						fprintf(fpLogFileSEC, "Year: %d\n", i);

						for (SECLog_use = landUnits.first(); ii_count < landUnits.number(); ii_count++){

							fprintf(fpLogFileSEC, "Landtype%d:\n", ii_count);

							for (int jj_count = 1; jj_count <= speciesAttrs.number(); jj_count++){

								fprintf(fpLogFileSEC, "spec%d: %f, ", jj_count, SECLog_use->probRepro(jj_count));
							}

							SECLog_use = landUnits.next();

							fprintf(fpLogFileSEC, "\n");
						}
					}

				}
			}

		}

		if ((gDLLMode & G_HARVEST) != 0 && i%sites.TimeStep_Harvest == 0)

		{

			//   currentDecade = i;  modified by Vera Nov. 18, 2003

			HarvestPassCurrentDecade(i);

			//if (parameters.harvest) {

			for (int r = 1; r <= snr; r++)

			{

				for (int c = 1; c <= snc; c++)

					setUpdateFlags(r, c);

			}

			//}

		}



		//if (pSuccession) 

		//	delete pSuccession;

		//pSuccession = new SUCCESSION(&sites, &landUnits, &optim, parameters.cellSize);



		sprintf(str, "\nProcessing Year %d", i);//J.Yang hard coding from i*sites.TimeStep

		printMessage(str);

		//End Harvest Init 2-----------------------------------------------//



		singularLandisIteration(i, run_extraSeed, (numSitesActive / 1000), snr, snc, specAtNum, wAdfGeoTransform, pPDP);

	
		if ((i%sites.TimeStep  == 0) || (i == sites.TimeStep*parameters.numberOfIterations)){

			if ((i % (sites.TimeStep * freq[0]) ==0) &&(i / sites.TimeStep  < parameters.numberOfIterations)){

				putOutput_Landis70Pro(0, i / sites.TimeStep, freq, wAdfGeoTransform);
			}
			
			if (i == sites.TimeStep*parameters.numberOfIterations){

				putOutput_Landis70Pro(0, parameters.numberOfIterations, frequency, wAdfGeoTransform);
			}

			if ((i % (sites.TimeStep * freq[4]) == 0) && (i / sites.TimeStep  < parameters.numberOfIterations)){

				putOutput(0, i / sites.TimeStep, freq, wAdfGeoTransform);
			}
			if (i == sites.TimeStep*parameters.numberOfIterations){
				
				putOutput(0, parameters.numberOfIterations, frequency, wAdfGeoTransform);
			}


			putOutput_AgeDistStat(i / sites.TimeStep);



		}



		if ((gDLLMode & G_FUEL) != 0 && i%sites.TimeStep_Fuel == 0)

			FuelputFuelOutput(i / sites.TimeStep_Fuel, parameters.outputDir, parameters.cellSize);



	}



	//Simulation loops end/////////////////////////////////////////////////





	AgeDistOutputFromBufferToFile();





	//Close program.

	if ((gDLLMode & G_HARVEST) != 0)

	{

		CleanHarvest();

	}



	if (pSuccession)

		delete pSuccession;

	LDfclose(infile);

	ioTerm();



	fclose(fpforTimeBU);

	fclose(fpLogFileSEC);

	printf("End of simulation.\n");

	return 0;

}



//<Add By Qia on June 29 2009>

/////////////////////////////////////////////////////////////////////////////

//                      Landis 7.0 Pro New Succession Routine                  //

/////////////////////////////////////////////////////////////////////////////

void initiateRDofSite_Landis70(int snr, int snc)

//initiating Landis70 RD values

{

	int i, j;

	for (i = 1; i <= snr; i++)

	{

		for (j = 1; j <= snc; j++)

		{

			sites.GetRDofSite(i, j);

		}

	}

}

void Succession_Landis70(int snr, int snc, PDP* ppdp)

// According to shade-rule and RD-rule determine species succession on sites, main function 

{
	int i, j, k;

	LANDUNIT *l;

	int shade;

	SPECIE *s;

	SPECIESATTR *sa;

	int speciesNum;

	long ltimeDiff;

	time_t ltime, ltimeTemp;

	sites.GetMatureTree();





	//increase ages

	for (i = 1; i <= snr; i++)

	{

		for (j = 1; j <= snc; j++)

		{



			ppdp->sTSLMortality[i][j] += (short)sites.TimeStep;



			if ((gDLLMode & G_WIND) != 0)

				ppdp->sTSLWind[i][j] += (short)sites.TimeStep;



			if ((gDLLMode & G_HARVEST) != 0)

			{

				ppdp->sTSLHarvest[i][j] += (short)sites.TimeStep;

			}

			//Define Land unit.

			l = sites.locateLanduPt(i, j);

			//original landis4.0: sites(i,j)->landUnit

			//changed By Qia on Oct 13 2008

			if (l != NULL && l->active())

			{
				for (k = 1; k <= speciesAttrs.number(); k++)

				{


					
					sites(i, j)->SpecieIndex(k)->GrowTree(k);

				}



			}



		}

	}

	//seed dispersal

	
	initiateRDofSite_Landis70(snr, snc);

	printf("Seed Dispersal:\n");

	for (i = 1; i <= snr; i++)

	{

		printf("\r%3d%%", 100 * i / snr);

		for (j = 1; j <= snc; j++)

		{

			l = sites.locateLanduPt(i, j);

			KillTrees(i, j); //</Add By Yang on Nov 04 2014>

			if (l != NULL && l->active()){

				//if(sites(i,j)->RD<0.55){

				if (sites(i, j)->RD < l->MaxRDArray[0]){

					sites.SiteDynamics(0, i, j);

				}

				//else if(sites(i,j)->RD>=0.55&&sites(i,j)->RD<0.85){

				else if (sites(i, j)->RD >= l->MaxRDArray[0] && sites(i, j)->RD<l->MaxRDArray[1]){

					sites.SiteDynamics(1, i, j);

				}

				//else if(sites(i,j)->RD>=0.85&&sites(i,j)->RD<=1.0){

				else if (sites(i, j)->RD >= l->MaxRDArray[1] && sites(i, j)->RD <= l->MaxRDArray[2]){

					sites.SiteDynamics(2, i, j);

				}

				//else if(sites(i,j)->RD>1.0&&sites(i,j)->RD<=l->MaxRD){

				else if (sites(i, j)->RD>l->MaxRDArray[2] && sites(i, j)->RD <= l->MaxRDArray[3]){

					sites.SiteDynamics(3, i, j);

				}

				else if (sites(i, j)->RD > l->MaxRDArray[3]){

					sites.SiteDynamics(4, i, j);

				}

				else

				{

				}

			}

		}

	}

}

//</Add By Yang on Nov 04 2014>

void KillTrees(int snr, int snc)

//start killing trees gradually at the 80 % longevity until they reach their longevity

// modified version of function : void SUCCESSION::kill(SPECIE *s, SPECIESATTR *sa) 

{

	float *e0; e0 = new float; *e0 = (float) 0.00000001;             //for 32 bit system

	int tmpTreeNum, tmpMortality, numYears, longev;

	unsigned int DeadTreeInt;

	float chanceDeath, chanceMod;


	for (int k = 1; k <= speciesAttrs.number(); k++) //sites.specNum

	{
		longev = speciesAttrs(k)->longevity;

		numYears = (int)(longev / 5);

		chanceMod = (float) 0.8 / ((float)numYears + *e0);

		chanceDeath = (float) 0.2;

		for (int m = (longev - numYears) / sites.TimeStep; m <= longev / sites.TimeStep; m++)

		{

			tmpTreeNum = sites(snr, snc)->SpecieIndex(k)->getTreeNum(m, k);

			tmpMortality = 0;

			if (tmpTreeNum > 0)
			{
				for (int x = 1; x <= tmpTreeNum; x++)

				{
					if (frand() < (chanceDeath / 10 * sites.TimeStep))

						tmpMortality += 1;
				}

				sites(snr, snc)->SpecieIndex(k)->setTreeNum(m, k, max(0, tmpTreeNum - tmpMortality));
			}

			chanceDeath += chanceMod;

		}

	}

	delete e0;

}

//</Add By Qia on June 29 2009>
/////////////////////////////////////////////////////////////////////////////

//                      SINGULAR LANDIS ITERATION ROUTINE                  //

/////////////////////////////////////////////////////////////////////////////



void singularLandisIteration(int itr, int run_extraSeed, int numSitesActive, int snr, int snc, int specAtNum, double wAdfGeoTransform[], PDP* ppdp)

//This processes a singular Landis iteration.  It loops through each site

//followed by each species.  For every iteration of the loop grow and kill

//are called.  Then seed availability is checked.  If seed is available

//and shade conditions are correct birth is called.



{

	char str[100];

	int i, j;

	LANDUNIT *l;

	int shade;

	SPECIE *s;

	SPECIESATTR *sa;

	int speciesNum;



	time_t ltime, ltimeTemp;

	long ltimeDiff;

	fprintf(fpforTimeBU, "\nYear: %d:\n", itr);// Add By Qia

	//int debut = sites.GetSeedRain(1, 74);

	fflush(stdout);

	//printf("number of sites: %d\n",sites.SortedIndex.size());

	//Wind process

	if ((gDLLMode & G_WIND) != 0 && itr%sites.TimeStep_Wind == 0)

	{

		printMessage("\nProcessing windthrow.\n");

		time(&ltime);//Add By Qia

		//    pWINDdll->activate(itr, freq, &sites, &speciesAttrs, parameters.cellSize, parameters.randSeed, parameters.wind, parameters.numberOfIterations, gDLLMode);

		typedef void(*GetWindACTIVETYPE)(WIND*, int, int freq[], SITES*, SPECIESATTRS*, int, int, int, int);



		FARPROC  pnProc1 = GetProcAddress(gLibWind, "GetWindACTIVATE");

		if (!pnProc1)

		{

			DWORD m = GetLastError();

			errorSys("BDA: Error in access BDAActive.", STOP);

		}



		GetWindACTIVETYPE GetWindACTIVATE = (GetWindACTIVETYPE)pnProc1;

		GetWindACTIVATE(pWINDdll, itr / sites.TimeStep_Wind, freq, &sites, &speciesAttrs, parameters.cellSize, parameters.randSeed, parameters.numberOfIterations, gDLLMode);

		time(&ltimeTemp);//Add By Qia

		ltimeDiff = (long)ltimeTemp - ltime;

		fprintf(fpforTimeBU, "Processing windthrow: %ld seconds\n", ltimeDiff); //Add B
		fseed(parameters.randSeed+itr*2);//Commented By Qia on Dec 18 2008y Qia


	}



	time_t time1, time2, time3, time4, time5;

	// fire process

	if ((gDLLMode & G_FIRE) != 0 && itr%sites.TimeStep_Fire == 0)

	{

		time(&ltime);

		printf("Start simulating fire disturbance ... at %s", ctime(&ltime));

		fseed(parameters.randSeed + itr / sites.TimeStep * 1);

		time(&time1);
		//cout << "time1 is " << ctime(&time1) << endl;

		typedef CFIRE* (*GetFireACTIVATETYPE)(CFIRE* pf, int itr, int freq[], double wAdfGeoTransform[]);

		gLibFire = LoadLibrary("FireDll.dll");

		time(&time2);
		//cout << "time2 is " << ctime(&time2) << endl;

		FARPROC pnProc = GetProcAddress(gLibFire, "GetFireACTIVATE");

		if (!pnProc)

		{

			DWORD m = GetLastError();

			errorSys("Fire: Error in load in Fire DLL, check if there is a Fire dll.", STOP);

		}

		time(&time3);
		//cout << "time3 is " << ctime(&time3) << endl;

		GetFireACTIVATETYPE GetFireACTIVATE = (GetFireACTIVATETYPE)pnProc;

		time(&time4);
		//cout << "time4 is " << ctime(&time4) << endl;

		GetFireACTIVATE(pFire, itr / sites.TimeStep_Fire, freq, wAdfGeoTransform);



		time(&ltimeTemp);

		ltimeDiff = (long)ltimeTemp - ltime;

		printf("Finish simulating fire disturbance at %sit took %ld seconds\n", ctime(&ltimeTemp), ltimeDiff);

		fprintf(fpforTimeBU, "Processing fire: %ld seconds\n", ltimeDiff);

		fflush(stdout);



	}



	//BDA process

	if ((gDLLMode & G_BDA) != 0 && itr%sites.TimeStep_BDA == 0)

	{

		time_t lBDAtime, lBDAtimeTemp;

		long lBDAtimeDiff;

		time(&lBDAtime);

		printf("Start BDA at %s", ctime(&lBDAtime));

		//<Add By Qia on Dec 18 2008>

		//fseed(parameters.randSeed + itr / sites.TimeStep * 2);

		//</Add By Qia on Dec 18 2008>



		typedef void(*GetBDAACTIVETYPE)(BDAS* pBDAS, int itr);



		FARPROC  pnProc1 = GetProcAddress(gLibBDA, "GetBDAACTIVE");

		if (!pnProc1)

		{

			DWORD m = GetLastError();

			errorSys("BDA: Error in access BDAActive.", STOP);

		}



		GetBDAACTIVETYPE GetBDAACTIVE = (GetBDAACTIVETYPE)pnProc1;



		GetBDAACTIVE(pBDAS, itr / sites.TimeStep_BDA);

		//	pBDAS->Active();

		//fseed(parameters.randSeed+itr*4);//Commented By Qia on Dec 18 2008



		time(&lBDAtimeTemp);

		printf("End BDA at %s", ctime(&lBDAtimeTemp));

		lBDAtimeDiff = (long)(lBDAtimeTemp - lBDAtime);

		sprintf(str, "The whole BDA procedure took %ld seconds\n", lBDAtimeDiff);

		fprintf(fpforTimeBU, "Processing BDA: %ld seconds\n", lBDAtimeDiff);

		printMessage(str);

	}







	//Fuel process--------------------------------------//

	if ((gDLLMode & G_FUEL) != 0 && itr%sites.TimeStep_Fuel == 0)

	{

		printf("Processing Fuel\n");

		time(&ltime);

		//<Add By Qia on Dec 18 2008>

		//fseed(parameters.randSeed + itr / sites.TimeStep * 3);

		//</Add By Qia on Dec 18 2008>

		FuelProcessEvent();

		//fseed(parameters.randSeed+itr*5);//Commented By Qia on Dec 18 2008

		time(&ltimeTemp);

		ltimeDiff = (long)ltimeTemp - ltime;

		fprintf(fpforTimeBU, "Processing fuel: %ld seconds\n", ltimeDiff);



	}





	//Harvest process

	if ((gDLLMode & G_HARVEST) != 0 && itr%sites.TimeStep_Harvest == 0)

	{

		printMessage("Processing harvest events.\n");

		time(&ltime);

		//   harvestEvents.processEvents();  modified by Vera

		//<Add By Qia on Dec 18 2008>

		//fseed(parameters.randSeed + itr / sites.TimeStep * 4);

		//</Add By Qia on Dec 18 2008>


		HarvestprocessEvents(itr / sites.TimeStep);

		//fseed(parameters.randSeed+itr*6);//Commented By Qia on Dec 18 2008

		putHarvestOutput(itr / sites.TimeStep_Harvest, wAdfGeoTransform);

		time(&ltimeTemp);

		ltimeDiff = (long)ltimeTemp - ltime;

		fprintf(fpforTimeBU, "Processing harvest: %ld seconds\n", ltimeDiff);

	}



	//Fuel management process--------------------------------------//



	if ((gDLLMode & G_FUELMANAGEMENT) != 0 && itr%sites.TimeStep_Fuel == 0)

	{

		printf("Fuel: Processing fuel management.\n");

		// process fuel management events

		time(&ltime);

		//<Add By Qia on Dec 18 2008>

		//fseed(parameters.randSeed + itr / sites.TimeStep * 5);

		//</Add By Qia on Dec 18 2008>

		FuelManageProcessEvents(itr / sites.TimeStep_Fuel);

		//fseed(parameters.randSeed+itr*7);//Commented By Qia on Dec 18 2008

		time(&ltimeTemp);

		ltimeDiff = (long)ltimeTemp - ltime;

		fprintf(fpforTimeBU, "Processing fuel management: %ld seconds\n", ltimeDiff);

	}





	if (itr%sites.TimeStep == 0){

		time(&ltime);

		printf("Start succession ... at %s", ctime(&ltime));

		fflush(stdout);

		//<Add By Qia on Dec 18 2008>

		fseed(parameters.randSeed + itr / sites.TimeStep * 6);

		//</Add By Qia on Dec 18 2008>

		//<Add By Qia on Jan 20 2009>

		landUnits.ReprodUpdate(itr / sites.TimeStep);

		//</Add By Qia on Jan 20 2009>



		Succession_Landis70(snr, snc, ppdp);//Add By Qia on July 6 2009



		time(&ltimeTemp);

		ltimeDiff = (long)ltimeTemp - ltime;

		printf("Finish succession at %sit took %ld seconds\n", ctime(&ltimeTemp), ltimeDiff);

		fprintf(fpforTimeBU, "Processing succession: %ld seconds\n", ltimeDiff);

	}

	fseed(parameters.randSeed + itr * 0);//Changed By Qia on Dec 18 2008; Original: itr*6

}



