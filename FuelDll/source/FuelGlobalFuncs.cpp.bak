/***********************************************

Name: FuelGlobalFuncs.cpp







************************************************/

#include <stdio.h>

#include "system1.h"

#include "error.h"

#include "FuelGlobalFuncs.h"

#include "FuelGlobalVariables.h"

#include "FuelDefines.h"

#include "Reclass4.h"



#ifdef __BORLANDC__

#include <dir.h>

#endif

#include <direct.h>

#ifdef __UNIX__

#include <sys/stat.h>

#endif



#include <ctype.h>

#include <string.h>

#include "defines.h"



static int red2[maxLeg]={0,70,0,0,0,0,0,0,200,100,255,150,200,200,255,255};

static int green2[maxLeg]={0,70,0,0,0,150,200,255,30,200,50,50,200,0,255};

static int blue2[maxLeg]={0, 70,125,200,255,0,100,0,30,50,50,0,0,255};



FILE*	fuelout;	

FILE*	fuelManageFile;

FILE*	fuelManOutStand;



void getFuelInput(char* strfuelInputFile, int specAttrsNo, int luNo) 

{



	int i=0;

	FILE *fuelFile;	

	if(gDLLMode & G_FUEL) 

	{

		if ((fuelFile=LDfopen(strfuelInputFile,1))==NULL)

			errorSys("Fuel input file not found.",STOP);



//		printf("Begin reading in fuel data\n");

		fuelsites.init(specAttrsNo, luNo);		

		fuelsites.read(fuelFile, strfuelInputFile);

		fuelsites.initFuelSite(pfuelcoresites->numRows()+1,pfuelcoresites->numColumns()+1);

	}



}



void getFuelManage(char* strfuelManFile) 

{

	int i=0;

	FILE *fuelFile;	



	if(gDLLMode & G_FUELMANAGEMENT) 

	{

		if ((fuelFile=LDfopen(strfuelManFile,1))==NULL)

			errorSys("Fuel input file not found.",STOP);



//		printf("Begin reading in fuel management data\n");

		fuelManager.read(fuelFile);

	}

}





void getFuelRule(char* strfuelRuleFile) 

{

	FILE *fuelRuleFile;	

	if(gDLLMode & G_FUEL) 

	{

		if ((fuelRuleFile=LDfopen(strfuelRuleFile,1))==NULL)

			errorSys("Fuel Rule file not found.",STOP);		

		fuelrule.read(fuelRuleFile);

	}

}



//added by Wei Li

//void FuelInit(PDP* ppdp, char* strfuelInitFile, int specAttrsNo, int luNo, char* stroutputDir, SITES* s, int iDllMode, char* pmgtAreaMapFile, char* pstandMapFile)

int FuelInit(PDP* ppdp, char* strfuelInitFile, int specAttrsNo, int luNo, char* stroutputDir, SITES* s, int iDllMode)

{

    char	str1[100];

	char*	strfuelInputFile;	//Fuel input file name

	char*	strfuelRuleFile;	//Fuel ruls file name

	char*	strfuelManFile;		//Fuel management file name

	char*	strfuelOutputFile;	//Fuel output file

	char*	strfuelManOutputFile;	//Fuel management output file

	char*	strfuelManOutNameForStand;	//Fuel management output file, record for each stand

	FILE*	pfFUELInit;



	char*	strpmgtAreaMapFile;

	char*	strpstandMapFile;



	// Shang add 04/04

	char*	strFireRegimeAttr;	//Fire regime attribute file

	char*	strFireRegimeMap;	//Fire regime map file



	pfuelcoresites = s;

	gDLLMode = iDllMode;

	pPDP = ppdp;

	int giRow = pPDP->iRows;

	int giCol = pPDP->iCols;



	strfuelInputFile = new char[FNSIZE];	//Fuel input file name

	strfuelRuleFile = new char[FNSIZE];	//Fuel ruls file name

	strfuelManFile = new char[FNSIZE];		//Fuel management file name

	strfuelOutputFile = new char[FNSIZE];	//Fuel output file

	strfuelManOutputFile = new char[FNSIZE];	//Fuel management output file

	strfuelManOutNameForStand = new char[FNSIZE];	//Fuel management output for eadh stand

	strpmgtAreaMapFile = new char[FNSIZE];

	strpstandMapFile = new char[FNSIZE];



	strFireRegimeAttr = new char[FNSIZE];	//Fire regime attribute file

	strFireRegimeMap = new char[FNSIZE];	//Fire regime map file



	if ((pfFUELInit = LDfopen(strfuelInitFile, 1)) == NULL)

		errorSys("FUEL: FUELInit file not found.",STOP);

	

	if (fscanc(pfFUELInit,"%s",strfuelInputFile)!=1)

		 errorSys("Error reading in fuelInputFile from parameter file.",STOP);

	if (fscanc(pfFUELInit,"%s",strfuelRuleFile)!=1)

		 errorSys("Error reading in fuelRuleFile from parameter file.",STOP);



	// Shang add 04/04

	if (fscanc(pfFUELInit,"%s",strFireRegimeAttr)!=1)

		 errorSys("Error reading in strFireRegimeAttr from parameter file.",STOP);

	if (fscanc(pfFUELInit,"%s",strFireRegimeMap)!=1)

		 errorSys("Error reading in strFireRegimeMap from parameter file.",STOP);



	if (fscanc(pfFUELInit,"%s",strfuelManFile)!=1)

		 errorSys("Error reading in fuelManFile from parameter file.",STOP);



	if (fscanc(pfFUELInit,"%s",strfuelOutputFile)!=1)

		 errorSys("Error reading in fuelOutputFile from parameter file.",STOP);

	if (fscanc(pfFUELInit,"%s",strfuelManOutputFile)!=1)

		 errorSys("Error reading in fuelManOutputFile from parameter file.",STOP);

	if (fscanc(pfFUELInit,"%s",strfuelManOutNameForStand)!=1)

		 errorSys("Error reading in fuelManOutNameForStand from parameter file.",STOP);

	if (fscanc(pfFUELInit,"%s",strpstandMapFile)!=1)

		 errorSys("Error reading in fuelManOutNameForStand from parameter file.",STOP);

	if (fscanc(pfFUELInit,"%s",strpmgtAreaMapFile)!=1)

		 errorSys("Error reading in fuelManOutputFile from parameter file.",STOP);



	if (strcmp (strfuelManFile, "N/A")) {

		gDLLMode = gDLLMode | G_FUELMANAGEMENT;

		fuelsites.initFuelManSite();

	}

	getFuelInput(strfuelInputFile, specAttrsNo, luNo);	// readin input of fuel



	// Shang read in the fire regime attribute

	fuelsites.readFireRegimeAttr(strFireRegimeAttr);

	fuelsites.readFireRegimeMap(strFireRegimeMap);



	sprintf(str1,"%s/%s",stroutputDir, "fuel");



#ifdef __UNIX__

_mkdir(str1, 493);

#else

_mkdir(str1);

#endif





	sprintf(str1,"%s/%s/%s",stroutputDir, "fuel",strfuelOutputFile);

	//if ((fuelout=LDfopen(str1,3))==NULL)

	//	  errorSys("Can not open fuelout file for write\n",STOP);

	//if ((diFile=LDfopen(strn,1))==NULL)

	  //errorSys("Wind input file not found.",STOP);



	

	if ((fuelout=fopen(str1,"w"))==NULL)

		errorSys("Can not open fuelout file for write\n",STOP);

	

	// write the title into fuel output file

		for(int t=0; t<5;t++)			

	//		LDfprintf0(fuelout,"Year        ITEM          Water       No-active   Background  0           1           2           3           4           5   Average  ");

	//	LDfprintf0(fuelout,"\n");



			fprintf(fuelout,"Year        ITEM          Water       No-active   Background  0           1           2           3           4           5   Average  ");

		fprintf(fuelout,"\n");

	

	char *str;

	str = new char[FNSIZE];

	getFuelRule(strfuelRuleFile);			// get fuel rule

	fueltrack.FFTrack();	// track fine fuel

	fueltrack.CFInit();		// track coarse fuel

//	printf("Fuel: Begin calculate potential fire probility.\n\n");

//	PotentialFireProbility();	// calculate the potential fire probability

	fueltrack.FireRiskTrack();		// track fire risk



	if ((gDLLMode & G_FUELMANAGEMENT) != 0)

	{

		 // FILE* pffuelManageFile;

		  //FILE* pffuelManOutStand;		

		//<Add By Qia on Nov 20 2008>

	int filenamelength;

	char fileextensive[10];

	filenamelength=strlen(strpstandMapFile);

	fileextensive[0]=strpstandMapFile[filenamelength-4];

	fileextensive[1]=strpstandMapFile[filenamelength-3];

	fileextensive[2]=strpstandMapFile[filenamelength-2];

	fileextensive[3]=strpstandMapFile[filenamelength-1];

	

	fileextensive[4]='\0';

	if(strcmp(fileextensive,".asc")==0){

		

	

    	standMap.readtxt(strpstandMapFile);

		}

	else{

			standMap.readImg(strpstandMapFile, giRow, giCol);

		}

	  //</Add By Qia on Nov 20 2008>  

		managementAreaMap.readImg(strpmgtAreaMapFile, giRow, giCol);

		fuelpstands = new FUELSTANDS(); //change by Qia on Nov 20 2008

		fuelpstands->construct(); //change by Qia on Nov 20 2008

	    managementAreas.construct();



		

		// readin fuel management events

		sprintf(str,"%s/%s/%s",stroutputDir,"fuel",strfuelManOutputFile);

		if ((fuelManageFile=fopen(str,"w"))==NULL)

			errorSys("Can not open fuel management file for write\n.",STOP);		

		sprintf(str,"%s/%s/%s",stroutputDir,"fuel",strfuelManOutNameForStand);

		if ((fuelManOutStand=fopen(str,"w"))==NULL)

			errorSys("Can not open fuelManagenet Output for Stand file for write\n.",STOP);

		fprintf(fuelManOutStand, "Iteration   ManagementArea   Stand   ManageStie  FireRiskBeforeTreatment FireRiskAfterTreatment\n");

		getFuelManage(strfuelManFile);



		//<Add By Qia on Nov 20 2008>

		managementAreaMap.freeMAPdata();

	//</Add By Qia on Nov 20 2008>

		//fclose(pffuelManageFile);

		//fclose(pffuelManOutStand);

	}



	return gDLLMode;

}





void FuelProcessEvent()

{

	fueltrack.FFTrack();		// track fine fuel

	fueltrack.CFTrack();		// track coarse fuel

//	printf("Fuel: Begin calculate potential fire probility.\n\n");

//	PotentialFireProbility();	// track fire probability (decimal)

	fueltrack.FireRiskTrack();

}





void FuelManageProcessEvents(int itr)

{

	fuelManager.processEvents(itr);

}





void FuelputFuelOutput(int itr, char* FueloutputDir, int nCellSize) 

{

	char str[100];

	char fuelOutDir[100];

	

	MAP8 m(pfuelcoresites->getHeader());



	sprintf(fuelOutDir,"%s/%s",FueloutputDir,"fuel");





//	printf("Reclassfy fine fuel load!\n");

	fprintf(fuelout, "%-4d  finefuel            ",itr*pfuelcoresites->TimeStep_Fuel);



	//FuelReclass(m,0, fueloutfile);	// reclass fine fuel load	

	FuelReclass(m,0, fuelout);	// reclass fine fuel load	

	sprintf(str,"%s/FF%d",fuelOutDir,itr*pfuelcoresites->TimeStep_Fuel);

	m.setCellSize(nCellSize);

	double wAdfGeoTransform[6] = { 0.00, nCellSize, 0.00, 600.00, 0.00, nCellSize };//*

	float nodata = 0;

	m.write(str, red2, green2, blue2, wAdfGeoTransform);



//	printf("Reclassfy coarse fuel load\n");

	fprintf(fuelout,"%-4d  coarsefuel          ", itr*pfuelcoresites->TimeStep_Fuel);



	//FuelReclass(m,1, fueloutfile);  // reclass coarse fuel load

	FuelReclass(m,1, fuelout);  // reclass coarse fuel load

	sprintf(str,"%s/CF%d",fuelOutDir,itr*pfuelcoresites->TimeStep_Fuel);

	m.setCellSize(nCellSize);

	

	m.write(str, red2, green2, blue2, wAdfGeoTransform);

	

	// First, relcass potential fire probility into category

	if (!fuelrule.fireProbReclass)

		if (!fireProbilityCategory())

			 errorSys("Error! Can not reclassify potential fire probility into categories\n", STOP);



//	printf("Reclassfy fire probility, severity and risk\n");

	MAP8 m1(pfuelcoresites->getHeader());	// map for fire probability

	MAP8 m2(pfuelcoresites->getHeader());	// map for potential fire intensity



	fireReclass(m1,m2,m,fuelout, itr); // reclass fire probility, severity & risk

//	fireReclass(m1,m2,m); // reclass fire probility, severity & risk



	sprintf(str,"%s/FR%d",fuelOutDir,itr*pfuelcoresites->TimeStep_Fuel);	// fire risk

	m.setCellSize(nCellSize);

	

	m.write(str, red2, green2, blue2, wAdfGeoTransform);



	sprintf(str,"%s/FP%d",fuelOutDir,itr*pfuelcoresites->TimeStep_Fuel);  // fire probility

	m1.setCellSize(nCellSize);


	m1.write(str, red2, green2, blue2, wAdfGeoTransform);



	sprintf(str,"%s/FI%d",fuelOutDir,itr*pfuelcoresites->TimeStep_Fuel);  // fire severity

	m2.setCellSize(nCellSize);

	

	m2.write(str, red2, green2, blue2, wAdfGeoTransform);



}