#include <stdio.h>

#include <math.h>

#include <errno.h>

#include <direct.h>



//<Add By Qia on Nov 4 2008>

#include <string.h>

//</Add By Qia on Nov 4 2008>

#include "point.h"

#include "map8.h"

#include "site.h"

//#include "landis.h"

#include "Stand.h"

#include "StandIterator.h"

#include "SiteHarvester.h"

#include "HarvestEvent.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#include "system1.h"

#include "error.h"

#include <iostream> //*

#include <cstdio> //*

#include <stdio.h> //*

#include <stdlib.h>//*

#include "gdal_priv.h"//*

#include "cpl_conv.h" // for CPLMalloc() //*

#include "cpl_string.h"//*

#include "ogr_spatialref.h"//*





static int HEventsmode = 0;

//modified by Vera Nov. 11, 2003

void HarvestPass(SITES* psi, SPECIESATTRS*	psa)

{

	pspeciesAttrs = psa;

}



void HarvestPassCurrentDecade(int cd)

{

	currentDecade = cd;

}



void outputFileheader(FILE *fp);



//void HarvestPassInit(SITES* psi, char* strstandMapFile, char* strmgtAreaMapFile, FILE* haFile, int isp)  //add by Vera

void HarvestPassInit(SITES* psi, int isp, char* stroutputdir, char* strHarvestInitFile, PDP* pdp)  //add by Vera

{

//	char str[100];



	char*	harvestFile;

	//char*	strstandMapFile;      //Stand identifier map file name.

	char*   strstandImgMapFile;   //Stand identifer .img map file name

	//char*	strmgtAreaMapFile;    //Management area map file name.

	char*	strmgtAreaImgMapFile; // Management area .img map file name.

	char*	strharvestOutputFile1;

	char*	strharvestOutputFile2;

	char	outputdir[200];		  //added by Wei Li, April 26, 2004



	sprintf(outputdir, "%s/%s", stroutputdir, "Harvest");

	if (_mkdir(outputdir) != 0)

	{

		if (errno != EEXIST)

			errorSys("Harvest: Can't create the direcory", STOP);

	}





	int		timber;

    int		harvest;           //Turn harvest events on/off.



	FILE*	haFile;





	harvestFile=new char[FNSIZE];

	//strstandMapFile=new char[FNSIZE];

	strstandImgMapFile = new char[FNSIZE];

	//strmgtAreaMapFile=new char[FNSIZE];

	strmgtAreaImgMapFile = new char[FNSIZE];

	strharvestOutputFile1 = new char[FNSIZE];

	strharvestOutputFile2 = new char[FNSIZE];


	pCoresites = psi;

	giRow = pCoresites->numRows();

	giCol = pCoresites->numColumns();



	m_pPDP = pdp;



	numberOfSpecies = isp;



	FILE* pfHarvest;



	if ((pfHarvest=LDfopen(strHarvestInitFile,1))==NULL)

		errorSys("Harvest event file not found.",STOP);

	

	if (fscanc(pfHarvest,"%d",&timber)!=1)

		errorSys("Error reading in timber flag from parameter file.",STOP);

	if (fscanc(pfHarvest,"%d",&harvest)!=1)

		errorSys("Error reading in harvest event flag from parameter file.",STOP);

	if (harvest!=0) 

	{

		if (fscanc(pfHarvest,"%d",&iParamstandAdjacencyFlag)!=1)

			 errorSys("Error reading in stand adjacency flag from parameter file.",STOP);

		if (fscanc(pfHarvest,"%d",&iParamharvestDecadeSpan)!=1)	//iParamharvestDecadeSpan

			 errorSys("Error reading in harvest decade span from parameter file.",STOP);

			/*iParamharvestDecadeSpan=iParamharvestDecadeSpan/pCoresites->TimeStep_Harvest;//Bu, Rencang May 21 2009

			if(iParamharvestDecadeSpan<pCoresites->TimeStep_Harvest)

					iParamharvestDecadeSpan=1;	*/	

		if (fscanc(pfHarvest,"%f",&fParamharvestThreshold)!=1) 

			 errorSys("Error reading in harvest threshold from parameter file.",STOP);



		if (fscanc(pfHarvest,"%s",harvestFile)!=1)

			 errorSys("Error reading in harvestFile from parameter file.",STOP);

		/*if (fscanc(pfHarvest,"%s",strstandMapFile)!=1)

			 errorSys("Error reading in standMapFile from parameter file.",STOP);*/

		if (fscanc(pfHarvest, "%s", strstandImgMapFile) != 1)//standmap.img

				errorSys("Error reading in standMapFile .img from parameter file.", STOP);

	/*	if (fscanc(pfHarvest,"%s",strmgtAreaMapFile)!=1)

			 errorSys("Error reading in mgtAreaMapFile from parameter file.",STOP);*/

	    if (fscanc(pfHarvest, "%s", strmgtAreaImgMapFile) != 1)//managearea.img

				errorSys("Error reading in mgtAreaMapFile .img from parameter file.", STOP);


		if (fscanc(pfHarvest,"%s",strharvestOutputFile1)!=1)

			 errorSys("Error reading in harvestOutputFile1 from parameter file.",STOP);

		if (fscanc(pfHarvest,"%s",strharvestOutputFile2)!=1)

			 errorSys("Error reading in harvestOutputFile2 from parameter file.",STOP);

	}



	LDfclose(pfHarvest);



	if ((haFile=LDfopen(harvestFile,1))==NULL)

		errorSys("Harvest event file not found.",STOP);

	

	printf("Build visitation Map\n");
	fflush(stdout);

	visitationMap.dim(giRow, giCol);

    visitationMap.fill(0);

	//<Add By Qia on Nov 4 2008>

	int filenamelength;

	char fileextensive[10];

	//for(filenamelength=0;filenamelength<FNSIZE;filenamelength++)

	//	{

	//		if(strstandMapFile[filenamelength])

	//			{

	//			}

	//		else

	//			break;

	//	}

	//filenamelength=strlen(strstandMapFile);

	

	//memcpy(fileextensive,&strstandMapFile[filenamelength-5],4);

	//fileextensive[0]=strstandMapFile[filenamelength-4];

	//fileextensive[1]=strstandMapFile[filenamelength-3];

	//fileextensive[2]=strstandMapFile[filenamelength-2];

	//fileextensive[3]=strstandMapFile[filenamelength-1];

	//fileextensive[4]='\0';

	//

	//if(strcmp(fileextensive,".asc")==0){

	//	

	////</Add By Qia on Nov 4 2008>

	//	//standMap.readtxt(strstandMapFile); 
	//	standMap.readtxt(strstandMapFile, giRow, giCol);

	//	}

	//else{

	//		

	//		//standMap.read(strstandMapFile);
	//	standMap.read(strstandMapFile, giRow, giCol);

		standMap.readImg(strstandImgMapFile, giRow, giCol);

		//}



	//managementAreaMap.read(strmgtAreaMapFile);
	//managementAreaMap.read(strmgtAreaMapFile, giRow, giCol);
	
	managementAreaMap.readImg(strmgtAreaImgMapFile, giRow, giCol);

//    stands.construct(); //modified by Vera

//	pstands = Stands;

	pstands = new STANDS();



	

	pstands->construct(); 


    managementAreas.construct();


    HEventsmode = harvestEvents.read(haFile);

	



	//<Add By Qia on Nov 3 2008>

	

    managementAreaMap.freeMAPdata();

	

	//</Add By Qia on Nov 3 2008>



	

	pHarvestsites = new HARVESTSites(giRow, giCol);

	

	char str[100];



	sprintf(str,"%s/%s",outputdir, strharvestOutputFile1);

	if ((harvestOutputFile1 = LDfopen(str, 3)) == 0)  //write, modified by Vera

		errorSys("Error opening stand harvest output file.",STOP);

	sprintf(str,"%s/%s",outputdir, strharvestOutputFile2);

	if ((harvestOutputFile2 = LDfopen(str, 3)) == 0)

		errorSys("Error opening management area harvest output file.",STOP);

	

	LDfclose(haFile);

}



void   HarvestprocessEvents(int itr)

{

	harvestEvents.processEvents(itr);

}





int inBounds(int r, int c)

{

    if (r >= 1 && r <= giRow && c >= 1 && c <= giCol)

        return 1;

    else

        return 0;

}



float gasdev()

{

	static int iset=0;

	static float gset;

	float fac,rsq,v1,v2;



	if  (iset == 0) {

		do {

			v1=(float)2.0*frand()-(float)1.0;

			v2=(float)2.0*frand()-(float)1.0;

			rsq=v1*v1+v2*v2;

		} while (rsq >= 1.0 || rsq == 0.0);

		fac=(float)sqrt((float)-2.0*log(rsq)/rsq);

		gset=v1*fac;

		iset=1;

		return v2*fac;

	} else {

		iset=0;

		return gset;

	}

}



float gasdev(float mean, float sd){

    float gset;

    gset = gasdev()*sd + mean;

    return gset;

}



void setUpdateFlags(int r, int c) {

    int sid, mid, tempMid=0;

//    sites(r,c)->setUpdateFlag(); //modified by Vera

	pHarvestsites->BefStChg(r,c); //Add By Qia on Nov 07 2008

	(*pHarvestsites)(r,c)->setUpdateFlag();

	pHarvestsites->AftStChg(r,c); //Add By Qia on Nov 07 2008

//    if ((sid = standMap(r,c)) > 0) stands(sid)->setUpdateFlag();  //modified by Vera

    if ((sid = standMap.getvalue32out(r,c)) > 0) //changed By Qia on Nov 4 2008

	//<Add By Qia on Nov 3 2008>

	{ (*pstands)(sid)->setUpdateFlag();

	

	

	tempMid=(*pstands)(sid)->getManagementAreaId();}

	

	

	if (sid > 0 && tempMid>0) managementAreas(tempMid)->setUpdateFlag(); 

	//</Add By Qia on Nov 3 2008>

	//<Landis 4.0 changed by Qia on Nov 3 2008>

    //if ((mid = managementAreaMap(r,c)) > 0) managementAreas(mid)->setUpdateFlag(); 

	//</Landis 4.0 changed by Qia on Nov 3 2008>

	

}



int getRandomHarvestablePoint(Stand* theStand, LDPOINT& thePoint) {

    LDPOINT pt;

    int found;



    for (int i=0; i<100; i++) {

        pt = theStand->getRandomPoint();

        found = canBeHarvested(pt);

        if (found) break;

    }



    if (!found) {

        for (StandIterator it(*theStand); it.moreSites(); it.gotoNextSite()) {

            pt = it.getCurrentSite();

            found = canBeHarvested(pt);

            if (found) break;

        }

    }



    thePoint = pt;

    return found;

}





//modified by Vera

int canBeHarvested(LDPOINT& thePoint) {

//    SITE* site = sites(thePoint.y, thePoint.x); modified by Vera

//	SITE* site = (*pCoresites)(thePoint.y, thePoint.x);



//  return site->canBeHarvested(); modified by Vera, Nov. 10, 2003

	//begin add by Vera

	return (*pHarvestsites)(thePoint.y, thePoint.x)->canBeHarvested(thePoint.y, thePoint.x);

	//end add by Vera



}

void output_harvest_Dec_Type(int itr, char str_htyp[200], char str_dec[200]){

	// Harvest type map

	FILE *fp;

	int i,j;

	int temp;

	//char str[200];

	//createHarvestTypeMap(m);

	

	if ((fp = LDfopen(str_htyp, 3)) == NULL)

		errorSys("can not open output file 1",STOP);

	outputFileheader(fp);

	for(i=pCoresites->numRows();i>0;i--)

		{

		//printf("\r%3d%%",100*i/sites.numRows());

		for(j=1;j<=pCoresites->numColumns();j++)

			{	if ((*pHarvestsites)(i,j)->getHarvestDecade() == currentDecade)

					  temp = (*pHarvestsites)(i,j)->getHarvestType();

				 else

					  temp =  0;

				fprintf(fp,"%d ",temp);									

			}

		}

	fclose(fp);

		

		// Last harvest decade map

		//createHarvestDecadeMap(m);

	

	if ((fp = LDfopen(str_dec, 3)) == NULL)

		errorSys("can not open output file 1",STOP);

	outputFileheader(fp);

	for(i=pCoresites->numRows();i>0;i--)

		{

		//printf("\r%3d%%",100*i/sites.numRows());

		for(j=1;j<=pCoresites->numColumns();j++)

			{	

				temp =  (*pHarvestsites)(i,j)->getHarvestDecade();

				fprintf(fp,"%d ",temp);									

			}

		}

	fclose(fp);

	return ;

}


void output_harvest_Dec_Type(int itr, char str_htyp[200], char str_htyp1[200], char str_dec[200], char str_dec1[200]){

	// Harvest type map

	FILE *fp;

	int i, j;

	int temp;


	const char *pszFormat = "HFA";//*

	GDALDriver *poDriver;//*

	char **papszMetadata;//*

	poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);//*

	if (poDriver == NULL)//*
		exit(1);

	papszMetadata = poDriver->GetMetadata();//*

	GDALDataset *poDstDS;//*

	GDALRasterBand *outPoBand; //*

	float cellsize = *(((float*)pCoresites->getHeader()) + 30);

	double wAdfGeoTransform[6] = { 0.00, cellsize, 0.00, 28350.00, 0.00, -cellsize };//*

	char **papszOptions = NULL;//*

	float *pafScanline;//*

	unsigned int *pintScanline;

	char *pszSRS_WKT = NULL;//*

	OGRSpatialReference oSRS;//*

	oSRS.SetUTM(11, TRUE);//*

	oSRS.SetWellKnownGeogCS("HEAD74");//*

	oSRS.exportToWkt(&pszSRS_WKT);//*

	CPLFree(pszSRS_WKT);

	pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (pCoresites->numRows()*pCoresites->numColumns()));//*

	poDstDS = poDriver->Create(str_htyp1, pCoresites->numColumns(), pCoresites->numRows(), 1, GDT_UInt32, papszOptions);//*

	if (poDstDS == NULL)

		errorSys("Img file not be created.", STOP);//*

	outPoBand = poDstDS->GetRasterBand(1);//*

	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

	for (i = pCoresites->numRows(); i>0; i--)

	{

		for (j = 1; j <= pCoresites->numColumns(); j++)

		{
			if ((*pHarvestsites)(i, j)->getHarvestDecade() == currentDecade)

				temp = (*pHarvestsites)(i, j)->getHarvestType();

			else

				temp = 0;

			//fprintf(fp,"%d ",temp);

			*(pintScanline + (pCoresites->numRows() - i)*pCoresites->numColumns() + j - 1) = temp;//*

		}

	}

	outPoBand->RasterIO(GF_Write, 0, 0, pCoresites->numColumns(), pCoresites->numRows(), pintScanline, pCoresites->numColumns(), pCoresites->numRows(), GDT_UInt32, 0, 0);//*

	if (poDstDS != NULL)
		GDALClose((GDALDatasetH)poDstDS);//*

	CPLFree(pintScanline);

	pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (pCoresites->numRows()*pCoresites->numColumns()));//*

	poDstDS = poDriver->Create(str_dec1, pCoresites->numColumns(), pCoresites->numRows(), 1, GDT_UInt32, papszOptions);//*

	if (poDstDS == NULL)

		errorSys("Img file not be created.", STOP);//*

	outPoBand = poDstDS->GetRasterBand(1);//*

	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

	for (i = pCoresites->numRows(); i>0; i--)

	{

		for (j = 1; j <= pCoresites->numColumns(); j++)

		{

			temp = (*pHarvestsites)(i, j)->getHarvestDecade();

			*(pintScanline + (pCoresites->numRows() - i)*pCoresites->numColumns() + j - 1) = temp;//*

		}

	}

	outPoBand->RasterIO(GF_Write, 0, 0, pCoresites->numColumns(), pCoresites->numRows(), pintScanline, pCoresites->numColumns(), pCoresites->numRows(), GDT_UInt32, 0, 0);//*

	if (poDstDS != NULL)
		GDALClose((GDALDatasetH)poDstDS);//*

	CPLFree(pintScanline);

	return;

}

/*********************************************

Legend error modified by Vera, April 10, 2004 



**********************************************/

void createHarvestTypeMap(MAP8 &m) {

    char str[80];

    int i,j;

    int snr, snc;



	snr=pCoresites->numRows(); //sites access modifiled by Vera

    snc=pCoresites->numColumns();

    m.dim(snr,snc);

    for (i=1;i<=snr;i++) {

	    for (j=1;j<=snc;j++) {

//           if (sites(i,j)->getHarvestDecade() == currentDecade) modifiled by Vera

			if ((*pHarvestsites)(i,j)->getHarvestDecade() == currentDecade)

			      m(i,j) = (unsigned char) (*pHarvestsites)(i,j)->getHarvestType();

		     else

			      m(i,j) = (unsigned char) 0;

		 }

    }

    sprintf(str,"Harvest events for year %d.", currentDecade*pCoresites->TimeStep_Harvest);

    m.rename(str);



	for (j=0; j<maxLeg; j++)	m.assignLeg(j,"");  //added by Wei Li, April 1, 2004 //Changed By Qia on Feb 04 2009



	for (i = 1; i <= harvestEvents.LegendLabeNo; i++)

		m.assignLeg(i, (char*)harvestEvents.LegendLabe[i]);



/*

    m.assignLeg(0,"None");

    m.assignLeg(EVENT_ONE_PASS_STAND_FILLING_REGIME,"One pass filling");

    m.assignLeg(EVENT_PERIODIC_STAND_FILLING_REGIME,"Periodic filling");

    m.assignLeg(EVENT_TWO_PASS_STAND_FILLING_REGIME,"Two pass filling");

    m.assignLeg(EVENT_ONE_PASS_STAND_SPREADING_REGIME,"One pass spreading");

    m.assignLeg(EVENT_TWO_PASS_STAND_SPREADING_REGIME,"Two pass spreading");

    m.assignLeg(EVENT_GROUP_SELECTION_REGIME,"Group selection");

// 21-SEP-99 

    m.assignLeg(EVENT_PERIODIC_TWO_PASS_STAND_FILLING_REGIME,"Periodic two pass filling");

    m.assignLeg(EVENT_REPEATING_TWO_PASS_STAND_FILLING_REGIME,"Repeating two pass filling");

/// -- END -- 

*/



}



void createHarvestDecadeMap(MAP8 &m) {

    char str[80];

    int i,j;

    int snr, snc;



	/* Modified by Vera

    snr=sites.numRows();

    snc=sites.numColumns();

	*/

	snr=pCoresites->numRows();

    snc=pCoresites->numColumns();

    m.dim(snr,snc);

    for (i=1;i<=snr;i++) {

	    for (j=1;j<=snc;j++) {

  //         m(i,j) = (unsigned char) sites(i,j)->getHarvestDecade();  Modified by Vera

		   m(i,j) = (unsigned char) (*pHarvestsites)(i,j)->getHarvestDecade();

		 }

    }

    sprintf(str,"Last decade harvested for year %d.", currentDecade*pCoresites->TimeStep_Harvest);

    m.rename(str);



	//added by Vera

	for (j=0;j<maxLeg;j++)

		m.assignLeg(j,"");



 //   m.assignLeg(0,"None");

//	m.assignLeg(1,"Water");

//	m.assignLeg(2,"NonForest");

	for (i=1;i<maxLeg-2;i++)

	{

		sprintf(str,"%3d - %3d yr",(i-1)*pCoresites->TimeStep_Harvest+1,(i-1)*pCoresites->TimeStep_Harvest+pCoresites->TimeStep_Harvest);

		m.assignLeg(i,str);

	}

	sprintf(str,"     >%3d yr", (i-1)*pCoresites->TimeStep_Harvest);

	m.assignLeg(maxLeg-2,str);

	m.assignLeg(maxLeg-1,"NoSpecies");

	//end of added by Vera April, 1, 2004



}



void writeStandReport() {

//    IntArray sumCut(stands.number());		Modified by Vera

    IntArray sumCut(pstands->number());



    int i,j, snr, snc;

    static int firstTime = 1;



    if (firstTime) {

        LDfprintf(harvestOutputFile1, "decade\tmanagementArea\tstand\tnumSitesHarvested\n");

        firstTime = 0;

    }



 	/* Modified by Vera

    snr=sites.numRows();

    snc=sites.numColumns();

	*/

	snr=pCoresites->numRows();

    snc=pCoresites->numColumns();



    for (i=1;i<=snr;i++) {

	    for (j=1;j<=snc;j++) {

 //          if (sites(i,j)->getHarvestDecade() == currentDecade) Modified by Vera

			 if ((*pHarvestsites)(i,j)->getHarvestDecade() == currentDecade)

               sumCut[standMap.getvalue32out(i,j)]++;//change by Qia on Nov 4 2008

 		 }

    }



//  for (i = 1; i <= stands.number(); i++) {   Modified by Vera

    for (i = 1; i <= pstands->number(); i++) {



        if (sumCut[i] > 0)

//          fprintf(outfile, "%d\t%d\t%d\t%d\n", currentDecade, stands(i)->getManagementAreaId(), i, sumCut[i]);  Modified by Vera

			LDfprintf4(harvestOutputFile1, "%d\t%d\t%d\t%d\n", currentDecade, (*pstands)(i)->getManagementAreaId(), i, sumCut[i]);

    }

}



void dumpHarvestMap(int key) {

    MAP8 m;

    int snr, snc;

    int i, j, k;



    if (key == 1)

        printf("Harvest type map:\n");

    else

        printf("Harvest decade map:\n");

  	/* Modified by Vera

    snr=sites.numRows();

    snc=sites.numColumns();

	*/

	snr=pCoresites->numRows();

    snc=pCoresites->numColumns();



    m.dim(snr,snc);

    for (i=snr;i>=1;i--) {

        for (j=1;j<=snc;j++) {

            if (key == 1)

   //           k = sites(i,j)->getHarvestType(); Modified by Vera

				k = (*pHarvestsites)(i,j)->getHarvestType();

            else

   //           k = sites(i,j)->getHarvestDecade(); Modified by Vera

				k = (*pHarvestsites)(i,j)->getHarvestDecade();

            m(i,j)=(unsigned char) k;

        }

    }

 //   m.dump();

}



void CleanHarvest()

{

	if (harvestOutputFile1 != NULL)

		LDfclose(harvestOutputFile1);

	if (harvestOutputFile2 != NULL)

		LDfclose(harvestOutputFile2);



}

void outputFileheader(FILE *fp)

{

	fprintf(fp,"ncols  %d\n",pCoresites->numColumns());

	fprintf(fp,"nrows  %d\n",pCoresites->numRows());

	fprintf(fp,"xllcorner  %.f\n", pCoresites->xLLCorner-*(((float*)pCoresites->getHeader())+30)/2);

	fprintf(fp,"yllcorner  %.f\n",pCoresites->yLLCorner-*(((float*)pCoresites->getHeader())+30)*pCoresites->numRows()+*(((float*)pCoresites->getHeader())+30)/2);

	fprintf(fp,"cellsize  %.f\n",*(((float*)pCoresites->getHeader())+30));

	fprintf(fp,"NODATA_value  -9999\n");

	

}



void PutOutput_harvestBACut(char *fn){

	FILE *fpOutput;

	int i,j;

	if ((fpOutput = LDfopen(fn, 3)) == NULL)

		{

			errorSys("Can not open species index output file",STOP);

		}

	outputFileheader(fpOutput);

	for(i=pCoresites->numRows();i>0;i--){

		//printf("\r%3d%%",100*i/sites.numRows());

		for(j=1;j<=pCoresites->numColumns();j++){	

			fprintf(fpOutput,"%f ", pHarvestsites->GetValueHarvestBA(i,j));

		}

	}

	pHarvestsites->clearValueHarvestBA();

	fclose(fpOutput);

}

void PutOutput_harvestBACut(char *fn, char *fn1){

	FILE *fpOutput;

	int i, j;

	const char *pszFormat = "HFA";//*

	GDALDriver *poDriver;//*

	char **papszMetadata;//*

	poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);//*

	if (poDriver == NULL)//*
		exit(1);

	papszMetadata = poDriver->GetMetadata();//*

	GDALDataset *poDstDS;//*

	//GDALRasterBand  *poBand;//*

	GDALRasterBand *outPoBand; //*

	float cellsize = *(((float*)pCoresites->getHeader()) + 30);

	double wAdfGeoTransform[6] = { 0.00, cellsize, 0.00, 28350.00, 0.00, -cellsize };//*

	char **papszOptions = NULL;//*

	float *pafScanline;//*

	unsigned int *pintScanline;

	char *pszSRS_WKT = NULL;//*

	OGRSpatialReference oSRS;//*

	//poDstDS->SetGeoTransform(wAdfGeoTransform);

	oSRS.SetUTM(11, TRUE);//*

	oSRS.SetWellKnownGeogCS("HEAD74");//*

	oSRS.exportToWkt(&pszSRS_WKT);//*

	pafScanline = (float*)CPLMalloc(sizeof(float)* (pCoresites->numRows()*pCoresites->numColumns()));//*

	poDstDS = poDriver->Create(fn1, pCoresites->numColumns(), pCoresites->numRows(), 1, GDT_Float32, papszOptions);//*

	if (poDstDS == NULL)

		errorSys("Img file not be created.", STOP);//*

	outPoBand = poDstDS->GetRasterBand(1);//*

	poDstDS->SetGeoTransform(wAdfGeoTransform);//*


	for (i = pCoresites->numRows(); i>0; i--){

		for (j = 1; j <= pCoresites->numColumns(); j++){

			//fprintf(fpOutput,"%f ", pHarvestsites->GetValueHarvestBA(i,j));

			*(pafScanline + (pCoresites->numRows() - i)*pCoresites->numColumns() + j - 1) = pHarvestsites->GetValueHarvestBA(i, j);//* 

		}

	}

	pHarvestsites->clearValueHarvestBA();
	
	outPoBand->RasterIO(GF_Write, 0, 0, pCoresites->numColumns(), pCoresites->numRows(), pafScanline, pCoresites->numColumns(), pCoresites->numRows(), GDT_Float32, 0, 0);//*


	if (poDstDS != NULL)
		GDALClose((GDALDatasetH)poDstDS);//*

	CPLFree(pafScanline);

}


void PutOutput_harvestBACut_spec(char *fn,int spec){

	FILE *fpOutput;

	int i,j;

	if ((fpOutput = LDfopen(fn, 3)) == NULL)

		{

			errorSys("Can not open species index output file",STOP);

		}

	outputFileheader(fpOutput);

	for(i=pCoresites->numRows();i>0;i--){

		//printf("\r%3d%%",100*i/sites.numRows());

		for(j=1;j<=pCoresites->numColumns();j++){	

			fprintf(fpOutput,"%f ", pHarvestsites->GetValueHarvestBA_spec(i,j,spec));

		}

	}

	fclose(fpOutput);

}

void PutOutput_harvestBACut_spec(char *fn, char *fn1, int spec){

	FILE *fpOutput;

	int i, j;
	const char *pszFormat = "HFA";//*

	GDALDriver *poDriver;//*

	char **papszMetadata;//*

	poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);//*

	if (poDriver == NULL)//*
		exit(1);

	papszMetadata = poDriver->GetMetadata();//*

	GDALDataset *poDstDS;//*

	GDALRasterBand *outPoBand; //*

	float cellsize = *(((float*)pCoresites->getHeader()) + 30);

	double wAdfGeoTransform[6] = { 0.00, cellsize, 0.00, 28350.00, 0.00, -cellsize };//*

	char **papszOptions = NULL;//*

	float *pafScanline;//*

	unsigned int *pintScanline;

	char *pszSRS_WKT = NULL;//*

	OGRSpatialReference oSRS;//*

	oSRS.SetUTM(11, TRUE);//*

	oSRS.SetWellKnownGeogCS("HEAD74");//*

	oSRS.exportToWkt(&pszSRS_WKT);//*

	CPLFree(pszSRS_WKT); //*

	pafScanline = (float*)CPLMalloc(sizeof(float)* (pCoresites->numRows()*pCoresites->numColumns()));//*

	poDstDS = poDriver->Create(fn1, pCoresites->numColumns(), pCoresites->numRows(), 1, GDT_Float32, papszOptions);//*

	if (poDstDS == NULL)

		errorSys("Img file not be created.", STOP);//*

	outPoBand = poDstDS->GetRasterBand(1);//*

	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

	
	for (i = pCoresites->numRows(); i>0; i--){

		for (j = 1; j <= pCoresites->numColumns(); j++){

			//fprintf(fpOutput,"%f ", pHarvestsites->GetValueHarvestBA_spec(i,j,spec));

			*(pafScanline + (pCoresites->numRows() - i)*pCoresites->numColumns() + j - 1) = pHarvestsites->GetValueHarvestBA_spec(i, j, spec);//* 

		}

	}

	outPoBand->RasterIO(GF_Write, 0, 0, pCoresites->numColumns(), pCoresites->numRows(), pafScanline, pCoresites->numColumns(), pCoresites->numRows(), GDT_Float32, 0, 0);//*

	if (poDstDS != NULL)
		GDALClose((GDALDatasetH)poDstDS);//*

	CPLFree(pafScanline);


}