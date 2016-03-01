// FuelSites.cpp: implementation of the FuelSites class.

//

//////////////////////////////////////////////////////////////////////

#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include "FuelSites.h"

#include "error.h"

#include "system1.h"

#include "FuelTrack.h"

#include "defines.h"



// Shang 03/04

#include "FuelGlobalVariables.h"



//#ifdef _FUEL_

//////////////////////////////////////////////////////////////////////

// Construction/Destruction

//////////////////////////////////////////////////////////////////////



FuelSites::FuelSites()

{

	fireFlag = 0;

	windFlag = 0;

	cols = 0;

	rows = 0;

	fireModFF = new int[5];

	fireModCF = new int[5];

	windModFF = new int[5];

	windModCF = new int[5];

	BDAModFF = new int[FNSIZE*3];

	BDAModCF = new int[FNSIZE*3];

	totalHarvestEvent = 0;

	HarvestModFF = new int[FNSIZE*6];

	HarvestModCF = new int[FNSIZE*6];

//	mortality = NULL;

	spFFAccumulation = NULL;

	landtypeInfo = NULL;

//	spDensity = NULL;

	fuelSite = NULL;

	fuelManSite = NULL;

	fireRegime = NULL;			// array of fire regime

	numFireRegimes = 0;

	totalBDAType = 0;

}



FuelSites::~FuelSites()

{

	

	if (fireModFF)			delete [] fireModFF;

	if (fireModCF)			delete [] fireModCF;

	if (windModFF)			delete [] windModFF;

	if (windModCF)			delete [] windModCF;

	if (spFFAccumulation)	delete [] spFFAccumulation;

	if (landtypeInfo)		delete [] landtypeInfo;

//	if (spDensity)			delete [] spDensity;

	if (fuelSite)			delete [] fuelSite;

	if (BDAModFF)			delete [] BDAModFF;

	if (BDAModCF)			delete [] BDAModCF;

	if (HarvestModFF)		delete [] HarvestModFF;

	if (HarvestModCF)		delete [] HarvestModCF;

	if (fireRegime)			delete [] fireRegime;

	if (fuelManSite)		delete [] fuelManSite;

	if(map) delete [] map; //Add By Qia on Nov 24 2008

	//<Add By Qia on Nov 24 2008>

for(int i=0;i<SortedIndex.size();i++)

{

	FuelSite *temp;

	temp=SortedIndex.at(i);;

	delete temp;

}

//</Add By Qia on Nov 24 2008>

}



void FuelSites::init(int speicesNum, int ltNum) {

	// initialize the species number and landtype number

	spNum = speicesNum;	

	landtypeNum = ltNum;



//	mortality = new int[spNum];

	// allocoate fine fuel accumulation for each species 

	spFFAccumulation = new SpecieFFAccumulation[spNum];

	// allocoate coarse fuel accumulation for each landtype

	landtypeInfo = new LandtypeInfo[ltNum];

//	spDensity = new SpecieDensity[ltNum];

//	for (int i=0;i<ltNum; i++) {

//		spDensity[i].SpNum = spNum;

//		spDensity[i].density = new float[spNum];

//	}

	numFireRegimes = 0;

	fireRegime = new FireRegime[MAX_LANDUNITS];

}



void FuelSites::initFuelSite (int row, int col) {

	// allocoate fuel sites

	//fuelSite = new FuelSite [row*col];//commented By Qia on Nov 19 2008

	//<Add By Qia on Nov 19 2008>

	map=new FuelSite* [row*col];

	printf("LandisPro FuelSite map allocated\n");

	FuelSite *site;

	int i,j,x;

	site=new FuelSite;

	sitetouse=new FuelSite;

	site->beginCFDecompClass=0;

	site->cFireProbabilityClass=0;

	site->fireRegime;

	site->timeOfCFAccumulation=0;

	site->numofsites=row*col;

	SortedIndex.push_back(site);

	

	for (i = 1; i <= row; i++)

		for (j = 1; j <= col; j++)

		{

			x=(i - 1) * col;

			x=x + j - 1;

			map[x]=site;

		}

	//</Add By Qia on Nov 19 2008>

	rows = row;

	cols = col;



}



void FuelSites::initFuelManSite () {

	// allocoate fuel sites

	if(rows>0 && cols>0) {

		fuelManSite = new FuelManSite [rows*cols];

		for(int i=0; i<rows*cols;i++) {

			fuelManSite[i].sTSLFUELMAN = (short)999;

			fuelManSite[i].cFUELMANEvent = (char)-1;

		}

	}

}



void FuelSites::updateFuelManSite () {

	// add the time since last fuel management by 10 yrs

	if(rows>0 && cols>0) {

		fuelManSite = new FuelManSite [rows*cols];

		for(int i=0; i<rows*cols;i++) {

			fuelManSite[i].sTSLFUELMAN ++;

			//fuelManSite[i].cFUELMANEvent = (char)-1;

		}

	}

}



FuelSite* FuelSites:: operator () (int row, int col) {

	// get the fuelsite

	if (row >0 && row <rows && col >0 && col <= cols) 

		//return &fuelSite[(row-1)*cols + col-1]; commented By Qia on Nov 19 2008

		//<Add By Qia on Nov 19 2008>

		return map[(row-1)*cols + col-1]; 

		//</Add By Qia on Nov 19 2008>

	else return NULL;

}



// Shang 03/04

int FuelSites::setFFLoad(int ffload, int row, int col) {

	// this function will set the fine fuel load into PDP



	int FFLoad = 0;

	if(ffload<0)	FFLoad = 0;

	else if(ffload>5)	FFLoad = 5;

	else FFLoad = ffload;

	if(row<0 || row>rows || col<0 || col>cols)

		return -1;

	(pPDP->cFineFuel)[row][col] = (char)FFLoad;	

	return FFLoad;

}



// Shang 03/04

int FuelSites::getFFLoad(int row, int col) {

	// this function will get the fine fuel load from PDP



	int FFLoad = 0;

	if(row<0 || row>rows || col<0 || col>cols)

		return -1;

	FFLoad = (pPDP->cFineFuel)[row][col];

	if(FFLoad<0)	FFLoad = 0;

	else if(FFLoad>5)	FFLoad = 5;

	

	return FFLoad;

}

// Shang 03/04

int FuelSites::setCFLoad(int cfload, int row, int col) {

	// this function will set the coarse fuel load into PDP



	int CFLoad = 0;

	if(cfload<0)	CFLoad = 0;

	else if(cfload>5)	CFLoad = 5;

	else CFLoad = cfload;	

	if(row<0 || row>rows || col<0 || col>cols)

		return -1;

	(pPDP->cCoarseFuel)[row][col] = (char)CFLoad;

	return CFLoad;

}



// Shang 03/04

int FuelSites::getCFLoad(int row, int col) {

	// this function will get the coarse fuel load from PDP



	int CFLoad = 0;

	if(row<0 || row>rows || col<0 || col>cols)

		return -1;

	CFLoad = (pPDP->cCoarseFuel)[row][col];

	if(CFLoad<0)	CFLoad = 0;

	else if(CFLoad>5)	CFLoad = 5;	

	return CFLoad;

}



// Shang 03/04

int FuelSites::setFireIntensityClass(int fireInten, int row, int col) {

	// this function will set the fine intensity into PDP



	int FireInten = 0;

	if(fireInten<0)	FireInten = 0;

	else if(fireInten>5)	FireInten = 5;

	else FireInten = fireInten;	

	if(row<0 || row>rows || col<0 || col>cols)

		return -1;

	(pPDP->cFireIntensityClass)[row][col] = (char)FireInten;

	return FireInten;

}



// Shang 03/04

int FuelSites::getFireIntensityClass(int row, int col) {

	// this function will get the fire intensity from PDP



	int FireInten = 0;

	if(row<0 || row>rows || col<0 || col>cols)

		return -1;

	FireInten = (pPDP->cFireIntensityClass)[row][col];

	if(FireInten<0)	FireInten = 0;

	else if(FireInten>5)	FireInten = 5;	

	return FireInten;

}



// Shang 03/04

int FuelSites::setFireProbabiltyClass(int fireProb, int row, int col) {

	// this function will set the fire probability into PDP



	int FireProb = 0;

	if(fireProb<0)	FireProb = 0;

	else if(fireProb>5)	FireProb = 5;

	else FireProb = fireProb;	

	if(row<0 || row>rows || col<0 || col>cols)

		return -1;

	// shang delete

	//(pPDP->cFireProbabilityClass)[row][col] = (char)FireProb;

	//<Add By Qia on Nov 19 2008>

	fuelsites.BefStChg(row,col);

	//</Add By Qia on Nov 19 2008>

	fuelsites(row,col)->cFireProbabilityClass = (char) FireProb;

	//<Add By Qia on Nov 19 2008>

	fuelsites.AftStChg(row,col);

	//</Add By Qia on Nov 19 2008>

	return FireProb;

}



// Shang 03/04

int FuelSites::getFireProbabiltyClass(int row, int col) {

	// this function will get the potential fire probability from PDP



	int FireProb = 0;

	if(row<0 || row>rows || col<0 || col>cols)

		return -1;

	// shang delete

	//FireProb = (pPDP->cFireProbabilityClass)[row][col];

	FireProb = fuelsites(row,col)->cFireProbabilityClass;

	if(FireProb<0)	FireProb = 0;

	else if(FireProb>5)	FireProb = 5;	

	return FireProb;

}



// Shang 03/04

int FuelSites::setFireRiskClass(int fireRisk, int row, int col) {

	// this function will set the fire risk into PDP



	int FireRisk = 0;

	if(fireRisk<0)	FireRisk = 0;

	else if(fireRisk>5)	FireRisk = 5;

	else FireRisk = fireRisk;	

	if(row<0 || row>rows || col<0 || col>cols)

		return -1;

	(pPDP->cFireRiskClass)[row][col] = (char)FireRisk;

	return FireRisk;

}



// Shang 03/04

int FuelSites::getFireRiskClass(int row, int col) {

	// this function will get the fire risk from PDP



	int FireRisk = 0;

	if(row<0 || row>rows || col<0 || col>cols)

		return -1;

	FireRisk = (pPDP->cFireRiskClass)[row][col];

	if(FireRisk<0)	FireRisk = 0;

	else if(FireRisk>5)	FireRisk = 5;	

	return FireRisk;

}





void FuelSites::readFireRegimeMap(char* mapName) {



//This will read fire regime map and associate fire regime Unit to each site.

//mapFile is an Erdas 8 bit gis file.  The file pointer is

//placed on the first map element.  yDim and xDim are the (x,y) dimensions

//of the Erdas map.

	FILE* mapFile;

	if ((mapFile = LDfopen(mapName, 2)) == NULL)

		errorSys("Fire regime map file not found!\n",STOP);

	/*

	if ((mapFile=fopen(mapName,"rb"))==NULL)

		errorSys("Can not open fire regime attribute file for read\n",STOP);

	*/

	unsigned char c;

	unsigned long dest[64];

	int 	nCols,

			nRows,

			numRead,

			coverType;	

	LDfread((char*)dest,4,32,mapFile);

#ifdef __UNIX__

	ERDi4_c(&dest[4],nCols);

	ERDi4_c(&dest[5],nRows);

#else

	nCols=dest[4];

	nRows=dest[5];

#endif



	if ((nCols != cols-1)||(nRows!= rows-1))

		errorSys("the dimension of fire regime GIS map is not consistent.",STOP);



	for (int i=nRows;i>0;i--)

	{

		for (int j=1;j<=nCols;j++)

		{

   			numRead=LDfread((char*)(&c),1,1,mapFile);

   			coverType=(int)c;

			if ((numRead>=0)&&(coverType>=0))		{	

				//<Add By Qia on Nov 19 2008>

				fuelsites.BefStChg(i,j);

				//</Add By Qia on Nov 19 2008>

				fuelsites(i,j)->fireRegime = (char)c;

				//<Add By Qia on Nov 19 2008>

				fuelsites.AftStChg(i,j);

				//</Add By Qia on Nov 19 2008>

				}

			

			else

        		errorSys("illegel fire regime unit found.",STOP);

		}

	}

	LDfclose(mapFile);



}



//void FuelSites::readFireRegimeAttr(FILE* infile) {

void FuelSites::readFireRegimeAttr(char* filename) {

	// read in the fire regime attributes

	FILE* infile;



	if ((infile = LDfopen(filename, 1)) == NULL)

		errorSys("Fire regime attribute file not found!\n",STOP);

	

	while (!LDeof(infile))

	{	

		if (numFireRegimes<MAX_LANDUNITS) {			

			int i;

			int tem;

			float temp;

			char str[255];



			if (fscanc(infile,"%s",str)!=1)

				errorSys("Error reading in name from landtype file.",STOP);

			strcpy(fireRegime[numFireRegimes].fireRegimeName,str);

			if (fscanc(infile,"%d",&tem)!=1)

				errorSys("Error reading in fireInterval from landtype file.",STOP);

			fireRegime[numFireRegimes].fireInterval = tem;

			if (fscanc(infile,"%f",&temp)!=1)

				errorSys("Error reading in fire ignition poisson parameter from landtype file.",STOP);

			if (fscanc(infile,"%f",&temp)!=1)

				errorSys("Error reading in MFS from landtype file.",STOP);

			if (fscanc(infile,"%f",&temp)!=1)

				errorSys("Error reading in fire size Variance from landtype file.",STOP);

			if (fscanc(infile,"%d",&tem)!=1)

				errorSys("Error reading in initialLastFire from landtype file.",STOP);

			fireRegime[numFireRegimes].initialLastFire = tem;

			for (i=0;i<5;i++)  

				if (fscanc(infile,"%d",&tem)!=1)

					errorSys("Error reading in fireCurve from landtype file.",STOP);

			for (i=0;i<5;i++)  

				if (fscanc(infile,"%d",&tem)!=1)

					errorSys("Error reading in fireClass from landtype file.",STOP);

			for (i=0;i<5;i++)  

				if (fscanc(infile,"%d",&tem)!=1)

					errorSys("Error reading in fireCurve from landtype file.",STOP);

			for (i=0;i<5;i++)  

				if (fscanc(infile,"%d",&tem)!=1)

					errorSys("Error reading in fireClass from landtype file.",STOP);

			numFireRegimes++;

		}

		else

			errorSys("CFireRegimeUnits::read(FILE*)-> Array bounds error.",STOP);

		

		

	}

	LDfclose(infile);

}



void FuelSites::read(FILE *inFile, char* strfuelInputFile) {

	// read in fuel accumulation info

	int i, j;

	int temp = 0;

	char str[25];

	float tem = 0;



	// read species fine fuel accumulation information

	if (fscanc(inFile,"%s",str)!=1) {

		sprintf(str,"%s%s","Error in reading [SPECIES] section from file: ", strfuelInputFile);

		errorSys(str,STOP);

	}

	// read in species info

	if (strcmp(str,"[SPECIES]")==0)	 {

		// read in Live Fuel Quality Coefficient

		// Shang 06/04

		for (i=0;i<spNum;i++) {

			if (fscanc(inFile,"%f",&tem)!=1)

				errorSys("Error reading in species live fuel quality coefficient from fuel.dat.",STOP);

			spFFAccumulation[i].LiveFuelQualityCoeff = tem;			

		}

		

		for (i=0;i<spNum;i++) {	

			for (j=0;j<FUELCATEGORY;j++) {

				if (fscanc(inFile,"%d",&temp)!=1)

					errorSys("Error reading in species fuel accumulation from fuel.dat.",STOP);

				spFFAccumulation[i].spFFClass[j] = temp;				

				// read in fine fuel class for each species

			}

			for (j=0;j<FUELCATEGORY;j++) {

				if (fscanc(inFile,"%d",&temp)!=1)

					errorSys("Error reading in species fuel accumulation from fuel.dat.",STOP);

				spFFAccumulation[i].spFFAccumulation[j] = temp;								

			}

			//printf("\n");

		}

	}

	

	else {  		

		sprintf(str,"%s%s","Error in reading [SPECIES] section from file: ", strfuelInputFile);

		errorSys(str,STOP);

	}
	//<Add By Qia on Dec 03 2012>
	for(i = 0;i<5;i++){
		float temp;
		for(j=0;j<3;j++){
			if (fscanc(inFile, "%f", &temp) != 1) 
				errorSys("Error in reading values.", STOP);
			fire_betavalues[i][j] = temp;
		}
		if (fscanc(inFile, "%f", &temp) != 1) 
			errorSys("Error in reading values.", STOP);
		fire_X2values[i] = temp;
	}
	//</Add By Qia on Dec 03 2012>


	// read landtype based fuel information (fine fuel accumulation & coarse fuel variation)

//	if (strcmp(str,"[DENSITY]")==0) {



	if (fscanc(inFile,"%s",str)!=1) {

		sprintf(str,"%s%s","Error in reading [LANDTYPE] section from file: ", strfuelInputFile);

		errorSys(str,STOP);	

	}

//	}

	// read in land type info

		if (strcmp(str,"[LANDTYPE]")==0) {

		for(i=0;i<landtypeNum;i++) {

			if (fscanc(inFile,"%f",&tem)!=1)

				errorSys("Error reading in crown fire coefficient from fuel.dat file.",STOP);

			landtypeInfo[i].CrownFireCoeff = tem;			

		}



		for(i=0;i<landtypeNum;i++) {

			if (fscanc(inFile,"%s",landtypeInfo[i].LandtypeName)!=1)

				errorSys("Error reading in landtype name from fuel.dat file.",STOP);

			// read in land ypte name

			for (j=0;j<FUELCATEGORY;j++) {

				if (fscanc(inFile,"%d",&temp)!=1)

					errorSys("Error reading in  fineFuelLoad from fuel.dat.",STOP);

				landtypeInfo[i].fineFuelLoad[j] = temp;	

				// read in landtype modifer for each fine fuel class

			}

			for (j=0;j<FUELCATEGORY;j++) {

				if (fscanc(inFile,"%d",&temp)!=1)

					errorSys("Error reading in  coarseFuelAccumulation from fuel.dat.",STOP);

				landtypeInfo[i].coarseFuelAccumulation[j] = temp;

				// read in coarse fuel accumulation for each class

			}

			for (j=FUELCATEGORY-1;j>=0;j--) {

				if (fscanc(inFile,"%d",&temp)!=1)

					errorSys("Error reading in  coarseFuelDecomposition from fuel.dat.",STOP);

				landtypeInfo[i].coarseFuelDecomposition[j] = temp;

				// read in coarse fuel decomposition for each class

			}			

		}

	}

		else {

			sprintf(str,"%s%s","Error in reading [LANDTYPE] section from file: ", strfuelInputFile);

			errorSys(str,STOP);	

		}

			



	// read fire modifier

		if (fscanc(inFile,"%s",str)!=1) {

			sprintf(str,"%s%s","Error in reading [FIRE] section from file: ", strfuelInputFile);

			errorSys(str,STOP);	

		}

	// read in fire info

	if (strcmp(str,"[FIRE]")==0) {

		// Keep for future use

		/*

		if (fscanc(inFile,"%d",&fireFlag)!=1)

			errorSys("Error reading in fire modifer flag from fuel.dat file.",STOP);

		*/

		for(i=0;i<5;i++) {

			if (fscanc(inFile,"%d",&temp)!=1)

				errorSys("Error reading in fire modifer from fuel.dat file.",STOP);

			fireModFF[i] = temp;

			// read in fire modifier for fine fuel

		}

		for(i=0;i<5;i++) {

			if (fscanc(inFile,"%d",&temp)!=1)

				errorSys("Error reading in fire modifer from fuel.dat file.",STOP);

			fireModCF[i] = temp;

			// read in fire modifier for coarse fuel

		}

	}

	else {

		sprintf(str,"%s%s","Error in reading [FIRE] section from file: ", strfuelInputFile);

		errorSys(str,STOP);	

	}





	// read wind modifier

	if (fscanc(inFile,"%s",str)!=1) {

		sprintf(str,"%s%s","Error in reading [WIND] section from file: ", strfuelInputFile);

		errorSys(str,STOP);	

	}

	// read in wind info

	if (strcmp(str,"[WIND]")==0) {

		// Keep for future use

		/*

		if (fscanc(inFile,"%d",&windFlag)!=1)

			errorSys("Error reading in fire modifer flag from fuel.dat file.",STOP);

		*/

		for(i=0;i<5;i++) {

			if (fscanc(inFile,"%d",&temp)!=1)

				errorSys("Error reading in fire modifer from fuel.dat file.",STOP);

			windModFF[i] = temp;

			// read in wind modifier for fine fuel



		}

		for(i=0;i<5;i++) {

			if (fscanc(inFile,"%d",&temp)!=1)

				errorSys("Error reading in fire modifer from fuel.dat file.",STOP);

			windModCF[i] = temp;

			//printf("%d  ",temp);

			// read in wind modifier for coarse fuel



		}

	}



	else  {

		sprintf(str,"%s%s","Error in reading [WIND] section from file: ", strfuelInputFile);

		errorSys(str,STOP);		

	}



	// read BDA modifier

	if (fscanc(inFile,"%s",str)!=1) {

		sprintf(str,"%s%s","Error in reading [BDA] section from file: ", strfuelInputFile);

		errorSys(str,STOP);		

	}

	// read in wind info

	if (strcmp(str,"[BDA]")==0) {

		// Keep for future use

		/*

		if (fscanc(inFile,"%d",&windFlag)!=1)

			errorSys("Error reading in fire modifer flag from fuel.dat file.",STOP);

		*/

		if (fscanc(inFile,"%d",&temp)!=1)

			errorSys("Can't find Number Of BDA types from fuel.dat file.",STOP);

		if (temp<0)	

			errorSys("Number Of Total BDA types in fuel.dat file <0",STOP);

		if (temp>FNSIZE)	

			errorSys("Number Of BDA types in fuel.dat file >255",STOP);

		totalBDAType = temp;

		for(j=0;j<totalBDAType;j++) {

			for(i=0;i<3;i++) {

				if (fscanc(inFile,"%d",&temp)!=1)

					errorSys("Error reading in fire modifer from fuel.dat file.",STOP);

				BDAModFF[i] = temp;

				// read in BDA modifier for fine fuel

			}

			for(i=0;i<3;i++) {

				if (fscanc(inFile,"%d",&temp)!=1)

					errorSys("Error reading in fire modifer from fuel.dat file.",STOP);

				BDAModCF[i] = temp;

				//printf("%d  ",temp);

				// read in BDA modifier for coarse fuel

			}

		}

	}



	else  {

		sprintf(str,"%s%s","Error in reading [BDA] section from file: ", strfuelInputFile);

		errorSys(str,STOP);		

	}



	// read in Harvest modifier

	if (fscanc(inFile,"%s",str)!=1) {

		sprintf(str,"%s%s","Error in reading [HARVEST] section from file: ", strfuelInputFile);

		errorSys(str,STOP);		

	}

	// read in wind info

	if (strcmp(str,"[HARVEST]")==0) {		

		if (fscanc(inFile,"%d",&temp)!=1)

			errorSys("Can't find Number Of Total Harvest Events from fuel.dat file.",STOP);

		if (temp<0)	

			errorSys("Number Of Total Harvest Events in fuel.dat file <0",STOP);

		if (temp>50)	

			errorSys("Number Of Total Harvest Events in fuel.dat file >50",STOP);

		totalHarvestEvent = temp;

		for(int event =0; event <totalHarvestEvent; event ++) {

			for(i=0;i<6;i++) {

				if (fscanc(inFile,"%d",&temp)!=1)

					errorSys("Error reading in harvest modifer from fuelinput.dat file.",STOP);

				HarvestModFF[event*6 + i] = temp;				

			}

			for(i=0;i<6;i++) {

				if (fscanc(inFile,"%d",&temp)!=1)

					errorSys("Error reading in harvest modifer from fuelinput.dat file.",STOP);

				HarvestModCF[event*6 + i] = temp;				

			}

		}

	}



	else {

		sprintf(str,"%s%s","Error in reading [HARVEST] section from file: ", strfuelInputFile);

		errorSys(str,STOP);		

	}



/*

	// read mortality modifer based on species

	if (fscanc(inFile,"%s",str)!=1)

		errorSys("Can't find [MORTALITY] from fuel.dat file.",STOP);



	if (strcmp(str,"[MORTALITY]")==0) {

		for(i=0;i<spNum;i++) {

			if (fscanc(inFile,"%d",&temp)!=1)

				errorSys("Error reading in mortality modifer from fuel.dat file.",STOP);

			mortality[i] = temp;



		}

	}

	else  errorSys("Can't find [MORTALITY] from fuel.dat file.",STOP);

*/

}



int FuelSites::CalculateFFLoad(int spID, int spage, int splong, int ltID) {

	// this function will return fine fuel load



	int FFLoad = 0;

	float FF = 0;

	if (spID <0 || spID >= spNum)	

		errorSys("Error! FFF sp code > sp Num.",STOP);	

	else if(ltID <0 || ltID >=landtypeNum)	

		errorSys("Error! landtype code > landtype Num.",STOP);	

	else if (spage <=0)	return 0;

	else {

		if (spage > splong)	spage = splong;		

		for(int i=4; i>=0; i--) {

			if (spage >= spFFAccumulation[spID].spFFAccumulation[i]) {				

				//FFLoad = i + 1;

				FFLoad = spFFAccumulation[spID].spFFClass[i];

				break;

			}			

		}

		//printf("%f \n",spFFAccumulation[spID].spFFAccumulation[0]);		

	}

	FF = FFLoad * spFFAccumulation[spID].LiveFuelQualityCoeff;

	//FFLoad = (int)(FF + 0.5);

	FFLoad = (int)(FF+0.45);

	//if (FFLoad > 4) 

	//	printf("SPID  %d  Age: %d  Long %d  LTID  %d   FF: %d\n", spID, spage, splong, ltID, FFLoad);

	return FFLoad;

}

/*

float FuelData::getSpWeight(int spID, int ltID) {

	//float weight = 0;

	if (spID <0 || spID >= spNum)	

		errorSys("Error! sp code > sp Num.",STOP);

	else if (ltID<0 || ltID>=landtypeNum)

		errorSys("Error! landtype code > landtype Num.",STOP);



	else	return 0;		

	return spDensity[ltID].density[spID];	

	

}

*/



int FuelSites::fireDisFFLoad (int FFLoad, int row, int col) {

	// this function will return the fine fuel load after fire



	int fireClass = 0;

	int timeSinceLastFire = -999;

	if (FFLoad <0)	FFLoad = 0;

	else if (FFLoad > 5)	FFLoad = 5;

	int finalFuel = FFLoad;

	if (row>=0 && row <= rows && col>=0 && col<=cols) {

		timeSinceLastFire = (pPDP->sTSLFire)[row][col];

		//timeSinceLastFire = getTimeSinceLastFire(row, col);

		if(timeSinceLastFire==0) {	

			fireClass = getFireIntensityClass(row, col);			

			if (fireClass >0 && fireClass <=5)	{

				finalFuel = min (5,  max (0, FFLoad + fireModFF[fireClass-1]));

			//printf("Fireclass %d   Modifier  %d  Finalfule  %d\n",fireClass, fireModFF[fireClass-1],finalFuel);

			}

		}

	}

	return finalFuel;

}





int FuelSites::fireDisCFLoad (int CFLoad, int row, int col) {

	// this function will return the fine fuel load after fire

	if (CFLoad <0)	CFLoad = 0;

	else if (CFLoad > 5)	CFLoad = 5;

	int fireClass = 0;

	int timeSinceLastFire = -999;

	int finalFuel = CFLoad;

	if (row>=0 && row <= rows && col>=0 && col<=cols) {

		//timeSinceLastFire = getTimeSinceLastFire(row, col);

		timeSinceLastFire = (pPDP->sTSLFire)[row][col];

		if(timeSinceLastFire==0) {

			fireClass = getFireIntensityClass(row, col);

			if (fireClass >0 || fireClass <=5)			

				finalFuel = min(5, max (0, CFLoad + fireModCF[fireClass-1]));

			//if(finalFuel>CFLoad) {

				// set the start class of coarse fuel decompositation

				LANDUNIT *l;

				l=pfuelcoresites->locateLanduPt(row,col);//Original landis4.0: (*pfuelcoresites)(row,col)->landUnit

														//Changed By Qia Oct 13 2008

				//<Add By Qia on Nov 19 2008>

				fuelsites.BefStChg(row,col);

				//</Add By Qia on Nov 19 2008>

				fuelsites(row,col)->timeOfCFAccumulation = fuelsites.getCFAccumulationTime(l->ltID, finalFuel);

				fuelsites(row,col)->beginCFDecompClass = finalFuel;

				//<Add By Qia on Nov 19 2008>

				fuelsites.AftStChg(row,col);

				//</Add By Qia on Nov 19 2008>

			//}

		}

	}

	return finalFuel;

}



int FuelSites::BDADisFFLoad (int FFLoad, int row, int col) {

	if (FFLoad <0)	FFLoad = 0;

	else if (FFLoad > 5)	FFLoad = 5;

	int finalFuel = FFLoad;

	for(int i = 0; i<pPDP->iBDANum; i++) {

		if((pPDP->pBDAPDP[i].sTSLBDA)[row][col]==0){

			int BDASeverity = (pPDP->pBDAPDP[i]).cBDASeverity[row][col];

			//if(BDASeverity>0)

			//	printf("BDASeverity %d \n", BDASeverity);

			if(BDASeverity>0 && BDASeverity<4) {

				

				finalFuel = finalFuel + BDAModFF[i*3+BDASeverity-1];

			}

		}

	}

	finalFuel = min (5,  max (0, finalFuel));

	return finalFuel;

}





int FuelSites::BDADisCFLoad (int CFLoad, int row, int col) {

	if (CFLoad <0)	CFLoad = 0;

	else if (CFLoad > 5)	CFLoad = 5;

	int finalFuel = CFLoad;

	for(int i = 0; i<pPDP->iBDANum; i++) {		//(m_pPDP->pBDAPDP[m_iBDANo]).sTSLBDA[i][j]

		if((pPDP->pBDAPDP[i]).sTSLBDA[row][col]==0){

			int BDASeverity = (pPDP->pBDAPDP[i]).cBDASeverity[row][col];

			if(BDASeverity>0 && BDASeverity<4) {

				//printf("col: %d  Row: %d  BDASeverity: %d\n", col, row, BDASeverity);

				finalFuel = finalFuel + BDAModCF[i*3+BDASeverity-1];

			}

		}

	}

	finalFuel = min (5,  max (0, finalFuel));

	if(finalFuel>CFLoad) {

		LANDUNIT *l;

		l=pfuelcoresites->locateLanduPt(row,col);

		//Original landis4.0: l=(*pfuelcoresites)(row,col)->landUnit

		//Changed By Qia on Oct 13 2008

		//<Add By Qia on Nov 19 2008>

		fuelsites.BefStChg(row,col);

		//</Add By Qia on Nov 19 2008>

		fuelsites(row,col)->timeOfCFAccumulation = fuelsites.getCFAccumulationTime(l->ltID, finalFuel);

		fuelsites(row,col)->beginCFDecompClass = finalFuel;

		//<Add By Qia on Nov 19 2008>

		fuelsites.AftStChg(row,col);

		//</Add By Qia on Nov 19 2008>

	}

	return finalFuel;

}





int FuelSites::HarvestDisFFLoad (int FFLoad, int row, int col) {

	// this function will return the fine fuel load after fire



	int harvetEvent = -1;

	int timeSinceLastHarvest = -999;

	int finalFuel = FFLoad;

	if (FFLoad <0)	FFLoad = 0;

	else if (FFLoad > 5)	FFLoad = 5;

	if (row>=0 && row <= rows && col>=0 && col<=cols) {

		timeSinceLastHarvest = (pPDP->sTSLHarvest)[row][col];

		harvetEvent = (pPDP->cHarvestEvent)[row][col];

		if(timeSinceLastHarvest==0 && harvetEvent>0) {

			FFLoad = HarvestModFF[(harvetEvent-1)*6 + FFLoad];

		}

	}

	finalFuel = min (5,  max (0, FFLoad));



	return finalFuel;

}



int FuelSites::HarvestDisCFLoad (int CFLoad, int row, int col) {

	// this function will return the fine fuel load after fire



	int harvetEvent = -1;

	int timeSinceLastHarvest = -999;

	int finalFuel = CFLoad;

	if (CFLoad <0)	CFLoad = 0;

	else if (CFLoad > 5)	CFLoad = 5;

	if (row>=0 && row <= rows && col>=0 && col<=cols) {

		timeSinceLastHarvest = (pPDP->sTSLHarvest)[row][col];

		harvetEvent = (pPDP->cHarvestEvent)[row][col];

		if(timeSinceLastHarvest==0 && harvetEvent>0) {

			

			//int CF1 = CFLoad;

			

			//harvetEvent = (pPDP->strHarvestEvent)[row][col];			

			CFLoad = HarvestModFF[(harvetEvent-1)*6 + CFLoad];

			//if(CFLoad>4)

			//	printf("Harvest -> CF from %d  to %d \n",CF1,CFLoad);

			

			finalFuel = min (5,  max (0, CFLoad));

			// set the start class of coarse fuel decompositation

			LANDUNIT *l;

			l=pfuelcoresites->locateLanduPt(row,col);//Original landis4.0: (*pfuelcoresites)(row,col)->landUnit

													//Changed By Qia on Oct 13 2008

			//<Add By Qia on Nov 19 2008>

				fuelsites.BefStChg(row,col);

				//</Add By Qia on Nov 19 2008>

			fuelsites(row,col)->timeOfCFAccumulation = fuelsites.getCFAccumulationTime(l->ltID, finalFuel);

			fuelsites(row,col)->beginCFDecompClass = finalFuel;

			//<Add By Qia on Nov 19 2008>

				fuelsites.AftStChg(row,col);

				//</Add By Qia on Nov 19 2008>

		}

	}

	return finalFuel;

}



/*

int FuelSites::UpdateFireRisk (int row, int col) {

	// this function will update the fire risk based new fine fuel load and coarse fuel loads after harvest

	int Risk = 0;

	int Intensity = 0;

	int Probility = 0;

	int timeSinceLastFuelManagement = -999;

	int timeSinceLastHarvest = -999;

	int timeSinceLastWind = -999;

	int timeSinceLastBDA = -999;	

	int FFLoad = 0;

	int CFLoad = 0;

	if (row>=0 && row <= rows && col>=0 && col<=cols) {

		FFLoad = (pPDP->cFineFuel)[row][col];

		CFLoad = (pPDP->cCoarseFuel)[row][col];

		timeSinceLastWind = (pPDP->sTSLWind)[row][col];

		// need to add timesincelastBDA in PDP

//		timeSinceLastBDA =  (pPDP->sTSLBDA)[row][col];

		timeSinceLastHarvest = (pPDP->sTSLHarvest)[row][col];

		timeSinceLastFuelManagement = (pPDP->sTSLFUELMAN)[row][col];



		if((timeSinceLastWind * timeSinceLastHarvest * timeSinceLastFuelManagement) ==0 ) {

			LANDUNIT *l;

			l=(*pfuelcoresites)(row,col)->landUnit;

			// change beginCFDecompositionClass and time of coarse fuel accumulation

			fuelsites(row,col)->timeOfCFAccumulation = fuelsites.getCFAccumulationTime(l->ltID, CFLoad);

			fuelsites(row,col)->beginCFDecompClass = CFLoad;				



			// Adujust fire intensity

			Intensity = fuelrule.getFireSeverity((int)FFLoad, (int)CFLoad);

			if (Intensity>5)	Intensity = 5;

			// Shang 03/04

			//fuelsites(pt.y, pt.x)->fireIntensity = Intensity;

			fuelsites.setFireIntensityClass(Intensity, row, col);			



			// Adjust fire risk			

			Probility = fuelsites.getFireProbabiltyClass (row, col);

			if(Probility>5)		Probility = 5;

			if (Intensity<=0 || Probility<=0)	Risk = 0;

			else	Risk = (char) fuelrule.fireRisk[Probility-1][Intensity-1];

			

			fuelsites.setFireRiskClass (Risk, row, col);

		}

	}

	return Risk;

}

*/





int FuelSites::CFAccumulation(int ltID, int timeOfCFAccum) {

	// this function will return coarse fuel accumulation

	int CFClass = 0;

	for (int i=4; i>=0; i-- ){

		if (timeOfCFAccum >= landtypeInfo[ltID].coarseFuelAccumulation[i]) {

			CFClass = i+1;

			break;

		}

	}

	return CFClass;

}





int FuelSites::CalculateCFLoad(int ltID, int currCFLoad, int timeOfCFAccum, int timeSinceLastDisturbance, int beginCFDecompClass) {

	// this function will return the coarse fuel load



	if (ltID<0 || ltID>=landtypeNum)

		errorSys("Error! CF landtype code > landtype Num.",STOP);

	int CFLoad = currCFLoad;

	int CFAccum = CFAccumulation(ltID, timeOfCFAccum);



	int CFAfterDecom = 0;

		int beginCFDecompYear = 999;

		if (beginCFDecompClass<5 && beginCFDecompClass>=0)

			beginCFDecompYear = landtypeInfo[ltID].coarseFuelDecomposition[beginCFDecompClass];

		int totalYear = beginCFDecompYear + timeSinceLastDisturbance;

		if (totalYear <=0)	CFAfterDecom = 5;

		else if (totalYear >= landtypeInfo[ltID].coarseFuelDecomposition[0])	CFAfterDecom = 0;

		else {



			for (int i=1; i<5; i++) {

				if ((totalYear < landtypeInfo[ltID].coarseFuelDecomposition[i-1]) && 

					(totalYear >= landtypeInfo[ltID].coarseFuelDecomposition[i]) )

				{

					CFAfterDecom = i;

					break;

				}

			}

		}





	CFLoad = max(CFAccum, CFAfterDecom);



	if (CFLoad<0)	CFLoad = 0;

	if (CFLoad>5)	CFLoad = 5;

	return CFLoad;

	

}



int FuelSites::getCFAccumulationTime (int ltID, int CFClass)  {

	// this function will return coarse fuel accumulation time

	int CFAccumulationTime = 0;

	if (ltID<0 || ltID>=landtypeNum)

		errorSys("Error! landtype code > landtype Num.",STOP);

	if (CFClass <=0)			return 0;

	else if (CFClass >5)	return landtypeInfo[ltID].coarseFuelAccumulation[4];

	else return landtypeInfo[ltID].coarseFuelAccumulation[CFClass-1];

	

}



int FuelSites::windDisFFLoad (int FFLoad, int row, int col) {



	int windClass = 0;

	int timeSinceLastWind = -999;

	int finalFuel = FFLoad;	

	if (row>=0 && row <= rows && col>=0 && col<=cols) {

		timeSinceLastWind = (pPDP->sTSLWind)[row][col];

		if(timeSinceLastWind==0) {	

			windClass = (pPDP->cWindSeverity)[row][col];

			if (windClass >0 && windClass <=5)			

				finalFuel = max(0, min (5, FFLoad + windModFF[windClass-1]));

		}

	}

	return finalFuel;

}



int FuelSites::windDisCFLoad (int CFLoad, int row, int col) {

	

	

	int windClass = 0;

	int timeSinceLastWind = -999;

	int finalFuel = CFLoad;	

	if (row>=0 && row <= rows && col>=0 && col<=cols) {

		timeSinceLastWind = (pPDP->sTSLWind)[row][col];

		if(timeSinceLastWind==0) {	

			windClass = (pPDP->cWindSeverity)[row][col];

			if (windClass >0 && windClass <=5)			

				finalFuel = max(0, min (5, CFLoad + windModFF[windClass-1]));

			// set the start class of coarse fuel decompositation

			LANDUNIT *l;

			l=pfuelcoresites->locateLanduPt(row,col);//Original landis4.0: (*pfuelcoresites)(row,col)->landUnit

													//changed By Qia on Oct 13 2008

			//<Add By Qia on Nov 19 2008>

				fuelsites.BefStChg(row,col);

				//</Add By Qia on Nov 19 2008>

			fuelsites(row,col)->timeOfCFAccumulation = fuelsites.getCFAccumulationTime(l->ltID, finalFuel);

			fuelsites(row,col)->beginCFDecompClass = finalFuel;		

			//<Add By Qia on Nov 19 2008>

				fuelsites.AftStChg(row,col);

				//</Add By Qia on Nov 19 2008>

		}

	}

	return finalFuel;

}



int FuelSites:: CrownFire(int fireInte, int i, int j) {

	

	if (fireInte<=0) return 0;

	else if (fireInte <3) return fireInte;

	else if (fireInte>=5)	return 5;

	SPECIE *s;

	SPECIESATTR *sa;

	int finalFire = fireInte;

	

	if (i>=0 && i <= rows && j>=0 && j<=cols) {

		float FQC = 0;

		int spNum = 0;

		s=(*pfuelcoresites)(i,j)->first();        //Get the first specie.

		sa=(*pfuelcoresites)(i,j)->specAtt();     //Associated attributes.

		int oldage = 0;

		int spID = 0;	

		while (s!=NULL && sa!=NULL) {

			oldage = s->oldest();									

			if(oldage >0) {						

				FQC = FQC + spFFAccumulation[spID].LiveFuelQualityCoeff;

				spNum++;						

			}

			spID ++;

			s = (*pfuelcoresites)(i,j)->next();

			// get the next species

			sa = (*pfuelcoresites)(i,j)->specAtt();				

			// get the associated attributes

			

		}		

		

		//pfuelcoresites->harvestplantcount=pfuelcoresites->harvestplantcount+spID;

		if (spNum <=0 || FQC<=0){

			

			return fireInte;

			}

		

		//printf("Crown fire  row: %d col: %d \n", i, j);

		

		// calculate the mean FQC

		FQC = FQC / (float)spNum;

		if (FQC >1)	FQC = 1;

		

		//printf("FQC:  %6.4f  Species Num: %d\n", FQC, spNum);

		

		

		//float prob =(float)((double)rand()/(double)(RAND_MAX+1));//original 4.0

		float prob=frand1();//try to test

	//printf("FQC %f  prob  <  %f\n", FQC, prob);



		//printf("Rand()  %f \n", prob);

		// if rand() >= FQC, won't have crown fire

		if (prob >= FQC) {

			//printf("\n");

			

			return fireInte;

		}

		LANDUNIT *l;

		l=pfuelcoresites->locateLanduPt(i,j);//original landis4.0: (*pfuelcoresites)(i,j)->landUnit

											//changed By Qia on Oct 13 2008

		float p = landtypeInfo[l->ltID].CrownFireCoeff;

		

		//printf("Landtype p: %6.2f", p);

		//prob =(float)((double)rand()/(double)(RAND_MAX+1));//original 4.0

		prob=frand1();//try to test

		

		//printf("P   %f  prob  <  %f\n", p, prob);

		//pfuelcoresites->harvestplantcount=pfuelcoresites->harvestplantcount+(int)(prob*1000);

		if (prob < p)		{

			finalFire = 5;

			

			}

		//printf("rand() %f Initial fire:  %d -> Final fire  %d \n\n", prob, fireInte, finalFire);

	}	

	

	return finalFire;

}



//<Add By Qia on Nov 19 2008>

int FuelSites::SITE_compare(int site1_x,int site1_y,int site2_x,int site2_y)

{

	int x,y;

	int result;

	FuelSite *site1, *site2;

	x=(site1_x-1)*cols;

	x=x+site1_y-1;



	y=(site2_x-1)*cols;

	y=y+site2_y-1;



	site1=map[x];

	site2=map[y];

	result=SITE_compare(site1,site2);

	return result;

}

int FuelSites::SITE_compare(FuelSite * site1,FuelSite * site2)

{

	

	

			if(site1->beginCFDecompClass>site2->beginCFDecompClass)

				return 1;

			if(site1->beginCFDecompClass<site2->beginCFDecompClass)

				return 2;



			if(site1->timeOfCFAccumulation>site2->timeOfCFAccumulation)

				return 1;

			if(site1->timeOfCFAccumulation<site2->timeOfCFAccumulation)

				return 2;



			if(site1->cFireProbabilityClass>site2->cFireProbabilityClass)

				return 1;

			if(site1->cFireProbabilityClass<site2->cFireProbabilityClass)

				return 2;



			if(site1->fireRegime>site2->fireRegime)

				return 1;

			if(site1->fireRegime<site2->fireRegime)

				return 2;



			

	return 0;

}



int FuelSites::SITE_sort()

//use babble algorithm to sort the initial site list array

{

	int size,i,j;

	FuelSite *site1, *site2,*temp;

	size=SortedIndex.size();

	for(i=SortedIndex.size()-1;i>0;i--)

		{

			for(j=0;j<=i-1;j++)

				{

					site1=SortedIndex.at(j);

					site2=SortedIndex.at(j+1);

					if(SITE_compare(site1,site2)==1)

						{

							temp=SortedIndex.at(j);

							SortedIndex.at(j)=SortedIndex.at(j+1);

							SortedIndex.at(j+1)=temp;

						}

				}

		}

	return 1;

}



int FuelSites::SITE_insert(int pos_sortIndex, FuelSite *site, int i, int j)

//when there is a new site during harvest, we need to 

//check if the new site already exists, if yes combine with existing one

//if not insert to the position according to sort

{

	

	int x;

	int ifexist=0, pos=0;

	FuelSite *temp;

	x=(i-1)*cols;

	x=x+j-1;  

	std::vector<FuelSite *>::iterator temp_sitePtr;

	temp_sitePtr=SortedIndex.begin();

	

	SITE_LocateinSortIndex(site, &pos,&ifexist);

	if(ifexist)

		{

			map[x]=SortedIndex.at(pos);

			map[x]->numofsites++;

			//delete  site;

		}

	else

		{

			temp=new FuelSite;

			temp->beginCFDecompClass=site->beginCFDecompClass;

			temp->cFireProbabilityClass=site->cFireProbabilityClass;

			temp->fireRegime=site->fireRegime;

			temp->timeOfCFAccumulation=site->timeOfCFAccumulation;

			temp->numofsites=1;

			map[x]=temp;

			SortedIndex.insert(temp_sitePtr+pos, temp);

		}

	return 1;

}



int FuelSites::SITE_delete(int pos_sortIndex, FuelSite *site, int i, int j)

//When a site disappears, delete it

{

	int x;

	std::vector<FuelSite *>::iterator temp_sitePtr;

	x=(i-1)*cols;

	x=x+j-1;

	if(site!=SortedIndex.at(pos_sortIndex))

		return 0;

	if(site!=map[x])

		return 0;

	delete site;

	temp_sitePtr=SortedIndex.begin();

	SortedIndex.erase(temp_sitePtr+pos_sortIndex);

	return 1;	

}



int FuelSites::SITE_LocateinSortIndex(FuelSite *site, int *pos, int *ifexist)

//Find if a new site exists in sorted list

//If a new site exists, find its location and set *ifexist as 1

//if this no site matches this one, find location before which new site pointer should be inserted

//By Qia Nov 07 2008

{

	int begin, end, mid;

	FuelSite *temp;

	int temp_flag;

	*ifexist=0;

	begin=0;

	end=SortedIndex.size();

	if(end==0){

		printf("No site at all wrong wrong wrong\n");

		return -1;

		}

	end--;

	mid=(begin+end)/2;

	temp=SortedIndex.at(mid);

	while(begin<end)

		{

			temp_flag=SITE_compare(site,temp);

			if(temp_flag==0)

				{

					*ifexist=1;

					*pos=mid;

					return 1;

				}

			else if(temp_flag==1)

				{

					begin=mid+1;

					mid=(begin+end)/2;

				}

			else if(temp_flag==2)

				{

					end=mid-1;

					mid=(begin+end)/2;

				}

			else

				{

					return -1;

				}

			temp=SortedIndex.at(mid);

		}

	temp_flag=SITE_compare(site,temp);

	if(temp_flag==0)

		{

			*ifexist=1;

			*pos=mid;

			return 1;

		}

	else if(temp_flag==2)

		{

			*ifexist=0;

			*pos=mid;

			return 0;

		}

	else if(temp_flag==1)

		{

			*ifexist=0;

			*pos=mid+1;

			return 0;

		}

	else

		{

			return -1;

		}

}



void FuelSites::fillinSitePt(int i, int j, FuelSite *site)

//

{

	int x;

	x=(i-1)*cols;

	x=x+j-1;

	map[x]=site;

}



FuelSite * FuelSites::locateSitePt(int i, int j)

//

{

	int x;

	x=(i-1)*cols;

	x=x+j-1;

	return map[x];

}



void FuelSites::BefStChg(int i, int j)

//Before Site Change

//This function back up a site and following changes are based on this seprated site

//sort vector is not touched here

{

	FuelSite *temp;

	temp=locateSitePt(i,j);

	

	sitetouse->beginCFDecompClass=temp->beginCFDecompClass;

	sitetouse->cFireProbabilityClass=temp->cFireProbabilityClass;

	sitetouse->fireRegime=temp->fireRegime;

	sitetouse->timeOfCFAccumulation=temp->timeOfCFAccumulation;

	

	if(temp->numofsites==1)

		{

			int pos,ifexist=0;

			SITE_LocateinSortIndex(sitetouse,&pos,&ifexist);

			if(ifexist)

				{

					std::vector<FuelSite *>::iterator temp_sitePtr;

					temp_sitePtr=SortedIndex.begin();

					SortedIndex.erase(temp_sitePtr+pos);

					delete temp;

				}

			else

				{

					printf("num of vectors %d\n",SortedIndex.size());

					printf("ERROR ERROR ERROR ERROR!!~~~%d\n",pos);

					

				}

		}

	else if(temp->numofsites<=0)

		{

			printf("NO NO NO NO NO\n");

		}

	else

		{

			temp->numofsites--;

		}

	fillinSitePt(i,j,sitetouse);

	return ;

}

void FuelSites::AftStChg(int i,int j)

//After Site Change

//This function does combination and delete of the seprated site made by BefStChg(int i, int j)

//insert this site to the sorted vector

{

	SITE_insert(0,sitetouse,i,j);

	return ;

}

//</Add By Qia on Nov 19 2008>