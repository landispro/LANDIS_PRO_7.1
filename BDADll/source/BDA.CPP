/*
Name:			BDA.cpp 
Description:	Biological Disturbance Agent Module class definition
Input:			BDA.dat
Output:			updated species cohorts, LiveBiomass and DeadBiomass
Date:			Oct. 15, 2002
Notes:			also made small modification in defines.h and Specie.h
Last Modifier:	Oct. 16, Oct. 17, Nov. 10, Nov. 17, Mar 2016
*/


#include <stdlib.h>		
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <random>


#include "io.h"
#include "system1.h"

#include "BDA.h"
#include "PosList.h"
#include "error.h"
//#include "MAP8.h"
#include "landus.h"
#include "landu.h" 
//#include "stdafx.h"


#include <iostream>
#include <cstdio>
#include <stdio.h>
#include "gdal_priv.h"
#include "cpl_conv.h" // for CPLMalloc()
#include "cpl_string.h"
#include "ogr_spatialref.h"
#include "gdalwarper.h"
//#include "landis.h"
#include "float.h" //add By Qia on May 4th 2009
static int red2[maxLeg]={0,255,255,0,0,0,0,0,150,0,150,255,80,150,255};
static int green2[maxLeg]={0,255,0,255,0,100,150,255,0,150,150,255,80,150,255};
static int blue2[maxLeg]={0,255,0,0,0,255,0,0,150,150,0,0,80,150,255};
extern int gDLLMode;
float mn, mx;
int ssum = 0;
float spA[5000][5000],spB[5000][5000],sp[5000][5000];
float *pafScanline2, *pafScanline2out;



Delta DilationElemA[] = 
{
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0}
};

Delta DilationElemB[] = 
{
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1}
};

Delta DilationElemC[] = 
{
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
    {-2, 0},
    {2, 0},
    {0, -2},
    {0, 2},
};

Delta DilationElemD[] = 
{
    {-2, -2},
    {-2, -1},
    {-2, 0},
    {-2, 1},
    {-2, 2},
    {-1, -2},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {-1, 2},
    {0, -2},
    {0, -1},
    {0, 1},
    {0, 2},
    {1, -2},
    {1, -1},
    {1, 0},
    {1, 1},
    {1, 2},
    {2, -2},
    {2, -1},
    {2, 0},
    {2, 1},
    {2, 2}
};

struct Element
{
    int		size;
    Delta*	item;
} StruElem[4] = 
{
    {4, DilationElemA},
    {8, DilationElemB},
    {12, DilationElemC},
    {24, DilationElemD}
};

//##ModelId=3F01D0EB0269
BDA::BDA()
{
	m_iCol = 0;				 
	m_iRow = 0;
	m_pBDA = NULL;
	m_pEpiList = NULL;	//set newEpicenter to be invalid
}

/*************************************************************
name:			BDA
Description:	not used in this version
**************************************************************/

//##ModelId=3F01D0EB026A
BDA::BDA(FILE*	pfile)
{

	read(pfile);
	m_bEpidemicYear = 0;
	m_pEpiList = NULL;	//set newEpicenter to be invalid

}

/*************************************************************
name:			BDA
Description:	main constructor
**************************************************************/
//##ModelId=3F01D0EB0278
BDA::BDA(char*	strfn, SITES* outsites, int outcellsize, LANDUNITS* outlus, SPECIESATTRS*  outsa, PDP* ppdp, int ifBDArepeat, int gDllMd, int BDANo)
{
	FILE* fBDA;
		
	m_pPDP = ppdp;
	m_iDllMode = gDllMd;
	m_iBDANo = BDANo;
	pBDAsites = outsites;
	cellSize = outcellsize;
	pBDAlandUnits = outlus;
	pBDAspeciesAttrs = outsa;


	if (m_ifBDArepeat == 0)  //0: random and not repeat; 1: repeat
		m_pStochastic = new StochasticLib(time(0));
	else
		m_pStochastic = new StochasticLib(1000);


	m_ifBDArepeat = ifBDArepeat;

	if ((fBDA = LDfopen(strfn, 1)) == NULL)
		errorSys("BDA: BDA parameter file not found.",STOP);

	read(fBDA);
	m_bEpidemicYear = 0;

	m_iRow = pBDAsites->numRows();				 
	m_iCol = pBDAsites->numColumns();
	m_pBDA = new BDASites(m_iRow, m_iCol);

//initilize first TimetoNextEpidemic
	if (m_ifBDArepeat == 0)  //0: random and not repeat; 1: repeat   modifiied by Wei Li, 2004
		srand( (unsigned)time( NULL ) );
	
	if (m_enumRandomFuncs == RFuniform)
		m_iTimetoNextEpidemic = m_fRandomParam1 - m_iTimeSinceLastEpidemic + frandrand() % (int)(m_fRandomParam2 - m_fRandomParam1);
	else if (m_enumRandomFuncs == RFnormal)
		m_iTimetoNextEpidemic = (int)m_pStochastic->Normal(m_fRandomParam1, m_fRandomParam2) - m_iTimeSinceLastEpidemic;

	m_pEpiList = NULL;	//set newEpicenter to be invalid
	
	//make slidingWindow template
	if (m_bNeighborFlag == true) 
		m_pfSlidingWindow = WindowFloatTemplate();
	else 
		m_pfSlidingWindow = NULL;

	SitesClean(true);
}

	
//##ModelId=3F01D0EB0288
BDA::~BDA()
{
	
	if (m_pEpiList != NULL)
		free (m_pEpiList);

	if (m_pDilation != NULL)
		DilationFree(m_pDilation);

	//delete [] m_pBDA;//commented By Qia on Dec 03 2008
	m_pBDA->~BDASites(); //Add BY Qia on Dec 03 2008

	delete m_pStochastic;

	free(MinorHostAge);
	free(SecondaryHostAge);
	free(PrimaryHostAge);
	free(ResistantHostAge);
	free(Toleranthostage);
	free(VulnerableHostAge);

	WindowFree(m_pfSlidingWindow, m_iSlidingWindowSize);
}

/***********************************************************
Function:	 SitesClean
Description: Initialize BDASites map
************************************************************/
//##ModelId=3F01D0EC00A5
void BDA::SitesClean(bool bwithDisturbSeverity)
{
	int	i, j;
	//<Changed By Qia on Dec 03 2008>
	for (i = 1; i <= 1; i++)
		for (j = 1; j <= 1; j++)	
		{
			(*m_pBDA)(i, j)->enumOutbreakZone = Nozone;
			(*m_pBDA)(i, j)->fNeighborResDom =0.0;
			(*m_pBDA)(i, j)->fSiteResDomMod = 0.0;
			(*m_pBDA)(i, j)->fSiteResourceDom = 0.0;
			(*m_pBDA)(i, j)->fSV = 0.0;
			(*m_pBDA)(i, j)->iLastBDADisturb = -10000;
			(*m_pBDA)(i, j)->cDispersal = 0;
			if (bwithDisturbSeverity)
				(*m_pBDA)(i, j)->iDisturbSeverity = 0;
			(*m_pBDA)(i, j)->bDeadArea = false;			//true dead area; false live area		
		}
	//</Changed By Qia on Dec 03 2008>
	
}

/***********************************************************
Function: BDA::read
Description: read int BDA parameters
************************************************************/
//##ModelId=3F01D0EB0289
void BDA::read(FILE* pfile) // read insect1.dat parameter
{
	int		i, iTemp;
	float	fTemp;
	int		numLTMod = 0;	//counter of Land Type modifier
	char	strTemp[BDA_MAX_STRTEMP];

	GDALDataset  *swiFile, *iniFile; //* added by Nancy on July 23th 2016

	if (fscanc(pfile, "%s", m_strName) != 1)
		errorSys("Error in reading BDA name.", STOP);

	if (fscanc(pfile, "%s", m_strICMap) != 1)
		errorSys("Error in reading BDA initial conditions map.", STOP);

	if (fscanc(pfile, "%f", &m_fSVCalibrator) != 1)
		errorSys("Error in reading BDA SVCalibrator.", STOP);

	if (fscanc(pfile, "%s", strTemp) != 1)
		errorSys("Error in reading SRD Mode.", STOP);

	if ((!strcmp(strTemp, "max")) || (!strcmp(strTemp, "Max")) || (!strcmp(strTemp, "MAX"))) // Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumSRDMode = SRDmax;
	else if ((!strcmp(strTemp, "mean")) || (!strcmp(strTemp, "Mean")) || (!strcmp(strTemp, "MEAN")))// Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumSRDMode = SRDmean;
	else
	errorSys("Error in reading BDA parameter,  name dosn't match.Please check spell or use all lowercase", STOP);

	if (fscanc(pfile, "%d", &m_iTimeStep) != 1)
		errorSys("Error in reading BDA TimeStep.", STOP);
	// added on April 5th 2016 by Nancy
	if (fscanc(pfile, "%d", &n_numInterval) != 1)
		errorSys("Error in reading BDA TimeStep.", STOP);
	// added on April 5th 2016 by Nancy, 
	for (int i = 0; i < n_numInterval; i++){
		
		if (fscanc(pfile, "%d", &startYear[i]) != 1)
			errorSys("Error in reading BDA TimeStep.", STOP);
		if (fscanc(pfile, "%d", &endYear[i]) != 1)
			errorSys("Error in reading BDA TimeStep.", STOP);
		//cout << "startYear: " << startYear[i] << " endYear: " << endYear[i] << endl;
		if (i >=1 && (startYear[i]< endYear[i-1]))
			errorSys("Start Year should be larger than last end year.", STOP);
	}
	//pBDAsites->TimeStep_BDA=m_iTimeStep;
/*
	//read land type modifiers
	m_iLTModNum = pBDAlandUnits->number();
	fscanc(pfile, "%d", &iTemp);;
	if (m_iLTModNum != iTemp)
		errorSys("BDA: Error 01, land type modifiers doen't match number of Land Unit", STOP);
	LANDUNIT*	pLU = pBDAlandUnits->first();
	for (i = 0; i < m_iLTModNum; i++)
	{

		fscanc(pfile, "%s", m_strLTModName[i]);
		if (!strcmp(pLU->name, m_strLTModName[i]))	//two strings are identical
		{
			fscanc(pfile, "%f", &m_fLTModVal[i]);
			pLU = pBDAlandUnits->next();
		}
		else
			errorSys("BDA: Error 02 in reading land type modifiers. Inconsistance with Landtype.dat", STOP);

	}
*/
	if (fscanc(pfile, "%s", swiImgMapFile) != 1) //* added by Nancy on July 23th 2016
		errorSys("Error in reading PDSI.img name.", STOP); //* added by Nancy on July 23th 2016

	//if (fscanc(pfile, "%s", iniImgMapFile) != 1) //* added by Nancy on July 23th 2016
	//	errorSys("Error in reading ini.img name.", STOP); //* added by Nancy on July 23th 2016

	if (fscanc(pfile, "%s", ecoImgMapFile) != 1) //* added by Cheney on July 23th 2016
		errorSys("Error in reading ecoregion.img name.", STOP); //* added by Cheney on July 23th 2016

	if (fscanc(pfile, "%f", &p1) != 1) //* added by Nancy on July 23th 2016
		errorSys("Error in reading P1.", STOP); //* added by Nancy on July 23th 2016

	if (fscanc(pfile, "%f", &p2) != 1) //* added by Nancy on July 23th 2016
		errorSys("Error in reading P2.", STOP); //* added by Nancy on July 23th 2016

	if (fscanc(pfile, "%f", &p3) != 1) //* added by Nancy on July 23th 2016
		errorSys("Error in reading P3.", STOP); //* added by Nancy on July 23th 2016
	//cout << p1 << " " << p2 << " " << p3 << endl;
	m_iNodataIndex = 0;
	//read land type modifiers
	m_iLTModNum = pBDAlandUnits->number();
	fscanc(pfile, "%d", &iTemp);
	if (m_iLTModNum != iTemp){
		printf("%d, %d\n",m_iLTModNum,iTemp);
		errorSys("BDA: Error 01, land type modifiers doen't match number of Land Unit %d", STOP);
		}
	LANDUNIT*	pLU = pBDAlandUnits->first();
	for (i = 0; i < m_iLTModNum; i++)
	{
		fscanc(pfile, "%s", m_strLTModName[i]);
		if (!strcmp(pLU->name, m_strLTModName[i]))	//two strings are identical
		{
			fscanc(pfile, "%f", &m_fLTModVal[i]);
			if (m_fLTModVal[i] < -2)		//add at Nov.10, 2003 by Vera to process no data landtype
			{
				strcpy(m_strLTModNameNodata[m_iNodataIndex], m_strLTModName[i]);
				m_iNodataIndex++;
			}	
			pLU = pBDAlandUnits->next();
		}
		else
			errorSys("BDA: Error 02 in reading land type modifiers. Inconsistance with Landtype.dat", STOP);

	}

	//read in disturbance modifiers
	fscanc(pfile, "%d", &m_iDMNo);
	m_iDisturbType = 0;

	for (i = 0; i < m_iDMNo; i ++)
	{
		//disturbance type list fire, wind, timber, harvest
		fscanc(pfile, "%s", strTemp);
		if ((!strcmp(strTemp, "fire")) || !(strcmp(strTemp, "Fire")) || !(strcmp(strTemp, "FIRE")))
		{
			m_iDisturbType |= BDA_DISTTYPE_FIRE;
			fscanc(pfile, "%f", &m_fDisturbMod[BDA_FIRE]); //disturbance modifiers list
			fscanc(pfile, "%d", &m_iDisturbModYear[BDA_FIRE]);
		}
		else if ((!strcmp(strTemp, "wind")) || !(strcmp(strTemp, "Wind")) || !(strcmp(strTemp, "WIND")))
		{
			m_iDisturbType |= BDA_DISTTYPE_WIND;
			fscanc(pfile, "%f", &m_fDisturbMod[BDA_WIND]); //disturbance modifiers list
			fscanc(pfile, "%d", &m_iDisturbModYear[BDA_WIND]);
		}
		else if ((!strcmp(strTemp, "timber")) || !(strcmp(strTemp, "Timber")) || !(strcmp(strTemp, "TIMBER")))
		{
			m_iDisturbType |= 0x4;
			fscanc(pfile, "%f", &m_fDisturbMod[BDA_TIMBER]); //disturbance modifiers list
			fscanc(pfile, "%d", &m_iDisturbModYear[BDA_TIMBER]);
		}
		else if ((!strcmp(strTemp, "harvest")) || !(strcmp(strTemp, "Harvest")) || !(strcmp(strTemp, "HARVEST")))
		{
			m_iDisturbType |= BDA_DISTTYPE_HARVEST;
			fscanc(pfile, "%f", &m_fDisturbMod[BDA_HARVEST]); //disturbance modifiers list
			fscanc(pfile, "%d", &m_iDisturbModYear[BDA_HARVEST]);
		}
	}

	//read in temporal parameters

	fscanc(pfile, "%d", &m_iTimeSinceLastEpidemic);	//TimeSinceLastEpidemic

	//read in TempPattern // no longer used by May 09, 2016 
	//fscanc(pfile, "%s", strTemp);
	//if ((!strcmp(strTemp, "random")) || (!strcmp(strTemp, "Random")) || (!strcmp(strTemp, "RANDOM")))// Changed by Nancy to handle uppercase <Mar 30 2016>
	//	m_enumTempPattern = random;
	//else if ((!strcmp(strTemp, "cyclic")) || (!strcmp(strTemp, "Cyclic")) || (!strcmp(strTemp, "CYCLIC")))// Changed by Nancy to handle uppercase <Mar 30 2016>
	//	m_enumTempPattern = cyclic;
	//else
	//	errorSys("Error in reading BDA m_enumTempPattern, name dosn't match.Please check spell or use all lowercase", STOP);

	//read in TempType
	fscanc(pfile, "%s", strTemp);
	if ((!strcmp(strTemp, "pulse")) || (!strcmp(strTemp, "Pulse")) || (!strcmp(strTemp, "PULSE")))// Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumTempType = TTpulse;
	else if ((!strcmp(strTemp, "variablepulse")) || (!strcmp(strTemp, "Variablepulse")) || (!strcmp(strTemp, "VARIABLEPULSE")))// Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumTempType = TTvariablepulse;
	else if ((!strcmp(strTemp, "continuous")) || (!strcmp(strTemp, "Continuous")) || (!strcmp(strTemp, "CONTINUOUS")))// Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumTempType = TTcontinuous;
	else
		errorSys("Error in reading BDA m_enumTempType, name dosn't match.Please check spell or use all lowercase", STOP);

	//read in RandomFuncton 
	fscanc(pfile, "%s", strTemp);
	if ((!strcmp(strTemp, "cyclicnormal")) || (!strcmp(strTemp, "CyclicNormal")) || (!strcmp(strTemp, "Cyclicnormal")) || (!strcmp(strTemp, "CYCLICNORMAL")))//Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumRandomFuncs = RFnormal;
	else if ((!strcmp(strTemp, "cyclicuniform")) || (!strcmp(strTemp, "CyclicUniform")) || (!strcmp(strTemp, "Cyclicuniform")) || (!strcmp(strTemp, "CYCLICUNIFORM")))// Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumRandomFuncs = RFuniform;
	else
		errorSys("Error in reading BDA RandomFuncton,  name dosn't match RandomFuncton type. Please check spell or use all lowercase", STOP);


	fscanc(pfile, "%f", &m_fRandomParam1);
	fscanc(pfile, "%f", &m_fRandomParam2);
	//cout << "RandomParam1:   " << m_fRandomParam1 << "    RandomParam2:   " << m_fRandomParam2 << endl;
	if ((m_fRandomParam1 > m_fRandomParam2) && (m_enumRandomFuncs  == RFuniform))
		errorSys("Error in reading BDA RandomFuncton, random paramter 1 is bigger than random parameter 2.", STOP);

	fscanc(pfile, "%d", &m_iTemporalFreq);
	fscanc(pfile, "%d", &m_iMinROS);
	fscanc(pfile, "%d", &m_iMaxROS);
	// added on April 11th 2018 by Cheney
	fscanc(pfile, "%f", &r);
	fscanc(pfile, "%f", &m);
	fscanc(pfile, "%d", &econum);
	fscanc(pfile, "%d", &iterationNumber);
	for (int i = 0; i < econum; i++){
		for (int j = 0; j < iterationNumber; j++){
			fscanc(pfile, "%d", &ecoArr[i][j]);
			//cout <<"ecoArr"<<ecoArr[i][j] << endl;
		}
	}
	//read in intensity threadhold
	fscanc(pfile, "%f", &intensityThre1); // added on April 5th 2016 by Nancy
	fscanc(pfile, "%f", &intensityThre2); // added on April 5th 2016 by Nancy
	//cout << "intensity Threshold: " << intensityThre1 << ", " << intensityThre2 << endl;

	//read in species parameters
	fscanc(pfile, "%d", &iTemp); //i number of species
	//cout << "species number: " << pBDAspeciesAttrs->number() << endl;
	if (iTemp != pBDAspeciesAttrs->number())
		errorSys("BDA: number of species doesn't match", STOP);

	MinorHostAge = (int*)malloc(iTemp*sizeof(int));
	SecondaryHostAge = (int*)malloc(iTemp*sizeof(int));
	PrimaryHostAge = (int*)malloc(iTemp*sizeof(int));
	ResistantHostAge = (int*)malloc(iTemp*sizeof(int));
	Toleranthostage = (int*)malloc(iTemp*sizeof(int));
	VulnerableHostAge = (int*)malloc(iTemp*sizeof(int));

	//The percentage of killing trees at each severity level
	ResistantPercentage = (double*)malloc(iTemp*sizeof(double)); // added on April 5th 2016 by Nancy
	TolerantPercentage = (double*)malloc(iTemp*sizeof(double));// added on April 5th 2016 by Nancy
	VulnerablePercentage = (double*)malloc(iTemp*sizeof(double));// added on April 5th 2016 by Nancy

	//The threshold of SRD
	MinorHostThreshold = (double*)malloc(iTemp*sizeof(double)); // added on May 5th 2016 by Nancy
	SecondaryHostThreshold = (double*)malloc(iTemp*sizeof(double));// added on May 5th 2016 by Nancy
	PrimaryThreshold = (double*)malloc(iTemp*sizeof(double));// added on May 5th 2016 by Nancy

	SPECIESATTR*	pSA = pBDAspeciesAttrs->first();
	for (i = 0; i < iTemp; i++)
	{
		fscanc(pfile, "%s", strTemp);
		if (strcmp(strTemp, pSA->name))
			errorSys("species name doesn't match", STOP);
		fscanc(pfile, "%d", &MinorHostAge[i]);	
		fscanc(pfile, "%lf", &MinorHostThreshold[i]);// added on May 5th 2016 by Nancy
		fscanc(pfile, "%d", &SecondaryHostAge[i]);	
		fscanc(pfile, "%lf", &SecondaryHostThreshold[i]);// added on May 5th 2016 by Nancy
		fscanc(pfile, "%d", &PrimaryHostAge[i]);	
		fscanc(pfile, "%lf", &PrimaryThreshold[i]);// added on May 5th 2016 by Nancy
		fscanc(pfile, "%d", &ResistantHostAge[i]);	
		fscanc(pfile, "%lf", &ResistantPercentage[i]);// added on April 5th 2016 by Nancy
		fscanc(pfile, "%d", &Toleranthostage[i]);
		fscanc(pfile, "%lf", &TolerantPercentage[i]);// added on April 5th 2016 by Nancy
		fscanc(pfile, "%d", &VulnerableHostAge[i]);	
		fscanc(pfile, "%lf", &VulnerablePercentage[i]);// added on April 5th 2016 by Nancy
		pSA = pBDAspeciesAttrs->next();
		//cout << endl;
		//cout << "MinorHAge:" << MinorHostAge[i] << "  SRD: " << MinorHostThreshold[i] << endl;
		//cout << "SecondaryHAge:" << SecondaryHostAge[i] << "  SRD: " << SecondaryHostThreshold[i] << endl;
		//cout << "PrimaryHAge:" << PrimaryHostAge[i] << "  SRD: " << PrimaryThreshold[i] << endl;
		//cout << "ResistantHostAge:" << ResistantHostAge[i]  << " ResistantPercentage:" << ResistantPercentage[i] << endl;
		//cout <<"Toleranthostage:" << Toleranthostage[i] << " " << "TolerantPercentage:" << TolerantPercentage[i] << endl;
		//cout << "VulnerableHostAge:" << VulnerableHostAge[i] << " " << "VulnerablePercentage:" << VulnerablePercentage[i] << endl;
		//cout << endl;
	}

	//read in Neighborhood parameters
	fscanc(pfile, "%d", &m_bNeighborFlag);
	fscanc(pfile, "%f", &fTemp);
	m_fNeighborRadius = fTemp / cellSize;
	if (m_fNeighborRadius < 0.5)
		errorSys("m_iNeighborRadius smaller than one cellSize", STOP);


	fscanc(pfile, "%s", strTemp);	//neighborshape uniform, linear, gaussian
	if ((!strcmp(strTemp, "uniform")) || (!strcmp(strTemp, "Uniform")) || (!strcmp(strTemp, "UNIFORM")))//Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumNeighborShape = uniform;
	else if ((!strcmp(strTemp, "linear")) || (!strcmp(strTemp, "Linear")) || (!strcmp(strTemp, "LINEAR")))//Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumNeighborShape = linear;
	else if ((!strcmp(strTemp, "gaussian")) || (!strcmp(strTemp, "Gaussian")) || (!strcmp(strTemp, "GAUSSIAN")))//Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumNeighborShape = gaussian;
	else 
		errorSys("BDA:Unrecognized neighborshape, name doesn't match.Please check spell or use all lowercase", STOP);

	fscanc(pfile, "%f", &m_fNeighborWeight);

	//read in Dispersal
	fscanc(pfile, "%d", &m_bDispFlag);	//not used
	fscanc(pfile, "%d", &m_bSpatialSyn);
	fscanc(pfile, "%d", &iTemp);
	m_iDispersalRate =BDA_ROUND(((float)iTemp * pBDAsites->TimeStep_BDA/ cellSize));//Changed By Qia on Jan 13 2009

	//cout << "m_iDispersalRate:  " << m_iDispersalRate  << endl;
	//cout << "before round: " << ((float)iTemp * pBDAsites->TimeStep_BDA / cellSize) << endl;
	//cout << "after round: " << m_iDispersalRate << endl;

	fscanc(pfile, "%f", &m_fEpidemicThresh);
	fscanc(pfile, "%d", &m_uiEpicenterNum);
	fscanc(pfile, "%d", &m_bSeedEpicenter);
	fscanc(pfile, "%f", &m_fOutbreakCoeff);
	fscanc(pfile, "%f", &m_fNonOutbreakCoeff);
	fscanc(pfile, "%s", strTemp);
	if ((!strcmp(strTemp, "map")) || (!strcmp(strTemp, "Map")) || (!strcmp(strTemp, "MAP")))//Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumInitialCondition = map;
	else if ((!strcmp(strTemp, "none")) || (!strcmp(strTemp, "None")) || (!strcmp(strTemp, "NONE")))//Changed by Nancy to handle uppercase <Mar 30 2016>
		m_enumInitialCondition = none;
	else 
		errorSys("BDA: Unrecognized map type,  name doesn't match.Please check spell or use all lowercase", STOP);

	//initialize dilation
	fscanc(pfile, "%d", &m_iDispersalTemplate);
	if (m_iDispersalTemplate >=1 && m_iDispersalTemplate <= 4)
	{
		if ((m_pDilation = DilationNew(StruElem[m_iDispersalTemplate-1].size, StruElem[m_iDispersalTemplate-1].item)) == NULL)
			DilationFree(m_pDilation);
	}
	else if (m_iDispersalTemplate != 0)
		errorSys("BDA: Incorrect DispersalTemplate, must be 0 ~ 4", STOP);

	// Added by Nancy May 16 2016,Option for output SRD , BDP
	
	if (fscanc(pfile, "%d", &m_OutSRD) != 1)
		errorSys("Error in reading SRD output option.", STOP);
	if(fscanc(pfile, "%d", &m_OutBDP)!=1)
		errorSys("Error in reading BDP output option.", STOP);
	//cout << "m_OutSRD: " << m_OutSRD << " m_OutBDP: " << m_OutBDP << endl;
}



/********************************
Name:		 BDAActive
Description: main procedure of BDA

    0001	1	//SiteResDom
    0010	2	//SiteResDomMod
    0100	4	//lastFire, lastHarvest
    1000	8	//Neighbor ResDomMod
   10000	16	// SV
  100000    32  //severity
 1000000    64	//
10000000    128 //new epicenters
*********************************/
//##ModelId=3F01D0EB02B9
void BDA::BDAActive(int itr)
{
	mn = 1.0*INT_MAX; mx = 1.0*INT_MIN;
	for (int m = 0; m < n_numInterval; m++){
		if (itr >= startYear[m] && itr <= endYear[m]){
			//	printf("BDA map size %d X %d\n", m_iRow, m_iCol);
			SitesClean(false);	//reset every thing except severity
			//	FILE* m_pW = fopen( "windowROS.out", "aw" );
			//	m_iROS = Temporal();
			m_iROS = Temporal2();
			cout << "m_iROS: " << m_iROS << endl;
			//	fprintf(m_pW, "%d %s", m_iROS, "\n");
			//	fclose(m_pW);
			time_t	lBDAtime1, lBDAtime2;
			long	lBDAtimeDiff;
			char str[100];

			//printf("Neighbor: %d, Radius: %f\n", m_bNeighborFlag, m_fNeighborRadius);
			if (m_iROS > 0)	// for test if(m_iROS > 0)
			{
				SiteResDom(0);
				//added by Cheney
				/*int u, v;
				float temp;
				for (u = 0; u < 10; u++){
					for (v = 0; v < 10; v++){
						temp = (sp[u][v] - mn) / (mx - mn);
						if (sp[u][v] != 0)
							cout << "C final Parameter: " << sp[u][v] << " " << mn << " " << mx << " " << temp << endl;
						else
							cout << "C final Parameter: " << sp[u][v] << " " << mn << " " << mx << " " << 0 << endl;
					}
				}*/
				SiteResDom(1);
				SiteResDomMod();
				if (m_bSpatialSyn == false)	//spacial asynchronous  No.41 in insect1.dat
				 {

					SiteVulnerability(false,itr);  //don't consider neighborhood

					time(&lBDAtime1);
					NewEpicenters();
					time(&lBDAtime2);
					lBDAtimeDiff = (long)(lBDAtime2 - lBDAtime1);
					sprintf(str, "NewEpicenters and dispersal procedure %d took %ld seconds", m_iDispersalTemplate, lBDAtimeDiff);
					//			printMessage(str);
					printf("%s\n", str);
					if (m_bNeighborFlag == true)
					{
						NeighborResDom();
						SiteVulnerability(m_bNeighborFlag,itr);
					}
				}
				else // spacial synchronous
				{
					SetOutbreakZone(Newzone);
					if (m_bNeighborFlag == true)
					{
						if (m_bSpeedUp == true)  //
						{
							//time1
							time(&lBDAtime1);

							NeighborResDomSample();

							//time2
							time(&lBDAtime2);
							lBDAtimeDiff = (long)(lBDAtime2 - lBDAtime1);
							sprintf(str, "Speedup NeighorResDom took %ld seconds", lBDAtimeDiff);
							//printMessage(str);
							printf("%s\n", str);
						}
						else
						{
							//time1
							time(&lBDAtime1);

							NeighborResDom();
							//time2
							time(&lBDAtime2);
							lBDAtimeDiff = (long)(lBDAtime2 - lBDAtime1);
							sprintf(str, "---->Regular NeighorResDom took %ld seconds", lBDAtimeDiff);
							//printMessage(str);
							printf("%s\n", str);
						}
					}
					SiteVulnerability(m_bNeighborFlag,itr);
				}

				DisturbSite();
				if (m_iDllMode & G_FUEL)
					UpdatePDP();
			}
			else
			{
				int i, j;
				if (m_iDllMode & G_FUEL)
				{
					for (i = 1; i < m_iRow; i++)
						for (j = 1; j < m_iCol; j++)
						{
						(m_pPDP->pBDAPDP[m_iBDANo]).sTSLBDA[i][j] += pBDAsites->TimeStep_BDA;
						}
				}
			}
		}
		else {
			cout << "BDA is not running at iteration " << itr << endl;
		}
	}
}

/*****************************************************************
Name:			ParamAdjust
Input:			
Output:			
Description:	This function is not used in this version

*******************************************************************/
//##ModelId=3F01D0EC00B4
void BDA::ParamAdjust( )
{


}


/*****************************************************************
Name:			Temporal
Input:			
Output:			m_iROS (regional Outbreak Status, [0-3]
Description:	output ROS 
*******************************************************************/
//##ModelId=3F01D0EB02C6
//int BDA::Temporal()
//{
//	float	ProbEvent;
//
////	srand( (unsigned)time( NULL ) );  //by ver Nov. 24, comment it for reapeat result
////	srand( 1 );
//	if (m_ifBDArepeat == 0)  //0: random and not repeat; 1: repeat
//		srand( (unsigned)time( NULL ) );
//
//	m_iTimeSinceLastEpidemic += pBDAsites->TimeStep_BDA;	
//	if(m_enumTempPattern == random)			//random
//	{
//		ProbEvent = (float)m_iTimeSinceLastEpidemic / m_iTemporalFreq;
//		UniformRandomNum = (float)(frandrand() % 100) / 100;
//		if (ProbEvent >= UniformRandomNum)
//		{
//			if (m_enumTempType == pulse)	//pulse
//			{
//				m_iROS = m_iMaxROS;
//				m_iTimeSinceLastEpidemic = 0;
//			}
//			else if (m_enumTempType == continuous)	//continuous
//				m_iROS = m_iMinROS + frandrand() % (m_iMaxROS - m_iMinROS + 1); //random;y selects an ROS between ROSmin and ROSmax
//		}
//		else
//			m_iROS = 0;
//	}
//	else if (m_enumTempPattern == cyclic)	//cyclic
//	{
//		if (m_enumTempType == pulse)		//pulse
//		{
//			if (m_iTimeSinceLastEpidemic % m_iTemporalFreq == 0) //???
//				m_iROS = m_iMaxROS;
//			else
//				m_iROS = 0;
//		}
//		else if (m_enumTempType == continuous)  //continuous
//			m_iROS = m_iMinROS + frandrand() % (m_iMaxROS - m_iMinROS + 1);
//	}
//
//	return m_iROS;
//}

/********************************
Wei Li added on March 20, 2004
Updated on Apri 24, 2004 
**************************************************/
int BDA::Temporal2()
{
//	FILE* m_pW = fopen( "2004ROS_normal.txt", "aw" );

	if (m_ifBDArepeat == 0)  //0: random and not repeat; 1: repeat   modifiied by Wei Li, 2004
		srand( (unsigned)time( NULL ) );


	m_iTimeSinceLastEpidemic = m_iTimeSinceLastEpidemic + pBDAsites->TimeStep_BDA;
	m_iTimetoNextEpidemic = m_iTimetoNextEpidemic - pBDAsites->TimeStep_BDA;

	if ((m_enumTempType == TTpulse) || (m_enumTempType == TTvariablepulse))
	{
		if (m_iTimetoNextEpidemic < (m_iTemporalFreq / 2))
		{
			//calculate ROS
			if (m_enumTempType == TTpulse)						
				m_iROS = m_iMaxROS;
			else if (m_enumTempType == TTvariablepulse)
			{
				
				//randomly select an ROS netween ROSmin and ROSmax
				//m_iROS = rand() % (m_iMaxROS - m_iMinROS + 1) + m_iMinROS;


				// changed random number on April 14th 2016 by Nancy
				std::random_device rd; // obtain a random number from hardware
				std::mt19937 eng(rd()); // seed the generator
				std::uniform_int_distribution<> distr(m_iMinROS, m_iMaxROS); // define the range
				m_iROS = distr(eng);
							
			}
	
			//calcualte TimetoNextEpidemic
			if (m_enumRandomFuncs == RFuniform)
			{
				m_iTimeSinceLastEpidemic = 0;
				m_iTimetoNextEpidemic = m_fRandomParam1 + frandrand() % (int)(m_fRandomParam2 - m_fRandomParam1);
				//cout << "m_fRandomParam1: " << m_fRandomParam1 << "m_fRandomParam2: " << m_fRandomParam2<< endl;
//				fprintf(m_pW, "%d\n", m_iTimetoNextEpidemic);
				//cout << "m_iTimetoNextEpidemic" << m_iTimetoNextEpidemic << endl;
			}
			else if (m_enumRandomFuncs == RFnormal)
			{
				m_iTimeSinceLastEpidemic = 0;
				// create a function that randomly selects the TimeToNextEpidemic
				//from a normally distributuion with mean = Param1 and standard deviation = RandomParam2
				m_iTimetoNextEpidemic = (int)m_pStochastic->Normal(m_fRandomParam1, m_fRandomParam2);
//				fprintf(m_pW, "%d\n", m_iTimetoNextEpidemic);
				//cout << "m_iTimetoNextEpidemic" << m_iTimetoNextEpidemic << endl;
			}
		}
		else  //m_iTimetoNextEpidemic is bigger than half of timestep
			m_iROS = m_iMinROS;  //modified Updated on Apri 24, 2004
	}	
//	fprintf(m_pW, "%d %s", m_iROS, "\n");
//	fclose(m_pW);

	return m_iROS;
	
}

/*****************************************************************
Name:		SiteResDom
Input:			
Output:		[0-1]	
Description: calculate the SiteResDom
Note:
	loop (i, j) begin with (1, 1)
	loop species begines with 1
	sites(i, j)->next can't used to traves species
*******************************************************************/
//##ModelId=3F01D0EB02C7
void BDA::SiteResDom(int id)
{
	int		i, j, k;
	int		iNumSpecies = 0, iValidNumber;
	float	fSumValue = 0.0, fMaxValue = 0.0;
	int		iOldestCohortPresent;
	int     iTreeNumber;
	float	fSpeciesHostValue; // Original :float	fSpeciesHostValue <03/25/2016>

	int n_species = pBDAspeciesAttrs->number(); // added on July 12th by Nancy
	//cout << "add species:" << n_species << endl;// added on July 12th by Nancy
	float* totalTree = new float[n_species];// added on July 12th by Nancy
	int* longevity_bda = new int[n_species];// added on July 12th by Nancy
	float* totalGrowRate = new float[n_species]; //added on July 12th by Nancy
	float* percentage = new float[n_species];//added on July 12th by Nancy
	float* probBA = new float[n_species];//added on July 12th by Nancy
	int treeN;//added on July 12th by Nancy
	float finalTree = 0;//added on July 12th by Nancy
	float finalGrow = 0;//added on July 12th by Nancy
	float fMax, fMin; //Added by Nancy on July 23th 2016
	float hostGrow = 0.0; //added by Cheney

	int temp;
	float growrate;
	float growRateSqre;
	float tempSpecies=0.0;
	float sumAllSpecies = 0;
	float sumHostSpecies = 0;

	GDALDataset  *swiimgFile, *initimgFile, *swiimgFileOutput; //* Added by Nancy on July 23th 2016
	GDALDataset  *ecoimgFile; //* Added by Cheney on April 2018

	int nCols, nRows;//* Added by Nancy on July 23th 2016

	double        adfGeoTransform[6]; //*Added by Nancy on July 23th 2016

	double ecoTransform[6]; //*Added by Chency on April 10th 2018

	GDALAllRegister(); //*Added by Nancy on July 23th 2016

	float *pafScanline, *pafScanlineout; //*Added by Nancy on July 23th 2016

	GDALRasterBand  *poBand, *outPoBand;//*Added by Nancy on July 23th 2016

	float fCellVal; //*Added by Nancy on July 23th 2016

	float fAPara, fBPara, fCPara;//*Added by Nancy on July 23th 2016

	const char *pszFormat = "HFA"; //*Added by Nancy on July 23th 2016

	GDALDriver *poDriver;//*Added by Nancy on July 23th 2016

	char **papszMetadata;//*Added by Nancy on July 23th 2016

	poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);//*Added by Nancy on July 23th 2016

	if (poDriver == NULL)//*Added by Nancy on July 23th 2016
		exit(1);//*

	papszMetadata = poDriver->GetMetadata();//*Added by Nancy on July 23th 2016

	char **papszOptions = NULL;//*Added by Nancy on July 23th 2016

	char *pszSRS_WKT = NULL;//*Added by Nancy on July 23th 2016

	OGRSpatialReference oSRS;//*Added by Nancy on July 23th 2016

	oSRS.SetUTM(11, TRUE);//*Added by Nancy on July 23th 2016

	oSRS.SetWellKnownGeogCS("HEAD74");//*Added by Nancy on July 23th 2016

	oSRS.exportToWkt(&pszSRS_WKT);//*Added by Nancy on July 23th 2016

	CPLFree(pszSRS_WKT);
		//printf("SiteResDom...\n");

		if ((swiimgFile = (GDALDataset *)GDALOpen(swiImgMapFile, GA_ReadOnly)) == NULL) //* swi.img,Added by Nancy on July 23th 2016

			errorSys("landtype img map input file not found.", STOP);//* Added by Nancy on July 23th 2016

		if (swiimgFile->GetGeoTransform(adfGeoTransform) == CE_None){ //* Added by Nancy on July 23th 2016

			for (int i = 0; i < 6; i++){//*

				wAdfGeoTransform[i] = adfGeoTransform[i];//* Added by Nancy on July 23th 2016
			}//*

		}//*

		poBand = swiimgFile->GetRasterBand(1);//*Added by Nancy on July 23th 2016

		nCols = swiimgFile->GetRasterXSize(); //*Added by Nancy on July 23th 2016

		nRows = swiimgFile->GetRasterYSize(); //*Added by Nancy on July 23th 2016

		pafScanline = (float *)CPLMalloc(sizeof(float)* (nCols * nRows));//*Added by Nancy on July 23th 2016


		poBand->RasterIO(GF_Read, 0, 0, nCols, nRows, pafScanline, nCols, nRows, GDT_Float32, 0, 0);//*Added by Nancy on July 23th 2016

		swiimgFileOutput = poDriver->Create("SRD.img", nCols, nRows, 1, GDT_Float32, papszOptions);//*

		if (swiimgFileOutput == NULL)

			errorSys("Img file not be  created.", STOP);//*

		swiimgFileOutput->SetGeoTransform(wAdfGeoTransform);//* 

		outPoBand = swiimgFileOutput->GetRasterBand(1);//*

		pafScanlineout = (float *)CPLMalloc(sizeof(float)* (nRows*nCols));//*

		//std::cout << "PDSI.img" << endl;//*Added by Nancy on July 23th 2016

		//*Added by Cheney on Apr 10th 2018
		if ((ecoimgFile = (GDALDataset *)GDALOpen(ecoImgMapFile, GA_ReadOnly)) == NULL) //*eco.img,Added by Cheney on April 9th 2018

			errorSys("ecoregion img map input file not found.", STOP);//* Added by Cheney on April 9th 2018

		if (ecoimgFile->GetGeoTransform(ecoTransform) == CE_None){

			for (int i = 0; i < 6; i++){//*

				wEcoTransform[i] = ecoTransform[i];
			}

		}

		poBand = ecoimgFile->GetRasterBand(1);

		nCols = ecoimgFile->GetRasterXSize();

		nRows = ecoimgFile->GetRasterYSize();

		pafScanline2 = (float *)CPLMalloc(sizeof(float)* (nCols * nRows));


		poBand->RasterIO(GF_Read, 0, 0, nCols, nRows, pafScanline2, nCols, nRows, GDT_Float32, 0, 0);
		//std::cout << "eco.img" << endl;


		fMin = fMax = *(pafScanline + (nRows)*nCols - 1);
		//std::cout <<"fMin_Initial: "<< fMin << "  fMax_Initial:" << fMax << endl;
	for (int m = nRows; m > 0; m--)//*Added by Nancy on July 23th 2016

	{
		for (int n = 1; n <= nCols; n++)//*Added by Nancy on July 23th 2016

		{
			fCellVal = *(pafScanline + (nRows - m)*nCols + n - 1);//*//*Added by Nancy on July 23th 2016

			if (fCellVal > fMax)

				fMax = fCellVal;

			if (fCellVal < fMin)

				fMin = fCellVal;

			//std::cout << fCellVal;//*Added by Nancy on July 23th 2016

		}
		//std::cout << std::endl;//*Added by Nancy on July 23th 2016

	}

		//std::cout << "fMax:" << fMax << std::endl;
		//std::cout << "fMin:" << fMin << std::endl;
	if (m_enumSRDMode == SRDmean)	//mean
	{
		for (i = m_iRow; i > 0; i--){
			for (j = 1; j <= m_iCol; j++)
			{

				if (pBDAsites->locateLanduPt(i, j)->active())		//active sites
					//Original Landis4.0: ((*pBDAsites)(i, j))->landUnit->active()
					//Changed By Qia on Oct 13 2008
				{
					fSumValue = 0.0;
					iNumSpecies = ((*pBDAsites)(i, j))->number();
					iValidNumber = 0;
					fMaxValue = 0.0;
					finalTree = 0;
					finalGrow = 0.0;//added by Cheney
					hostGrow = 0.0;//added by Cheney
					for (k = 0; k < iNumSpecies; k++)				//for all species
					{
						iOldestCohortPresent = ((*(*pBDAsites)(i, j))(k + 1))->oldest();



						totalTree[k] = 0;// added on July 12th by Nancy

						totalGrowRate[k] = 0;

						//cout << " k+1: " << k+1 << " " << (*pBDAspeciesAttrs)(k+1)->longevity;// added on July 12th by Nancy

						longevity_bda[k] = (*pBDAspeciesAttrs)(k + 1)->longevity;// added on July 12th by Nancy

						// added on July 12th by Nancy
						for (int m = 1; m <= longevity_bda[k] / m_iTimeStep; m++){

							//cout << "landtype is: " <<int (pBDAsites->locateLanduPt(i, j)->ltID) << endl;

							// calculate tree number for each cell
							treeN = ((*(*pBDAsites)(i, j))(k + 1))->getTreeNum(m, k + 1);

							//cout << "tree number test " << ((*(*pBDAsites)(2, 3))(1))->getTreeNum(m, 1) << endl;  //important checkpoint
							totalTree[k] = totalTree[k] + treeN;

							// std::cout << "cell position:(" << i << ", " << j << " ) species:" << k + 1 << " , age:" << m *m_iTimeStep << endl; //important checkpoint
							 //std::cout << "species k+1 " << k + 1 << "  m (year)  " << m << "  parameter  " << pBDAsites->locateLanduPt(i, j)->ltID<< endl;

							// calculate growth rate for each cell
							growrate = pBDAsites->GetGrowthRates(k + 1, m, int(pBDAsites->locateLanduPt(i, j)->ltID));

							growRateSqre = 0.00007854 * growrate * growrate *treeN;

							totalGrowRate[k] = totalGrowRate[k] + growRateSqre;
							
								//std::cout << " growrate is:" << growrate;

								//std::cout << " BA is: " << growRateSqre;

								//std::cout << " tree number: " << treeN << endl;
					


						}

						//cout << "add total tree for species number " << k << " is: " << totalTree[k] << endl;	// added on July 12th by Nancy

						finalTree = finalTree + totalTree[k];	// added on July 12th by Nancy



						finalGrow = finalGrow + totalGrowRate[k];	// added on July 19th by Nancy
						//added by Cheney
						hostGrow += (MinorHostAge[k] == 999 && (MinorHostAge[k] ^ SecondaryHostAge[k] ^ PrimaryHostAge[k] ^ ResistantHostAge[k] ^ Toleranthostage[k] ^ VulnerableHostAge[k] == 0)) ? 0 : totalGrowRate[k];

						 //cout << "total BA: " << finalGrow << endl;

						iTreeNumber = ((*(*pBDAsites)(i, j))(k + 1))->getTreeNum(iOldestCohortPresent / m_iTimeStep, k + 1); // added on March 31 2016

						if (iOldestCohortPresent > 0)
						{
							iValidNumber++;

							if (iOldestCohortPresent >= PrimaryHostAge[k])
								fSpeciesHostValue = (float)PrimaryThreshold[k];
							else if (iOldestCohortPresent >= SecondaryHostAge[k])
								fSpeciesHostValue = (float)SecondaryHostThreshold[k];
							else if (iOldestCohortPresent >= MinorHostAge[k])
								fSpeciesHostValue = (float)MinorHostThreshold[k];
							else
								fSpeciesHostValue = (float)0.0;

							fSumValue += fSpeciesHostValue;
							fMaxValue = (fMaxValue > fSpeciesHostValue) ? fMaxValue : fSpeciesHostValue;
						}
						else{
							fSpeciesHostValue = (float)0.0; //Added by Nancy <03 / 25 / 2016>
						}

						 //cout << "HostValue:" << fSpeciesHostValue << endl;
					}

					// added on July 12th by Nancy

					// Calculate Parameter A:

					fCellVal = *(pafScanline + (nRows - i)*nCols + j - 1);
					 //cout << "A value:" << fCellVal << endl;

					//added on Mar 13th by Cheney
					 if (finalTree ==0)
						 fAPara = 0;
					 else
						fAPara = (fCellVal - fMin) / (fMax - fMin);
					 spA[i][j] = fAPara;
					 if (id == 1){
						// cout << "A Parameter:" << fAPara << endl;// important checkpoint
					 }

					//Calculate Parameter B and C:

					// cout << "final tree: " << finalTree << endl;

					for (k = 0; k < iNumSpecies; k++)				//for all species
					{
						if (finalTree == 0)

							percentage[k] = 0;
						else
							percentage[k] = totalTree[k] / finalTree;
					
						if (id == 1){
							//cout << "totalTree[k] " << k + 1 << " is " << float(totalTree[k]) << endl;

							//cout << "finalTree: " << finalTree << endl;

							//cout << "percentage with species:  " << k + 1 << " is " << percentage[k] << endl;
						}
							bool b = false;
							if (percentage[k]>0){
								tempSpecies = percentage[k] * log(percentage[k]);
								b = true;
							}
						//tempSpecies = percentage[k] * log(percentage[k]);
							if (id==1)
						//cout << "p*ln(P)  with species " << k + 1 << " is: " << tempSpecies << endl;
						if (b)
						sumAllSpecies = sumAllSpecies + tempSpecies;
						tempSpecies = 0;
						//sumHostSpecies = sumHostSpecies + ;

						probBA[k] = totalGrowRate[k] / finalGrow;


					}
					
										
					/*if (sumAllSpecies!=0)
						fBPara = sumAllSpecies / sumAllSpecies;*/

						//cout << "B parameter is " << fBPara << endl;
					//added by Cheney
					if (id == 1){
						if (finalGrow != 0){
							for (int u = 0; u < k; u++)
								//cout << totalGrowRate[u] << " ";
							//cout << endl;
							fBPara = float(hostGrow / finalGrow);
							//cout << "finalGrow is " << finalGrow << " " << "hostGrow is " << hostGrow << " " << "B parameter is " << fBPara << endl;
							//cout << "B parameter is " << fBPara << endl; // important checkpoint
						}
						else{
							fBPara = 0;
							//cout << "B parameter is " << fBPara << endl;
						}
					}
					//added by Cheney
					if (id == 0){
						mn = (mn > -sumAllSpecies ? -sumAllSpecies : mn);
						mx = (mx > -sumAllSpecies ? mx : -sumAllSpecies);
						sp[i][j] = -sumAllSpecies;
					}
					else{
						//fCPara=(sp[i][j] - mn) / (mx - mn);
						fCPara = 0.213;
						//cout << "C parameter is " << fCPara << endl;  //  important checkpoint
					}
					sumAllSpecies = 0;
						//float fCParaMax = -(0.5 * log(0.5) * 2);

						//fCPara = -sumAllSpecies / fCParaMax;

					/*	if (fCPara < 0)

							fCPara = 0;*/

		

						//cout << "C parameter is: " << fCPara << endl;
						//<Add By Qia on Dec 03 2008>
					if (id==1){
						m_pBDA->BefStChg(i, j);
						//cout << "value before: "<<p1<<" "<<p2<<" "<<p3 << endl;
						//cout << "ABC para  " << fAPara << " " << fBPara << " " << fCPara << endl;  //important checkpoint
						(*m_pBDA)(i, j)->fSiteResourceDom = p1 * fAPara + p2 * fBPara + p3 * fCPara;
						//cout << "SRD(fSiteResourceDom): " << (*m_pBDA)(i, j)->fSiteResourceDom << endl;   //important checkpoint
						*(pafScanlineout + (nRows-i)*nCols + j-1 ) = (*m_pBDA)(i, j)->fSiteResourceDom;
						/**(pafScanlineout + (i-1)*nCols + j - 1) = (*m_pBDA)(i, j)->fSiteResourceDom;*/
					}//*
						//</Add by Qia on Dec 03 2008>
						//(*m_pBDA)(i, j)->fSiteResourceDom = (float) fSumValue / iValidNumber;

						//cout << "before fSiteResourceDom (" << i << "," << j << ") :" << (*m_pBDA)(i, j)->fSiteResourceDom << endl;
						////<Add By Qia on May 4th 2009>
						//if(_isnan((*m_pBDA)(i, j)->fSiteResourceDom)){ // if NaN, return true
						//	if(fSumValue*iValidNumber>0){
						//		(*m_pBDA)(i, j)->fSiteResourceDom=128.0; //???
						//		}
						//	else{
						//		(*m_pBDA)(i, j)->fSiteResourceDom=-128.0;//??
						//		}
						//	}
						//</Add By Qia on May 4th 2009>
						if (fMaxValue <= (1.0 - (float)m_iROS / 3))
							(*m_pBDA)(i, j)->bDeadArea = true;	//dead area
						else
							(*m_pBDA)(i, j)->bDeadArea = false;	//active area
						//cout << "after fSiteResourceDom (" << i << "," << j << ") :" << (*m_pBDA)(i, j)->fSiteResourceDom << endl;
						//<Add By Qia on Dec 03 2008>
						m_pBDA->AftStChg(i, j);
						//</Add by Qia on Dec 03 2008>
					}//end active if 
					else{
						//<Add By Qia on Dec 03 2008>
						m_pBDA->BefStChg(i, j);
						//</Add by Qia on Dec 03 2008>
						(*m_pBDA)(i, j)->bDeadArea = true;	//dead area
						//<Add By Qia on Dec 03 2008>
						m_pBDA->AftStChg(i, j);
						//</Add by Qia on Dec 03 2008>
					}


				}
			}
		}
		// SRDMAX MODE IS NO LONGER NEEDED  added by Cheney
		if (id==1)
	outPoBand->RasterIO(GF_Write, 0, 0, nCols, nRows, pafScanlineout, nCols, nRows, GDT_Float32, 0, 0);///*added on July 23th by Nancy

	if (swiimgFileOutput != NULL)
		GDALClose((GDALDatasetH)swiimgFileOutput);//*added on July 23th by Nancy

	delete[] totalTree; //added on July 12th by Nancy
	delete[] longevity_bda;//added on July 12th by Nancy
	delete[] probBA; //added on July 12th by Nancy
	delete[] totalGrowRate;//added on July 12th by Nancy
	delete[] percentage; //added on July 12th by Nancy
}

/*****************************************************************
Name:		SiteResDomMod
Input: 
Output:		[0-1]
Description:calculate SiteResDomMod for every site whose fSiteResourceDom
			is bigger than one
Description:
	disturbance type list, 
   harvest, timber, wind, fire
	 1		1		1		1	
	 1		1		1		0   
	 1		0	    0		0	
	 0		1		0		0   
	 0		0		0		1   
	 0		0		0		0   
	 
#define	BDA_FIRE			0
#define	BDA_WIND			1
#define	BDA_TIMBER			2
#define BDA_HARVEST			3

LTAMod not used 

******************************************************************/
//##ModelId=3F01D0EB02D6
void BDA::SiteResDomMod()
{
	int		i, j, k;
	int		iLast = 0, iModYear;
	float	fDisturbMod;
	float	fSum = 0.0;


	//printf("SiteResDomMod...\n");
	for (i = 1; i <= m_iRow; i++)
	{
		for (j = 1; j <= m_iCol; j++)
		{
			
			if ((*m_pBDA)(i, j)->fSiteResourceDom > 0.0)	//SiteResDominance > 0
			{
				fSum = 0.0;
				if ((m_iDisturbType & BDA_DISTTYPE_FIRE) && (m_iDllMode & G_FIRE))	//fire: G_FIRE:32
				{
				//	iLast = (*pBDAsites)(i, j)->lastFire;
					iLast = m_pPDP->sTSLFire[i][j];
					iModYear = m_iDisturbModYear[BDA_FIRE];

					if (iLast < iModYear)
					{
						fDisturbMod = m_fDisturbMod[BDA_FIRE] * (float)(iModYear - iLast) / iModYear;
						fSum += fDisturbMod;
					}
				}
				if ((m_iDisturbType & BDA_DISTTYPE_WIND) && (m_iDllMode & G_WIND) )//wind: m_iDllMode: 2; G_WIND:4 
				{
					iLast = m_pPDP->sTSLWind[i][j];
					iModYear = m_iDisturbModYear[BDA_WIND];

					if (iLast < iModYear)
					{
						fDisturbMod = m_fDisturbMod[BDA_WIND] * (float)(iModYear - iLast) / iModYear;
						fSum += fDisturbMod;
					}
				}

				if ((m_iDisturbType & BDA_DISTTYPE_HARVEST) && (m_iDllMode & G_HARVEST))	//harvest:  G_HARVEST:8
				{

		//			iLast = sites(i, j)->lastHarvest;
					iLast = m_pPDP->sTSLHarvest[i][j];
					iModYear = m_iDisturbModYear[BDA_HARVEST];

					if (iLast < iModYear)
					{
						fDisturbMod = m_fDisturbMod[BDA_HARVEST] * (float)(iModYear - iLast) / iModYear;
						fSum += fDisturbMod;
					}

				} 
				for (k = 0; k < m_iLTModNum; k++)
				{
					if (!strcmp(pBDAsites->locateLanduPt(i, j)->name, (char*)m_strLTModName[k]))
						//Original landis4.0: !strcmp((*pBDAsites)(i, j)->landUnit->name, (char*)m_strLTModName[k])
						//changed By Qia on Oct 13 2008
					{
						if (m_fLTModVal[k] > -2)  //add on Mar, 2004
							fSum = (*m_pBDA)(i, j)->fSiteResourceDom + fSum + m_fLTModVal[k];
						else 
							fSum = (*m_pBDA)(i, j)->fSiteResourceDom + fSum;
						k = m_iLTModNum;
					}
				}

			if (fSum < 0.0)
				fSum = 0.0;
			else if (fSum > 1.0)
				fSum = 1.0;
			//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(i,j);
				//</Add by Qia on Dec 03 2008>
			(*m_pBDA)(i, j)->fSiteResDomMod = fSum;
				//<Add By Qia on Dec 03 2008>
				m_pBDA->AftStChg(i,j);
				//</Add by Qia on Dec 03 2008>
			}//end of one site
			else{
				//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(i,j);
				//</Add by Qia on Dec 03 2008>
				//(*m_pBDA)(i, j)->fSiteResDomMod = -9.0;// SRM
				(*m_pBDA)(i, j)->fSiteResDomMod = 0.0;
				//<Add By Qia on Dec 03 2008>
				m_pBDA->AftStChg(i,j);
				//</Add by Qia on Dec 03 2008>
				}

			
		}
	}
}


/*****************************************************************
Name:		NeighborResDom
Types:		uniform, linear, gaussian
Discription:Calculate mean SiteResDomMod for all sites falling within 
			NeighborRadius circular window centered at a given site

  FILE* m_pW = fopen( "windowShape.out", "w" );

	for (int x = 0; x < iWindowSize; x ++)
	{
		for (int y = 0; y < iWindowSize; y++)
		{
			fprintf(m_pW, "%d", (int)(10 * fWindow[x][y]) % 10);
		}
		fprintf(m_pW, "%s", "\n");
	}
	fprintf(m_pW, "%s", "\n");
	fclose(m_pW);
*****************************************************************/
//##ModelId=3F01D0EB02D7
void BDA::NeighborResDom()
{
	int		i, j, s0, s1, w0, w1;
	int		w_x0, w_y0, w_x1, w_y1, s_x0, s_y0, s_x1, s_y1;

	int		iHalfSize;
	float**	fWindow;
	float	fMean = 0;
	float	fNumWt;

	printf("NeighborResDom...\n");
	
	iHalfSize = BDA_ROUND(m_fNeighborRadius);
	if (iHalfSize == 0)
		errorSys("Neighbor raduis too small, stop.", STOP);
	fWindow = m_pfSlidingWindow;

	for (i = 1; i <= m_iRow; i++)
	{
		for (j = 1; j <= m_iCol; j++)
		{
			
			//if ((*m_pBDA)(i, j)->enumOutbreakZone == Newzone)
			//{
				fMean = 0.0;
				fNumWt = 0.0;
				if ((*m_pBDA)(i, j)->fSiteResourceDom > 0)	//SiteResDominance > 0
				{
					WindowCoordinates(i, j, iHalfSize, &s_x0, &s_y0, &s_x1, &s_y1, &w_x0, &w_y0, &w_x1, &w_y1);

					for (s0 = s_x0, w0 = w_x0; s0 <= s_x1, w0 <= w_x1; s0++, w0++)
						for (s1 = s_y0, w1 = w_y0; s1 <= s_y1, w1 <= w_y1; s1++, w1++)
						{
						//cout << "fWindow[w0][w1](" << w0 << "," << w1 << "):" << fWindow[w0][w1] << endl;   //important checkpoint
						//cout << "IsNotNodata (" << s0 << "," << s1 << "):" << IsNotNodata(s0, s1) << endl;   //important checkpoint
							if ((fWindow[w0][w1] !=0.0) && (IsNotNodata(s0, s1)))
							{
								if ((*m_pBDA)(s0, s1)->fSiteResDomMod > 0)
									fMean += (*m_pBDA)(s0, s1)->fSiteResDomMod * fWindow[w0][w1];
								fNumWt += fWindow[w0][w1];

								
							}
							//added by Cheney on March 2018
							fMean += (*m_pBDA)(s0, s1)->fSiteResourceDom * fWindow[w0][w1];
							fNumWt += fWindow[w0][w1];
						}
				//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(i,j);
				//</Add by Qia on Dec 03 2008>
					(*m_pBDA)(i, j)->fNeighborResDom = fMean / fNumWt;

					//cout << "fMean" << fMean << endl;
					//cout << "fNumWt" << fNumWt << endl;
				//<Add By Qia on May 4th 2009>
				/*	if(_isnan((*m_pBDA)(i, j)->fNeighborResDom)){
						if((fMean * fNumWt)>0){
							(*m_pBDA)(i, j)->fNeighborResDom=128.0;
							}
						else{
							(*m_pBDA)(i, j)->fNeighborResDom=-128.0;
							}
						}*/
					//</Add By Qia on May 4th 2009>
				//<Add By Qia on Dec 03 2008>
				m_pBDA->AftStChg(i,j);
				//</Add by Qia on Dec 03 2008>
				}
				
			//}

			//cout << "NRD: (" << i << "," << j << ") : " << (*m_pBDA)(i, j)->fNeighborResDom << endl;
		}
	}

}


/*****************************************************************
Name:		IsNotNodata
Types:		check whether the given site is no data or not
Discription:Calculate site(i, j)'s NeighborResDom
*****************************************************************/
bool BDA::IsNotNodata(int i, int j)
{
	int	k;
	for (k = 0; k < m_iNodataIndex; k ++)
	{
		if (!strcmp(pBDAsites->locateLanduPt(i, j)->name, m_strLTModNameNodata[k])) //the same
			//Original landis4.0: !strcmp((*pBDAsites)(i, j)->landUnit->name, m_strLTModNameNodata[k])
			//Changed By Qia on Oct 13 2008
			return false;   //site(i, j) has a landtype that in no data landtype list
	}
	return true;
}

/*****************************************************************
Name:		SingleNeighborResDom
Types:		uniform, linear, gaussian
Discription:Calculate site(i, j)'s NeighborResDom
*****************************************************************/
//##ModelId=3F01D0EC00D2
void BDA::SingleNeighborResDom(int i, int j, int iSize)
{
	int		s0, s1, w0, w1;
	int		w_x0, w_y0, w_x1, w_y1, s_x0, s_y0, s_x1, s_y1;
	float	fMean = 0;
	float	fNumWt;
	int		iHalfSize;
	float**	fWindow;

	fWindow = m_pfSlidingWindow;
	iHalfSize = iSize;
	//cout << "SingleNeighborResDom" << endl;
	//cout << "(" << i << "," << j << ")" << endl;
	if ((*m_pBDA)(i, j)->enumOutbreakZone == Newzone)
	{
		fMean = 0.0;
		fNumWt = 0.0;
		if ((*m_pBDA)(i, j)->fSiteResourceDom > 0)	//SiteResDominance > 0
		{
			WindowCoordinates(i, j, iHalfSize, &s_x0, &s_y0, &s_x1, &s_y1, &w_x0, &w_y0, &w_x1, &w_y1);
			
			for (s0 = s_x0, w0 = w_x0; s0 <= s_x1, w0 <= w_x1; s0++, w0++)
				for (s1 = s_y0, w1 = w_y0; s1 <= s_y1, w1 <= w_y1; s1++, w1++)
				{

				//cout << "fWindow[w0][w1](" << w0 << "," << w1 << "):" << fWindow[w0][w1] << endl;  //important checkpoint
				//cout << "fSiteResDomMod (" << s0 << "," << s1 << "):" << (*m_pBDA)(s0, s1)->fSiteResDomMod << endl;  //important checkpoint
					if ((fWindow[w0][w1] != 0.0) && (IsNotNodata(s0, s1)))
					{
						if ((*m_pBDA)(s0, s1)->fSiteResDomMod > 0)
							fMean += (*m_pBDA)(s0, s1)->fSiteResDomMod * fWindow[w0][w1];
						fNumWt += fWindow[w0][w1];
						
					}
				}
				//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(i,j);
				//</Add by Qia on Dec 03 2008>
			(*m_pBDA)(i, j)->fNeighborResDom = fMean / fNumWt;

			//cout << "fMean: " << fMean << endl;
			//cout << "fNumWt: " << fNumWt << endl;
				//<Add By Qia on May 4th 2009>
					if(_isnan((*m_pBDA)(i, j)->fNeighborResDom)){
						if((fMean * fNumWt)>0){
							(*m_pBDA)(i, j)->fNeighborResDom=128.0;
							}
						else{
							(*m_pBDA)(i, j)->fNeighborResDom=-128.0;
							}
						}
					//</Add By Qia on May 4th 2009>
				//<Add By Qia on Dec 03 2008>
				m_pBDA->AftStChg(i,j);
				//</Add by Qia on Dec 03 2008>
		}
				
	}
	
}


/*****************************************************************
Name:		NeighborResDomSample
Types:		uniform, linear, gaussian
Discription:Calculate mean SiteResDomMod for all sites falling within 
			NeighborRadius circular window centered at a given site
*****************************************************************/
//##ModelId=3F01D0EB02D8
void BDA::NeighborResDomSample()
{
	int		iHalfSize;
	float	fSampleMean;
	int		iSampleNum;

	int		i, j;

	iHalfSize = BDA_ROUND(m_fNeighborRadius);

	//cout << "iHalfSize: " << iHalfSize << endl;
	if (iHalfSize == 0)
		errorSys("Neighbor raduis too small, stop.", STOP);

	printf("NeighborResDom(speed up)...\n");
	//boundaries
	i = 1;
	for (j = 1; j <= m_iCol; j++)
		SingleNeighborResDom(i, j, iHalfSize);
	i = m_iRow;
	for (j = 1; j <= m_iCol; j++)
		SingleNeighborResDom(i, j, iHalfSize);

	j = 1;
	for (i = 1; i <= m_iRow; i++)
		SingleNeighborResDom(i, j, iHalfSize);
	j = m_iCol;
	for (i = 1; i <= m_iRow; i++)
		SingleNeighborResDom(i, j, iHalfSize);

	//inside
	for (i = 2; i < m_iRow; i++, i++)
		for (j = 2; j < m_iCol; j++, j++)
			SingleNeighborResDom(i, j, iHalfSize);
			
	for (i = 3; i < m_iRow; i++, i++)
		for (j = 3; j < m_iCol; j++, j++)
			SingleNeighborResDom(i, j, iHalfSize);
		
	//samples
	//cout << "Output NRD before:" << endl;
	for (int m = 1; m <= m_iRow; m++){
		for (int n = 1; n <= m_iCol; n++){
			//cout << (*m_pBDA)(m, n)->fNeighborResDom << " ";
		}
		//cout << endl;
	}
	for (i = 2; i < m_iRow; i++)
	for (j = 2 + (i + 1) % 2; j < m_iCol; j++, j++)
	{
		
		//cout << "in for loop:" << endl;
		//cout << "(" << i << "," << j << ")" << endl;
		fSampleMean = 0.0;
		iSampleNum = 0;
		if ((*m_pBDA)(i, j)->fSiteResDomMod <= 0.0)
			continue;

		if ((*m_pBDA)(i - 1, j)->fSiteResourceDom > 0.0)
		{
			fSampleMean += (*m_pBDA)(i - 1, j)->fNeighborResDom;
			iSampleNum ++;
		}
		if ((*m_pBDA)(i + 1, j)->fSiteResourceDom > 0.0)
		{
			fSampleMean += (*m_pBDA)(i + 1, j)->fNeighborResDom;
			iSampleNum ++;
		}
		if ((*m_pBDA)(i, j - 1)->fSiteResourceDom > 0.0)
		{
			fSampleMean += (*m_pBDA)(i, j - 1)->fNeighborResDom;
			iSampleNum ++;
		}
		if ((*m_pBDA)(i, j + 1)->fSiteResourceDom > 0.0)
		{
			fSampleMean += (*m_pBDA)(i, j + 1)->fNeighborResDom;
			iSampleNum ++;
		}
		if (iSampleNum >= 1){
			//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(i,j);
				//</Add by Qia on Dec 03 2008>
			(*m_pBDA)(i, j)->fNeighborResDom = fSampleMean / iSampleNum;
				//<Add By Qia on Dec 03 2008>
				//<Add By Qia on May 4th 2009>
					if(_isnan((*m_pBDA)(i, j)->fNeighborResDom)){
						if((fSampleMean * iSampleNum)>0){
							(*m_pBDA)(i, j)->fNeighborResDom=128.0;
							}
						else{
							(*m_pBDA)(i, j)->fNeighborResDom=-128.0;
							}
						}
					//</Add By Qia on May 4th 2009>
				m_pBDA->AftStChg(i,j);
				//</Add by Qia on Dec 03 2008>
			}
		else
			SingleNeighborResDom(i, j, iHalfSize);

		
	}

	//cout << "Output NRD after:" << endl;
	for (int m = 1; m <= m_iRow; m++){
		for (int n = 1; n <= m_iCol; n++){
			//cout << (*m_pBDA)(m, n)->fNeighborResDom << " ";
		}
		//cout << endl;
	}

}

/***************************************************************************
Name:	SetOutbreakZone
Input:	enumZoneValue
Description: set the enumOutbreakZone filed of all active sites with a
			 given zone value should be either Nozone, Lastzone, or Newzone
*****************************************************************************/
//##ModelId=3F01D0EC00C3
void BDA::SetOutbreakZone(Zone enumZoneValue)
{
	int	i, j;

	for (i = 1; i <= m_iRow; i++)
		for (j = 1; j <= m_iCol; j++)
		{
			
			if (pBDAsites->locateLanduPt(i, j)->active())		//active sites
				//Original landis4.0: (*pBDAsites)(i, j)->landUnit->active()
				//Changed By Qia on Oct 13 2008
			{
				//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(i,j);
				//</Add by Qia on Dec 03 2008>
				(*m_pBDA)(i, j)->enumOutbreakZone = enumZoneValue;
				//<Add By Qia on Dec 03 2008>
				m_pBDA->AftStChg(i,j);
				//</Add by Qia on Dec 03 2008>
			}
			
		}
}


/***********************************************************************
Name:	SiteVulnerability
Input:	bNeighbor: neighbor flag, 1 consider neighbors, 0 dont consider
Description: calculate the SiteVulnerability of a site

************************************************************************/
//##ModelId=3F01D0EB02E6
void BDA::SiteVulnerability(bool bNeighbor,int itr)  
{
	int		i, j;
	float	fSRD, fSRDMod, fTemp;	
	float	fCaliROS3 = ((float)m_iROS / 4) * m_fSVCalibrator; //added by Cheney on Apr 11th,2018
	float	fCali3 = 0.25 * m_fSVCalibrator;

	//printf("SiteVulnerability...\n");

	//cout << "FSV in SiteVulnerability" << endl;

	if (bNeighbor)		//take neigborhood into consideration
	{
		for (i = 1; i <= m_iRow; i++)
		{
			for (j = 1; j <= m_iCol; j++)
			{
				
				fSRD = (*m_pBDA)(i, j)->fSiteResourceDom;
				fSRDMod = (*m_pBDA)(i, j)->fSiteResDomMod;
				//cout << "fSRDMod (" << i << "," << j << "): " << fSRDMod << endl;
				//cout << "fSRD (" << i << "," << j << "): " << fSRD << endl;
				//cout << "n_NRD (" << i << "," << j << "): " << (*m_pBDA)(i, j)->fNeighborResDom << endl;
				//cout << "outbreakzone (" << i << "," << j << "): " << (*m_pBDA)(i, j)->enumOutbreakZone << endl;

				if (((*m_pBDA)(i, j)->enumOutbreakZone == Newzone) && fSRD > 0)
				{
					//(*m_pBDA)(i, j)->fNeighborResDom; added by Cheney on Mar 2018
					fTemp = fSRDMod + (*m_pBDA)(i, j)->fNeighborResDom * m_fNeighborWeight;
					//cout << "fTemp:" << fTemp << endl;
					//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(i,j);
				//</Add by Qia on Dec 03 2008>
					(*m_pBDA)(i, j)->fSV = (float)(fCaliROS3 * fTemp / (1.0 + m_fNeighborWeight));
				//added by Cheney on Apr 2018
					int tmpAdd=*(pafScanline2 + (i - 1)*m_iCol + j - 1);
					int add = ecoArr[tmpAdd - 1][itr-1];
					float deltapu = 1 / (1 + exp(-r*(add - m)));
					//cout << "Pu: " << deltapu << endl;
					float v = 0.5 + 0.5*deltapu;
					//cout << "The probability of univoltine (v):  " << v << endl;
					double tmpfSV = (float)(fCali3 *v* fTemp / (1.0 + m_fNeighborWeight));
					(*m_pBDA)(i, j)->fSV += (float)(fCali3 *v* fTemp / (1.0 + m_fNeighborWeight));
				//<Add By Qia on May 4th 2009>
					if(_isnan((*m_pBDA)(i, j)->fSV)){

						if(fCaliROS3 * fTemp * (1.0 + m_fNeighborWeight)>0){

							(*m_pBDA)(i, j)->fSV=128.0;
							}
						else{
							(*m_pBDA)(i, j)->fSV=-128.0;
							}
						}
					//</Add By Qia on May 4th 2009>
				//<Add By Qia on Dec 03 2008>
				
				m_pBDA->AftStChg(i,j);
				//</Add by Qia on Dec 03 2008>
				}
				else {
					//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(i,j);
				//</Add by Qia on Dec 03 2008>
					(*m_pBDA)(i, j)->fSV = 0;
				//<Add By Qia on Dec 03 2008>
				m_pBDA->AftStChg(i,j);
				//</Add by Qia on Dec 03 2008>
					}
				//cout << "FSV neigborhood true: (" << i << "," << j << ") " << (*m_pBDA)(i, j)->fSV << endl;
				
			}
		}
	}
	else		//don't take neigborhood into consideration
	{
		for (i = 1; i <= m_iRow; i++)
		{
			for (j = 1; j <= m_iCol; j++)
			{
				//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(i,j);
				//</Add by Qia on Dec 03 2008>
				fSRD = (*m_pBDA)(i, j)->fSiteResourceDom;  //-128; 0.66
				fSRDMod = (*m_pBDA)(i, j)->fSiteResDomMod;  //-9; 0.66

				if (fSRD > 0)
					(*m_pBDA)(i, j)->fSV =  fCaliROS3 * fSRDMod;
				else
					(*m_pBDA)(i, j)->fSV = -1.0;//<Add By Qia on Dec 03 2008>
					
				m_pBDA->AftStChg(i, j);//</Add by Qia on Dec 03 2008>

				//cout << "FSV neigborhood false: (" << i << "," << j << ") " << (*m_pBDA)(i, j)->fSV << endl;
			}
		}
	}
	//	dump(16);
}


/*****************************************************************
Name: DisturbSite
Input:
Description: disturb a site if it has a severity between 1 to 3
*****************************************************************/
//##ModelId=3F01D0EB02F5
void BDA::DisturbSite()
{
	int		i, j, k, max, iTreeNumber, totalAge;
	int count70;
	double tmpBiomass, tmpCarbon;
	float	fSV;
	SPECIE*	SP;
	float	fRN;
	int num;

	printf("DisturbSite...\n\n");
	//	srand( (unsigned)time( NULL ) );	//by ver Nov. 24, comment it for reapeat result
	//	srand( 1 );
	if (m_ifBDArepeat == 0)  //0: random and not repeat; 1: repeat   modifiied by Wei Li, 2004
		srand((unsigned)time(NULL));

	for (i = 1; i <= m_iRow; i++)
	{
		for (j = 1; j <= m_iCol; j++)
		{
			//<Add By Qia on Nov 26 2008>
			pBDAsites->BefStChg(i, j);
			//</Add By Qia on Nov 26 2008>


			//<Add By Qia on Dec 03 2008>
			m_pBDA->BefStChg(i, j);
			//</Add by Qia on Dec 03 2008>

			(*m_pBDA)(i, j)->iDisturbSeverity = 0;  //initialize to be zone

			//cout << "index(" << i << " , " << j << " ): " << endl;

			//cout << "check Newzone: " << (*m_pBDA)(i, j)->enumOutbreakZone << endl;

			//cout << "check SRD: " << (*m_pBDA)(i, j)->fSiteResourceDom << endl;


			//for (int m = 1; m < 6; m++){

			//	iTreeNumber = ((*(*pBDAsites)(i, j))(1))->getTreeNum(m * 10 / m_iTimeStep, 1); // added on March 31 2016

			//	cout << "tree number before " << m * 10 << " age, tree number: " << iTreeNumber << endl;
			//}
			//cout << "check zone number: " << (*m_pBDA)(i, j)->enumOutbreakZone << endl;

			if ((*m_pBDA)(i, j)->fSiteResourceDom > 0 && (*m_pBDA)(i, j)->enumOutbreakZone == Newzone) // (*m_pBDA)(i, j)->enumOutbreakZone == Newzone &&
			{
				fSV = (*m_pBDA)(i, j)->fSV;

				//cout << "FSV (" << i << " , " << j << " ): " << fSV << endl;

				fRN = (float)(frandrand() % 100) / 100;

				//cout << "random number FRN: " << fRN << endl;

				if (fSV > fRN)			//UniformRandomNum cut out! if (fSV > RandomNumber())
				{

					if (fSV <= intensityThre1)
				{
					for (k = 1; k <= pBDAspeciesAttrs->number(); k++)
					{
						SP = (*(*pBDAsites)(i, j))(k);

						//cout << "oldest tree: " << SP->oldest() << endl; // return age

						//for (int m = 1; m < 6; m++){

						//	iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(m * 10 / m_iTimeStep, k); // added on March 31 2016

						//	cout << "age: " << m * 10 << " tree number before: " << iTreeNumber << endl;
						//}

						if (SP->oldest() > 0)	//have species
						{
							max = (*pBDAspeciesAttrs)(k)->longevity;

							//cout << "VulnerableHostAg: " << VulnerableHostAge[k - 1] << endl;

							//cout << "max: " << max << endl;

							if (VulnerableHostAge[k - 1] <= max) // && SP->oldest() >= VulnerableHostAge[k-1])
							{
								// if TolerantPercentage == 999, kill all trees
								if ((abs(VulnerablePercentage[k - 1] -999))<0.1){

									num = SP->getTimeStep();

									for (int d = 10; d <= max; d += num){

										iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

										//cout << " age : " << d << " tree number BDA_SEVERITY_1 before kill 999: " << iTreeNumber << endl;  //important checkpoint

									}

									SP->kill(VulnerableHostAge[k - 1], max);

									for (int d = 10; d <= max; d += num){

										iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

										//cout << " age : " << d << " tree number BDA_SEVERITY_1 after kill 999: " << iTreeNumber << endl;   //important checkpoint

									}
								}
								else{

									num = SP->getTimeStep();

									//kill severity level 1; added on April 5th 2016 by Nancy
									for (int d = VulnerableHostAge[k - 1]; d <= max; d += num){

										iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

										//cout << " age : " << d << " tree number SEVERITY_1 before kill: " << iTreeNumber << endl;   //important checkpoint

										SP->setTreeNum(d / m_iTimeStep, k, round((1 - VulnerablePercentage[k - 1])*iTreeNumber));

										iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

										//cout << " age : " << d << " tree number SEVERITY_1 after kill: " << iTreeNumber << endl;  //important checkpoint
									}
								}
									

									
									

									for(count70=VulnerableHostAge[k-1];count70<=max;count70+=pBDAsites->TimeStep_BDA){

										tmpBiomass=exp(pBDAsites->GetBiomassData((*pBDAspeciesAttrs)(k)->BioMassCoef,1)+pBDAsites->GetBiomassData((*pBDAspeciesAttrs)(k)->BioMassCoef,2)*log(pBDAsites->GetGrowthRates(k,count70/pBDAsites->TimeStep,pBDAsites->locateLanduPt(i,j)->ltID)))*((*pBDAsites) (i,j)->SpecieIndex(k)->getTreeNum(count70/pBDAsites->TimeStep,k))/1000.00;

										pBDAsites->BDA70outputIncreaseBiomassvalue(i,j,tmpBiomass);

										tmpCarbon=exp(pBDAsites->GetBiomassData((*pBDAspeciesAttrs)(k)->BioMassCoef,1)+pBDAsites->GetBiomassData((*pBDAspeciesAttrs)(k)->BioMassCoef,2)*log(pBDAsites->GetGrowthRates(k,count70/pBDAsites->TimeStep,pBDAsites->locateLanduPt(i,j)->ltID)))*(*pBDAsites) (i,j)->SpecieIndex(k)->getTreeNum(count70/pBDAsites->TimeStep,k);
										
										pBDAsites->BDA70outputIncreaseCarbonvalue(i,j,tmpCarbon*(*pBDAspeciesAttrs)(k)->CarbonCoEfficient);
									}
									(*m_pBDA)(i, j)->iDisturbSeverity = 1;
						
								}

							}
						}
					}	//end of SEVERITY 1
					else if (fSV <= intensityThre2) //iSeverityIndex = 2
					{
						for (k = 1; k <= pBDAspeciesAttrs->number(); k ++)
						{
							SP = (*(*pBDAsites)(i, j))(k);

							if (SP->oldest() > 0)	//have species
							{
								max = (*pBDAspeciesAttrs)(k)->longevity;

								if (Toleranthostage[k-1] <= max && SP->oldest() >= Toleranthostage[k-1])
								{
									// if TolerantPercentage == 999, kill all trees

									//cout << "test: " << abs(TolerantPercentage[k - 1] - 999) << endl;   //important checkpoint

									if ((abs(TolerantPercentage[k - 1] - 999)) < 0.1){

										num = SP->getTimeStep();

										for (int d = 10; d <= max; d += num){

											iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

											//cout << " age : " << d << " tree number BDA_SEVERITY_2 before kill 999: " << iTreeNumber << endl;  //important checkpoint

										}
										SP->kill(Toleranthostage[k - 1], max);

										for (int d = 10; d <= max; d += num){

											iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

											//cout << " age : " << d << " tree number BDA_SEVERITY_2 after kill 999: " << iTreeNumber << endl;  //important checkpoint

										}
									
									}
									else{

										num = SP->getTimeStep();//added on April 5th 2016 by Nancy

										//kill severity level 2; added on April 5th 2016 by Nancy
										for (int d = Toleranthostage[k - 1]; d <= max; d += num){

											iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

											//cout << " age : " << d << " tree number BDA_SEVERITY_2 before kill: " << iTreeNumber << endl;   //important checkpoint

											SP->setTreeNum(d / m_iTimeStep, k, round((1 - TolerantPercentage[k - 1])*iTreeNumber));

											iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

											//cout << " age : " << d << " tree number BDA_SEVERITY_2 after kill: " << iTreeNumber << endl;   //important checkpoint
										}
									}

									(*m_pBDA)(i, j)->iDisturbSeverity = 2;
								}
							}
						}
					}	//end of SEVERITY 2
					else if (fSV > intensityThre2) ////iSeverityIndex = 3
					{
						for (k = 1; k <= pBDAspeciesAttrs->number(); k ++)
						{
							SP = (*(*pBDAsites)(i, j))(k);

							if (SP->oldest() > 0)	//have species
							{
								max = (*pBDAspeciesAttrs)(k)->longevity;

								if (ResistantHostAge[k-1] <= max && SP->oldest() >= ResistantHostAge[k-1])
								{
									
									//for (int m = 1; m < 10; m++){

									//	iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(m * 10 / m_iTimeStep, k); // added on March 31 2016

									//	cout << "age: " << m * 10 << " tree number before: " << iTreeNumber << endl;
									//}

									// if TolerantPercentage == 999, kill all trees
									if ((abs(TolerantPercentage[k - 1] - 999)) < 0.1){

										num = SP->getTimeStep();

										for (int d = 10; d <= max; d += num){

											iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

											//cout << " age : " << d << " tree number BDA_SEVERITY_3 before kill 999: " << iTreeNumber << endl;  //important checkpoint

										}
										SP->kill(ResistantHostAge[k - 1], max);

										for (int d =10; d <= max; d += num){

											iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

											//cout << " age : " << d << " tree number BDA_SEVERITY_3 after kill 999: " << iTreeNumber << endl;  //important checkpoint

										}
									}
									else{

										num = SP->getTimeStep();//added on April 5th 2016 by Nancy

										//kill severity level 3; added on April 5th 2016 by Nancy
										for (int d = ResistantHostAge[k - 1]; d <= max; d += num){

											iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

											//cout << " age : " << d << " tree number  BDA_SEVERITY_3 before kill: " << iTreeNumber << endl;  //important checkpoint

											SP->setTreeNum(d / m_iTimeStep, k, round((1 - ResistantPercentage[k - 1])*iTreeNumber));

											iTreeNumber = ((*(*pBDAsites)(i, j))(k))->getTreeNum(d / m_iTimeStep, k);

											//cout << " age : " << d << " tree number BDA_SEVERITY_3 after kill: " << iTreeNumber << endl;  //important checkpoint
										}
									}
									
									(*m_pBDA)(i, j)->iDisturbSeverity = 3;
								}
							}
						
						}
					}//end of SEVERITY 3
				}
			}

			
			//<Add By Qia on Dec 03 2008>
			m_pBDA->AftStChg(i,j);
			//</Add by Qia on Dec 03 2008>

			//<Add By Qia on Nov 26 2008>
			pBDAsites->AftStChg(i,j);
			//</Add By Qia on Nov 26 2008>
}//end of j loop
	}// end of i loop

}//end of function



// update PDP
void BDA::UpdatePDP()
{
	int i, j;

	strcpy ((m_pPDP->pBDAPDP[m_iBDANo]).BDAType, m_strName);
	
	for (i = 1; i < m_iRow; i++)
		for (j = 1; j < m_iCol; j++)
		{
			(m_pPDP->pBDAPDP[m_iBDANo]).cBDASeverity[i][j] = (*m_pBDA)(i, j)->iDisturbSeverity;
			if ((*m_pBDA)(i, j)->iDisturbSeverity == 0)
				(m_pPDP->pBDAPDP[m_iBDANo]).sTSLBDA[i][j] += pBDAsites->TimeStep_BDA;
			else
				(m_pPDP->pBDAPDP[m_iBDANo]).sTSLBDA[i][j] = 0;
		}
}



/*********************************************************************************************
Name:			NewEpicenters
Description: 1. Inputs: two coefficents: BreakzoneCoeff, NobreakzoneCoeff, and Last NewEpicenters List
		  2. Calulate the # of trials inside Last Outbreakzone A at this step
		  3. Calulate the # of trials out side of Last Outbreakzone B at this step
		  4. Randomly generate up to A number of newEpicenters inside last outbreak zone using 
		     Fire ignition algorithm based on BreakzoneCoeff
		  5. Randomly generate up to B number of newEpicenters outside last outbreak zone using 
		     Fire ignition algorithm based on NobreakzoneCoeff
		  6. Save all the new epicenters to Last NewEpicenters List
**********************************************************************************************/

//##ModelId=3F01D0EB02F6
void BDA::NewEpicenters()
{
	char**	pWindow;
	int		iWindowSize;
	int		i, j, k, k0, k1, k2;
	int		 s0, s1, w0, w1;
	int		w_x0, w_y0, w_x1, w_y1, s_x0, s_y0, s_x1, s_y1;
	int		iMaxIn;	//max qualified sites as newEpicenter inside outbreakzone
	int		iMaxOut;//max qualified sites as newEpicenter inside outbreakzone
	int		iMaxInExamed;
	int		iMaxOutExamed;
	int		iOldEpicenterNum;
	int*	pOldList;
	bool	bFirstIteration;

	bFirstIteration = false;
	//printf("NewEpicenters...\n");
	iOldEpicenterNum = m_uiEpicenterNum;

	//cout << "m_iRow: " << m_iRow << endl;
	//cout << "m_iCol: " << m_iCol << endl;
	if (m_pEpiList == NULL)	//the first time to run this
	{
		bFirstIteration = true;
		m_pEpiList = (int*)malloc(BDA_MAX_LISTLENGTH * sizeof(int) * 2);
		
		//randomly generate new epicenters
		for (k = 0; k < iOldEpicenterNum; k ++) // may generate cell at the same place
		{
			i = frandrand()%m_iRow + 1; // random generate index of cell
			j = frandrand()%m_iCol + 1;
			m_pEpiList[2*k] = i;
			m_pEpiList[2*k+1] = j; //m_pEpiList: index of cell

			//cout << "Type 1 of Epicenter: (" << i << " , " <<j <<  " ) " << endl;
		}
	}

	//cout << "m_pEpiList after Type 1" << endl;
	for (int s = 0; s < 30; s++){
		//cout << m_pEpiList[s] << " ";
	}
	//cout << endl;

	pOldList = (int*)malloc(iOldEpicenterNum * sizeof(int) * 2);
	memcpy(pOldList, m_pEpiList, iOldEpicenterNum * 2*sizeof(int));

	if (m_iDispersalTemplate == 0)
	{
		iWindowSize = m_iDispersalRate * 2 + 1;
		pWindow = WindowChar(iWindowSize, 1); //epicenter template
		WindowCharBoundary(pWindow, iWindowSize, (float)m_iDispersalRate, true);
	}	
	//generate outbreakZone map
	for (k = 0; k < iOldEpicenterNum; k ++)
	{
		i = pOldList[2 * k];
		j = pOldList[2 * k + 1];

		//cout << "epicenter for Lastzone (" << i << " , " << j << ") " << endl;

		if (m_iDispersalTemplate != 0)
			DispersalRegion(i, j, m_iDispersalRate, m_pDilation, Lastzone);
		else
		{
			WindowCoordinates(i, j, m_iDispersalRate, &s_x0, &s_y0, &s_x1, &s_y1, &w_x0, &w_y0, &w_x1, &w_y1);

			for (s0 = s_x0, w0 = w_x0; s0 <= s_x1, w0 <= w_x1; s0++, w0++)
				for (s1 = s_y0, w1 = w_y0; s1 <= s_y1, w1 <= w_y1; s1++, w1++)
				{
					if (pWindow[w0][w1] == 1){
						//<Add By Qia on Dec 03 2008>
						m_pBDA->BefStChg(s0,s1);
						//</Add by Qia on Dec 03 2008>
						(*m_pBDA)(s0, s1)->enumOutbreakZone = Lastzone;		//last outbreakzone
						//<Add By Qia on Dec 03 2008>
						m_pBDA->AftStChg(s0,s1);
						//</Add by Qia on Dec 03 2008>
						}
				}
		}
	}
	//generate new Epicenter // type2:
	m_uiEpicenterNum = 0;
	iMaxIn = 0;
	iMaxOut = 0;
	iMaxInExamed = 0;
	iMaxOutExamed = 0;

	//count # of qualified potential new epicenters
	for (i = 1; i <= m_iRow; i++)
	{
		for (j = 1; j <= m_iCol; j++)
		{
			if ((*m_pBDA)(i, j)->fSV > m_fEpidemicThresh) //potential new epicenter
			{
				if ((*m_pBDA)(i, j)->enumOutbreakZone == Lastzone) 
					iMaxIn ++;		//potential new epicenter inside lastOutBreakZone
				else											
					iMaxOut++;		//potential new epicenter outside lastOutBreakZone
				 
			}
		}
	}
	//cout << "potential new epicenters: " << endl;
	//cout << "iMaxIn: " << iMaxIn << "   iMaxOut: " << iMaxOut << endl;
//	srand( (unsigned)time( NULL ) );	//by ver Nov. 24, comment it for reapeat result
//	srand(1);
	if (m_ifBDArepeat == 0)  //0: random and not repeat; 1: repeat // parameter.dat NO.12 random seed
		srand( (unsigned)time( NULL ) );

	i = frandrand()%m_iRow + 1;
	j = frandrand()%m_iCol + 1;

	//for SeedEpicenters
	if (m_bSeedEpicenter)
	{
		while ((iMaxOutExamed < iMaxOut) && (iMaxOut > 0))
		{
			if ((*m_pBDA)(i, j)->fSV > m_fEpidemicThresh)  //qualified 
			{
				//cout << "iMaxOut before (" << i << ", " << j << "): " << iMaxOut << endl;//Shawn
				iMaxOut = (int)((float)iMaxOut * exp(-1.0 * m_fNonOutbreakCoeff * m_uiEpicenterNum));
				//cout << "iMaxOut after (" << i << ", " << j << "): " << iMaxOut << endl;//Shawn
				iMaxOutExamed = 0;						
				m_pEpiList[m_uiEpicenterNum * 2] = i;
				m_pEpiList[m_uiEpicenterNum * 2 + 1] = j;
				m_uiEpicenterNum ++;
			}
			else	//unqualified site
			{
				iMaxOutExamed ++;
			}
			i = frandrand()%m_iRow + 1;
			j = frandrand()%m_iCol + 1;
		}
	}

	//cout << "m_pEpiList after Type 2" << endl;
	for (int s = 0; s < 30; s++){
		//cout << m_pEpiList[s] << " ";
	}
	//cout << endl;


	//for ZoneEpicenters
	while ((iMaxInExamed < iMaxIn)  && (iMaxIn > 0)) //ZoneEpicenters
	{
		int sign;
		//randomly generate index (i,j)
		k0 = frandrand() % iOldEpicenterNum;	//chose the kth last new Epicenter

		sign = frandrand() % 2;  // randomly generate positive or negative sign
		if (sign == 0)
			sign = -1;
		k1 = sign * (frandrand() % m_iDispersalRate + 1);

		sign = frandrand() % 2;
		if (sign == 0)
			sign = -1;
		k2 = sign * (frandrand() % m_iDispersalRate + 1);

		i = pOldList[2 * k0] + k1;
		j = pOldList[2 * k0 + 1] + k2;

		if (i <= 0) 
			i = 1;
		else if ( i > m_iRow)
			i = m_iRow;

		if (j <= 0)
			j = 1;
		else if (j > m_iCol)
			j = m_iCol; 

		//cout << "random generate index: " << i << " , " << j << endl;

		if ((*m_pBDA)(i, j)->enumOutbreakZone == Lastzone)
		{
			if ((*m_pBDA)(i, j)->iDisturbSeverity > 0 || bFirstIteration)	//be disturbed last time step
			{
				//cout << "iMaxIn befor (" << i << ", " << j << "): " << iMaxIn << endl;//Shawn
				iMaxIn = (int)((float)iMaxIn * exp(-1.0 * m_fOutbreakCoeff * m_uiEpicenterNum));
				//cout << "iMaxIn after (" << i << ", " << j << "): " << iMaxIn << endl;
				iMaxInExamed = 0;
				m_pEpiList[m_uiEpicenterNum * 2] = i;
				m_pEpiList[m_uiEpicenterNum * 2 + 1] = j;
				m_uiEpicenterNum ++;
			}
			else
				iMaxInExamed ++;
		}
	}
	
	//cout << "m_pEpiList after Type 3" << endl;
	for (int s = 0; s < 30; s++){
		//cout << m_pEpiList[s] << " ";
	}
	//cout << endl;

	//Generate new outbreak zone
	for (k = 0; k < (int)m_uiEpicenterNum; k ++)
	{
		i = m_pEpiList[2 * k];
		j = m_pEpiList[2 * k + 1];
		
		//cout << "epicenter for Newzone (" << i << " , " << j << ") " << endl;

		if (m_iDispersalTemplate != 0)
			DispersalRegion(i, j, m_iDispersalRate, m_pDilation, Newzone);
		else
		{
			WindowCoordinates(i, j, m_iDispersalRate, &s_x0, &s_y0, &s_x1, &s_y1, &w_x0, &w_y0, &w_x1, &w_y1);

			for (s0 = s_x0, w0 = w_x0; s0 <= s_x1, w0 <= w_x1; s0++, w0++)
				for (s1 = s_y0, w1 = w_y0; s1 <= s_y1, w1 <= w_y1; s1++, w1++)
				{
					if (pWindow[w0][w1] == 1)
						//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(s0,s1);
				//</Add by Qia on Dec 03 2008>
						(*m_pBDA)(s0, s1)->enumOutbreakZone = Newzone;
				//<Add By Qia on Dec 03 2008>
				m_pBDA->AftStChg(s0,s1);
				//</Add by Qia on Dec 03 2008>
				}
		}
	}

	if (pOldList != NULL)
		free (pOldList);
	if (m_iDispersalTemplate == 0)
		WindowCharFree(pWindow, iWindowSize);
}

/*****************************************************************
Name:	     DispersalRegion
Input:		 List: list of new epicenters
Description: Generate outbreakzone based on new epicenters, note that
the outbreakzone may not necessarily be a perfect circle
*****************************************************************/
//##ModelId=3F01D0EB02F7
void BDA::DispersalRegion(int iX, int iY, int iRadius, Dilation* d, Zone zone)
{
	int		iSize, tx, ty, i, j;
	Delta*	elem;
    ListNode*	pNode;

	for (i = 1; i <= m_iRow; i++)
		for (j = 1; j <= m_iCol; j++)	{
			//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(i,j);
				//</Add by Qia on Dec 03 2008>
			(*m_pBDA)(i, j)->cDispersal = 0;
				//<Add By Qia on Dec 03 2008>
				m_pBDA->AftStChg(i,j);
				//</Add by Qia on Dec 03 2008>
			}

	PosList* pList = new PosList();
	pList->ListAppend(iX, iY);
	//cout << " start (" << iX << "," << iY << ")" << endl;

	while (!pList->ListEmpty())
	{
		
		pNode = (ListNode*)pList->ListRemoveHead();
		//<Add By Qia on Dec 03 2008>
				m_pBDA->BefStChg(pNode->x,pNode->y);
				//</Add by Qia on Dec 03 2008>
		(*m_pBDA)(pNode->x, pNode->y)->cDispersal = 2;
		(*m_pBDA)(pNode->x, pNode->y)->enumOutbreakZone = zone;
		
		//cout << " newzone or lastzone: " << zone;
		//cout << " (" << pNode->x << " , " << pNode->y << " ) " << endl;
		//<Add By Qia on Dec 03 2008>
				m_pBDA->AftStChg(pNode->x,pNode->y);
				//</Add by Qia on Dec 03 2008>
		for (iSize = d->size, elem = d->elem; iSize--;)
		{
			tx = pNode->x + elem->dx;
			ty = pNode->y + elem->dy;
			 
			elem++;
			//check if site(tx, ty) inside map and dispersal circle
			if ((tx <= m_iRow) && (tx > 0) && (ty <= m_iCol) && (ty > 0))
			{
				if ((*m_pBDA)(tx, ty)->cDispersal == 0) //not dilated yet
				{
					if (sqrt(pow(fabs((float)iX - (float)tx), 2.0f) + pow(fabs((float)iY - (float)ty), 2.0f)) <= (float)iRadius)
					{
						if((*m_pBDA)(tx, ty)->bDeadArea == false)  //actvie site
						{
							pList->ListAppend(tx, ty);
							//<Add By Qia on Dec 03 2008>
							m_pBDA->BefStChg(tx,ty);
							//</Add by Qia on Dec 03 2008>
							(*m_pBDA)(tx, ty)->cDispersal = 1;
							//<Add By Qia on Dec 03 2008>
							m_pBDA->AftStChg(tx,ty);
							//</Add by Qia on Dec 03 2008>
						}//end of active site
					}
				}//end of dilated check
			}//end of inside check
		}

	}//list empty
	pList->ListDestroyAll();
}

//##ModelId=3F01D0EC00F3
Dilation* BDA::DilationNew(int size, Delta *elem)
{
	Dilation*	d;
    Delta*	e;
    int		i;

    if ((d = (Dilation*)malloc(sizeof(Dilation))) != NULL)
    {
        if ((e = (Delta*)malloc(size * sizeof(Delta))) != NULL)
        {
            for (i = 0; i < size; i++)
            {
                e[i].dx = elem[i].dx;
                e[i].dy = elem[i].dy;
            }
            d->size = size;
            d->elem = e;
            return d;
        }
        free(d);
    }
	return NULL;
}

//##ModelId=3F01D0EC0111
void BDA::DilationFree(Dilation* d)
{
	free(d->elem);
    free(d);
}

/*****************************************************************
Name:	     Window
Input:		 iSize:		size of the Window
			 fInitial:	initial values 
Description: allocate a 2-D array with give size and initiate it with
			 given float value: fInitial
*****************************************************************/
//##ModelId=3F01D0EB0372
float** BDA::Window(int iSize)
{
	float**	fWindow;
	int		i;
					 
	fWindow = (float**)malloc(iSize*sizeof(float*));
	for (i = 0; i < iSize; i ++)
		fWindow[i] = (float*)malloc(iSize * sizeof(float));

	return	fWindow;
}

/*****************************************************************
Name: WindowBoundary
Input:	fWindow:	sliding window
		iSize:		size of the sliding window
		fRadius:	epidemic radius
		b_Uniform:	Unifrom window or not
Description: set the area outside of circule (define by the center of the window
             and fRadius) to be 0
*****************************************************************/
//##ModelId=3F01D0EB03C1
float** BDA::WindowBoundary(float** fWindow, int iSize, float fRadius, NeighborShape enumShape) // Calculate weight
{
	int	iBoundary, i, j;
	int	iCenter = (iSize - 1) / 2;		//find the center coordinates of the window
	int	iDist, iMeanDist, iDistStd;		//distance, mean distance and standard deviation 

	for (j = 0; j <= iCenter; j ++)
	{
		iBoundary = 0;

		while (Distance(iCenter, iCenter, iBoundary, j) > fRadius)
			iBoundary ++;

		for (i = 0; i < iBoundary; i++)
		{
			fWindow[i][j] = 0.0;
			fWindow[iSize - 1 - i][j] = 0.0;
			fWindow[i][iSize - 1 - j] = 0.0;
			fWindow[iSize - 1 - i][iSize - 1 - j] = 0.0;
		}

		if (enumShape == uniform)
		{
			for (i = iBoundary; i <= iCenter; i ++)
			{
				fWindow[i][j] = 1.0;
				fWindow[iSize - 1 - i][j] = 1.0;
				fWindow[i][iSize - 1 - j] = 1.0;
				fWindow[iSize - 1 - i][iSize - 1 - j] = 1.0;
				//cout << "uniform" << endl;
				//cout << "weight position: (" << i << ", " << j << ")" << endl;    //important checkpoint
				//cout << "weight position: (" << iSize - 1 - i << ", " << j << ")" << endl;    //important checkpoint
				//cout << "weight position: (" << i << ", " << iSize - 1 - j << ")" << endl;   //important checkpoint
				//cout << "weight position: (" << iSize - 1 - i << ", " << iSize - 1 - j << ")" << endl;   //important checkpoint
			}
		}
		else if (enumShape == linear)
		{
			for (i = iBoundary; i <= iCenter; i ++)
			{
				fWindow[i][j] = 1 - (Distance(iCenter, iCenter, i, j) / fRadius);
				fWindow[iSize - 1 - i][j] = fWindow[i][j];
				fWindow[i][iSize - 1 - j] = fWindow[i][j];
				fWindow[iSize - 1 - i][iSize - 1 - j] = fWindow[i][j];

				//cout << "linear" << endl;
				//cout << "weight position: (" << i << ", " << j << "): " << 1 - (Distance(iCenter, iCenter, i, j) / fRadius)<< endl;  //important checkpoint
				//cout << "weight position: (" << iSize - 1 - i << ", " << j << "): " << fWindow[i][j] <<endl;  //important checkpoint
				//cout << "weight position: (" << i << ", " << iSize - 1 - j << "): " << fWindow[i][j]<< endl;   //important checkpoint
				//cout << "weight position: (" << iSize - 1 - i << ", " << iSize - 1 - j << "): " << fWindow[i][j]<< endl;   //important checkpoint
				//cout << "Distance" << Distance(iCenter, iCenter, i, j) << endl;
			}
		}
		else if (enumShape == gaussian)
		{
			iMeanDist = (int)Distance(iCenter, iCenter, iCenter / 2, iCenter / 2);
			for (i = iBoundary; i <= iCenter; i ++)
			{
				iDist = (int)Distance(iCenter, iCenter, i, j);
				iDistStd = iDist - iMeanDist;
				
				fWindow[i][j] = (float)exp(0.0 - pow((float)iDist, 2.0f) / (2 * pow((float)iDistStd, 2.0f)));
				fWindow[iSize - 1 - i][j] = fWindow[i][j];
				fWindow[i][iSize - 1 - j] = fWindow[i][j];
				fWindow[iSize - 1 - i][iSize - 1 - j] = fWindow[i][j];

				//cout << "gaussian" << endl;
				//cout << "weight position: (" << i << ", " << j << "): " <<fWindow[i][j] << endl;   //important checkpoint
				//cout << "weight position: (" << iSize - 1 - i << ", " << j << "): " << fWindow[i][j] << endl;   //important checkpoint
				//cout << "weight position: (" << i << ", " << iSize - 1 - j << "): " << fWindow[i][j] << endl;   //important checkpoint
				//cout << "weight position: (" << iSize - 1 - i << ", " << iSize - 1 - j << "): " << fWindow[i][j] << endl;   //important checkpoint
				//cout << "iDist" << iDist << endl;   //important checkpoint
				//cout << "iDistStd" << iDistStd << endl;   //important checkpoint
			}
		}

	}
	return fWindow;
}

/*****************************************************************
Name: WindowCharBoundary
Input:	pcWindow:	sliding window
		iSize:		size of the Window
		fRadius:	epidemic radius
		b_Uniform:	not used in this version
Description: set the area outside of circule (define by the center of the window
             and fRadius) to be 0
*****************************************************************/
//##ModelId=3F01D0EC0007
char** BDA::WindowCharBoundary(char** pcWindow, int iSize, float fRadius, bool b_Uniform)
{
	int	iBoundary, i, j;
	int	iCenter = (iSize - 1) / 2;

	for (j = 0; j < iCenter; j ++)
	{
		iBoundary = 0;

		while (Distance(iCenter, iCenter, iBoundary, j) > fRadius)
			iBoundary ++;

		for (i = 0; i < iBoundary; i++)
		{
			pcWindow[i][j] = 0;
			pcWindow[iSize - 1 - i][j] = 0;
			pcWindow[i][iSize - 1 - j] = 0;
			pcWindow[iSize - 1 - i][iSize - 1 - j] = 0;

		}

	}
	return pcWindow;
}

/*****************************************************************
Name: WindowCoordinates
Input:	
		iOX:	center x
		iOY		center y
		iX
		iY
	 -------	
	|	 ---|----
	|	|///|	 |
	|	|///|	 |
	 ---|---	 |
		|		 |
		 --------
Description: calcualte the coordinates of 4 corners of a rectangular
			 formed by the overlapping area of two rectangulars
*****************************************************************/
//##ModelId=3F01D0EC0028
void BDA::WindowCoordinates(int i, int j, int iRadius, int* s_x0, int* s_y0, int* s_x1, int* s_y1, int* w_x0, int* w_y0, int* w_x1, int* w_y1)
{
		*s_x0 = ((i - 1 - iRadius) < 0)? 1: i - iRadius;	//site x, y
		*s_y0 = ((j - 1 - iRadius) < 0)? 1: j - iRadius;
		*s_x1 = ((i + iRadius) <= m_iRow)? i + iRadius:m_iRow;
		*s_y1 = ((j + iRadius) <= m_iCol)? j + iRadius:m_iCol;

		*w_x0 = iRadius + *s_x0 - i; //window template x, y
		*w_y0 = iRadius + *s_y0 - j;
		*w_x1 = iRadius + *s_x1 - i;
		*w_y1 = iRadius + *s_y1 - j;
}

/*****************************************************************
Name: Distance
Input:	
		iOX:	center x
		iOY		center y
		iX		site x
		iY      site y
Description: calcualte the distance between two given points
*****************************************************************/
//##ModelId=3F01D0EC0084
float BDA::Distance(int iOX, int iOY, int iX, int iY)
{
	return (float)sqrt(pow(fabs((float)iX - (float)iOX) - 0.5f, 2.0f) + pow(fabs((float)iY - (float)iOY) - 0.5f, 2.0f));

}


/*****************************************************************
Name: WindowFree
Input:	
Description: free 2-D float array
*****************************************************************/
//##ModelId=3F01D0EB0393
void BDA::WindowFree(float** fWindow, int iWindowSize)
{
	int	i;
	for (i = 0; i < iWindowSize; i++)
		free(fWindow[i]);
	free(fWindow);
}


/*****************************************************************
Name:	WindowChar
Input:	iSize:		size of the Window
		iInital:	initial value
Description: allocate a 2-D array with give size and initiate it with
			 given char value: cInitial
*****************************************************************/
//##ModelId=3F01D0EB0382
char** BDA::WindowChar(int iSize, char cInitial)
{
	char**	cWindow;
	int		i, j;
					 
	cWindow = (char**)malloc(iSize * sizeof(char*));
	for (i = 0; i < iSize; i ++)
		cWindow[i] = (char*)malloc(iSize * sizeof(char));

	for (i = 0; i < iSize; i ++)
		for (j = 0; j < iSize; j ++)
			cWindow[i][j] = cInitial;

	return	cWindow;
}

/*****************************************************************
Name:	WindowCharFree
Input:	cWindow
		iWinSize: size of the window	
Description: free 2-D array
*****************************************************************/
//##ModelId=3F01D0EB03B1
void BDA::WindowCharFree(char** cWindow, int iWinSize)
{
	int	i;
	for (i = 0; i < iWinSize; i++)
		free(cWindow[i]);
	free(cWindow);
}


/*****************************************************************
Name:			WindowFloatTemplate
Input:
Output:			m_pfSlidingWindow	
Description:	set the sliding window tempalte used for calculating
				the neighborhood weight
*****************************************************************/
//##ModelId=3F01D0EB0363
float** BDA::WindowFloatTemplate()
{

	int		iHalfSize;
	float**	fWindow;
	
//	printf("WindowFloatTemplate...\n");

	iHalfSize = BDA_ROUND(m_fNeighborRadius);
	if (iHalfSize == 0)
		errorSys("Neighbor raduis too small, stop.", STOP);

	m_iSlidingWindowSize = iHalfSize * 2 + 1;
	fWindow = Window(m_iSlidingWindowSize); 
	if (fWindow == NULL)
		errorSys("BDA: Error in WindowFloatTemplate, malloc memery failure.", STOP);

	WindowBoundary(fWindow, m_iSlidingWindowSize, m_fNeighborRadius, m_enumNeighborShape);

	return fWindow;
}


/*****************************************************************
Name:			BDAOutputMap
Input:	
Description:	Output DisturbSeverity maps
		
*****************************************************************/
//##ModelId=3F01D0EB02B7

void BDA::BDAOutputMap(int num,int itr, double wAdfGeoTransform[])
{
	for (int i = 0; i < n_numInterval; i++){
		if (itr >= startYear[i] && itr <= endYear[i]){
			int			i, j;
			int			iRows, iCols;
			char		strName[64];
			MAP8		m(pBDAsites->getHeader());
			MAP8		mSRD(pBDAsites->getHeader());
			char		str[100], str1[100];

			iRows = m_pBDA->m_iRows;
			iCols = m_pBDA->m_iCols;

			m.dim(iRows, iCols);
			sprintf(strName, "BDA Disturbance and Severity");
			m.rename(strName);
			for (j = 3; j < maxLeg; j++)	//Changed By Qia on Feb 04 2009 to maxleg
				m.assignLeg(j, "");

			m.assignLeg(0, "No Severity 0");
			m.assignLeg(1, "Severity 1");
			m.assignLeg(2, "Severity 2");
			m.assignLeg(3, "Severity 3");

			if (m_iROS > 0)
			{
				for (i = iRows; i >= 1; i--)
					for (j = 1; j <= iCols; j++)
						m(i, j) = (*m_pBDA)(i, j)->iDisturbSeverity;
			}
			else
			{
				for (i = iRows; i >= 1; i--)
					for (j = 1; j <= iCols; j++)
						m(i, j) = 0;
			}

			sprintf(str, "%s%s%d_%d", m_strBDAOutput, m_strName,num+1, itr*pBDAsites->TimeStep_BDA);
			m.setCellSize(cellSize);
			//double wAdfGeoTransform[6] = { 0.00, cellSize, 0.00, 600.00, 0.00, -cellSize };
			float nodata = 0;
			m.write(str, red2, green2, blue2, wAdfGeoTransform);

			//output SRD.img added by Nancy on May 09 2016
			const char *pszFormat = "HFA";//*

			GDALDriver *poDriver;//*

			char **papszMetadata;//*

			poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);//*

			if (poDriver == NULL)//*
				exit(1);

			papszMetadata = poDriver->GetMetadata();//*

			GDALDataset *poDstDS;//*

			GDALRasterBand *outPoBand; //*

			char **papszOptions = NULL;//*

			float *pafScanline;//*

			float *pintScanline; //*

			char *pszSRS_WKT = NULL;//*

			OGRSpatialReference oSRS;//*

			oSRS.SetUTM(11, TRUE);//*

			oSRS.SetWellKnownGeogCS("HEAD74");//*NAD27

			oSRS.exportToWkt(&pszSRS_WKT);//*

			//sprintf(str, "%s.gis", fn);

			//sprintf(str1, "%s.img", fn); //*

			if (m_OutSRD){
				sprintf(str1, "%s%s%d_%d.img", m_strBDAOutput, "SRD", num + 1, itr*pBDAsites->TimeStep_BDA);

				poDstDS = poDriver->Create(str1, iCols, iRows, 1, GDT_Float32, papszOptions);//*

				pafScanline = (float *)CPLMalloc(sizeof(float)* (iRows*iCols));//*

				if (poDstDS == NULL){

					printf("could not create file for img file output");//*
				}

				poDstDS->SetGeoTransform(wAdfGeoTransform);//*

				outPoBand = poDstDS->GetRasterBand(1);//*

				for (i = iRows; i > 0; i--)
				{
					for (j = 1; j <= iCols; j++)
					{
						//cout << "fSiteResourceDom: " << (*m_pBDA)(iRows - i + 1, j)->fSiteResourceDom << " ";
						//*(pafScanline + (iRows - i)*iCols + j - 1) = (*m_pBDA)(iRows - i + 1, j)->fSiteResourceDom;
						//added by Cheney on Mar 21,2018,handle visualization problem 
						*(pafScanline + (i-1)*iCols + j - 1) = (*m_pBDA)(iRows - i + 1, j)->fSiteResourceDom;
						//cout << "img" << *(pintScanline + (iRows - i)*iCols + j - 1) << " ";
					}
				}
				//cout << endl;
				outPoBand->RasterIO(GF_Write, 0, 0, iCols, iRows, pafScanline, iCols, iRows, GDT_Float32, 0, 0);//*

				GDALClose((GDALDatasetH)poDstDS);//*
			}

			if (m_OutBDP){

				sprintf(str1, "%s%s%d_%d.img", m_strBDAOutput, "BDP", num + 1, itr*pBDAsites->TimeStep_BDA);

				poDstDS = poDriver->Create(str1, iCols, iRows, 1, GDT_Float32, papszOptions);//*

				pafScanline = (float *)CPLMalloc(sizeof(float)* (iRows*iCols));//*

				if (poDstDS == NULL){

					printf("could not create file for img file output");//*
				}

				poDstDS->SetGeoTransform(wAdfGeoTransform);//*

				outPoBand = poDstDS->GetRasterBand(1);//*

				for (i = iRows; i > 0; i--)
				{
					for (j = 1; j <= iCols; j++)
					{
						//cout << "Output fSV: " << (*m_pBDA)(iRows - i + 1, j)->fSV << " ";
						//*(pafScanline + (iRows - i)*iCols + j - 1) = (*m_pBDA)(iRows - i + 1, j)->fSV;//*
						*(pafScanline + (i-1)*iCols + j - 1) = (*m_pBDA)(iRows - i + 1, j)->fSV;//*
						//cout << "img" << *(pintScanline + (iRows - i)*iCols + j - 1) << " ";
					}
				}
				//cout << endl;
				outPoBand->RasterIO(GF_Write, 0, 0, iCols, iRows, pafScanline, iCols, iRows, GDT_Float32, 0, 0);//*

				GDALClose((GDALDatasetH)poDstDS);//*
			}
		}
		else{
			cout << "BDA is not writing at iteration " << itr << endl;
		}
	}
}

/*****************************************************************
Name:			RandomNumber
Input:	
Output:			A number between [0, 1]
Description:	Generate a uniform random number between [0, 1]		
*****************************************************************/
//##ModelId=3F01D0EC00F2
float BDA::RandomNumber()
{
	float	fRN;

	fRN = (float)(frandrand() % 100) / 100;

	return fRN;
}

/*****************************************************************
Name:			dump(int )
Description:	This is only for debuging, output the intermediate
				result to files

       1	 //SiteResDom
      10  //SiteResDomMod
     100  //lastFire, lastHarvest
    1000	 //NeighborResDomMod
   10000  //SiteVulnerability
  100000  //severity
 1000000  //OutbreakZone 
10000000  //new epicenters
*****************************************************************/
//##ModelId=3F01D0EB02A7
void BDA::dump(int type)
{

	int x, y;

	if (type & 0x1)	//dump SiteResDom
	{
		FILE* m_pW = fopen( "windowSRD.out", "w" );

		for (x = 1; x <= m_iRow; x ++)
		{
			for (y = 1; y <= m_iCol; y++)
			{
				fprintf(m_pW, "%.1f  ", (*m_pBDA)(x, y)->fSiteResourceDom);
			}
			fprintf(m_pW, "%s", "\n");
		}
		fprintf(m_pW, "%s", "\n");
		fclose(m_pW);
	}

	if (type & 2)	////dump SiteResDomMod
	{
	 	FILE* m_pWMod = fopen( "windowSRDMod.out", "w" );
		
		for (x = 1; x <= m_iRow; x ++)
		{
			for (y = 1; y <= m_iCol; y++)
			{
				fprintf(m_pWMod, "%.1f  ", (*m_pBDA)(x, y)->fSiteResDomMod);
			}
			fprintf(m_pWMod, "%s", "\n");
		}
		fprintf(m_pWMod, "%s", "\n");
		fclose(m_pWMod);
	}

	if (type & 4)  //dump last fire, harvest
	{
		//fire
	 	FILE* m_pWFire = fopen( "windowLastFire.out", "w" );
		
		for (x = 1; x <= m_iRow; x ++)
		{
			for (y = 1; y <= m_iCol; y++)
			{
//				fprintf(m_pWFire, "%d  ", (*pBDAsites)(x, y)->lastFire);
			}
			fprintf(m_pWFire, "%s", "\n");
		}
		fprintf(m_pWFire, "%s", "\n");
		fclose(m_pWFire);

		//harvest
	 	FILE* m_pWH = fopen( "windowLastHarvest.out", "w" );
		
		for (x = 1; x <= m_iRow; x ++)
		{
			for (y = 1; y <= m_iCol; y++)
			{
//				fprintf(m_pWH, "%d  ", sites(x, y)->lastHarvest);
			}
			fprintf(m_pWH, "%s", "\n");
		}
		fprintf(m_pWH, "%s", "\n");
		fclose(m_pWH);
	}
	
	if (type & 8)	////dump neigbor resdom
	{
	 	FILE* m_pWNeighbor = fopen( "windowNeighbor.out", "w" );
		
		for (x = 1; x <= m_iRow; x ++)
		{
			for (y = 1; y <= m_iCol; y++)
			{
				fprintf(m_pWNeighbor, "%.3f  ", (*m_pBDA)(x, y)->fNeighborResDom);
			}
			fprintf(m_pWNeighbor, "%s", "\n");
		}
		fprintf(m_pWNeighbor, "%s", "\n");
		fclose(m_pWNeighbor);
	}

	if (type & 16)	////dump SV
	{
	 	FILE* m_pWNeighbor = fopen( "windowSV.out", "w" );
		
		for (x = 1; x <= m_iRow; x ++)
		{
			for (y = 1; y <= m_iCol; y++)
			{
				fprintf(m_pWNeighbor, "%.1f  ", (*m_pBDA)(x, y)->fSV);
			}
			fprintf(m_pWNeighbor, "%s", "\n");
		}
		fprintf(m_pWNeighbor, "%s", "\n");
		fclose(m_pWNeighbor);
	}

	if (type & 32)	////dump severity
	{
	 	FILE* m_pWSeverity = fopen( "windowSeverity.out", "w" );
		
		for (x = 1; x <= m_iRow; x ++)
		{
			for (y = 1; y <= m_iCol; y++)
			{
				fprintf(m_pWSeverity, "%d", (*m_pBDA)(x, y)->iDisturbSeverity);
			}
			fprintf(m_pWSeverity, "%s", "\n");
		}
		fprintf(m_pWSeverity, "%s", "\n");
		fclose(m_pWSeverity);
	}

	if (type & 64)	//dump OutbreakZone
	{
		FILE* m_pWZone = fopen( "windowBreakZone.out", "w" );
		
		for (x = 1; x <= m_iRow; x ++)
		{
			for (y = 1; y <= m_iCol; y++)
			{
				fprintf(m_pWZone, "%d", (*m_pBDA)(x, y)->enumOutbreakZone);
			}
			fprintf(m_pWZone, "%s", "\n");
		}
		fprintf(m_pWZone, "%s", "\n");
		fclose(m_pWZone);
	}

	if (type & 128)	//dump number of new epicenters
	{
		FILE* m_pNum = fopen( "windowNumEpicenters.out", "w" );
		fprintf(m_pNum, "%d%s", m_uiEpicenterNum, "\n");
		fclose(m_pNum);
	}

	if (type & 256) //dump epicenters
	{
		char** center = (char**)Window(m_iRow);
		FILE* m_pNum = fopen( "epicenters.out", "w" );
		for (x = 0; x < m_iRow; x ++)
		{
			for (y = 0; y < m_iCol; y++)
			{
				center[x][y] = 0;
			}
			
		}
		int i, j;
		for (x = 0; x < (int)m_uiEpicenterNum; x ++)
		{
			i = m_pEpiList[2 * x];
			j = m_pEpiList[2 * x + 1];
			center[i][j] = 1;
		}
		for (x = 0; x < m_iRow; x ++)
		{
			for (y = 0; y < m_iCol; y++)
			{
				fprintf(m_pNum, "%d", center[i][j]);
			}
			fprintf(m_pNum, "%s", "\n");
		}
		fprintf(m_pNum, "%s", "\n");
		fclose(m_pNum);
	}

}


/*****************************************************************
Name:			DataWrite ()
Description:	This is only for debuging, write data into files
******************************************************************/
//##ModelId=3F01D0EC0121
void BDA::DataWrite(char* strFileName)
{
	int	i, j;
	FILE* m_pW = fopen(strFileName, "w" );

	for (i = 1; i <= m_iRow; i++)
	{
		for (j = 1; j <= m_iCol; j++)
		{
			fprintf(m_pW, "%f ", (*m_pBDA)(i, j)->fNeighborResDom);
		}
//		fprintf(m_pW, "%s", "\n");
	}
//	fprintf(m_pW, "%s", "\n");
	fclose(m_pW);
}

/*****************************************************************
Name:			DataWrite ()
Description:	This is only for debuging, write data into files
******************************************************************/
//##ModelId=3F01D0EC0130
void BDA::DataWriteSingle(char* strFileName, float fValue)
{
	FILE* m_pW = fopen(strFileName, "aw" );
	fprintf(m_pW, "%f\n", fValue);
	fclose(m_pW);
}

//##ModelId=3F01D0EC0141
void BDA::PSNR(char* strFN1, char* strFN2, float* fTErr, float* fAErr)
{
	int	i, j;
	FILE* m_pW1 = fopen(strFN1, "r" );
	FILE* m_pW2 = fopen(strFN2, "r" );
	float	fdata1, fdata2;

	*fTErr = 0.0;

	for (i = 1; i <= m_iRow; i++)
	{
		for (j = 0; j < m_iCol; j++)
		{
			fscanf(m_pW1, "%f", &fdata1);
			fscanf(m_pW2, "%f", &fdata2);

			*fTErr += (fdata1 - fdata2) * (fdata1 - fdata2);
		}
	}

	*fAErr = (float)sqrt(*fTErr) / m_iRow / m_iCol;
	printf("fError = %f,  Mean ferror = %f\n", *fTErr, *fAErr);
	fclose(m_pW1);
	fclose(m_pW2);
	
}