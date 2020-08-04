#include <ctype.h>

#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include <time.h>

#include <vector>

#include "defines.h"

#include "system1.h"

#include "error.h"

#include "species.h"

#include "site.h"

#include "map8.h"

#include "reclass.h"

#include "reclass2.h"

#include "fire.h"

#include "wind.h"

//#include <vld.h>

//#include "BDAS.h"

#include "landis.h"

#include "PARAMS.H"

#include "io.h"

#include <direct.h>

#include <errno.h>

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#ifdef __UNIX__

#include <sys/stat.h>

#endif



#include "BDAExport.h"

#include <windows.h>  

//*gdal 

#include <iostream>

#include <cstdio>

#include <stdio.h>

#include "gdal_priv.h"

#include "cpl_conv.h" // for CPLMalloc()

#include "cpl_string.h"

#include "ogr_spatialref.h"




//#ifdef __HARVEST__

//#endif

//////////////////////////////////////////////////////////////////////////////

//			NON INTERACTIVE VERSION IMPLEMENTATION		    //

//////////////////////////////////////////////////////////////////////////////

#define TPA		0

#define BA		1

#define Bio		2

#define Car		3

#define IV		4

#define Seeds	5

#define RDensity	6

#define DBH 7





int reclassMethods=0,numAgeMaps=0;   

static int red[maxLeg]={0,0,100,150,200,0,0,0,150,0,150,255,80,150,255};

static int green[maxLeg]={0,0,0,0,0,100,150,255,0,150,150,255,80,150,255};

static int blue[maxLeg]={0,150,0,0,0,0,0,0,150,150,0,0,80,150,255};



static int red2[maxLeg]={0,70,0,0,0,0,0,0,200,100,255,150,200,200,255,255};

static int green2[maxLeg]={0,70,0,0,0,150,200,255,30,200,50,50,200,0,255};

static int blue2[maxLeg]={0, 70,125,200,255,0,100,0,30,50,50,0,0,255};



static int red3[maxLeg]={0,70,0,0,0,0,0,0,200,100,255,150,200,200,255,255};

static int green3[maxLeg]={0,70,0,0,0,150,200,255,30,200,50,50,200,0,255};

static int blue3[maxLeg]={0,70,125,200,255,0,100,0,30,50,50,0,0,255};



static int red4[maxLeg]={0,70,0,0,0,0,0,0,200,100,255,150,200,200,255,255};

static int green4[maxLeg]={0,70,0,0,0,150,200,255,30,200,50,50,200,0,255};

static int blue4[maxLeg]={0,70,125,200,255,0,100,0,30,50,50,0,0,255};



//for Dll

extern int gDLLMode;

//end for dll

//extern BDAS*	  pBDAS;

extern HINSTANCE	  gLibBDA;



//<Add By Qia on July 8 2009>

vector<string> BioMassFileNames;

vector<string> BasalFileNames;

vector<string> TreesFileNames;

vector<string> IVFileNames; //add April 05 2010

vector<string> DBHFileNames; //add By Qia on April 09 2010

vector<string> RDFileNames;// Add by Qia on Nov 03 2010

vector<string> SeedsFileNames;//Add By Qia on Nov 03 2010

int flagoutputBiomass;

int flagoutputBasal;

int flagoutputTrees;

int flagoutputIV; //add April 05 2010

int flagoutputDBH; //Add April 09 2010

//</Add By Qia on July 8 2009>



//<Add By Qia on Dec 30 2010>

double *AgeDistOutputBuffer_TPA = NULL;

double *AgeDistOutputBuffer_BA = NULL;

double *AgeDistOutputBuffer_TPA_landtype = NULL;

double *AgeDistOutputBuffer_BA_landtype = NULL;



void AgeDistOutputBufferInitialize(int specNum, int LandTypeNum)

{

	if(sites.Flag_AgeDistStat==0)

		return ;

	AgeDistOutputBuffer_TPA=new double[specNum*500/sites.TimeStep*500/sites.TimeStep];

	AgeDistOutputBuffer_BA=new double[specNum*500/sites.TimeStep*500/sites.TimeStep];

	for(int i =0; i< specNum*500/sites.TimeStep*500/sites.TimeStep ; i++){

		AgeDistOutputBuffer_TPA[i]=0;

		AgeDistOutputBuffer_BA[i] =0;

		}

	AgeDistOutputBuffer_TPA_landtype=new double[specNum*500/sites.TimeStep*500/sites.TimeStep*LandTypeNum];

	AgeDistOutputBuffer_BA_landtype=new double[specNum*500/sites.TimeStep*500/sites.TimeStep*LandTypeNum];

	for(int i =0; i< specNum*500/sites.TimeStep*500/sites.TimeStep*LandTypeNum ; i++){

		AgeDistOutputBuffer_TPA_landtype[i]=0;

		AgeDistOutputBuffer_BA_landtype[i] =0;

		}

}

void AgeDistOutputBufferRelease()

{

	if(sites.Flag_AgeDistStat==0)

		return ;

	if(AgeDistOutputBuffer_TPA)

		delete AgeDistOutputBuffer_TPA;

	if(AgeDistOutputBuffer_BA)

		delete AgeDistOutputBuffer_BA;

	if(AgeDistOutputBuffer_TPA_landtype)

		delete AgeDistOutputBuffer_TPA_landtype;

	if(AgeDistOutputBuffer_BA_landtype)

		delete AgeDistOutputBuffer_BA_landtype;

}

void SetAgeDistoutputBuffer(int type, int specIndex, int ageIndex, int yearIndex, double value)

{

	if(sites.Flag_AgeDistStat==0)

		return ;

	int index;

	int dimension = 500/sites.TimeStep;

	index = (specIndex-1)*dimension*dimension+(ageIndex-1)*dimension+yearIndex-1;

	if(type==BA){

		AgeDistOutputBuffer_BA[index] = value;

		}

	if(type==TPA){

		AgeDistOutputBuffer_TPA[index] = value;

		}

}

double GetAgeDistoutputBuffer(int type, int specIndex, int ageIndex, int yearIndex)

{

	

	int index;

	int dimension = 500/sites.TimeStep;

	index = (specIndex-1)*dimension*dimension+(ageIndex-1)*dimension+yearIndex-1;

	if(type==BA){

		return AgeDistOutputBuffer_BA[index];

		}

	if(type==TPA){

		return AgeDistOutputBuffer_TPA[index];

		}

}

void SetAgeDistoutputBuffer_Landtype(int type, int specIndex, int ageIndex, int yearIndex, int landtypeIndex, double value)

{

	if(sites.Flag_AgeDistStat==0)

		return ;

	int index;

	int dimension = 500/sites.TimeStep;

	index = (landtypeIndex)*sites.specNum*dimension*dimension+(specIndex-1)*dimension*dimension+(ageIndex-1)*dimension+yearIndex-1;

	if(type==BA){

		AgeDistOutputBuffer_BA_landtype[index] = value;

		}

	if(type==TPA){

		AgeDistOutputBuffer_TPA_landtype[index] = value;

		}

}

double GetAgeDistoutputBuffer_Landtype(int type, int specIndex, int ageIndex, int yearIndex, int landtypeIndex)

{

	

	int index;

	int dimension = 500/sites.TimeStep;

	index = (landtypeIndex)*sites.specNum*dimension*dimension+(specIndex-1)*dimension*dimension+(ageIndex-1)*dimension+yearIndex-1;

	if(type==BA){

		return AgeDistOutputBuffer_BA_landtype[index];

		}

	if(type==TPA){

		return AgeDistOutputBuffer_TPA_landtype[index];

		}

}



//</Add By Qia on Dec 30 2010>



//extern STANDS stands;

//<Add By Qia on Oct 22 2008>

void lookupredundant(int *combineMatrix, int numCovers)

//This function is to look up the sites with same species structure

//for future delete of redundant site

//To make sure all sites are different from each other during run time

//By Qia Oct 22 2008

{

	int i,j,ifequal;

	SITE *siteI,*siteJ;

	for(i=0;i<numCovers-1;i++)

		{

			if(i==combineMatrix[i]){

				siteI=sites.SortedIndex.at(i);

				for(j=i+1;j<numCovers;j++)

					{

						siteJ=sites.SortedIndex.at(j);

						if(j==combineMatrix[j])

							{

								ifequal=sites.SITE_compare(siteI,siteJ);

								if(ifequal==0)

									{

										combineMatrix[j]=i;

									}

							}

					}

				}

		}

	return ;

}

//</Add By Qia on Oct 22 2008>



//<Add By Qia on Oct 22 2008>

void deleteRedundantInitial(int *combineMatrix, int numCovers)

//after looking up, this function is to delete the redunt sites 

//By Qia on Oct 22 2008

{

	int i;

	SITE *temp;

	for(i=numCovers-1;i>=0;i--)

		{

			if(i!=combineMatrix[i])

				{

					temp=sites.SortedIndex.at(i);

					delete temp;

					sites.SortedIndex.erase(sites.SortedIndex.begin()+i);

				}

		}

	return ;

}

//</Add By Qia on Oct 22 2008>

void HSV_to_RGB(float h, float s, float v,

                int &red, int &green, int &blue)

//This will convert HSV colors to RGB.



{

float f, p, q, t, r, g, b;

int i;



if (h==360.0)

   h=0.0;

h=h/(float)60.0;

i=(int)h;

f=h-i;

p=v*(1-s);

q=v*(1-(s*f));

t=v*(1-(s*(1-f)));

switch (i)

   {

    case 0:   r=v; g=t; b=p; break;

    case 1:   r=q; g=v; b=p; break;

    case 2:   r=p; g=v; b=t; break;

    case 3:   r=p; g=q; b=v; break;

    case 4:   r=t; g=p; b=v; break;

    case 5:   r=v; g=p; b=q; break;

    default:  printf("Exit from HSV_to_RGB\n");exit(0);

   }

red=(int)(r*255.0);   //Nim: cast to (int)

green=(int)(g*255.0); //Nim: cast to (int)

blue=(int)(b*255.0);  //Nim: cast to (int)

}



void printMessage

(const char *mssg)

//This will print a message on the CRT screen.



{

printf("%s\n",mssg);

fflush(stdout); 

}



void ioInit()

//This will call any computer dependent io calls (i.e. set up graphics

//system) at start up.



{

printMessage("Beginning Landis Run.\n");

}

void outputFileheader(FILE *fp)

{

	fprintf(fp,"ncols  %d\n",sites.numColumns());

	fprintf(fp,"nrows  %d\n",sites.numRows());

	fprintf(fp,"xllcorner  %.f\n", sites.xLLCorner-*(((float*)sites.getHeader())+30)/2);

	fprintf(fp,"yllcorner  %.f\n",sites.yLLCorner-*(((float*)sites.getHeader())+30)*sites.numRows()+*(((float*)sites.getHeader())+30)/2);

	fprintf(fp,"cellsize  %.f\n",*(((float*)sites.getHeader())+30));

	fprintf(fp,"NODATA_value  -9999\n");

	

}



void initiateOutput_landis70Pro()

{

	FILE *fpBiomass=NULL,*fpBasalArea=NULL,*fpTrees=NULL;

	FILE *fpOutputSpecieNames=NULL;

	char filename[256];

	char str[300];

	/*sprintf(str,"%s/output70index.dat",parameters.outputDir);

	if ((fpOutputSpecieNames = LDfopen(str, 3)) == NULL)

		{

			errorSys("Can not open species index output file",STOP);

		}

	fprintf(fpOutputSpecieNames,"Iterations: %d\n",parameters.numberOfIterations); //Add By Qia on Aug 16 2010

	fprintf(fpOutputSpecieNames,"TimeStep: %d\n",sites.TimeStep); //Add By Qia on Aug 16 2010

	fprintf(fpOutputSpecieNames,"%d\n",sites.specNum);

	

	for(int i=1;i<=sites.specNum;i++)

			{

			fprintf(fpOutputSpecieNames,"%s\n",speciesAttrs(i)->name);

			}

	fclose(fpOutputSpecieNames);*/

	if(strcmp(reMethods[0],"N/A")!=0)

		{

		/*if ((fpBiomass = LDfopen(reMethods[0], 1)) == NULL)

			errorSys("can not find biomassIndex output file",STOP);

		flagoutputBiomass=1;

		for(int i=0;i<sites.specNum;i++)

			{

			fscanc(fpBiomass,"%s",filename);

			BioMassFileNames.push_back(string(filename));

			}*/

		for(int i=1;i<=sites.specNum;i++)

			{

			//fscanc(fpBiomass,"%s",filename);

			sprintf(filename,"%s_Bio",speciesAttrs(i)->name);

			BioMassFileNames.push_back(string(filename));

			}

		flagoutputBiomass=1;

		}

	else

		{

		flagoutputBiomass=0;

		}

	

	if(strcmp(reMethods[1],"N/A")!=0)

		{

		/*if ((fpBasalArea= LDfopen(reMethods[1], 1)) == NULL)

			errorSys("can not find BasalAreaIndex output file",STOP);

		flagoutputBasal=1;

		for(int i=0;i<sites.specNum;i++)

			{

			fscanc(fpBasalArea,"%s",filename);

			BasalFileNames.push_back(string(filename));

			}*/

		for(int i=1;i<=sites.specNum;i++)

			{

			//fscanc(fpBiomass,"%s",filename);

			sprintf(filename,"%s_BA",speciesAttrs(i)->name);

			BasalFileNames.push_back(string(filename));

			}

		flagoutputBasal=1;

		}

	else

		{

		flagoutputBasal=0;

		}

	

	if(strcmp(reMethods[2],"N/A")!=0)

		{

		/*if ((fpTrees= LDfopen(reMethods[2], 1)) == NULL)

			errorSys("can not find Trees index output file",STOP);

		flagoutputTrees=1;

		for(int i=0;i<sites.specNum;i++)

			{

			fscanc(fpTrees,"%s",filename);

			TreesFileNames.push_back(string(filename));

			}*/

		for(int i=1;i<=sites.specNum;i++)

			{

			//fscanc(fpBiomass,"%s",filename);

			sprintf(filename,"%s_TreeNum",speciesAttrs(i)->name);

			TreesFileNames.push_back(string(filename));

			}

		flagoutputTrees=1;

		}

	else

		{

		flagoutputTrees=0;

		}

	{

		for(int i=1;i<=sites.specNum;i++)

		{

		//fscanc(fpBiomass,"%s",filename);

		sprintf(filename,"%s_IV",speciesAttrs(i)->name);

		IVFileNames.push_back(string(filename));



		sprintf(filename,"%s_AvailableSeed",speciesAttrs(i)->name);

		SeedsFileNames.push_back(string(filename));



		sprintf(filename,"%s_RelativeDensity",speciesAttrs(i)->name);

		RDFileNames.push_back(string(filename));

		}

	flagoutputIV=1;

	}

		

		{

			for(int i=1;i<=sites.specNum;i++)

			{

			//fscanc(fpBiomass,"%s",filename);

			sprintf(filename,"%s_DBH",speciesAttrs(i)->name);

			DBHFileNames.push_back(string(filename));

			}

		flagoutputDBH=1;

		}

	//flagoutputBasal=sites.GetOutputGeneralFlagArray(sites.specNum,BA);

	//flagoutputTrees=sites.GetOutputGeneralFlagArray(sites.specNum,TPA);

	//flagoutputBiomass=sites.GetOutputGeneralFlagArray(sites.specNum,Bio);

	//flagoutputIV=sites.GetOutputGeneralFlagArray(sites.specNum,IV);

	if(fpBiomass)

		fclose(fpBiomass);

	if(fpBasalArea)

		fclose(fpBasalArea);

	if(fpTrees)

		fclose(fpTrees);

	AgeDistOutputBufferInitialize(sites.specNum,landUnits.number());

}

void AgeDistOutputFromBufferToFile(){

	FILE *output;

	int count_year;

	int count_age;

	int count_landtype;

	int age1,age2, year;

	int k=1;

	double value;

	char str[300];

	sprintf(str,"%s/BA_TPADist.txt",parameters.outputDir);

	if(sites.Flag_AgeDistStat==0)

		return ;

	printf("Output BA and TPA stat:\n");

	if ((output = LDfopen(str, 3)) == NULL)

			errorSys("can not open output file 1",STOP);

	for(k=1;k<=sites.specNum;k++)

		{

		fprintf(output,"%s:\n", speciesAttrs(k)->name);

		fprintf(output,"AgeRange\\Year: ");

		for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

			{

			sites.GetAgeDistStat_YearVal(k-1,count_year,&year);

			fprintf(output,"TPA_%d ",year);

			}

		for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

			{

			sites.GetAgeDistStat_YearVal(k-1,count_year,&year);

			fprintf(output,"BA_%d ",year);

			}

		fprintf(output,"\n");

		for(count_age=1;count_age<=sites.GetAgeDistStat_AgeRangeCount(k-1);count_age++)

			{

			sites.GetAgeDistStat_AgeRangeVal(k-1,count_age,&age1,&age2);

			fprintf(output,"Age%d-%d ",age1,age2);

			for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

				{

				value = GetAgeDistoutputBuffer(TPA,k,count_age,count_year);

				fprintf(output,"%lf ",value);

				}

			for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

				{

				value = GetAgeDistoutputBuffer(BA,k,count_age,count_year);

				fprintf(output,"%lf ",value);

				}

			fprintf(output,"\n");

			}

		}

	fprintf(output,"\n\n");

	for(count_landtype=0; count_landtype<landUnits.number();count_landtype++)

		{

		fprintf(output,"Landtype:%d\n",count_landtype);

		for(k=1;k<=sites.specNum;k++)

			{

			fprintf(output,"%s:\n", speciesAttrs(k)->name);

			fprintf(output,"AgeRange\\Year: ");

			for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

				{

				sites.GetAgeDistStat_YearVal(k-1,count_year,&year);

				fprintf(output,"TPA_%d ",year);

				}

			for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

				{

				sites.GetAgeDistStat_YearVal(k-1,count_year,&year);

				fprintf(output,"BA_%d ",year);

				}

			fprintf(output,"\n");

			for(count_age=1;count_age<=sites.GetAgeDistStat_AgeRangeCount(k-1);count_age++)

				{

				sites.GetAgeDistStat_AgeRangeVal(k-1,count_age,&age1,&age2);

				fprintf(output,"Age%d-%d ",age1,age2);

				for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

					{

					value = GetAgeDistoutputBuffer_Landtype(TPA,k,count_age,count_year,count_landtype);

					fprintf(output,"%lf ",value);

					}

				for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

					{

					value = GetAgeDistoutputBuffer_Landtype(BA,k,count_age,count_year,count_landtype);

					fprintf(output,"%lf ",value);

					}

				fprintf(output,"\n");

				}

			}

		}

	

	AgeDistOutputBufferRelease();

	fclose(output);

}

void putOutput_AgeDistStat(int itr){

	int i,j,k,m,kk;  //Nim: added this line

	int count_year;

	int count_age;

	int count_landtype;

	time_t ltime,ltimeTemp;

	double TmpBasalAreaS=0;

	int TmpTreeT=0,TmpTreesS=0;

	int age1,age2, year;

	if(sites.Flag_AgeDistStat==0){

		return ;

		}

	//Below is for every species

		for(k=1;k<=sites.specNum;k++)

			{

			for(count_age=1;count_age<=sites.GetAgeDistStat_AgeRangeCount(k-1);count_age++)

				{

				sites.GetAgeDistStat_AgeRangeVal(k-1,count_age,&age1,&age2);

				

				for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

					{

						sites.GetAgeDistStat_YearVal(k-1,count_year,&year);

						if(itr*sites.TimeStep == year){

							TmpBasalAreaS=0;

							for(i=sites.numRows();i>0;i--)

							{
								
							//printf("\r%3d%%",100*i/sites.numRows());

							for(j=1;j<=sites.numColumns();j++)

								{		
									LANDUNIT *l;
									l = sites.locateLanduPt(i,j);
								for(m=min(speciesAttrs(k)->longevity,age1)/sites.TimeStep;m<=min(speciesAttrs(k)->longevity,age2)/sites.TimeStep;m++)	

									{

										TmpBasalAreaS+=sites.GetGrowthRates(k,m,l->ltID)*sites.GetGrowthRates(k,m,l->ltID)/4*3.1415926*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k)/10000.00;

									//TmpBasalAreaS+=0.005454*sites.GetGrowthRates(k,m)*sites.GetGrowthRates(k,m)*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k);

									}

								}

							}

							SetAgeDistoutputBuffer(BA,k,count_age,count_year,TmpBasalAreaS);

							}

						

					}

				

				}

			for(count_age=1;count_age<=sites.GetAgeDistStat_AgeRangeCount(k-1);count_age++)

				{

				sites.GetAgeDistStat_AgeRangeVal(k-1,count_age,&age1,&age2);

				for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

					{

					sites.GetAgeDistStat_YearVal(k-1,count_year,&year);

					if(itr*sites.TimeStep == year){

						TmpTreesS=0;

						for(i=sites.numRows();i>0;i--)

							{

							

							for(j=1;j<=sites.numColumns();j++)

								{			

								for(m=min(speciesAttrs(k)->longevity,age1)/sites.TimeStep;m<=min(speciesAttrs(k)->longevity,age2)/sites.TimeStep;m++)

									{

									TmpTreesS+=sites(i,j)->SpecieIndex(k)->getTreeNum(m,k);

									}

								}

							}

						SetAgeDistoutputBuffer(TPA,k,count_age,count_year,(double)TmpTreesS);

						}

						}

					

				}

					

			

			}

	for(count_landtype=0; count_landtype<landUnits.number();count_landtype++)

		{

		for(k=1;k<=sites.specNum;k++)

			{

			for(count_age=1;count_age<=sites.GetAgeDistStat_AgeRangeCount(k-1);count_age++)

				{

				sites.GetAgeDistStat_AgeRangeVal(k-1,count_age,&age1,&age2);

				

				for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

					{

					sites.GetAgeDistStat_YearVal(k-1,count_year,&year);

					if(itr*sites.TimeStep == year){

						TmpBasalAreaS=0;

						for(i=sites.numRows();i>0;i--)

						{

						//printf("\r%3d%%",100*i/sites.numRows());

						for(j=1;j<=sites.numColumns();j++)

							{
								LANDUNIT *l;
								l = sites.locateLanduPt(i,j);
							if(sites.locateLanduPt(i,j) == landUnits(count_landtype))

								{

								for(m=min(speciesAttrs(k)->longevity,age1)/sites.TimeStep;m<=min(speciesAttrs(k)->longevity,age2)/sites.TimeStep;m++)	

									{

										TmpBasalAreaS+=sites.GetGrowthRates(k,m,l->ltID)*sites.GetGrowthRates(k,m,l->ltID)/4*3.1415926*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k)/10000.00;

									//TmpBasalAreaS+=0.005454*sites.GetGrowthRates(k,m)*sites.GetGrowthRates(k,m)*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k);

									}

								}

							

							}

						}

						SetAgeDistoutputBuffer_Landtype(BA,k,count_age,count_year,count_landtype,TmpBasalAreaS);

						}

						

					}

				

				}

			for(count_age=1;count_age<=sites.GetAgeDistStat_AgeRangeCount(k-1);count_age++)

				{

				sites.GetAgeDistStat_AgeRangeVal(k-1,count_age,&age1,&age2);

				for(count_year = 1; count_year <= sites.GetAgeDistStat_YearCount(k-1); count_year++)

					{

					sites.GetAgeDistStat_YearVal(k-1,count_year,&year);

					if(itr*sites.TimeStep == year){

						TmpTreesS=0;

						for(i=sites.numRows();i>0;i--)

							{

							

							for(j=1;j<=sites.numColumns();j++)

								{	

								if(sites.locateLanduPt(i,j) == landUnits(count_landtype))

									{

									for(m=min(speciesAttrs(k)->longevity,age1)/sites.TimeStep;m<=min(speciesAttrs(k)->longevity,age2)/sites.TimeStep;m++)

										{

										TmpTreesS+=sites(i,j)->SpecieIndex(k)->getTreeNum(m,k);

										}

									}

								

								}

							}

						SetAgeDistoutputBuffer_Landtype(TPA,k,count_age,count_year,count_landtype,(double)TmpTreesS);

						}

					}

					

				}

					

			

			}

		}

	

			

}

void putOutput_Landis70Pro(int rep, int itr, int freq[], double wAdfGeoTransform[])

{

int i,j,k,m,kk;  //Nim: added this line

char str[100], str1[100], str2[100], str3[100], str4[100], str5[100];

char *pdest; //hsh

int ch= '\\';   //hsh

char strMsg[256];

time_t ltime,ltimeTemp;

FILE *fpTotalBiomass,*fpTotalcarbon,*fptotalbasal,*fptotaltrees,*fptotalRD, *fpRD, *fpIV, *fpDBH;

FILE *fpbiomass,*fpbasal,*fptree,*fpSeeds;

double TmpBiomassT=0,TmpBiomassS=0, TmpC=0, TmpBasalAreaT=0,TmpBasalAreaS=0,TmpCarbon=0,TmpCarbonTotal=0,TmpRDTotal;

int TmpTreeT=0,TmpTreesS=0;

const char *pszFormat = "HFA"; //*

GDALDriver *poDriver;//*

char **papszMetadata;//*

poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);//*

if (poDriver == NULL)//*
exit(1);//*

papszMetadata = poDriver->GetMetadata();//*

char **papszOptions = NULL;//*

//double wAdfGeoTransform[6] = { 0.00, parameters.cellSize, 0.00, 600.00, 0.00, -parameters.cellSize };//*

float *pafScanline;//*
float *pafScanline1;//*
float *pafScanline2;//*
float *pafScanline3;//*
float *pafScanline4;//*
float *pafScanline5;//*
unsigned int *pintScanline;

GDALRasterBand *outPoBand;//*
GDALRasterBand *outPoBand1;//*
GDALRasterBand *outPoBand2;//*
GDALRasterBand *outPoBand3;//*
GDALRasterBand *outPoBand4;//*
GDALRasterBand *outPoBand5;//*

GDALDataset *poDstDS;//*
GDALDataset *poDstDS1;//*
GDALDataset *poDstDS2;//*
GDALDataset *poDstDS3;//*
GDALDataset *poDstDS4;//*
GDALDataset *poDstDS5;//*

time(&ltime);

printf("Start 7.0 Style writing output at %s",ctime(&ltime));

//if (((itr%freq[4])==0)&&(freq[4]<=sites.TimeStep)||(itr*sites.TimeStep==freq[4])

 //     &&(freq[4]>=0)&&(!rep))




{

	

	//Below is for every species

	//1.Bio

	for(k=1;k<=sites.specNum;k++)

		{

		if(sites.GetOutputGeneralFlagArray(k-1,Bio))

			{

			if(strcmp(BioMassFileNames[k-1].c_str(),"N/A")!=0)

				{

					pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
					/*sprintf(str,"%s/%s_%d.asc",parameters.outputDir,BioMassFileNames[k-1].c_str(),itr*sites.TimeStep);

					if ((fpbiomass = LDfopen(str, 3)) == NULL)

						errorSys("can not open output file 1",STOP);

 					outputFileheader(fpbiomass);*/

				

			//	if ((itr*freq[0] <= parameters.numberOfIterations)){

							//pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

							sprintf(str1, "%s/%s_%d.img", parameters.outputDir, BioMassFileNames[k - 1].c_str(), itr* sites.TimeStep);//*

							poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

							if (poDstDS == NULL)

								errorSys("Img file not be created.", STOP);//*

							poDstDS->SetGeoTransform(wAdfGeoTransform);//*

							poDstDS->SetProjection(parameters.pszSRS_WKT);

							outPoBand = poDstDS->GetRasterBand(1);//*


							for (i = sites.numRows(); i > 0; i--)

							{

								//printf("\r%3d%%",100*i/sites.numRows());

								for (j = 1; j <= sites.numColumns(); j++)

								{
									LANDUNIT *l;
									l = sites.locateLanduPt(i, j);
									TmpBiomassS = 0;

									for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

									{

										if (sites.GetGrowthRates(k, m, l->ltID) >= sites.GetBiomassThreshold())

											TmpBiomassS += exp(sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 1) + sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 2)*log(sites.GetGrowthRates(k, m, l->ltID)))*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 1000.00;

									}

									//fprintf(fpbiomass,"%f ",TmpBiomassS);	

									*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBiomassS;//*

								}

							}

							//fclose(fpbiomass);

							outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

							if (poDstDS != NULL)
								GDALClose((GDALDatasetH)poDstDS);//*

							CPLFree(pafScanline);
							CSLDestroy(papszOptions); //*


							//CPLFree(pafScanline);
					//	}

				//if (parameters.numberOfIterations % freq[0] !=0){

				//	//pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

				//	sprintf(str1, "%s/%s_%d.img", parameters.outputDir, BioMassFileNames[k - 1].c_str(), parameters.numberOfIterations * sites.TimeStep);//*

				//	poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				//	if (poDstDS == NULL)

				//		errorSys("Img file not be created.", STOP);//*

				//	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

				//	outPoBand = poDstDS->GetRasterBand(1);//*


				//	for (i = sites.numRows(); i > 0; i--)

				//	{

				//		//printf("\r%3d%%",100*i/sites.numRows());

				//		for (j = 1; j <= sites.numColumns(); j++)

				//		{
				//			LANDUNIT *l;
				//			l = sites.locateLanduPt(i, j);
				//			TmpBiomassS = 0;

				//			for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

				//			{

				//				if (sites.GetGrowthRates(k, m, l->ltID) >= sites.GetBiomassThreshold())

				//					TmpBiomassS += exp(sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 1) + sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 2)*log(sites.GetGrowthRates(k, m, l->ltID)))*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 1000.00;

				//			}

				//			//fprintf(fpbiomass,"%f ",TmpBiomassS);	

				//			*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBiomassS;//*

				//		}

				//	}

				//	//fclose(fpbiomass);

				//	outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				//	if (poDstDS != NULL)
				//		GDALClose((GDALDatasetH)poDstDS);//*

				//	//CPLFree(pafScanline);
				//}



				}

			}

		//2.BA

	
	

		if(sites.GetOutputGeneralFlagArray(k-1,BA))

			{

			if(strcmp(BasalFileNames[k-1].c_str(),"N/A")!=0)

				{
					papszOptions = NULL;

					pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

					/*sprintf(str,"%s/%s_%d.asc",parameters.outputDir,BasalFileNames[k-1].c_str(),itr*sites.TimeStep);

					if ((fpbasal= LDfopen(str, 3)) == NULL)

						errorSys("can not open output file 1",STOP);

					outputFileheader(fpbasal);*/

			//	if (itr*freq[0] <= parameters.numberOfIterations){

					//pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

					sprintf(str1, "%s/%s_%d.img", parameters.outputDir, BasalFileNames[k - 1].c_str(), itr*sites.TimeStep);//* change

					poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

					if (poDstDS == NULL)

						errorSys("Img file not be created.", STOP);//*

					poDstDS->SetGeoTransform(wAdfGeoTransform);//*

					poDstDS->SetProjection(parameters.pszSRS_WKT);

					outPoBand = poDstDS->GetRasterBand(1);//*


					for (i = sites.numRows(); i > 0; i--)

					{

						//printf("\r%3d%%",100*i/sites.numRows());

						for (j = 1; j <= sites.numColumns(); j++)

						{
							LANDUNIT *l;
							l = sites.locateLanduPt(i, j);
							TmpBasalAreaS = 0;

							for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

							{

								TmpBasalAreaS += sites.GetGrowthRates(k, m, l->ltID)*sites.GetGrowthRates(k, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 10000.00;

								//TmpBasalAreaS+=0.005454*sites.GetGrowthRates(k,m)*sites.GetGrowthRates(k,m)*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k);

							}

							//fprintf(fpbasal,"%f ",TmpBasalAreaS);

							*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBasalAreaS;//* change

						}

					}

					//fclose(fpbasal);

					outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

					if (poDstDS != NULL)
						GDALClose((GDALDatasetH)poDstDS);//*
					CPLFree(pafScanline);
					CSLDestroy(papszOptions); //*

					//CPLFree(pafScanline);
			//	}

				//if (parameters.numberOfIterations % freq[0] !=0){

				//	//pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

				//	sprintf(str1, "%s/%s_%d.img", parameters.outputDir, BasalFileNames[k - 1].c_str(), parameters.numberOfIterations * sites.TimeStep);//* change

				//	poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				//	if (poDstDS == NULL)

				//		errorSys("Img file not be created.", STOP);//*

				//	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

				//	outPoBand = poDstDS->GetRasterBand(1);//*


				//	for (i = sites.numRows(); i > 0; i--)

				//	{

				//		//printf("\r%3d%%",100*i/sites.numRows());

				//		for (j = 1; j <= sites.numColumns(); j++)

				//		{
				//			LANDUNIT *l;
				//			l = sites.locateLanduPt(i, j);
				//			TmpBasalAreaS = 0;

				//			for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

				//			{

				//				TmpBasalAreaS += sites.GetGrowthRates(k, m, l->ltID)*sites.GetGrowthRates(k, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 10000.00;

				//				//TmpBasalAreaS+=0.005454*sites.GetGrowthRates(k,m)*sites.GetGrowthRates(k,m)*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k);

				//			}

				//			//fprintf(fpbasal,"%f ",TmpBasalAreaS);

				//			*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBasalAreaS;//* change

				//		}

				//	}

				//	//fclose(fpbasal);

				//	outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				//	if (poDstDS != NULL)
				//		GDALClose((GDALDatasetH)poDstDS);//*

				//	//CPLFree(pafScanline);
				//}
				}

			}
		//3.TPA  TreeNumber
			

		if(sites.GetOutputGeneralFlagArray(k-1,TPA))

			{

			if(strcmp(TreesFileNames[k-1].c_str(),"N/A")!=0)

				{
					pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));//*

					papszOptions = NULL;
				/*	sprintf(str,"%s/%s_%d.asc",parameters.outputDir,TreesFileNames[k-1].c_str(),itr*sites.TimeStep);

					if ((fptree= LDfopen(str, 3)) == NULL)

						errorSys("can not open output file 1",STOP);

					outputFileheader(fptree);*/

			//	if (itr*freq[0] <= parameters.numberOfIterations){

				//	pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));//*

					sprintf(str1, "%s/%s_%d.img", parameters.outputDir, TreesFileNames[k - 1].c_str(), itr*sites.TimeStep);//* change

					poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_UInt32, papszOptions);//*

					poDstDS->SetGeoTransform(wAdfGeoTransform);//*

					outPoBand = poDstDS->GetRasterBand(1);//*


					if (poDstDS == NULL)

						errorSys("Img file not be created.", STOP);//*

					for (i = sites.numRows(); i > 0; i--)

					{

						//printf("\r%3d%%",100*i/sites.numRows());

						for (j = 1; j <= sites.numColumns(); j++)

						{
							TmpTreesS = 0;

							for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

							{

								TmpTreesS += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);

							}

							//fprintf(fptree,"%d ",TmpTreesS);

							*(pintScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpTreesS;//*

						}

					}

					//fclose(fptree);

					outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pintScanline, sites.numColumns(), sites.numRows(), GDT_UInt32, 0, 0);//*

					if (poDstDS != NULL)
						GDALClose((GDALDatasetH)poDstDS);//*

					CPLFree(pintScanline);
					CSLDestroy(papszOptions); //*


					//CPLFree(pintScanline);
			//	}

				//if (parameters.numberOfIterations %freq[0] !=0){

				//	//pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));//*

				//	sprintf(str1, "%s/%s_%d.img", parameters.outputDir, TreesFileNames[k - 1].c_str(), parameters.numberOfIterations * sites.TimeStep);//* change

				//	poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_UInt32, papszOptions);//*

				//	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

				//	outPoBand = poDstDS->GetRasterBand(1);//*


				//	if (poDstDS == NULL)

				//		errorSys("Img file not be created.", STOP);//*

				//	for (i = sites.numRows(); i > 0; i--)

				//	{

				//		//printf("\r%3d%%",100*i/sites.numRows());

				//		for (j = 1; j <= sites.numColumns(); j++)

				//		{
				//			TmpTreesS = 0;

				//			for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

				//			{

				//				TmpTreesS += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);

				//			}

				//			//fprintf(fptree,"%d ",TmpTreesS);

				//			*(pintScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpTreesS;//*

				//		}

				//	}

				//	//fclose(fptree);

				//	outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pintScanline, sites.numColumns(), sites.numRows(), GDT_UInt32, 0, 0);//*

				//	if (poDstDS != NULL)
				//		GDALClose((GDALDatasetH)poDstDS);//*

				//	//CPLFree(pintScanline);
				//}

				}

			}
		//4.IV

	

		if(sites.GetOutputGeneralFlagArray(k-1,IV))

			{

			if(strcmp(IVFileNames[k-1].c_str(),"N/A")!=0)

				{
					papszOptions = NULL;

					pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

					/*sprintf(str,"%s/%s_%d.asc",parameters.outputDir,IVFileNames[k-1].c_str(),itr*sites.TimeStep);

					if ((fpIV= LDfopen(str, 3)) == NULL)

						errorSys("can not open output file 1",STOP);

					outputFileheader(fpIV);*/

				//if (itr*freq[0] <= parameters.numberOfIterations){

					//pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

					sprintf(str1, "%s/%s_%d.img", parameters.outputDir, IVFileNames[k - 1].c_str(), itr * sites.TimeStep);//* change

					poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

					if (poDstDS == NULL) //*

						errorSys("Img file not be created.", STOP);//*

					poDstDS->SetGeoTransform(wAdfGeoTransform);//*

					outPoBand = poDstDS->GetRasterBand(1);//*

					for (i = sites.numRows(); i > 0; i--)

					{

						//printf("\r%3d%%",100*i/sites.numRows());
						for (j = 1; j <= sites.numColumns(); j++)
						{
							LANDUNIT *l;
							l = sites.locateLanduPt(i, j);
							TmpBasalAreaT = 0;
							TmpTreeT = 0;
							for (kk = 1; kk <= sites.specNum; kk++)
							{
								if (speciesAttrs(kk)->SpType >= 0)
								{
									for (m = 1; m <= speciesAttrs(kk)->longevity / sites.TimeStep; m++)
									{
										//if(sites.GetGrowthRates(kk,m)>=sites.GetBiomassThreshold())
										//TmpBasalAreaT+=exp(sites.GetBiomassData(speciesAttrs(kk)->BioMassCoef,1)+sites.GetBiomassData(speciesAttrs(kk)->BioMassCoef,2)*log(sites.GetGrowthRates(kk,m)))*sites(i,j)->SpecieIndex(kk)->getTreeNum(m,kk)/1000.00;
										TmpBasalAreaT += sites.GetGrowthRates(kk, m, l->ltID)*sites.GetGrowthRates(kk, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(kk)->getTreeNum(m, kk) / 10000.00;
										TmpTreeT += sites(i, j)->SpecieIndex(kk)->getTreeNum(m, kk);
									}
								}
							}

							TmpBasalAreaS = 0;

							for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

							{

								//if(sites.GetGrowthRates(k,m)>=sites.GetBiomassThreshold())

								//TmpBasalAreaS+=exp(sites.GetBiomassData(speciesAttrs(k)->BioMassCoef,1)+sites.GetBiomassData(speciesAttrs(k)->BioMassCoef,2)*log(sites.GetGrowthRates(k,m)))*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k)/1000.00;
								TmpBasalAreaS += sites.GetGrowthRates(k, m, l->ltID)*sites.GetGrowthRates(k, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 10000.00;
							}



							TmpTreesS = 0;

							for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

							{

								TmpTreesS += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);

							}

							if (TmpTreeT == 0 || TmpBasalAreaT < 0.0001){

								//fprintf(fpIV,"0 ");

								*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = 0;//* 
							}

							else{

								//fprintf(fpIV, "%f ", (double)TmpTreesS / (double)TmpTreeT + TmpBasalAreaS / TmpBasalAreaT);

								*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = (double)TmpTreesS / (double)TmpTreeT + TmpBasalAreaS / TmpBasalAreaT;//* 

							}
						}

					}



					//fclose(fpIV);

					outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

					if (poDstDS != NULL)
						GDALClose((GDALDatasetH)poDstDS);//*

					CPLFree(pafScanline);
					CSLDestroy(papszOptions); //*

				//	CPLFree(pafScanline);
			//	}

				//if (parameters.numberOfIterations % freq[0] !=0){

				//	//pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

				//	sprintf(str1, "%s/%s_%d.img", parameters.outputDir, IVFileNames[k - 1].c_str(), parameters.numberOfIterations * sites.TimeStep);//* change

				//	poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				//	if (poDstDS == NULL) //*

				//		errorSys("Img file not be created.", STOP);//*

				//	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

				//	outPoBand = poDstDS->GetRasterBand(1);//*

				//	for (i = sites.numRows(); i > 0; i--)

				//	{

				//		//printf("\r%3d%%",100*i/sites.numRows());
				//		for (j = 1; j <= sites.numColumns(); j++)
				//		{
				//			LANDUNIT *l;
				//			l = sites.locateLanduPt(i, j);
				//			TmpBasalAreaT = 0;
				//			TmpTreeT = 0;
				//			for (kk = 1; kk <= sites.specNum; kk++)
				//			{
				//				if (speciesAttrs(kk)->SpType >= 0)
				//				{
				//					for (m = 1; m <= speciesAttrs(kk)->longevity / sites.TimeStep; m++)
				//					{
				//						//if(sites.GetGrowthRates(kk,m)>=sites.GetBiomassThreshold())
				//						//TmpBasalAreaT+=exp(sites.GetBiomassData(speciesAttrs(kk)->BioMassCoef,1)+sites.GetBiomassData(speciesAttrs(kk)->BioMassCoef,2)*log(sites.GetGrowthRates(kk,m)))*sites(i,j)->SpecieIndex(kk)->getTreeNum(m,kk)/1000.00;
				//						TmpBasalAreaT += sites.GetGrowthRates(kk, m, l->ltID)*sites.GetGrowthRates(kk, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(kk)->getTreeNum(m, kk) / 10000.00;
				//						TmpTreeT += sites(i, j)->SpecieIndex(kk)->getTreeNum(m, kk);
				//					}
				//				}
				//			}

				//			TmpBasalAreaS = 0;

				//			for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

				//			{

				//				//if(sites.GetGrowthRates(k,m)>=sites.GetBiomassThreshold())

				//				//TmpBasalAreaS+=exp(sites.GetBiomassData(speciesAttrs(k)->BioMassCoef,1)+sites.GetBiomassData(speciesAttrs(k)->BioMassCoef,2)*log(sites.GetGrowthRates(k,m)))*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k)/1000.00;
				//				TmpBasalAreaS += sites.GetGrowthRates(k, m, l->ltID)*sites.GetGrowthRates(k, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 10000.00;
				//			}



				//			TmpTreesS = 0;

				//			for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

				//			{

				//				TmpTreesS += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);

				//			}

				//			if (TmpTreeT == 0 || TmpBasalAreaT < 0.0001){

				//				//fprintf(fpIV,"0 ");

				//				*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = 0;//* 
				//			}

				//			else{

				//				//fprintf(fpIV, "%f ", (double)TmpTreesS / (double)TmpTreeT + TmpBasalAreaS / TmpBasalAreaT);

				//				*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = (double)TmpTreesS / (double)TmpTreeT + TmpBasalAreaS / TmpBasalAreaT;//* 

				//			}
				//		}

				//	}



				//	//fclose(fpIV);

				//	outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				//	if (poDstDS != NULL)
				//		GDALClose((GDALDatasetH)poDstDS);//*

				//	//CPLFree(pafScanline);
			//	}
				}

			}

			//5. Seeds

			

		if(sites.GetOutputGeneralFlagArray(k-1,Seeds))//sites.GetOutputGeneralFlagArray(k-1,DBH)&&

			{

			if(strcmp(SeedsFileNames[k-1].c_str(),"N/A")!=0)

				{
					papszOptions = NULL;

					pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));//*

				/*	sprintf(str,"%s/%s_%d.asc",parameters.outputDir,SeedsFileNames[k-1].c_str(),itr*sites.TimeStep);

					if ((fpSeeds= LDfopen(str, 3)) == NULL)

						errorSys("can not open output file 1",STOP);

					outputFileheader(fpSeeds);
*/
			//	if (itr*freq[0] <= parameters.numberOfIterations){

				//	pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));//*

					sprintf(str1, "%s/%s_%d.img", parameters.outputDir, SeedsFileNames[k - 1].c_str(), itr*sites.TimeStep);//* change

					poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_UInt32, papszOptions);//*

					if (poDstDS == NULL)//*

						errorSys("Img file not be created.", STOP);//*

					outPoBand = poDstDS->GetRasterBand(1);//*

					poDstDS->SetGeoTransform(wAdfGeoTransform);//*

					for (i = sites.numRows(); i > 0; i--)

					{

						//printf("\r%3d%%",100*i/sites.numRows());

						for (j = 1; j <= sites.numColumns(); j++)

						{

							//fprintf(fpSeeds,"%u ",sites(i,j)->SpecieIndex(k)->AvailableSeed);

							*(pintScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = sites(i, j)->SpecieIndex(k)->AvailableSeed;//* 

						}

					}

					//fclose(fpSeeds);

					outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pintScanline, sites.numColumns(), sites.numRows(), GDT_UInt32, 0, 0);//*

					if (poDstDS != NULL)
						GDALClose((GDALDatasetH)poDstDS);//*

					CPLFree(pintScanline);
					CSLDestroy(papszOptions); //*

				//	CPLFree(pintScanline);
			//	}

				//if (parameters.numberOfIterations %freq[0] != 0){

				//	//pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));//*

				//	sprintf(str1, "%s/%s_%d.img", parameters.outputDir, SeedsFileNames[k - 1].c_str(), parameters.numberOfIterations * sites.TimeStep);//* change

				//	poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_UInt32, papszOptions);//*

				//	if (poDstDS == NULL)//*

				//		errorSys("Img file not be created.", STOP);//*

				//	outPoBand = poDstDS->GetRasterBand(1);//*

				//	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

				//	for (i = sites.numRows(); i > 0; i--)

				//	{

				//		//printf("\r%3d%%",100*i/sites.numRows());

				//		for (j = 1; j <= sites.numColumns(); j++)

				//		{

				//			//fprintf(fpSeeds,"%u ",sites(i,j)->SpecieIndex(k)->AvailableSeed);

				//			*(pintScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = sites(i, j)->SpecieIndex(k)->AvailableSeed;//* 

				//		}

				//	}

				//	//fclose(fpSeeds);

				//	outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pintScanline, sites.numColumns(), sites.numRows(), GDT_UInt32, 0, 0);//*

				//	if (poDstDS != NULL)
				//		GDALClose((GDALDatasetH)poDstDS);//*

				//	//CPLFree(pintScanline);
				//}
				}

			}
		//6.RDensity

		
		if(sites.GetOutputGeneralFlagArray(k-1,RDensity))//sites.GetOutputGeneralFlagArray(k-1,DBH)&&

			{

			if(strcmp(RDFileNames[k-1].c_str(),"N/A")!=0)

				{
					papszOptions = NULL;

					pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*


					/*sprintf(str,"%s/%s_%d.asc",parameters.outputDir,RDFileNames[k-1].c_str(),itr*sites.TimeStep);

					if ((fpRD= LDfopen(str, 3)) == NULL)

						errorSys("can not open output file 1",STOP);

					outputFileheader(fpRD);*/

			//	if (itr*freq[0] <= parameters.numberOfIterations){

				//	pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*


					sprintf(str1, "%s/%s_%d.img", parameters.outputDir, RDFileNames[k - 1].c_str(), itr*sites.TimeStep);//* change

					poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

					if (poDstDS == NULL)

						errorSys("Img file not be created.", STOP);//*

					outPoBand = poDstDS->GetRasterBand(1);//*

					poDstDS->SetGeoTransform(wAdfGeoTransform);//*

					for (i = sites.numRows(); i > 0; i--)

					{

						//printf("\r%3d%%",100*i/sites.numRows());

						for (j = 1; j <= sites.numColumns(); j++)

						{
							LANDUNIT *l;
							l = sites.locateLanduPt(i, j);
							if (sites(i, j)->specAtt(k)->SpType >= 0)

							{

								float temp = 0.0;

								for (int jj = 1; jj <= sites(i, j)->specAtt(k)->longevity / sites.TimeStep; jj++)

								{

									temp = temp + pow((sites.GetGrowthRates(k, jj, l->ltID) / 25.4), 1.605)*sites(i, j)->specAtt(k)->MaxAreaOfSTDTree*sites(i, j)->SpecieIndex(k)->getTreeNum(jj, k) / sites.CellSize / sites.CellSize;

								}

								//fprintf(fpRD,"%f ",temp);

								*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = temp;//* 

							}

							else{

								//fprintf(fpRD,"0.0 ");

								*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = 0.0;//* 

							}

						}

					}

					//fclose(fpRD);

					outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

					if (poDstDS != NULL)
						GDALClose((GDALDatasetH)poDstDS);//*

					CPLFree(pafScanline);
					CSLDestroy(papszOptions); //*

					//CPLFree(pafScanline);

				//}

				//if (parameters.numberOfIterations % freq[0] !=0){

				//	pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*


				//	sprintf(str1, "%s/%s_%d.img", parameters.outputDir, RDFileNames[k - 1].c_str(), parameters.numberOfIterations* sites.TimeStep);//* change

				//	poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				//	if (poDstDS == NULL)

				//		errorSys("Img file not be created.", STOP);//*

				//	outPoBand = poDstDS->GetRasterBand(1);//*

				//	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

				//	for (i = sites.numRows(); i > 0; i--)

				//	{

				//		//printf("\r%3d%%",100*i/sites.numRows());

				//		for (j = 1; j <= sites.numColumns(); j++)

				//		{
				//			LANDUNIT *l;
				//			l = sites.locateLanduPt(i, j);
				//			if (sites(i, j)->specAtt(k)->SpType >= 0)

				//			{

				//				float temp = 0.0;

				//				for (int jj = 1; jj <= sites(i, j)->specAtt(k)->longevity / sites.TimeStep; jj++)

				//				{

				//					temp = temp + pow((sites.GetGrowthRates(k, jj, l->ltID) / 25.4), 1.605)*sites(i, j)->specAtt(k)->MaxAreaOfSTDTree*sites(i, j)->SpecieIndex(k)->getTreeNum(jj, k) / sites.CellSize / sites.CellSize;

				//				}

				//				//fprintf(fpRD,"%f ",temp);

				//				*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = temp;//* 

				//			}

				//			else{

				//				//fprintf(fpRD,"0.0 ");

				//				*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = 0.0;//* 

				//			}

				//		}

				//	}

				//	//fclose(fpRD);

				//	outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				//	if (poDstDS != NULL)
				//		GDALClose((GDALDatasetH)poDstDS);//*

				////	CPLFree(pafScanline);

				//}

				}

			}
		//7.DBH

		//pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

		if(flagoutputDBH&&0)//sites.GetOutputGeneralFlagArray(k-1,DBH)&&

			{

			if(strcmp(DBHFileNames[k-1].c_str(),"N/A")!=0)

				{
					papszOptions = NULL;

					pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
					/*sprintf(str,"%s/%s_%d.asc",parameters.outputDir,DBHFileNames[k-1].c_str(),itr*sites.TimeStep);

					if ((fpDBH= LDfopen(str, 3)) == NULL)

						errorSys("can not open output file 1",STOP);

					outputFileheader(fpDBH);*/

				if (itr*freq[0] <= parameters.numberOfIterations){

					sprintf(str1, "%s/%s_%d.img", parameters.outputDir, DBHFileNames[k - 1].c_str(), itr*sites.TimeStep);//* change

					poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

					if (poDstDS == NULL)

						errorSys("Img file not be created.", STOP);//*

					outPoBand = poDstDS->GetRasterBand(1);//*

					poDstDS->SetGeoTransform(wAdfGeoTransform);//*

					for (i = sites.numRows(); i > 0; i--)

					{

						//printf("\r%3d%%",100*i/sites.numRows());

						for (j = 1; j <= sites.numColumns(); j++)

						{
							LANDUNIT *l;
							l = sites.locateLanduPt(i, j);
							float tempDBH = 0.0;

							for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

							{

								if (sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) > 0){

									tempDBH = sites.GetGrowthRates(k, m, l->ltID);

									break;

								}

							}

							//fprintf(fpDBH,"%f ",tempDBH);

							*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = tempDBH;//* 

						}

					}

					//fclose(fpDBH);

					outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

					if (poDstDS != NULL)
						GDALClose((GDALDatasetH)poDstDS);//*

					CPLFree(pafScanline);
					CSLDestroy(papszOptions); //*
				//	CPLFree(pafScanline);

				}

				//if (parameters.numberOfIterations % freq[0] !=0){

				//	sprintf(str1, "%s/%s_%d.img", parameters.outputDir, DBHFileNames[k - 1].c_str(), parameters.numberOfIterations * sites.TimeStep);//* change

				//	poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				//	if (poDstDS == NULL)

				//		errorSys("Img file not be created.", STOP);//*

				//	outPoBand = poDstDS->GetRasterBand(1);//*

				//	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

				//	for (i = sites.numRows(); i > 0; i--)

				//	{

				//		//printf("\r%3d%%",100*i/sites.numRows());

				//		for (j = 1; j <= sites.numColumns(); j++)

				//		{
				//			LANDUNIT *l;
				//			l = sites.locateLanduPt(i, j);
				//			float tempDBH = 0.0;

				//			for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

				//			{

				//				if (sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) > 0){

				//					tempDBH = sites.GetGrowthRates(k, m, l->ltID);

				//					break;

				//				}

				//			}

				//			//fprintf(fpDBH,"%f ",tempDBH);

				//			*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = tempDBH;//* 

				//		}

				//	}

				//	//fclose(fpDBH);

				//	outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				//	if (poDstDS != NULL)
				//		GDALClose((GDALDatasetH)poDstDS);//*

				//	//CPLFree(pafScanline);

				//}

				}

			}

		}







		

		///////output available seeds and RD for every species///////////

		/*FILE **fpTempAvailableSeed;

		if(sites.GetOutputGeneralFlagArray(sites.specNum,Seeds)){

			fpTempAvailableSeed=new FILE*[sites.specNum];

			for(i=0;i<sites.specNum;i++){

				sprintf(str,"%s/%s_AvailableSeed_%d.txt",parameters.outputDir,speciesAttrs(i+1)->name,itr*sites.TimeStep);

				if ((fpTempAvailableSeed[i]= LDfopen(str, 3)) == NULL)

					errorSys("can not open output file Seeds",STOP);

				outputFileheader(fpTempAvailableSeed[i]);

				}

			}



		FILE **fpTempSpeciesRD;

		if(sites.GetOutputGeneralFlagArray(sites.specNum,RDensity)){

			fpTempSpeciesRD=new FILE*[sites.specNum];

			for(i=0;i<sites.specNum;i++){

				sprintf(str,"%s/%s_RD_%d.txt",parameters.outputDir,speciesAttrs(i+1)->name,itr*sites.TimeStep);

				if ((fpTempSpeciesRD[i]= LDfopen(str, 3)) == NULL)

					errorSys("can not open output file RD",STOP);

				outputFileheader(fpTempSpeciesRD[i]);

				}

			}*/

		/////////////////////////////////////

	if (sites.GetOutputGeneralFlagArray(sites.specNum, Bio) ||

		sites.GetOutputGeneralFlagArray(sites.specNum, Car) ||

		sites.GetOutputGeneralFlagArray(sites.specNum, BA) ||

		sites.GetOutputGeneralFlagArray(sites.specNum, RDensity) ||

		sites.GetOutputGeneralFlagArray(sites.specNum, TPA))

	{

		//below is for total 
		//1.Bio
		pafScanline1 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
		pafScanline2 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
		pafScanline3 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
		pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));//*
		//pafScanline4 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
		pafScanline5 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

		papszOptions = NULL;

	//	if (itr*freq[0] <= parameters.numberOfIterations){

			if (sites.GetOutputGeneralFlagArray(sites.specNum, Bio))
			{

				/*sprintf(str,"%s/TotalBio_%d.asc",parameters.outputDir,itr*sites.TimeStep);

				if ((fpTotalBiomass= LDfopen(str, 3)) == NULL)

				errorSys("can not open output file TotalBiomass",STOP);

				outputFileheader(fpTotalBiomass);*/
				//pafScanline1 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

				sprintf(str1, "%s/TotalBio_%d.img", parameters.outputDir, itr*sites.TimeStep);//* change

				poDstDS1 = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				if (poDstDS1 == NULL)

					errorSys("Img file not be created.", STOP);//*

				outPoBand1 = poDstDS1->GetRasterBand(1);//*

				poDstDS1->SetGeoTransform(wAdfGeoTransform);//*


			}
			//2.Car
			if (sites.GetOutputGeneralFlagArray(sites.specNum, Car))
			{

				/*sprintf(str,"%s/TotalCarbon_%d.asc",parameters.outputDir,itr*sites.TimeStep);

				if ((fpTotalcarbon= LDfopen(str, 3)) == NULL)

				errorSys("can not open output file TotalCarbon",STOP);

				outputFileheader(fpTotalcarbon);*/

				//pafScanline2 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

				sprintf(str2, "%s/TotalCarbon_%d.img", parameters.outputDir, itr*sites.TimeStep);//* change

				poDstDS2 = poDriver->Create(str2, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				if (poDstDS2 == NULL)

					errorSys("Img file not be created.", STOP);//*

				outPoBand2 = poDstDS2->GetRasterBand(1);//*

				poDstDS2->SetGeoTransform(wAdfGeoTransform);//*

			}


			//3.BA
			if (sites.GetOutputGeneralFlagArray(sites.specNum, BA))
			{

				/*sprintf(str,"%s/TotalBA_%d.asc",parameters.outputDir,itr*sites.TimeStep);

				if ((fptotalbasal= LDfopen(str, 3)) == NULL)

				errorSys("can not open output file TotalBasalArea",STOP);

				outputFileheader(fptotalbasal);*/

			//	pafScanline3 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

				sprintf(str3, "%s/TotalBA_%d.img", parameters.outputDir, itr*sites.TimeStep);//* change

				poDstDS3 = poDriver->Create(str3, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				if (poDstDS3 == NULL)

					errorSys("Img file not be created.", STOP);//*

				outPoBand3 = poDstDS3->GetRasterBand(1);//*

				poDstDS3->SetGeoTransform(wAdfGeoTransform);//*

			}


			//4.TPA
			if (sites.GetOutputGeneralFlagArray(sites.specNum, TPA))
			{

				/*sprintf(str,"%s/TotalTrees_%d.asc",parameters.outputDir,itr*sites.TimeStep);

				if ((fptotaltrees= LDfopen(str, 3)) == NULL)

				errorSys("can not open output file TotalTrees",STOP);

				outputFileheader(fptotaltrees);*/

				//pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));//*

				sprintf(str4, "%s/TotalTrees_%d.img", parameters.outputDir, itr*sites.TimeStep);//* change

				poDstDS4 = poDriver->Create(str4, sites.numColumns(), sites.numRows(), 1, GDT_UInt32, papszOptions);//*

				if (poDstDS4 == NULL)

					errorSys("Img file not be created.", STOP);//*

				outPoBand4 = poDstDS4->GetRasterBand(1);//*

				poDstDS4->SetGeoTransform(wAdfGeoTransform);//*

			}


			//5.RDensity
			if (sites.GetOutputGeneralFlagArray(sites.specNum, RDensity))
			{

				/*sprintf(str,"%s/RelativeDensity_%d.asc",parameters.outputDir,itr*sites.TimeStep);

				if ((fpRD= LDfopen(str, 3)) == NULL)

				errorSys("can not open output file TotalTrees",STOP);

				outputFileheader(fpRD);*/

				//pafScanline5 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

				sprintf(str5, "%s/RelativeDensity_%d.img", parameters.outputDir, itr*sites.TimeStep);//* change

				poDstDS5 = poDriver->Create(str5, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				if (poDstDS5 == NULL)

					errorSys("Img file not be created.", STOP);//*

				outPoBand5 = poDstDS5->GetRasterBand(1);//*

				poDstDS5->SetGeoTransform(wAdfGeoTransform);//*

			}



			for (i = sites.numRows(); i > 0; i--)

			{

				for (j = 1; j <= sites.numColumns(); j++)

				{
					LANDUNIT *l;
					l = sites.locateLanduPt(i, j);
					TmpBiomassT = 0;

					TmpBasalAreaT = 0;

					TmpTreeT = 0;

					TmpCarbon = 0;

					TmpCarbonTotal = 0;
					float temp;

					for (k = 1; k <= sites.specNum; k++)

					{

						TmpCarbon = 0;



						if (speciesAttrs(k)->SpType >= 0)

						{

							for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

							{

								if (sites.GetGrowthRates(k, m, l->ltID) >= sites.GetBiomassThreshold() && sites.GetOutputGeneralFlagArray(sites.specNum, Bio))

									TmpBiomassT += exp(sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 1) + sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 2)*log(sites.GetGrowthRates(k, m, l->ltID)))*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 1000.00;

								if (sites.GetOutputGeneralFlagArray(sites.specNum, BA))

									TmpBasalAreaT += sites.GetGrowthRates(k, m, l->ltID)*sites.GetGrowthRates(k, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 10000.00;



								//TmpBasalAreaT+=0.005454*sites.GetGrowthRates(k,m)*sites.GetGrowthRates(k,m)*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k);

								if (sites.GetOutputGeneralFlagArray(sites.specNum, TPA))

									TmpTreeT += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);

								if (sites.GetOutputGeneralFlagArray(sites.specNum, Car)){

									if ((sites.GetGrowthRates(k, m, l->ltID)) == 0){
										temp = 0;
									}
									else{
										temp = log(sites.GetGrowthRates(k, m, l->ltID));
									}
										
									
									
									TmpCarbon += exp(sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 1) + sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 2)*temp)*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);
																
								}
							}

						}

						if (sites.GetOutputGeneralFlagArray(sites.specNum, Car))

							TmpCarbonTotal = TmpCarbonTotal + TmpCarbon*speciesAttrs(k)->CarbonCoEfficient;

						/*if(sites.GetOutputGeneralFlagArray(sites.specNum,Seeds))

							fprintf(fpTempAvailableSeed[k-1],"%u ",sites(i,j)->SpecieIndex(k)->AvailableSeed);*/

					}
					//1.Bio
					if (sites.GetOutputGeneralFlagArray(sites.specNum, Bio)){

						//fprintf(fpTotalBiomass, "%f ", TmpBiomassT);

						*(pafScanline1 + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBiomassT;//*


					}
					//2.Car
					if (sites.GetOutputGeneralFlagArray(sites.specNum, Car)){

						//fprintf(fpTotalcarbon, "%f ", TmpCarbonTotal / 1000.00);

						*(pafScanline2 + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpCarbonTotal / 1000.00;//*
					}
					//3.BA
					if (sites.GetOutputGeneralFlagArray(sites.specNum, BA)){

						//fprintf(fptotalbasal, "%f ", TmpBasalAreaT);

						*(pafScanline3 + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBasalAreaT;//*
					}
					//5.RDensity
					if (sites.GetOutputGeneralFlagArray(sites.specNum, RDensity)){

						//fprintf(fpRD,"%f ",sites(i,j)->RD);

						*(pafScanline5 + (sites.numRows() - i)*sites.numColumns() + j - 1) = sites(i, j)->RD;//*

					}
					//4.TPA
					if (sites.GetOutputGeneralFlagArray(sites.specNum, TPA)){

						//fprintf(fptotaltrees, "%d ", TmpTreeT);

						*(pintScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpTreeT;//*
					}

				}

			}
			//1.Bio
			if (sites.GetOutputGeneralFlagArray(sites.specNum, Bio))
			{

				//fclose(fpTotalBiomass);

				outPoBand1->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline1, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				if (poDstDS1 != NULL)
					GDALClose((GDALDatasetH)poDstDS1);//*

				CPLFree(pafScanline1);
			}
			//2.Car
			if (sites.GetOutputGeneralFlagArray(sites.specNum, Car)){

				//fclose(fpTotalcarbon);

				outPoBand2->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline2, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				if (poDstDS2 != NULL)
					GDALClose((GDALDatasetH)poDstDS2);//*

				CPLFree(pafScanline2);
			}
			//3.BA
			if (sites.GetOutputGeneralFlagArray(sites.specNum, BA))
			{

				//fclose(fptotalbasal);

				outPoBand3->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline3, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				if (poDstDS3 != NULL)
					GDALClose((GDALDatasetH)poDstDS3);//*

				CPLFree(pafScanline3);

			}
			//4.TPA
			if (sites.GetOutputGeneralFlagArray(sites.specNum, TPA))
			{

				//fclose(fptotaltrees);

				outPoBand4->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pintScanline, sites.numColumns(), sites.numRows(), GDT_UInt32, 0, 0);//*

				if (poDstDS4 != NULL)
					GDALClose((GDALDatasetH)poDstDS4);//*

				CPLFree(pintScanline);
			}
			//5.RDensity
			if (sites.GetOutputGeneralFlagArray(sites.specNum, RDensity))
			{

				//fclose(fpRD);

				outPoBand5->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline5, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				if (poDstDS5 != NULL)
					GDALClose((GDALDatasetH)poDstDS5);//*

				CPLFree(pafScanline5);
			}

	}
	//below is for species age range

	int Agerangeage1, Agerangeage2, Agerangecount=0,Agerangeii;

	//1.Bio

	

	if (sites.flagAgeRangeOutput){

		for (k = 1; k <= sites.specNum; k++)

		{

			if (sites.GetOutputAgerangeFlagArray(k - 1, Bio))

			{

				Agerangecount = sites.GetAgerangeCount(k - 1);

				for (Agerangeii = 1; Agerangeii <= Agerangecount; Agerangeii++){

					sites.GetSpeciesAgerangeArray(k - 1, Agerangeii, &Agerangeage1, &Agerangeage2);

					if (strcmp(BioMassFileNames[k - 1].c_str(), "N/A") != 0)

					{
						papszOptions = NULL;

						pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
						/*sprintf(str,"%s/%s_Age%d_Age%d_%d.asc",parameters.outputDir,BioMassFileNames[k-1].c_str(),Agerangeage1,Agerangeage2,itr*sites.TimeStep);

						if ((fpbiomass = LDfopen(str, 3)) == NULL)

						errorSys("can not open output file 1",STOP);

						outputFileheader(fpbiomass);*/

					//	if (itr*freq[0] <= parameters.numberOfIterations){

							//pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

							sprintf(str1, "%s/%s_Age%d_Age%d_%d.img", parameters.outputDir, BioMassFileNames[k - 1].c_str(), Agerangeage1, Agerangeage2, itr* sites.TimeStep);//* change

							poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

							if (poDstDS == NULL)

								errorSys("Img file not be created.", STOP);//*

							outPoBand = poDstDS->GetRasterBand(1);//*

							poDstDS->SetGeoTransform(wAdfGeoTransform);//*

							for (i = sites.numRows(); i > 0; i--)

							{

								//printf("\r%3d%%",100*i/sites.numRows());

								for (j = 1; j <= sites.numColumns(); j++)

								{
									LANDUNIT *l;
									l = sites.locateLanduPt(i, j);
									TmpBiomassS = 0;

									for (m = min(speciesAttrs(k)->longevity, Agerangeage1) / sites.TimeStep; m <= min(speciesAttrs(k)->longevity, Agerangeage2) / sites.TimeStep; m++)

									{

										if (sites.GetGrowthRates(k, m, l->ltID) >= sites.GetBiomassThreshold())

											TmpBiomassS += exp(sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 1) + sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 2)*log(sites.GetGrowthRates(k, m, l->ltID)))*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 1000.00;

									}

									//fprintf(fpbiomass,"%f ",TmpBiomassS);		

									*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBiomassS;//*

								}

							}

							//fclose(fpbiomass);

							outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

							if (poDstDS != NULL)
								GDALClose((GDALDatasetH)poDstDS);//*
							CPLFree(pafScanline);
							CSLDestroy(papszOptions); //
					}

				}

			}


			//2.BA

			
			if (sites.GetOutputAgerangeFlagArray(k - 1, BA))

			{

				Agerangecount = sites.GetAgerangeCount(k - 1);

				for (Agerangeii = 1; Agerangeii <= Agerangecount; Agerangeii++){

					sites.GetSpeciesAgerangeArray(k - 1, Agerangeii, &Agerangeage1, &Agerangeage2);

					if (strcmp(BasalFileNames[k - 1].c_str(), "N/A") != 0)

					{
						papszOptions = NULL;

						pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*

						sprintf(str1, "%s/%s_Age%d_Age%d_%d.img", parameters.outputDir, BasalFileNames[k - 1].c_str(), Agerangeage1, Agerangeage2, itr* sites.TimeStep);//* change

							poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

							if (poDstDS == NULL)

								errorSys("Img file not be created.", STOP);//*

							outPoBand = poDstDS->GetRasterBand(1);//*

							poDstDS->SetGeoTransform(wAdfGeoTransform);//*

							for (i = sites.numRows(); i > 0; i--)

							{

								//printf("\r%3d%%",100*i/sites.numRows());

								for (j = 1; j <= sites.numColumns(); j++)

								{
									LANDUNIT *l;
									l = sites.locateLanduPt(i, j);
									TmpBasalAreaS = 0;

									for (m = min(speciesAttrs(k)->longevity, Agerangeage1) / sites.TimeStep; m <= min(speciesAttrs(k)->longevity, Agerangeage2) / sites.TimeStep; m++)

									{

										TmpBasalAreaS += sites.GetGrowthRates(k, m, l->ltID)*sites.GetGrowthRates(k, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 10000.00;

										//TmpBasalAreaS+=0.005454*sites.GetGrowthRates(k,m)*sites.GetGrowthRates(k,m)*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k);



									}

									//fprintf(fpbasal,"%f ",TmpBasalAreaS);

									*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBasalAreaS;//*

								}

							}

							//fclose(fpbasal);

							outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

							if (poDstDS != NULL)
								GDALClose((GDALDatasetH)poDstDS);//*

							CPLFree(pafScanline);
							CSLDestroy(papszOptions); //*

					}

				}

			}
			//3.TPA
			

			if (sites.GetOutputAgerangeFlagArray(k - 1, TPA))

			{

				Agerangecount = sites.GetAgerangeCount(k - 1);

				for (Agerangeii = 1; Agerangeii <= Agerangecount; Agerangeii++){

					sites.GetSpeciesAgerangeArray(k - 1, Agerangeii, &Agerangeage1, &Agerangeage2);

					if (strcmp(TreesFileNames[k - 1].c_str(), "N/A") != 0)

					{
						papszOptions = NULL;

						pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));//*

							sprintf(str1, "%s/%s_Age%d_Age%d_%d.img", parameters.outputDir, TreesFileNames[k - 1].c_str(), Agerangeage1, Agerangeage2, itr * sites.TimeStep);//* change

							poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_UInt32, papszOptions);//*

							if (poDstDS == NULL)

								errorSys("Img file not be created.", STOP);//*

							outPoBand = poDstDS->GetRasterBand(1);//*

							poDstDS->SetGeoTransform(wAdfGeoTransform);//*

							for (i = sites.numRows(); i > 0; i--)

							{

								//printf("\r%3d%%",100*i/sites.numRows());

								for (j = 1; j <= sites.numColumns(); j++)

								{
									TmpTreesS = 0;

									for (m = min(speciesAttrs(k)->longevity, Agerangeage1) / sites.TimeStep; m <= min(speciesAttrs(k)->longevity, Agerangeage2) / sites.TimeStep; m++)

									{

										TmpTreesS += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);

									}

									//fprintf(fptree,"%d ",TmpTreesS);

									*(pintScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpTreesS;//*

								}

							}

							//fclose(fptree);
							outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pintScanline, sites.numColumns(), sites.numRows(), GDT_UInt32, 0, 0);//*

							if (poDstDS != NULL)
								GDALClose((GDALDatasetH)poDstDS);//*

							CPLFree(pintScanline);
							CSLDestroy(papszOptions); //*

					}

				}

			}

			//4.IV

			

			if (sites.GetOutputAgerangeFlagArray(k - 1, IV))

			{

				Agerangecount = sites.GetAgerangeCount(k - 1);

				for (Agerangeii = 1; Agerangeii <= Agerangecount; Agerangeii++){

					sites.GetSpeciesAgerangeArray(k - 1, Agerangeii, &Agerangeage1, &Agerangeage2);



					if (strcmp(IVFileNames[k - 1].c_str(), "N/A") != 0)

					{
						papszOptions = NULL;

						pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*


							sprintf(str1, "%s/%s_Age%d_Age%d_%d.img", parameters.outputDir, IVFileNames[k - 1].c_str(), Agerangeage1, Agerangeage2, itr* sites.TimeStep);//* change

							poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

							if (poDstDS == NULL)

								errorSys("Img file not be created.", STOP);//*

							outPoBand = poDstDS->GetRasterBand(1);//*

							poDstDS->SetGeoTransform(wAdfGeoTransform);//*

							for (i = sites.numRows(); i > 0; i--)

							{

								//printf("\r%3d%%",100*i/sites.numRows());

								for (j = 1; j <= sites.numColumns(); j++)

								{
									LANDUNIT *l;
									l = sites.locateLanduPt(i, j);
									TmpBasalAreaT = 0;

									TmpTreeT = 0;

									for (kk = 1; kk <= sites.specNum; kk++)

									{

										if (speciesAttrs(kk)->SpType >= 0)

										{

											for (m = 1; m <= speciesAttrs(kk)->longevity / sites.TimeStep; m++)

											{

												//if(sites.GetGrowthRates(kk,m)>=sites.GetBiomassThreshold())

												//TmpBasalAreaT+=exp(sites.GetBiomassData(speciesAttrs(kk)->BioMassCoef,1)+sites.GetBiomassData(speciesAttrs(kk)->BioMassCoef,2)*log(sites.GetGrowthRates(kk,m)))*sites(i,j)->SpecieIndex(kk)->getTreeNum(m,kk)/1000.00;
												TmpBasalAreaT += sites.GetGrowthRates(kk, m, l->ltID)*sites.GetGrowthRates(kk, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(kk)->getTreeNum(m, kk) / 10000.00;
												TmpTreeT += sites(i, j)->SpecieIndex(kk)->getTreeNum(m, kk);

											}

										}

									}



									TmpBasalAreaS = 0;

									for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

									{

										//if(sites.GetGrowthRates(k,m)>=sites.GetBiomassThreshold())

										//TmpBasalAreaS+=exp(sites.GetBiomassData(speciesAttrs(k)->BioMassCoef,1)+sites.GetBiomassData(speciesAttrs(k)->BioMassCoef,2)*log(sites.GetGrowthRates(k,m)))*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k)/1000.00;
										TmpBasalAreaS += sites.GetGrowthRates(k, m, l->ltID)*sites.GetGrowthRates(k, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 10000.00;
									}



									TmpTreesS = 0;

									for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++)

									{

										TmpTreesS += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);

									}

									if (TmpTreeT == 0 || TmpBasalAreaT < 0.0001){

										//fprintf(fpIV, "0 ");
										*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = 0;//*

									}

									else{

										//fprintf(fpIV, "%f ", (double)TmpTreesS / (double)TmpTreeT + TmpBasalAreaS / TmpBasalAreaT);

										*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = (double)TmpTreesS / (double)TmpTreeT + TmpBasalAreaS / TmpBasalAreaT;//*
									}

								}

							}

							outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

							if (poDstDS != NULL)
								GDALClose((GDALDatasetH)poDstDS);//*
							CPLFree(pafScanline);
							CSLDestroy(papszOptions); //*

					}

				}

			}



		}

		papszOptions = NULL;

		pafScanline1 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
		//pafScanline2 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
		pafScanline3 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
		pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));//*
		pafScanline4 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*
		pafScanline5 = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));//*


		//below is for age range  total 

	//	if (itr*freq[0] <= parameters.numberOfIterations){
			//1.Bio
			if (sites.GetOutputAgerangeFlagArray(sites.specNum, Bio))
			{

				sprintf(str1, "%s/TotalBio_AgeRange_%d.img", parameters.outputDir, itr * sites.TimeStep);//* change

				poDstDS1 = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				if (poDstDS1 == NULL)

					errorSys("Img file not be created.", STOP);//*

				outPoBand1 = poDstDS1->GetRasterBand(1);//*

				poDstDS1->SetGeoTransform(wAdfGeoTransform);//*

			}

			//2.TPA
			if (sites.GetOutputAgerangeFlagArray(sites.specNum, TPA))
			{

				sprintf(str2, "%s/TotalTrees_AgeRange_%d.img", parameters.outputDir, itr * sites.TimeStep);//* change

				poDstDS2 = poDriver->Create(str2, sites.numColumns(), sites.numRows(), 1, GDT_UInt32, papszOptions);//*

				if (poDstDS2 == NULL)

					errorSys("Img file not be created.", STOP);//*

				outPoBand2 = poDstDS2->GetRasterBand(1);//*

				poDstDS2->SetGeoTransform(wAdfGeoTransform);//*


			}

			//3.BA
			if (sites.GetOutputAgerangeFlagArray(sites.specNum, BA))
			{

				sprintf(str3, "%s/TotalBasal_AgeRange_%d.img", parameters.outputDir, itr* sites.TimeStep);//* change

				poDstDS3 = poDriver->Create(str3, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				if (poDstDS3 == NULL)

					errorSys("Img file not be created.", STOP);//*

				outPoBand3 = poDstDS3->GetRasterBand(1);//*

				poDstDS3->SetGeoTransform(wAdfGeoTransform);//*


			}

			//4.Car
			if (sites.GetOutputAgerangeFlagArray(sites.specNum, Car))
			{

				sprintf(str4, "%s/TotalCarbon_AgeRange_%d.img", parameters.outputDir, itr* sites.TimeStep);//* change

				poDstDS4 = poDriver->Create(str4, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				if (poDstDS4 == NULL)

					errorSys("Img file not be created.", STOP);//*

				outPoBand4 = poDstDS4->GetRasterBand(1);//*

				poDstDS4->SetGeoTransform(wAdfGeoTransform);//*

			}

			//5.RDensity
			if (sites.GetOutputAgerangeFlagArray(sites.specNum, RDensity))
			{

				sprintf(str5, "%s/TotalRD_AgeRange_%d.img", parameters.outputDir, itr * sites.TimeStep);//* change

				poDstDS5 = poDriver->Create(str5, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);//*

				if (poDstDS5 == NULL)

					errorSys("Img file not be created.", STOP);//*

				outPoBand5 = poDstDS5->GetRasterBand(1);//*

				poDstDS5->SetGeoTransform(wAdfGeoTransform);//*

			}



			for (i = sites.numRows(); i > 0; i--)

			{

				for (j = 1; j <= sites.numColumns(); j++)

				{
					LANDUNIT *l;
					l = sites.locateLanduPt(i, j);
					TmpBiomassT = 0;

					TmpBasalAreaT = 0;

					TmpTreeT = 0;

					TmpCarbon = 0;

					TmpCarbonTotal = 0;

					TmpRDTotal = 0;

					for (k = 1; k <= sites.specNum; k++)

					{

						TmpCarbon = 0;

						Agerangecount = sites.GetAgerangeCount(k - 1);

						for (Agerangeii = 1; Agerangeii <= Agerangecount; Agerangeii++){

							sites.GetSpeciesAgerangeArray(k - 1, Agerangeii, &Agerangeage1, &Agerangeage2);

							if (speciesAttrs(k)->SpType >= 0)

							{

								for (m = min(speciesAttrs(k)->longevity, Agerangeage1) / sites.TimeStep; m <= min(speciesAttrs(k)->longevity, Agerangeage2) / sites.TimeStep; m++)

								{

									if (sites.GetGrowthRates(k, m, l->ltID) >= sites.GetBiomassThreshold())

										TmpBiomassT += exp(sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 1) + sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 2)*log(sites.GetGrowthRates(k, m, l->ltID)))*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 1000.00;

									TmpBasalAreaT += sites.GetGrowthRates(k, m, l->ltID)*sites.GetGrowthRates(k, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 10000.00;



									//TmpBasalAreaT+=0.005454*sites.GetGrowthRates(k,m)*sites.GetGrowthRates(k,m)*sites(i,j)->SpecieIndex(k)->getTreeNum(m,k);

									TmpTreeT += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);

									TmpCarbon += exp(sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 1) + sites.GetBiomassData(speciesAttrs(k)->BioMassCoef, 2)*log(sites.GetGrowthRates(k, m, l->ltID)))*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);

									TmpRDTotal += pow((sites.GetGrowthRates(k, m, l->ltID) / 25.4), 1.605)*sites(i, j)->specAtt(k)->MaxAreaOfSTDTree*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / sites.CellSize / sites.CellSize;

								}

							}

							TmpCarbonTotal = TmpCarbonTotal + TmpCarbon*speciesAttrs(k)->CarbonCoEfficient;

						}

						/*if(sites.GetOutputGeneralFlagArray(sites.specNum,Seeds))

							fprintf(fpTempAvailableSeed[k-1],"%u ",sites(i,j)->SpecieIndex(k)->AvailableSeed);*/

					}
					//1.Bio
					if (sites.GetOutputAgerangeFlagArray(sites.specNum, Bio)){

						//fprintf(fpTotalBiomass, "%f ", TmpBiomassT);

						*(pafScanline1 + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBiomassT;//*
					}
					//4.Car
					if (sites.GetOutputAgerangeFlagArray(sites.specNum, Car)){

						//fprintf(fpTotalcarbon, "%f ", TmpCarbonTotal / 1000.00);

						*(pafScanline4 + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpCarbonTotal / 1000.00;//*
					}
					//3.BA
					if (sites.GetOutputAgerangeFlagArray(sites.specNum, BA)){

						//fprintf(fptotalbasal, "%f ", TmpBasalAreaT);

						*(pafScanline3 + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBasalAreaT;//*
					}
					//5.RDensity
					if (sites.GetOutputAgerangeFlagArray(sites.specNum, RDensity)){

						//fprintf(fptotalRD,"%f ",TmpRDTotal);

						*(pafScanline5 + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpRDTotal;//*

					}
					//2.TPA
					if (sites.GetOutputAgerangeFlagArray(sites.specNum, TPA)){

						//fprintf(fptotaltrees, "%d ", TmpTreeT);

						*(pintScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpTreeT;//*
					}

				}

			}


			//1.Bio
			if (sites.GetOutputAgerangeFlagArray(sites.specNum, Bio)){

				//fclose(fpTotalBiomass);

				outPoBand1->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline1, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				if (poDstDS1 != NULL)
					GDALClose((GDALDatasetH)poDstDS1);//*

				CPLFree(pafScanline1);
			}
			//4.Car
			if (sites.GetOutputAgerangeFlagArray(sites.specNum, Car)){

				//fclose(fpTotalcarbon);
				outPoBand4->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline4, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				if (poDstDS4 != NULL)
					GDALClose((GDALDatasetH)poDstDS4);//*

				CPLFree(pafScanline4);
			}
			//3.BA
			if (sites.GetOutputAgerangeFlagArray(sites.specNum, BA)){

				//fclose(fptotalbasal);

				outPoBand3->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline3, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				if (poDstDS3 != NULL)
					GDALClose((GDALDatasetH)poDstDS3);//*

				CPLFree(pafScanline3);
			}
			//2.TPA
			if (sites.GetOutputAgerangeFlagArray(sites.specNum, TPA)){

				//fclose(fptotaltrees);

				outPoBand2->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pintScanline, sites.numColumns(), sites.numRows(), GDT_UInt32, 0, 0);//*

				if (poDstDS2 != NULL)
					GDALClose((GDALDatasetH)poDstDS2);//*

				CPLFree(pintScanline);
			}
			//5.RDensity
			if (sites.GetOutputAgerangeFlagArray(sites.specNum, RDensity)){

				//fclose(fptotalRD);

				outPoBand5->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline5, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);//*

				if (poDstDS5 != NULL)
					GDALClose((GDALDatasetH)poDstDS5);//*

				CPLFree(pafScanline5);
			}

	}

}

// Jacob - Custom agerange tree number output
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
int treeNumFlag = 0;
if (treeNumFlag == 1){
	int agerangeLow[5] = { 0, 20, 40, 70, 90 };
	int agerangeHigh[5] = { 10, 30, 60, 80, 300 };

	for (int ar = 0; ar < 5; ar++){
		papszOptions = NULL;
		pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));

		sprintf(str1, "%s/TotalTrees_Age%d_Age%d_%d.img", parameters.outputDir, agerangeLow[ar], agerangeHigh[ar], itr * sites.TimeStep);

		poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_UInt32, papszOptions);

		if (poDstDS == NULL)

			errorSys("Img file not be created.", STOP);

		outPoBand = poDstDS->GetRasterBand(1);

		poDstDS->SetGeoTransform(wAdfGeoTransform);

		for (i = sites.numRows(); i > 0; i--){
			for (j = 1; j <= sites.numColumns(); j++){
				TmpTreesS = 0;
				for (k = 1; k <= sites.specNum; k++){
					for (m = min(speciesAttrs(k)->longevity, agerangeLow[ar]) / sites.TimeStep; m <= min(speciesAttrs(k)->longevity, agerangeHigh[ar]) / sites.TimeStep; m++){
						TmpTreesS += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);
					}
				}
				*(pintScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpTreesS;
			}
		}

		outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pintScanline, sites.numColumns(), sites.numRows(), GDT_UInt32, 0, 0);

		if (poDstDS != NULL)
			GDALClose((GDALDatasetH)poDstDS);

		CPLFree(pintScanline);
		CSLDestroy(papszOptions);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//

// Jacob - Custom agerange basal area output
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
int treeBasalFlag = 0;
if (treeBasalFlag == 1){
	int agerangeLow[5] = { 10, 20, 40, 70, 90 };
	int agerangeHigh[5] = { 10, 30, 60, 80, 300 };

	for (int ar = 0; ar < 5; ar++){
		papszOptions = NULL;
		pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));

		sprintf(str1, "%s/TotalBA_Age%d_Age%d_%d.img", parameters.outputDir, agerangeLow[ar], agerangeHigh[ar], itr * sites.TimeStep);

		poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);

		if (poDstDS == NULL)

			errorSys("Img file not be created.", STOP);

		outPoBand = poDstDS->GetRasterBand(1);

		poDstDS->SetGeoTransform(wAdfGeoTransform);

		for (i = sites.numRows(); i > 0; i--){

			for (j = 1; j <= sites.numColumns(); j++){
				LANDUNIT *l;
				l = sites.locateLanduPt(i, j);
				if (l->active()){
					TmpBasalAreaS = 0;
					for (k = 1; k <= sites.specNum; k++){
						for (m = min(speciesAttrs(k)->longevity, agerangeLow[ar]) / sites.TimeStep; m <= min(speciesAttrs(k)->longevity, agerangeHigh[ar]) / sites.TimeStep; m++){
							float tempGrowth = sites.GetGrowthRates(k, m, l->ltID);
							int tempTreenum = sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);
							double TmpBasal = sites.GetGrowthRates(k, m, l->ltID)*sites.GetGrowthRates(k, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 10000.00;
							TmpBasalAreaS += TmpBasal;
						}
					}
				} else {
					TmpBasalAreaS = 0;
				}
				*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBasalAreaS;
			}
		}

		outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);

		if (poDstDS != NULL)
			GDALClose((GDALDatasetH)poDstDS);

		CPLFree(pafScanline);
		CSLDestroy(papszOptions);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//

// Jacob - Custom diameter class basal area output
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
int diameterBasalFlag = 0;
if (diameterBasalFlag == 1){
	int diameterLow[8] = { 0, 5, 10, 15, 20, 25, 30, 35};
	int diameterHigh[8] = { 5, 10, 15, 20, 25, 30, 35, 999 };

	for (int ar = 0; ar < 8; ar++){
		papszOptions = NULL;
		pafScanline = (float *)CPLMalloc(sizeof(float)* (sites.numColumns()*sites.numRows()));

		sprintf(str1, "%s/TotalBA_Dia%d_Dia%d_%d.img", parameters.outputDir, diameterLow[ar], diameterHigh[ar], itr * sites.TimeStep);

		poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_Float32, papszOptions);

		if (poDstDS == NULL)

			errorSys("Img file not be created.", STOP);

		outPoBand = poDstDS->GetRasterBand(1);

		poDstDS->SetGeoTransform(wAdfGeoTransform);

		for (i = sites.numRows(); i > 0; i--){

			for (j = 1; j <= sites.numColumns(); j++){
				LANDUNIT *l;
				l = sites.locateLanduPt(i, j);
				if (l->active()){
					TmpBasalAreaS = 0;
					for (k = 1; k <= sites.specNum; k++){
						for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++){
							float tempGrowth = sites.GetGrowthRates(k, m, l->ltID);
							if (tempGrowth > diameterLow[ar] & tempGrowth <= diameterHigh[ar]){
								double TmpBasal = sites.GetGrowthRates(k, m, l->ltID)*sites.GetGrowthRates(k, m, l->ltID) / 4 * 3.1415926*sites(i, j)->SpecieIndex(k)->getTreeNum(m, k) / 10000.00;
								TmpBasalAreaS += TmpBasal;
							}
						}
					}
				}
				else {
					TmpBasalAreaS = 0;
				}
				*(pafScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpBasalAreaS;
			}
		}

		outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pafScanline, sites.numColumns(), sites.numRows(), GDT_Float32, 0, 0);

		if (poDstDS != NULL)
			GDALClose((GDALDatasetH)poDstDS);

		CPLFree(pafScanline);
		CSLDestroy(papszOptions);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//

// Jacob - Custom diameter class tree number output
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
int diameterTreeFlag = 0;
if (diameterTreeFlag == 1){
	int diameterLow[8] = { 0, 5, 10, 15, 20, 25, 30, 35 };
	int diameterHigh[8] = { 5, 10, 15, 20, 25, 30, 35, 999 };

	for (int ar = 0; ar < 8; ar++){
		papszOptions = NULL;
		pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));

		sprintf(str1, "%s/TotalTrees_Dia%d_Dia%d_%d.img", parameters.outputDir, diameterLow[ar], diameterHigh[ar], itr * sites.TimeStep);

		poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_UInt32, papszOptions);

		if (poDstDS == NULL)

			errorSys("Img file not be created.", STOP);

		outPoBand = poDstDS->GetRasterBand(1);

		poDstDS->SetGeoTransform(wAdfGeoTransform);

		for (i = sites.numRows(); i > 0; i--){
			for (j = 1; j <= sites.numColumns(); j++){
				LANDUNIT *l;
				l = sites.locateLanduPt(i, j);
				TmpTreesS = 0;
				for (k = 1; k <= sites.specNum; k++){
					for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++){
						float tempGrowth = sites.GetGrowthRates(k, m, l->ltID);
						if (tempGrowth > diameterLow[ar] & tempGrowth <= diameterHigh[ar]){
							TmpTreesS += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);
						}
					}
				}
				*(pintScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpTreesS;
			}
		}

		outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pintScanline, sites.numColumns(), sites.numRows(), GDT_UInt32, 0, 0);

		if (poDstDS != NULL)
			GDALClose((GDALDatasetH)poDstDS);

		CPLFree(pintScanline);
		CSLDestroy(papszOptions);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//

// Jacob - Custom diameter class tree number output - Cohort kill design
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
int cohortTreeFlag = 0;
if (cohortTreeFlag == 1){
	int diameterLow[8] = { 0, 5, 10, 15, 20, 25, 30, 35 };
	int diameterHigh[8] = { 5, 10, 15, 20, 25, 30, 35, 999 };

	for (int ar = 0; ar < 8; ar++){
		papszOptions = NULL;
		pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (sites.numColumns()*sites.numRows()));

		sprintf(str1, "%s/CohortDesign_Dia%d_Dia%d_%d.img", parameters.outputDir, diameterLow[ar], diameterHigh[ar], itr * sites.TimeStep);

		poDstDS = poDriver->Create(str1, sites.numColumns(), sites.numRows(), 1, GDT_UInt32, papszOptions);

		if (poDstDS == NULL)

			errorSys("Img file not be created.", STOP);

		outPoBand = poDstDS->GetRasterBand(1);

		poDstDS->SetGeoTransform(wAdfGeoTransform);

		for (i = sites.numRows(); i > 0; i--){
			for (j = 1; j <= sites.numColumns(); j++){
				LANDUNIT *l;
				l = sites.locateLanduPt(i, j);
				TmpTreesS = 0;
				for (k = 1; k <= sites.specNum; k++){
					int fireDiff = 1 - speciesAttrs(k)->fireTolerance;
					float cohortRemove = 0.0;
					if (fireDiff == -2) {
						cohortRemove = 0.2;
					}
					else if (fireDiff == -1) {

						cohortRemove = 0.5;
					}
					else if (fireDiff == 0) {
						cohortRemove == 0.85;
					}
					else if (fireDiff == 1) {
						cohortRemove == 1.0;
					}
					for (m = 1; m <= speciesAttrs(k)->longevity / sites.TimeStep; m++){
						if ((m * sites.TimeStep) <= (speciesAttrs(k)->longevity * cohortRemove)) {
							float tempGrowth = sites.GetGrowthRates(k, m, l->ltID);
							if (tempGrowth > diameterLow[ar] & tempGrowth <= diameterHigh[ar]){
								TmpTreesS += 0;
							}
						}
						else {
							float tempGrowth = sites.GetGrowthRates(k, m, l->ltID);
							if (tempGrowth > diameterLow[ar] & tempGrowth <= diameterHigh[ar]){
								TmpTreesS += sites(i, j)->SpecieIndex(k)->getTreeNum(m, k);
							}
						}
					}
				}
				*(pintScanline + (sites.numRows() - i)*sites.numColumns() + j - 1) = TmpTreesS;
			}
		}

		outPoBand->RasterIO(GF_Write, 0, 0, sites.numColumns(), sites.numRows(), pintScanline, sites.numColumns(), sites.numRows(), GDT_UInt32, 0, 0);

		if (poDstDS != NULL)
			GDALClose((GDALDatasetH)poDstDS);

		CPLFree(pintScanline);
		CSLDestroy(papszOptions);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//

time(&ltimeTemp);

//CPLFree(pafScanline1);
//CPLFree(pafScanline2);
//CPLFree(pafScanline3);
//CPLFree(pafScanline4);
//CPLFree(pafScanline5);
//CPLFree(pintScanline);
//CPLFree(pafScanline);

printf("Finish 7.0 Style writing output at %s\n",ctime(&ltimeTemp));

printf("it took %ld seconds\n", (long) ltimeTemp-ltime);

fflush(stdout);

CSLDestroy(papszOptions); //*



}



void putOutput(int rep, int itr, int freq[], double wAdfGeoTransform[])

//This will write out a Landis description for this iteration and replicate.



{

int i;  //Nim: added this line

char str[100], str1[100];

char *pdest; //hsh

int ch= '\\';   //hsh

MAP8 m(sites.getHeader());

char strMsg[256];

time_t ltime,ltimeTemp;



time(&ltime);

printf("Start 6.0 Style writing output at %s",ctime(&ltime));



//if (((itr%freq[0])==0)&&(freq[0]<=sites.TimeStep)||(itr*sites.TimeStep==freq[0])&&(freq[0]>=0))



{

	for (i=0;i<0;i++) //Nim: changed int i to i

   {

	  pdest = strrchr (reMethods[i], ch); //hsh: assign map name to str1

	  if (pdest)

	  {
		pdest++;

	    strcpy (str1, pdest);

		sprintf(strMsg,"reclass %s\n",pdest);

		printMessage(strMsg);	    
	  }

	  else
	  {
		strcpy (str1, reMethods[i]);

		sprintf(strMsg,"reclass %s\n",reMethods[i]);

	  	printMessage(strMsg);

	  }

	  sprintf(str,"%s.rcs",reMethods[i]);

	  fileReclass(m,str);

	  sprintf(str,"%s/%s%d",parameters.outputDir,str1,itr);

	  m.setCellSize(parameters.cellSize);

	  m.write(str, red, green, blue, wAdfGeoTransform);

   }

	for (i = 1; ((i <= sites.specNum) && (!rep)); i++) //Nim: changed int i to i

	{

		//printf("reclass\n");

		/*pdest = strrchr (ageMaps[i], ch); //hsh: assign map name to str1

		if (pdest)

		{

		pdest++;

		strcpy (str1, pdest);

		printf("creating: %s %s\n",pdest,"age map");

		}

		else

		{

		strcpy (str1, ageMaps[i]);

		printf("creating %d %d %s %s\n",numAgeMaps,rep,ageMaps[i],"age map");

		}

		sprintf(str,"%s.age",ageMaps[i]);*/
		//if (itr*freq[4] <= parameters.numberOfIterations){

			//printf("creating %d %d %s %s\n", sites.specNum, rep, speciesAttrs(i)->name, "age map");

			speciesAgeMap(m, speciesAttrs(i)->name);

			sprintf(str, "%s/%s_%d", parameters.outputDir, speciesAttrs(i)->name, itr * sites.TimeStep);

			m.setCellSize(parameters.cellSize);

			m.write(str, red2, green2, blue2, wAdfGeoTransform);
		//}



		/*if (parameters.numberOfIterations % freq[4] != 0){

			speciesAgeMap(m, speciesAttrs(i)->name);

			sprintf(str, "%s/%s_%d", parameters.outputDir, speciesAttrs(i)->name, parameters.numberOfIterations* sites.TimeStep);

			m.setCellSize(parameters.cellSize);

			m.write(str, red2, green2, blue2);
		}*/

	}

}



//if (((itr%freq[4])==0)&&(freq[4]<=sites.TimeStep)||(itr*sites.TimeStep==freq[4])

//      &&(freq[4]>=0)&&(!rep))



 {
	// if (itr*freq[4] <= parameters.numberOfIterations)
	// {
		 ageReclass(m);

		 sprintf(str, "%s/ageOldest%d", parameters.outputDir, itr*sites.TimeStep);

		 m.setCellSize(parameters.cellSize);

		 m.write(str, red2, green2, blue2, wAdfGeoTransform);

		 //<Add By Qia on Jan 26 2010>

		 ageReclassYoungest(m);

		 sprintf(str, "%s/ageYoungest%d", parameters.outputDir, itr* sites.TimeStep);

		 m.setCellSize(parameters.cellSize);

		 m.write(str, red2, green2, blue2, wAdfGeoTransform);
	// }

	 //if (parameters.numberOfIterations % freq[4] != 0)
	 //{

		// ageReclass(m);

		// sprintf(str, "%s/ageOldest%d", parameters.outputDir, parameters.numberOfIterations* sites.TimeStep);

		// m.setCellSize(parameters.cellSize);

		// m.write(str, red2, green2, blue2);

		// //<Add By Qia on Jan 26 2010>

		// ageReclassYoungest(m);

		// sprintf(str, "%s/ageYoungest%d", parameters.outputDir, parameters.numberOfIterations* sites.TimeStep);

		// m.setCellSize(parameters.cellSize);

		// m.write(str, red2, green2, blue2);
	 //
	 //}



 }







time(&ltimeTemp);

printf("Finish 6.0 Style writing output at %s",ctime(&ltimeTemp));

printf("it took %ld seconds\n\n", (long) ltimeTemp-ltime);

fflush(stdout);





}



void ioTerm()

//This will call any computer dependent io calls (i.e. terminate graphics

//system) at the end of the model.



{

printMessage("Ending Landis Run.\n");

}



#ifdef __UNIX__

#define swap4bytes(srcptr, destptr) *((char*)destptr) = *(((char*)srcptr)+3); \

              *(((char*)destptr)+1) = *(((char*)srcptr)+2); \

              *(((char*)destptr)+2) = *(((char*)srcptr)+1); \

              *(((char*)destptr)+3) = *((char*)srcptr)

#define ERDi4_c(srcptr, dest)  swap4bytes(srcptr, &dest)



#define swap2bytes(srcptr, destptr) *((char*)destptr) = *(((char*)srcptr)+1);\

              *(((char*)destptr)+1) = *((char*)srcptr)

#define ERDi2_i(srcptr, dest)  dest = 0; swap2bytes(srcptr, (((char*)&dest)+2))

#endif



/*

Modifed by Wei Li June 23,  2004 to read both 16 and 8 bit map

*/



//<Add By Qia on July 6 2009>

void inputBin8(FILE* classFile, FILE* mapFile, GDALDataset* simgFileint, int yDim, int xDim, int b16or8)

//This will read in the global variable sites from class file and map file.

//Class file is a file containing site descriptions for a set of class values.

//Map file contains the corresponding map.  Thus every value in mapFile

//is represented by the cooresponding class descritption represented in

//classFile.  mapFile is an Erdas 8 bit gis file.  The file pointer is

//placed on the first map element.  yDim and xDim are the (x,y) dimensions

//of the Erdas map.



{

 int coverType, coverType1, numRead = 1, numCovers = 0; //*

 float *pafScanline; //*

 GDALRasterBand  *poBand;//*

 poBand = simgFileint->GetRasterBand(1);//*


unsigned char c;

SITE *s;

SITE *site, *site_temp; 

unsigned short		 intdata;

int *combineMatrix; 


printf("reading age cohort in inputBin8\n");

//Modified by Wei LI June 23, 2005, to incorporate more than 255 Map class 

if (b16or8 == 8)

{

	s=new SITE[256];

}

else if (b16or8 == 16)

{

	s = new SITE[50000];

}



while (!LDeof(classFile))

{

	s[numCovers].read(classFile);

   numCovers++;

}

//<Add By Qia Oct 10 2008>

//build sites and copy sites to sorted array, this array will be sorted later.

if(sites.Pro0or401==0){ //Add By Qia on April 14 2009

	for(int i=0;i<numCovers;i++)

	{

		site=new SITE;

		*site=s[i];

		sites.SortedIndex.push_back(site);

	}



	//<Add By Qia on Oct 22 2008>

	//combineMatrix is used to mark which site is redundant, as well as this site is the same with which one

	combineMatrix=new int[numCovers];

	for(int i=0;i<numCovers;i++)

	{

		combineMatrix[i]=i;

	}

	//</Add By Qia on Oct 22 2008>

}





//<Add By Qia on Oct 22 2008>

if(sites.Pro0or401==0){ //Add By Qia on April 14 2009

lookupredundant(combineMatrix,numCovers);

}

//</Add By Qia on Oct 22 2008>





//</Add By Qia Oct 10 2008>

printf("Reading species composition map\n");

pafScanline = (float *)CPLMalloc(sizeof(float)* (xDim * yDim));//*

poBand->RasterIO(GF_Read, 0, 0, xDim, yDim, pafScanline, xDim, yDim, GDT_Float32, 0, 0);//*



if (b16or8 == 8)  //8 bit

{

	for (int i=yDim;i>0;i--)

	{

		for (int j=1;j<=xDim;j++)

	   {

   		numRead=LDfread((char*)(&c),1,1,mapFile);

   		coverType=(int)c;


		coverType1 = (int)*(pafScanline + (yDim - i)*xDim + j - 1);//*

		assert(coverType == coverType1);//*

		cout << "number of class" << numCovers << endl;

		  if (numRead>0)

		  {

			  if ((coverType1)<numCovers && coverType1>=0) {//J.Yang 04/17/2002

      		     //<Change by Qia on Oct 10 2008>

      		     

				 //*(sites(i,j))=s[coverType]; // Original from Landis 4.0

				 if(sites.Pro0or401==0){ //Add By Qia on April 14 2009

				 sites.fillinSitePt(i,j,sites.SortedIndex.at(combineMatrix[coverType1]));

				 sites.SortedIndex.at(combineMatrix[coverType1])->numofsites++;

				 	}

				 else{

				 	*(sites(i,j))=s[coverType1];

				 	}

				 //</Change by Qia on Oct 10 2008>

			  }

			 else //J.Yang 04/17/2002

			 {

				 delete [] s;

				 cout << "coverType" << coverType1 << endl;

				 errorSys("Error reading in coverType from the map file 1", STOP);

			 }

		  }

	   }

	}

}

else if (b16or8 == 16)

{

	for (int i=yDim;i>0;i--)

	{

		for (int j=1;j<=xDim;j++)

	   {

   		numRead=LDfread((char*)(&intdata),2,1,mapFile);

   		coverType=(int)intdata;

		coverType1 = (int)*(pafScanline + (yDim - i)*xDim + j - 1);//*

		assert(coverType == coverType1);//*

		cout << "number of class" << numCovers << endl;

		  if (numRead>0)

		  {	

      		if ((coverType1)<numCovers && coverType1>=0){ //J.Yang 04/17/2002

				 //<Change by Qia on Oct 10 2008>

				 //*(sites(i,j))=s[coverType]; // Original from Landis 4.0

				 

				 if(sites.Pro0or401==0){

				 sites.fillinSitePt(i,j,sites.SortedIndex.at(combineMatrix[coverType1]));

				 sites.SortedIndex.at(combineMatrix[coverType1])->numofsites++;

				 	}

				 else{

				 	*(sites(i,j))=s[coverType1];

				 	}

				 //</Change by Qia on Oct 10 2008>

      			}

			else if (coverType != 55537)  //weili

					  //J.Yang 04/17/2002

			 {

				 delete [] s;

				 cout << "coverType" << coverType1 << endl;

				 errorSys("Error reading in coverType from the map file 2", STOP);

			 }

		  }

	   }

	}

}



//<Add By Qia on Oct 22 2008>

if(sites.Pro0or401==0){

printf("releasing redundant memory\n");

deleteRedundantInitial(combineMatrix,numCovers);



sites.SITE_sort();



//</Add By Qia on Oct 22 2008>

//<Add By Qia on Oct 22 2008>

delete [] combineMatrix;

//</Add By Qia on Oct 22 2008>

}



delete [] s;







}

void inputImgSpec(FILE* classFile, GDALDataset* simgFileint, int yDim, int xDim)

//This will read in the global variable sites from class file and simgFileint file.

//Class file is a file containing site descriptions for a set of class values.

//Map file contains the corresponding  img map.  Thus every value in mapFile

//is represented by the cooresponding class descritption represented in

//classFile. 
{

	int coverType, numCovers = 0, noDataValue;

	float *pafScanline; //*

	SITE *s;

	SITE *site;

	int *combineMatrix; //Add By Qia on Oct 22 2008

	int adMax;

	int  bGotMax, max = -100;

	GDALRasterBand  *poBand;

	poBand = simgFileint->GetRasterBand(1);

	adMax = (int) poBand->GetMaximum(&bGotMax);

	//cout << "max value is " << adMax << endl;


	pafScanline = (float *)CPLMalloc(sizeof(float)* (xDim * yDim));

	poBand->RasterIO(GF_Read, 0, 0, xDim, yDim, pafScanline, xDim, yDim, GDT_Float32, 0, 0);

	noDataValue = GDALGetRasterNoDataValue(poBand, NULL);

//	printf("reading age cohort in inputImgSpec2\n");

	//s = new SITE[adMax+2];

	//s = new SITE[50000];

	SITE temp;

	while (!LDeof(classFile))
	{
		//SITE *temp = new SITE;
		
		temp.read(classFile);

		numCovers++;
	}

	LDfclose(classFile);
	

	if ((classFile = LDfopen(parameters.reclassInFile, 1)) == NULL) //This one has age list

		errorSys("Map attribute input file not found.", STOP);
	
	s = new SITE[numCovers];

	for (int i = 0; i < numCovers; i++){

		s[i].read(classFile);
	}


	if (sites.Pro0or401 == 0) // for degug??
	{

		for (int i = 0; i<numCovers; i++)
		{
			site = new SITE;

			*site = s[i];

			sites.SortedIndex.push_back(site);
		}

		combineMatrix = new int[numCovers];

		for (int i = 0; i<numCovers; i++)
		{
			combineMatrix[i] = i;
		}
	}

	if (sites.Pro0or401 == 0) //for debug??
	{
		lookupredundant(combineMatrix, numCovers);
	}

	//printf("Reading species composition map in inputImgSpec1\n");

	cout << "Number of attribute classes is " << numCovers << endl;
	
	for (int i = yDim; i>0; i--)
	{
		for (int j = 1; j <= xDim; j++)
		{
			coverType = (int)*(pafScanline + (yDim - i)*xDim + j - 1);//*

			//cout << coverType << " ";
			if (coverType == noDataValue) {
				//Causing error with NoData in map -- Jacob 01/29/2019
				//sites.fillinSitePt(i, j, sites.SortedIndex.at(combineMatrix[0]));
				*(sites(i, j)) = s[0];
			}

			else if ((coverType) < numCovers && coverType >= 0)
			{
				if (sites.Pro0or401 == 0)
				{

					sites.fillinSitePt(i, j, sites.SortedIndex.at(combineMatrix[coverType]));

					sites.SortedIndex.at(combineMatrix[coverType])->numofsites++;

				}
				else
				{

					*(sites(i, j)) = s[coverType];
				}

			}else
			{
				delete[] s;

				cout << "coverType" << coverType << endl;

				errorSys(" Error reading in coverType from the map file 3", STOP);
			}
		}

		//std::cout << std::endl;
	}
	

	if (sites.Pro0or401 == 0) // for debug??
	{

		printf("releasing redundant memory\n");

		deleteRedundantInitial(combineMatrix, numCovers);

		sites.SITE_sort();

		delete[] combineMatrix;

	}

	delete[] s;
}

void inputBin16(FILE* classFile, FILE* mapFile, int yDim, int xDim)

//This will read in the global variable sites from class file and map file.

//Class file is a file containing site descriptions for a set of class values.

//Map file contains the corresponding map.  Thus every value in mapFile

//is represented by the cooresponding class descritption represented in

//classFile.  mapFile is an Erdas 16 bit gis file.  The file pointer is

//placed on the first map element.  yDim and xDim are the (x,y) dimensions

//of the Erdas map.



{

int coverType, numRead, numCovers=0,i;

unsigned short c;

SITE *s;

SITE *site; //Add By Qia on Oct 10 2008

int *combineMatrix; //Add By Qia on Oct 22 2008

printf("reading age cohort in inputBin16\n");

s=new SITE[50000]; //number is temporary //

while (!LDeof(classFile))

   {

    s[numCovers].read(classFile);

    numCovers++;

   }



//<Add By Qia Oct 10 2008>

//build sites and copy sites to sorted array, this array will be sorted later.

for(i=0;i<numCovers;i++)

{

	site=new SITE;

	*site=s[i];

	sites.SortedIndex.push_back(site);

}

//<Add By Qia on Oct 22 2008>

combineMatrix=new int[numCovers];

for(i=0;i<numCovers;i++)

{

	combineMatrix[i]=i;

}

//</Add By Qia on Oct 22 2008>



//<Add By Qia on Oct 22 2008>

lookupredundant(combineMatrix,numCovers);

//</Add By Qia on Oct 22 2008>



//</Add By Qia Oct 10 2008>

printf("Reading species composition map\n");

for (i=yDim;i>0;i--)

    {

     for (int j=1;j<=xDim;j++)

         {

          numRead=LDfread((char*)(&c),2,1,mapFile); 

          #ifdef __UNIX__

	     ERDi2_i(&c, coverType);

	  #else

 	     coverType=(int)c;

	  #endif

          if (numRead>0)

              {

			  if ((coverType)<numCovers && coverType>0){

                   //<Change by Qia on Oct 22 2008>

				 //*(sites(i,j))=s[coverType]; // Original from Landis 4.0

				 sites.fillinSitePt(i,j,sites.SortedIndex.at(combineMatrix[coverType]));

			   sites.SortedIndex.at(combineMatrix[coverType])->numofsites++;

				 //</Change by Qia on Oct 22 2008>

			  }

	       else{

                  //<Change by Qia on Oct 22 2008>

				 //*(sites(i,j))=s[0];  // Original from Landis 4.0

				 sites.fillinSitePt(i,j,sites.SortedIndex.at(0));

				  sites.SortedIndex.at(combineMatrix[coverType])->numofsites++;

				 //</Change by Qia on Oct 22 2008>

	       	}

              }

         }

    }

//<Add By Qia on Oct 22 2008>

printf("releasing redundant memory\n");

deleteRedundantInitial(combineMatrix,numCovers);

sites.SITE_sort();



//</Add By Qia on Oct 22 2008>

delete [] s;

//<Add By Qia on Oct 22 2008>

delete [] combineMatrix;



//</Add By Qia on Oct 22 2008>

}



//</Add By Qia on July 6 2009>

/*void inputBin8(FILE* classFile, FILE* mapFile, int yDim, int xDim, int b16or8)

//This will read in the global variable sites from class file and map file.

//Class file is a file containing site descriptions for a set of class values.

//Map file contains the corresponding map.  Thus every value in mapFile

//is represented by the cooresponding class descritption represented in

//classFile.  mapFile is an Erdas 8 bit gis file.  The file pointer is

//placed on the first map element.  yDim and xDim are the (x,y) dimensions

//of the Erdas map.



{

int coverType, numRead, numCovers=0;

unsigned char c;

SITE *s;

SITE *site, *site_temp; //Add By Qia on Oct 10 2008

unsigned short		 intdata;

int *combineMatrix; //Add By Qia on Oct 22 2008

//Modified by Wei LI June 23, 2005, to incorporate more than 255 Map class 

if (b16or8 == 8)

{

	s=new SITE[256];

}

else if (b16or8 == 16)

{

	s = new SITE[50000];

}



while (!LDeof(classFile))

{

	s[numCovers].read(classFile);

   numCovers++;

}

//<Add By Qia Oct 10 2008>

//build sites and copy sites to sorted array, this array will be sorted later.

for(int i=0;i<numCovers;i++)

{

	site=new SITE;

	*site=s[i];

	sites.SortedIndex.push_back(site);

}

//<Add By Qia on Oct 22 2008>

//combineMatrix is used to mark which site is redundant, as well as this site is the same with which one

combineMatrix=new int[numCovers];

for(int i=0;i<numCovers;i++)

{

	combineMatrix[i]=i;

}

//</Add By Qia on Oct 22 2008>



//<Add By Qia on Oct 22 2008>

lookupredundant(combineMatrix,numCovers);

//</Add By Qia on Oct 22 2008>





//</Add By Qia Oct 10 2008>

if (b16or8 == 8)  //8 bit

{

	for (int i=yDim;i>0;i--)

	{

		for (int j=1;j<=xDim;j++)

	   {

   		numRead=LDfread((char*)(&c),1,1,mapFile);

   		coverType=(int)c;

		  if (numRead>0)

		  {

			  if ((coverType)<numCovers && coverType>=0) {//J.Yang 04/17/2002

      		     //<Change by Qia on Oct 10 2008>

				 //*(sites(i,j))=s[coverType]; // Original from Landis 4.0

				 sites.fillinSitePt(i,j,sites.SortedIndex.at(combineMatrix[coverType]));

				 sites.SortedIndex.at(combineMatrix[coverType])->numofsites++;

				 //</Change by Qia on Oct 10 2008>

			  }

			 else //J.Yang 04/17/2002

			 {

				 delete [] s;

				 errorSys("Error reading in coverType from the map file", STOP);

			 }

		  }

	   }

	}

}

else if (b16or8 == 16)

{

	for (int i=yDim;i>0;i--)

	{

		for (int j=1;j<=xDim;j++)

	   {

   		numRead=LDfread((char*)(&intdata),2,1,mapFile);

   		coverType=(int)intdata;

		  if (numRead>0)

		  {

      		if ((coverType)<numCovers && coverType>=0){ //J.Yang 04/17/2002

				 //<Change by Qia on Oct 10 2008>

				 //*(sites(i,j))=s[coverType]; // Original from Landis 4.0

				 

				 

				 sites.fillinSitePt(i,j,sites.SortedIndex.at(combineMatrix[coverType]));

				 sites.SortedIndex.at(combineMatrix[coverType])->numofsites++;

				 //</Change by Qia on Oct 10 2008>

      			}

			else if (coverType != 55537)  //weili

					  //J.Yang 04/17/2002

			 {

				 delete [] s;

				 errorSys("Error reading in coverType from the map file", STOP);

			 }

		  }

	   }

	}

}



//<Add By Qia on Oct 22 2008>

deleteRedundantInitial(combineMatrix,numCovers);



sites.SITE_sort();



//</Add By Qia on Oct 22 2008>





delete [] s;

//<Add By Qia on Oct 22 2008>

delete [] combineMatrix;

//</Add By Qia on Oct 22 2008>





}



void inputBin16(FILE* classFile, FILE* mapFile, int yDim, int xDim)

//This will read in the global variable sites from class file and map file.

//Class file is a file containing site descriptions for a set of class values.

//Map file contains the corresponding map.  Thus every value in mapFile

//is represented by the cooresponding class descritption represented in

//classFile.  mapFile is an Erdas 16 bit gis file.  The file pointer is

//placed on the first map element.  yDim and xDim are the (x,y) dimensions

//of the Erdas map.



{

int coverType, numRead, numCovers=0,i;

unsigned short c;

SITE *s;

SITE *site; //Add By Qia on Oct 10 2008

int *combineMatrix; //Add By Qia on Oct 22 2008

s=new SITE[50000]; //number is temporary //

while (!LDeof(classFile))

   {

    s[numCovers].read(classFile);

    numCovers++;

   }



//<Add By Qia Oct 10 2008>

//build sites and copy sites to sorted array, this array will be sorted later.

for(i=0;i<numCovers;i++)

{

	site=new SITE;

	*site=s[i];

	sites.SortedIndex.push_back(site);

}

//<Add By Qia on Oct 22 2008>

combineMatrix=new int[numCovers];

for(i=0;i<numCovers;i++)

{

	combineMatrix[i]=i;

}

//</Add By Qia on Oct 22 2008>



//<Add By Qia on Oct 22 2008>

lookupredundant(combineMatrix,numCovers);

//</Add By Qia on Oct 22 2008>



//</Add By Qia Oct 10 2008>

for (i=yDim;i>0;i--)

    {

     for (int j=1;j<=xDim;j++)

         {

          numRead=LDfread((char*)(&c),2,1,mapFile); 

          #ifdef __UNIX__

	     ERDi2_i(&c, coverType);

	  #else

 	     coverType=(int)c;

	  #endif

          if (numRead>0)

              {

			  if ((coverType)<numCovers && coverType>0){

                   //<Change by Qia on Oct 22 2008>

				 //*(sites(i,j))=s[coverType]; // Original from Landis 4.0

				 sites.fillinSitePt(i,j,sites.SortedIndex.at(combineMatrix[coverType]));

			   sites.SortedIndex.at(combineMatrix[coverType])->numofsites++;

				 //</Change by Qia on Oct 22 2008>

			  }

	       else{

                  //<Change by Qia on Oct 22 2008>

				 //*(sites(i,j))=s[0];  // Original from Landis 4.0

				 sites.fillinSitePt(i,j,sites.SortedIndex.at(0));

				  sites.SortedIndex.at(combineMatrix[coverType])->numofsites++;

				 //</Change by Qia on Oct 22 2008>

	       	}

              }

         }

    }

//<Add By Qia on Oct 22 2008>

deleteRedundantInitial(combineMatrix,numCovers);

sites.SITE_sort();



//</Add By Qia on Oct 22 2008>

delete [] s;

//<Add By Qia on Oct 22 2008>

delete [] combineMatrix;

//</Add By Qia on Oct 22 2008>

}*/



void inputLandtypeMap8(FILE* mapFile, GDALDataset* ltimgFile, int xDim, int yDim, PDP* ppdp)

//This will read landtype map and associate landUnit to each site.

//mapFile is an Erdas 8 bit gis file.  The file pointer is

//placed on the first map element.  yDim and xDim are the (x,y) dimensions

//of the Erdas map.



{

unsigned char c;

unsigned long dest[64];

int 	nCols, nCols1,

nRows, nRows1,

      numRead,

	  coverType, coverType1;

SITE* s;

char	b16or8;   //true: 16, false 8 bit

unsigned short		 intdata;

float *pafScanline; //*

GDALRasterBand  *poBand;//*

poBand = ltimgFile->GetRasterBand(1);//*

//fread((char*)dest,4,32,mapintdataFile);

LDfread((char*)dest,4,32,mapFile);



//modifed bv Wei Li, June 2004

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

nCols=dest[4];

nRows=dest[5];

nCols1 = ltimgFile->GetRasterXSize(); //*

nRows1 = ltimgFile->GetRasterYSize(); //*

assert((nCols == nCols1) && (nRows == nRows1));
if ((nCols != nCols1) && (nRows != nRows1))

errorSys("landtype gis map and landtype img map do not match.", STOP);


#endif
pafScanline = (float *)CPLMalloc(sizeof(float)* (xDim * yDim));//*

poBand->RasterIO(GF_Read, 0, 0, xDim, yDim, pafScanline, xDim, yDim, GDT_Float32, 0, 0);//*





if ((nCols != xDim) && (nRows != yDim))

	errorSys("landtype map and species map do not match.",STOP);

if (b16or8 == 8)  //8 bit

{

	for (int i=yDim;i>0;i--)

	{

		for (int j=1;j<=xDim;j++)

	   {

   		numRead=LDfread((char*)(&c),1,1,mapFile);

   		coverType=(int)c;

		coverType1 = (int)*(pafScanline + (yDim - i)*xDim + j - 1);//*

		assert(coverType == coverType1);//*

		  if ((numRead>=0)&&(coverType1>=0))

		  {

			 //s=sites(i,j); // comment By Qia Oct 10 2008

			 //<Add By Qia on Oct 10 2008>

			 sites.fillinLanduPt(i,j,landUnits(coverType1));

			 
			 //</Add By Qia on Oct 10 2008>

	//         s->lastWind=(short)s->landUnit->initialLastWind;  modified by Vera Dec. 30

	//		 if ((gDLLMode & G_WIND && gDLLMode & G_BDA) || (gDLLMode & G_WIND && gDLLMode & G_FUEL))

			 if (gDLLMode & G_WIND)

				(ppdp->sTSLWind)[i][j] = (short)sites.locateLanduPt(i,j)->initialLastWind;

			 //original landis4.0: (ppdp->sTSLWind)[i][j] = (short)s->landUnit->initialLastWind;

			 //changed By Qia on Oct 13 2008



	 //        s->lastFire=(short)s->landUnit->initialLastFire;

	//		 ppdp->sTSLFire[i][j] = 

		  }

		  else

        		errorSys("Illegal landtype class found - 1.",STOP);

	   }

	}

}

else if (b16or8 == 16)	//16 bit

{

	for (int i=yDim;i>0;i--)

	{

		for (int j=1;j<=xDim;j++)

	   {

   			numRead=LDfread((char*)(&intdata),2,1,mapFile);

   			coverType=(int)intdata;

			coverType1 = (int)*(pafScanline + (yDim - i)*xDim + j - 1);//*

			assert(coverType == coverType1);//*

			  if ((numRead>=0)&&(coverType1>=0))

			  {

				 //s=sites(i,j);// comment By Qia Oct 10 2008

      			 //s->landUnit=landUnits(coverType);// comment By Qia Oct 10 2008

      			 //<Add By Qia on Oct 10 2008>

				 sites.fillinLanduPt(i,j,landUnits(coverType1));
				
				 

				 //</Add By Qia on Oct 10 2008>

		//         s->lastWind=(short)s->landUnit->initialLastWind;  modified by Vera Dec. 30

		//		 if ((gDLLMode & G_WIND && gDLLMode & G_BDA) || (gDLLMode & G_WIND && gDLLMode & G_FUEL))

				 if (gDLLMode & G_WIND)

					(ppdp->sTSLWind)[i][j] = (short)sites.locateLanduPt(i,j)->initialLastWind;

				 //original landis4.0: (ppdp->sTSLWind)[i][j] = (short)s->landUnit->initialLastWind

				 //changed By Qia on Oct 13 2008

		 //        s->lastFire=(short)s->landUnit->initialLastFire;

		//		 ppdp->sTSLFire[i][j] = 

			  }

			  else

        			errorSys("Illegal landtype class found - 2.",STOP);

		   }

		}

	}



}


void inputLandtypeImg(GDALDataset* ltimgFile, int xDim, int yDim, PDP* ppdp)
{
	//This will read landtype img map and associate landUnit to each site.

	//ltimgFile is an 32 bit img file.  
	{

		//cout << "reading landtypeImg" << endl;
		int nRows, nCols, numRead, coverType, noDataValue;

		SITE* s;

		unsigned short		 intdata;

		float *pafScanline; //*

		GDALRasterBand  *poBand;

#ifdef __UNIX__

		ERDi4_c(&dest[4], nCols);

		ERDi4_c(&dest[5], nRows);

#else

		nCols = ltimgFile->GetRasterXSize(); //*

		nRows = ltimgFile->GetRasterYSize(); //*

#endif
		pafScanline = (float *)CPLMalloc(sizeof(float)* (xDim * yDim));

		poBand = ltimgFile->GetRasterBand(1);

		poBand->RasterIO(GF_Read, 0, 0, xDim, yDim, pafScanline, xDim, yDim, GDT_Float32, 0, 0);

		noDataValue = GDALGetRasterNoDataValue(poBand, NULL);

		if (ltimgFile->GetProjectionRef() != NULL)
			printf("Projection is `%s'\n", ltimgFile->GetProjectionRef());

		if ((nCols != xDim) && (nRows != yDim))

			errorSys("landtype map and species map do not match.", STOP);

		for (int i = yDim; i>0; i--)
		{
			for (int j = 1; j <= xDim; j++)
			{
				coverType = (int)*(pafScanline + (yDim - i)*xDim + j - 1);//*
				if (coverType == noDataValue) {
					sites.fillinLanduPt(i, j, landUnits(0));
				}
				else if (coverType >= 0)
				{
					sites.fillinLanduPt(i, j, landUnits(coverType));

					if (gDLLMode & G_WIND)

						(ppdp->sTSLWind)[i][j] = (short)sites.locateLanduPt(i, j)->initialLastWind;
				}
				else {
					cout << "i = " << i << "j = " << j << "coverType =" << coverType << endl;
					errorSys("illegal landtype class found3.", STOP);
				}
			}
		}

	}

}




//modified by Vera Dec. 30

void getInput(FILE *infile, int freq[], char reMethods[MAX_RECLASS][80], char ageMap[MAX_SPECIES][80], PDP** ppdp, int BDANo, double wAdfGeoTransform[])

//This will read in all LANDIS global variables.



{

int colNum,x; //Nim: added this line

FILE	*saFile,

		*luFile,

		//*ltMapFile,

     //	*siFile,

		*rcFile,

		//*roFile,

		*palleteFile,

	  	*freqOfOutput,

		//*ageFile,

		*bioMass;

int i, nRows, nCols, packType, nRows1, nCols1;//*

unsigned long dest[64];

char str[100];

GDALDataset  *simgFile, *ltimgFile; //*

double        adfGeoTransform[6]; //*

GDALAllRegister(); //*

printMessage("Reading input.");


if (_mkdir(parameters.outputDir) != 0)

{

	if (errno != EEXIST)

		errorSys("BDAS: Can't create the direcory", STOP);

}

if ((saFile=LDfopen(parameters.specAttrFile, 1))==NULL)

	  errorSys("Species attribute file not found.",STOP);

if ((luFile=LDfopen(parameters.landUnitFile, 1))==NULL)

	  errorSys("Landtype attribute file not found.",STOP);
//
//if ((ltMapFile=LDfopen(parameters.landUnitMapFile,2))==NULL) // landtype.gis
//
//	  errorSys("Landtype map file not found.",STOP);

if ((ltimgFile = (GDALDataset *)GDALOpen(parameters.landImgMapFile, GA_ReadOnly)) == NULL) //* landtype.img

		errorSys("landtype img map input file not found.", STOP);//*

//if ((siFile=LDfopen(parameters.siteInFile,2))==NULL) // specnaotest.gis
//
//	  errorSys("GIS map input file not found.",STOP);

if ((simgFile = (GDALDataset *)GDALOpen(parameters.siteImgFile, GA_ReadOnly)) == NULL) //*

		errorSys("species img map input file not found.", STOP);  //*

if (simgFile->GetGeoTransform(adfGeoTransform) == CE_None){ //*

	for (int i = 0; i < 6; i++){//*

		wAdfGeoTransform[i] = adfGeoTransform[i];//*
	}//*

}//*

parameters.pszSRS_WKT = simgFile->GetProjectionRef();

if ((rcFile=LDfopen(parameters.reclassInFile,1))==NULL) //This one has age list

	  errorSys("Map attribute input file not found.",STOP);

//if ((roFile=LDfopen(parameters.reclassOutFile,1))==NULL)
//
//	  errorSys("Map index file not found.",STOP);
//
//if ((ageFile=LDfopen(parameters.ageIndexFile,1))==NULL)
//
//	  errorSys("Species age index file not found.",STOP);

if ((bioMass=LDfopen(parameters.Biomassfile,1))==NULL)

	  errorSys("BioMassfile not found.",STOP);

speciesAttrs.read(saFile, parameters.cellSize );

//<Add By Qia on July 5 2009>

time_step.getSpecNum(speciesAttrs.number());//Add By Qia on July 5 2009

for(x=1;x<=speciesAttrs.number();x++)

{

 time_step.Setlongevity(x,speciesAttrs(x)->longevity);

}

//</Add By Qia on July 5 2009>



if ((gDLLMode & G_HARVEST) != 0)

{

//	#ifdef __HARVEST__

	numberOfSpecies = speciesAttrs.number();

//	#endif

}

landUnits.attach(&speciesAttrs);

landUnits.read(luFile);

sites.BiomassRead(bioMass);

SPECIES::attach(&speciesAttrs);



//LDfread((char*)dest,4,32,siFile);
//
//packType=dest[1]&0xFFFF;

#ifdef __UNIX__

ERDi4_c(&dest[4],nCols);

ERDi4_c(&dest[5],nRows);

#else

//nCols=dest[4];
//
//nRows=dest[5];

nCols = simgFile->GetRasterXSize(); //*

nRows = simgFile->GetRasterYSize(); //*

//assert((nCols1 == nCols) && (nRows1 = nRows)); //*
//
//if ((nCols1 != nCols) && (nRows1 != nRows))
//{
//
//	errorSys("Species img map size is wrong.", STOP);
//} //*



#endif

//sites.setHeader(dest);

sites.MaxDistofAllSpec=speciesAttrs.MaxDistanceofAllSpecs;

sites.MaxShadeTolerance=speciesAttrs.MaxShadeTolerance;

sites.dim(speciesAttrs.number(), nRows, nCols);//need to change Qia Oct 06 2008

//<Add By Qia on May 4 2010>

sites.Read70OutputOption(parameters.OutputOption70);

//</Add By Qia on May 4 2010>

//added by Wei Li 

char	b16or8;   //true: 16, false 8 bit



//if ((dest[1] & 0xff0000) == 0x020000)
//
//	b16or8 = 16;
//
//else if ((dest[1] & 0xff0000) == 0)
//
//	b16or8 = 8;
//
//else
//
//{
//
//	b16or8 = -1;
//
//	errorSys("Error: IO: Landtype map is niether 16 bit or 8 bit.", STOP);
//
//}



//add by Vera

*ppdp = new PDP (gDLLMode, sites.numColumns(), sites.numRows(), BDANo);



//SPECIES::attach(&speciesAttrs);



/* J.Yang side-effect of del. the composite rel.

sites.attach(&landUnits);

*/



#ifdef __UNIX__

if (packType==512)

	 inputBin16(rcFile, siFile, nRows, nCols); // need to change Qia Oct 06 2008

else

	 inputBin8(rcFile, siFile, nRows, nCols, b16or8); // need to change Qia Oct 06 2008

#else 

//inputBin8(rcFile, siFile, simgFile,nRows, nCols, b16or8); // need to change Qia Oct 06 2008

inputImgSpec(rcFile, simgFile, nRows, nCols);

#endif

//inputLandtypeMap8(ltMapFile, ltimgFile, nCols, nRows, *ppdp); // need to change Qia Oct 06 2008

inputLandtypeImg(ltimgFile, nCols, nRows, *ppdp);

//while (!LDeof(roFile))
//
//	fscanc(roFile,"%s",reMethods[reclassMethods++]);
//
//while (!LDeof(ageFile))
//
//	LDfscanf(ageFile,"%s",ageMaps[numAgeMaps++]);



if ((gDLLMode & G_HARVEST) != 0)

{

	

	HarvestPassInit(&sites, numberOfSpecies, parameters.outputDir, parameters.strHarvestInitName, *ppdp);


}



LDfclose(saFile);

//LDfclose(ltMapFile);

GDALClose((GDALDatasetH)simgFile); //*

LDfclose(luFile);

//LDfclose(siFile);

GDALClose((GDALDatasetH)ltimgFile); //*

LDfclose(rcFile);

//LDfclose(roFile);
//
//LDfclose(ageFile);

LDfclose(bioMass);

/*if ((gDLLMode & G_HARVEST) != 0)

{

	if (parameters.harvest)

		LDfclose(haFile);

}*/

//if ((freqOfOutput=fopen(parameters.freq_out_put,"r"))!=NULL)

if ((freqOfOutput=LDfopen(parameters.freq_out_put,1))!=NULL)

	{

	 int c=0;

	 char temp[80];

	 while (!LDeof(freqOfOutput))

	  {

		fscanc(freqOfOutput, "%s",temp);

		freq[c]=atoi(temp);

      //if((freq[c]>sites.TimeStep)&&(freq[c]%sites.TimeStep))

      //	errorSys("Illegal frequency value encountered.",STOP); //Nim: changed spelling

		if (freq[c] > parameters.numberOfIterations) 

			errorSys("frequency value cannot be larger than number of iterations", STOP);

		if (freq[c] < 0)

			errorSys("frequency value cannot be smaller than zero", STOP);

		c++;

	  }

	 printf("\n");

    if(freq[0]<=1)

    {
		freq[0] = 1;

		printf("%s%i%s\n", "Species maps output every------->", freq[0] * sites.TimeStep, " years.");
		fflush(stdout);

		printf("%s%i%s\n", "Age maps output every----------->", freq[0] * sites.TimeStep, " years.");
	  fflush(stdout);

    }

    else

    {

		printf("%s%i%s\n", "Species map outputs for year---->", freq[0] * sites.TimeStep, ".");
		fflush(stdout);

		printf("%s%i%s\n", "Age map outputs for year-------->", freq[0] * sites.TimeStep, ".");
		fflush(stdout);

    }

	if (freq[4] <= 1){

		freq[4] = 1;

		printf("%s%i%s\n", "Age group maps output every----->", freq[4] * sites.TimeStep, " years.");
		fflush(stdout);
	}

	else{

		printf("%s%i%s\n", "Age group map outputs for year-->", freq[4] * sites.TimeStep, ".");
		fflush(stdout);
	}
    printf("\n");

	 LDfclose(freqOfOutput);

	}

  else

	{

	 freq[0]=1; freq[1]=1; freq[2]=1; freq[3]=1; freq[4]=1;



if ((gDLLMode & G_HARVEST) != 0)

{

//#ifdef __HARVEST__

    freq[5]=1;

//#endif

}

	 printf("file <FREQ_OUT.PUT> not found\n");
	 fflush(stdout);

	 printf("creating file\n");
	 fflush(stdout);

	 printf("frequency of output unknown assuming every iteration\n");
	 fflush(stdout);

	 if ((freqOfOutput=LDfopen("freq_out.put",3))!=NULL)

		{

		 fprintf(freqOfOutput,"#This file establishes the number of years for output for reclass methods#\n");

		 fprintf(freqOfOutput,"#fire, wind, timber, and age class. A one (1) in any field will produce maps#\n");

		 fprintf(freqOfOutput,"#every iteration#\n");

		 fprintf(freqOfOutput,"#output maps for reclass#  2\n");

		 fprintf(freqOfOutput,"#output maps for fire# 1\n");

		 fprintf(freqOfOutput,"#output maps for wind# 1\n");

		 fprintf(freqOfOutput,"#output maps for timber# 1\n");

		 fprintf(freqOfOutput,"#output maps for age class# 2\n");

if ((gDLLMode & G_HARVEST) != 0)

{

//#ifdef __HARVEST__

//Nim:??

		 fprintf(freqOfOutput,"#output maps for harvest# 1\n");

//#endif		 

}

		 LDfclose(freqOfOutput);

		}



	}



//if ((palleteFile=LDfopen(parameters.default_plt,1))!=NULL)
//
//	{
//
//	 for (colNum=0;colNum<=15;colNum++) //Nim: changed int colNum to colNum
//
//		 fscanf(palleteFile,"%d %d %d", &red[colNum], &green[colNum], &blue[colNum]);
//
//	 for (colNum=0;colNum<=15;colNum++) //Nim: changed int colNum to colNum
//
//		 fscanf(palleteFile,"%d %d %d", &red2[colNum], &green2[colNum], &blue2[colNum]);
//
//	 for (colNum=0;colNum<=15;colNum++) //Nim: changed int colNum to colNum
//
//		 fscanf(palleteFile,"%d %d %d", &red3[colNum], &green3[colNum], &blue3[colNum]);
//
//	 for (colNum=0;colNum<=15;colNum++) //Nim: changed int colNum to colNum
//
//		 fscanf(palleteFile,"%d %d %d", &red4[colNum], &green4[colNum], &blue4[colNum]);
//
//	 fclose(palleteFile);
//
//	}
//
//	else
//
//	 {
//
//	  printf("file <DEFAULT.PLT> not found ....  Continuing\n");
//	  fflush(stdout);
//
//	 }



	if ((gDLLMode & G_WIND) != 0)

	//	pwind->initColors(red3, green3, blue3);

//fire.initColors(red4, green4, blue4);



//Set age colors to a spectrum.

for (i=2;i<16;i++)

	{

	 HSV_to_RGB((float)(i-2)/(float)14.0*(float)360.0,1.0,1.0,red2[i],green2[i],blue2[i]);

	}



//Write landtype map

MAP8 m(sites.getHeader());


luReclass(m); // need to change Qia Oct 06 2008



sprintf(str,"%s/lu",parameters.outputDir);




m.setCellSize(parameters.cellSize);



m.write(str, red, green, blue, wAdfGeoTransform);






}



void help()

//This will print the landis parameter file format on CRT.

{

printMessage("-------------------------LANDIS PARAMETER INPUT FILE--------------------------");

printMessage("Species Attribute File   #Species vital attribute file#");

printMessage("Landtype Attribute File  #Attributes of each landtype class#");

printMessage("Landtype Map File        #Input map of landtype#");

printMessage("Species Map File         #Input map of species and their age classes#");

printMessage("Map Attribute File       #Attributes of each map elements#");

printMessage("Maps Indexes File        #Species name indexes for map output#");

printMessage("Age Index File           #Species name indexes for age map output#");

printMessage("Output Directory         #Path for Landis output#");

printMessage("Disturbance File         #Disturbance Input File#");

printMessage("default.plt              #Required in the parameter file directory#");

printMessage("freq_out.put             #Setting for alternative output#");

printMessage("Iteration Number         #Number of iterations of 10 year step#");

printMessage("Random Number Seed       #0: real time seed, others: fixed seed#");

printMessage("Cell Size                #Cell size in meters#");

printMessage("Seed Dispersal Method    #The name of the seed dispersal routine#");

printMessage("Wind Switch              #0-no, 1-standard, 2-mean, 3-strong, 4-light#");

printMessage("Fire Switch              #0-no, 1-standard, 2-mean, 3-strong, 4-light#");

printMessage("Harvesting Switch        #0-harvesting off, 1-harvesting on#");

if ((gDLLMode & G_HARVEST) != 0)

{

//#ifdef __HARVEST__

printMessage("Harvest Event Switch     #0-harvesting module off, 1-harvesting moduel on#");

printMessage("Stand Adjacency Flag     #0-off, 1-on#");

printMessage("n                        #decade span to consider an adjacent stand recently harvested#");

printMessage("p                        #Proportion of cells cut in the last n decades is at least p#");

printMessage("Harvest Event File       #User defined harvest scenarios#");

printMessage("Stand Map                #Stand identifier map#");

printMessage("Management Area Map      #Management area identifier map#");

printMessage("Stand Log File           #Harvest log by stands#");

printMessage("Management Area Log File #Harvest log by management areas#");

//#endif

}

}



void argHelp()

//This will print the valid argument list on CRT

{

printMessage("LANDIS Version Pro 7.0 ");

printMessage("University of Missouri--Columbia ");

printMessage("(C) Copyright 2000-2009");

printMessage(" ");

printMessage("Usage: LANDIS [-argument [...]] <input file> ");

printMessage(" ");

printMessage("       argument:");

printMessage("       -e: the years environmental change interpreted");

printMessage("       -h: this help menu");

printMessage("       -p: input file help");

printMessage("       -r: the year for reclassification");

}



/******************************************************

 added by Wei Li April 1, 2004

Name: OutputScenario

Description: Log file for main parameters 

******************************************************/

void  OutputScenario()

{



	printf("Output Landis Scenario.txt....\n\n");

	char	strScenario[2000];

	sprintf(strScenario,"%s/%s", parameters.outputDir, "Scenario.txt");

	FILE* pfScenario = fopen(strScenario, "w");

	fprintf(pfScenario, "Landis Scenario.txt\n\n");

	fprintf(pfScenario, "Landis version:		Pro 1.0\n");

	fprintf(pfScenario, "Output dir:		%s\n", parameters.outputDir);

	fprintf(pfScenario, "specAttrFile:		%s\\%s\n", parameters.outputDir, parameters.specAttrFile);

	fprintf(pfScenario, "landUnitFile:		%s\\%s\n", parameters.outputDir, parameters.landUnitFile);

	//fprintf(pfScenario, "landUnitMapFile:	%s\\%s\n", parameters.outputDir, parameters.landUnitMapFile);

	fprintf(pfScenario, "siteInFile:		%s\\%s\n", parameters.outputDir, parameters.siteInFile);



	fprintf(pfScenario, "\nMAIN PARAMETERS:----------------------------------------\n");



	if (parameters.randSeed)

		fprintf(pfScenario, "Random:			repeatable (1)\n");

	else

		fprintf(pfScenario, "Random:			NOT repeatable (0)\n");

	fprintf(pfScenario, "numberOfIterations:	%d\n", parameters.numberOfIterations);

	fprintf(pfScenario, "Map size:		Row: %d x Col: %d\n", sites.numRows(), sites.numColumns());



	fprintf(pfScenario, "\n\nDLLs----------------------------------------\n");

	if (gDLLMode & G_BDA)

		fprintf(pfScenario, "BDA ...............is turned on\n");

	if (gDLLMode & G_WIND)

		fprintf(pfScenario, "Wind ..............is turned on \n");

	if (gDLLMode & G_HARVEST)

		fprintf(pfScenario, "Harvest ...........is turned on \n");

	if (gDLLMode & G_FUEL)

		fprintf(pfScenario, "Fuel ..............is turned on \n");

	if (gDLLMode & G_FUELMANAGEMENT)

		fprintf(pfScenario, "Fuel management....is turned on \n");

	if (gDLLMode & G_FIRE)

		fprintf(pfScenario, "Fire ..............is turned on \n");

	fprintf(pfScenario, "\n");



	if (!(gDLLMode & G_BDA))

		fprintf(pfScenario, "BDA ....................  off\n");

	if (!(gDLLMode & G_WIND))

		fprintf(pfScenario, "Wind .................... off \n");

	if (!(gDLLMode & G_HARVEST))

		fprintf(pfScenario, "Harvest ..................off \n");

	if (!(gDLLMode & G_FUEL))

		fprintf(pfScenario, "Fuel .................... off\n");

	if (!(gDLLMode & G_FUELMANAGEMENT))

		fprintf(pfScenario, "Fuel management ..........off \n");

	if (!(gDLLMode & G_FIRE))

		fprintf(pfScenario, "Fire .................... off\n");





	fclose(pfScenario);

}

