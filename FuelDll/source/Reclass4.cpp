// Reclass4.cpp: implementation of the Reclass4 class.

//

//////////////////////////////////////////////////////////////////////



#include "Reclass4.h"

//#include "landis.h"

#include "map8.h"

#include "error.h"

#include "system1.h"

#include <io.h>

#include <string.h>

#include <math.h>

#include "List.h"



#include "FuelGlobalVariables.h"





void FuelReclass(MAP8 &m, int flag, FILE * fueloutfile) {



	char str[256];

	long cellNum[10];	

	int i, j;

	int snr, snc;

//	snr=sites.numRows();

//	snc=sites.numColumns();

	snr=pfuelcoresites->numRows();

	snc=pfuelcoresites->numColumns();

	

	m.dim(snr,snc);

	if (flag)	sprintf(str,"Fuel quantity class representation");

	else	sprintf(str,"Fuel quality class representation");

	m.rename(str);

	m.assignLeg(0,"Water");

	m.assignLeg(1,"NonActive");

	m.assignLeg(2,"NonForest");

	m.assignLeg(3,"BACKGROUND");

	for (i=0;i<10;i++)	cellNum[i] = 0;

	for (j=4; j<maxLeg; j++)	m.assignLeg(j,"");



	for (j=4;j<=9;j++)

		m.assignLeg(j,"");

	for (i=4;i<=9;i++) {

		sprintf(str,"Class %1d",i-4);

		m.assignLeg(i,str);

	}

	unsigned char fuelLoad = 0;

	for (i=snr;i>=1;i--){

		for (j=1;j<=snc;j++) {

//			if (sites(i,j)->landUnit->lowland() || sites(i,j)->landUnit->water() || !parameters.fuel) {  //deleted parameters.fuel cause it is on anyway by Vera

			if (pfuelcoresites->locateLanduPt(i,j)->water()) {

				//Original landis4.0: (*pfuelcoresites)(i,j)->landUnit->water()

				//changed By Qia on Oct 13 2008

				m(i,j)=0;

				cellNum[0]++;

			}

			else if (pfuelcoresites->locateLanduPt(i,j)->lowland()) {

				//Original landis4.0: (*pfuelcoresites)(i,j)->landUnit->lowland ()

				//changed By Qia on Oct 13 2008

				m(i,j)=2;

				cellNum[2]++;

			}

			else if (pfuelcoresites->locateLanduPt(i,j)->active()) {

				//Original landis4.0: (*pfuelcoresites)(i,j)->landUnit->active ()

				//changed By Qia on Oct 13 2008

				if (strcmp(pfuelcoresites->locateLanduPt(i,j)->name,"BACKGROUND")==0 || strcmp(pfuelcoresites->locateLanduPt(i,j)->name,"background")==0) {

				//Original landis4.0:(*pfuelcoresites)(i,j)->landUnit->name

				//changed By Qia on Oct 13 2008

					m(i,j)=3;

					cellNum[3]++;

				}

				else {

					m(i,j)=4;

					//if (!flag)	      fuelLoad = fuelsites(i,j)->FFLoad;

					// Shang 03/04

					if (!flag)	      {fuelLoad = fuelsites.getFFLoad(i,j);

					

					}

					//else			  fuelLoad = fuelsites(i,j)->CFLoad;

					else			  fuelLoad = fuelsites.getCFLoad(i,j);

					

//					if (fuelLoad > 4) 

//						printf(" FF: %d\n", fuelLoad);

					

					if (fuelLoad>=0 && fuelLoad<=5)	{

						m(i,j)=fuelLoad+4;

						cellNum[fuelLoad+4]++;

					}

				}

			} 

			else {

				m(i,j)=1;

				cellNum[1]++;

			}



        }

    }

	//if(flag) fprintf(fueloutfile, "Coarse fuel");

	//else	 fprintf(fueloutfile, "Fine fuel");





	for(i=0;i<9;i++)		fprintf(fueloutfile, "%-8d    ",cellNum[i]);

	float aver;

	int totalNum = cellNum[4] + cellNum[5] + cellNum[6] + cellNum[7] + cellNum[8] + cellNum[9];

	int totalClass = cellNum[5] + cellNum[6]*2 + cellNum[7]*3 + cellNum[8]*4 + cellNum[9]*5;

	if (totalNum>0)	aver = (float)totalClass / (float)totalNum;

	fprintf(fueloutfile,"%-8.3f    ",aver);



//	fprintf(fueloutfile,"\n");	



}





void fireReclass(MAP8 &m1, MAP8 &m2, MAP8 &m3, FILE * fueloutfile, int itr) {



//int probilityFlag = 1, severityFlag = 1, riskFlag = 1;



char str[256];

long fpNum[10], fsNum[10], frNum[10];

int i, j;

int snr, snc;



int totalFPNum, totalFSNum, totalFRNum;

int totalFP, totalFS, totalFR;

float averFP, averFS, averFR;

	for(i=0; i<10; i++) {

		fpNum[i] = 0;

		fsNum[i] = 0;

		frNum[i] = 0;

	}

	snr=pfuelcoresites->numRows();  //changed by Vera

	snc=pfuelcoresites->numColumns();

	

	m1.dim(snr,snc);

	sprintf(str,"Fire probility class representation");

	m1.rename(str);

	m1.assignLeg(0,"Water");

	m1.assignLeg(1,"NonActive");

	m1.assignLeg(2,"NonForest");

	m1.assignLeg(3,"BACKGROUND");

	for (j=4; j<maxLeg; j++)	m1.assignLeg(j,"");//Changed By Qia on Feb 04 2009 to maxleg

	for (j=4;j<=9;j++)

		m1.assignLeg(j,"");

	for (i=4;i<=9;i++) {

		sprintf(str,"Class:%1d",i-4);

		m1.assignLeg(i,str);

    }



	m2.dim(snr,snc);

	sprintf(str,"Fire severity class representation");

	m2.rename(str);

	m2.assignLeg(0,"Water");

	m2.assignLeg(1,"NonActive");

	m2.assignLeg(2,"NonForest");

	m2.assignLeg(3,"BACKGROUND");

	for (j=4; j<maxLeg; j++)	m2.assignLeg(j,"");//Changed By Qia on Feb 04 2009 to maxleg

	for (j=4;j<=9;j++)

		m2.assignLeg(j,"");

	for (i=4;i<=9;i++) {

		sprintf(str,"Class:%1d",i-4);

		m2.assignLeg(i,str);

    }



	m3.dim(snr,snc);

	sprintf(str,"Fire risk class representation");

	m3.rename(str);

	m3.assignLeg(0,"Water");

	m3.assignLeg(1,"NonActive");

	m3.assignLeg(2,"NonForest");

	m3.assignLeg(3,"BACKGROUND");

	for (j=4; j<maxLeg; j++)	m3.assignLeg(j,"");//Changed By Qia on Feb 04 2009 to maxleg

	for (j=4;j<=9;j++)

		m3.assignLeg(j,"");

	for (i=4;i<=9;i++) {

		sprintf(str,"Class:%1d",i-4);

		m3.assignLeg(i,str);

    }



	int intensity = 0, probility = 0, risk = 0;

	int FFClass = 0, CFClass = 0;

	LANDUNIT *l= NULL;



  for (i=snr;i>=1;i--) {

    for (j=1;j<=snc;j++){

		 if (pfuelcoresites->locateLanduPt(i,j)->water()) {

			 //Original landis4.0: (*pfuelcoresites)(i,j)->landUnit->water()

			 //Changed By Qia on Oct 13 2008

			 m1(i,j) = 0;

			 m2(i,j) = 0;

			 m3(i,j) = 0;

			 fpNum[0] ++;

			 fsNum[0] ++;

			 frNum[0] ++;

		 }

		 else if (pfuelcoresites->locateLanduPt(i,j)->lowland()) {

			 //Original landis4.0: (*pfuelcoresites)(i,j)->landUnit->lowland()

			 //Changed By Qia on Oct 13 2008

			 m1(i,j) = 2;

			 m2(i,j) = 2;

			 m3(i,j) = 2;

			 fpNum[2] ++;

			 fsNum[2] ++;

			 frNum[2] ++;

		 }

		 else if (pfuelcoresites->locateLanduPt(i,j)->active() && strcmp(pfuelcoresites->locateLanduPt(i,j)->name,"BACKGROUND")==0 || strcmp(pfuelcoresites->locateLanduPt(i,j)->name,"background")==0)

			 //Original landis4.0: (*pfuelcoresites)(i,j)->landUnit->active() && strcmp((*pfuelcoresites)(i,j)->landUnit->name,"BACKGROUND")==0 || strcmp((*pfuelcoresites)(i,j)->landUnit->name,"background")==0

			 //Changed By Qia on Oct 13 2008

		 {

 			 m1(i,j) = 3;

			 m2(i,j) = 3;

			 m3(i,j) = 3;

			 fpNum[3] ++;

			 fsNum[3] ++;

			 frNum[3] ++;



		 }         

		 else if (pfuelcoresites->locateLanduPt(i,j)->active()) {

			 //Original landis4.0: (*pfuelcoresites)(i,j)->landUnit->active()

			 //Changed By Qia on Oct 13 2008

			 //severity = fuelsites(i,j)->fireSeverity;

			 // Shang 03/04

			 //severity = fuelsites(i,j)->fireIntensity;

			 intensity = fuelsites.getFireIntensityClass (i,j);

			 //probility = fuelsites(i,j)->fireProbility;

			 

			 probility = fuelsites.getFireProbabiltyClass (i,j);

			 //risk = fuelsites(i,j)->fireRisk;

			 risk = fuelsites.getFireRiskClass (i,j);



			 int FF = fuelsites.getFFLoad(i,j);

			 int CF = fuelsites.getCFLoad(i,j);

			 //printf("FF: %d  CF: %d  FI: %d\n",FF,CF, severity);

			 m1(i,j) = probility + 4;

			 m2(i,j) = intensity + 4;

			 m3(i,j) = risk + 4;

			 fpNum[probility+4] ++;

			 fsNum[intensity+4] ++;

			 frNum[risk+4] ++;

			 //int FF = fuelsites.getFFLoad(i,j);

			 //int CF = fuelsites.getCFLoad(i,j);

			 //printf("FF: %d  CF: %d  FI:  %d\n",FF, CF,  severity);

		 }

		 else {

			 m1(i,j) = 1;

			 m2(i,j) = 1;

			 m3(i,j) = 1;

			 fpNum[1] ++;

			 fsNum[1] ++;

			 frNum[1] ++;

		 }

	}

  }







	fprintf(fueloutfile,"%-4d  potenFireProbility  ", itr*pfuelcoresites->TimeStep_Fuel);

	for(i=0;i<10;i++)		fprintf(fueloutfile, "%-8d    ",fpNum[i]);

	totalFPNum = fpNum[4] + fpNum[5] + fpNum[6] + fpNum[7] + fpNum[8] + fpNum[9];

	totalFP = fpNum[5] + fpNum[6]*2 + fpNum[7]*3 + fpNum[8]*4 + fpNum[9]*5;

	averFP = (float)totalFP / (float)totalFPNum;

	fprintf(fueloutfile, "%-8.3f    ",averFP);



//	fprintf(fueloutfile,"\n");

	fprintf(fueloutfile,"%-4d  potenFireintensity  ", itr*pfuelcoresites->TimeStep_Fuel);

	for(i=0;i<10;i++)		fprintf(fueloutfile, "%-8d    ",fsNum[i]);

	totalFSNum = fsNum[4] + fsNum[5] + fsNum[6] + fsNum[7] + fsNum[8] + fsNum[9];

	totalFS = fsNum[5] + fsNum[6]*2 + fsNum[7]*3 + fsNum[8]*4 + fsNum[9]*5;

	averFS = (float)totalFS / (float)totalFSNum;

	fprintf(fueloutfile, "%-8.3f    ",averFS);



//	fprintf(fueloutfile,"\n");

	fprintf(fueloutfile,"%-4d  potenFireRisk       ", itr*pfuelcoresites->TimeStep_Fuel);

	for(i=0;i<10;i++)		fprintf(fueloutfile, "%-8d    ",frNum[i]);

	totalFRNum = frNum[4] + frNum[5] + frNum[6] + frNum[7] + frNum[8] + frNum[9];

	totalFR = frNum[5] + frNum[6]*2 + frNum[7]*3 + frNum[8]*4 + frNum[9]*5;

	averFR = (float)totalFR / (float)totalFRNum;

	fprintf(fueloutfile, "%-8.3f    ",averFR);

	fprintf(fueloutfile,"\n");

	





}



/*

void PotentialFireProbility() {



int i, j;

int snr, snc;

snr=pfuelcoresites->numRows();

snc=pfuelcoresites->numColumns();

double fireProbility = 0, fireINTERV = 0, siteProb = 0;

LANDUNIT *l= NULL;



for (i=snr;i>=1;i--) {

    for (j=1;j<=snc;j++){

		 if ((*pfuelcoresites)(i,j)->landUnit->active()) {

			// classify the fire probility

		    fireINTERV=(*pfuelcoresites)(i,j)->landUnit->fireInterval;

   		    siteProb=(*pfuelcoresites)(i,j)->landUnit->probCoef*(1.0/(double)fireINTERV)*

   					(exp(1.0/(double)fireINTERV));

			fireProbility = siteProb*(double)(*pfuelcoresites)(i,j)->lastFire/(double)fireINTERV;

			if (fireProbility>1)	fireProbility = 1;

		 }		 

		else  fireProbility = 0;

		// Shang 03/04

		//fuelsites(i,j)->potentialFireProbility = (float) fireProbility;

		fuelsites.setFireProbability ((float)fireProbility, i,j);

	}

  }

}



*/



int fireProbilityCategory() {

	printf("Begin calculate the criterions for potential fire probility categories \n");

	printf("This procedure may take long time than you anticipate, 30mins, 1 hour, 2 hours, or even longer \n");

	printf("which depends on the extension of your study area, and the speed of your computer \n");

	printf("To avoid this procedure, kill this running, set the real creteria for calculating potential fire probability in fuelrule.dat, and rerun the program. \n");

	char fireProbilityFileName[256];

	FILE *fireProbilityFile;



	sprintf(fireProbilityFileName,"%s/%s", fueloutputDir,"fp.txt");



	if ((fireProbilityFile=fopen(fireProbilityFileName,"w"))==NULL)

		errorSys("Can't open potential fire probility file for write. \n",STOP);



	List<float> itsFireProbList;

	int i, j;

	float fireProbility = 0;

	double fireINTERV = 0, siteProb = 0;

	LANDUNIT *l= NULL;

	int finish = 0;

	for (i=pfuelcoresites->numRows();i>=1;i--) {

		for (j=1;j<=pfuelcoresites->numColumns();j++) {

			if (pfuelcoresites->locateLanduPt(i,j)->active() && strcmp(pfuelcoresites->locateLanduPt(i,j)->name,"BACKGROUND")==0 || strcmp(pfuelcoresites->locateLanduPt(i,j)->name,"background")==0)

				//Original landis4.0: (*pfuelcoresites)(i,j)->landUnit->active() && strcmp((*pfuelcoresites)(i,j)->landUnit->name,"BACKGROUND")==0 || strcmp((*pfuelcoresites)(i,j)->landUnit->name,"background")==0

				//Changed By Qia on Oct 13 2008

			{}

			else if (pfuelcoresites->locateLanduPt(i,j)->active()) {

				//Original landis4.0: (*pfuelcoresites)(i,j)->landUnit->active()

				//Changed By Qia on Oct 13 2008

				// classify the fire probility

				/*

				fireINTERV=(*pfuelcoresites)(i,j)->landUnit->fireInterval;

   				siteProb=(*pfuelcoresites)(i,j)->landUnit->probCoef*(1.0/(double)fireINTERV)*

   					(exp(1.0/(double)fireINTERV));

				float randnum = frand();

				if (randnum>1 || randnum <0)	printf("Randnum num: %f  \n",randnum);

				//fireProbility = (float) (siteProb*(double)sites(i,j)->lastFire/(double)fireINTERV);

				fireProbility = (float) (siteProb*randnum);

				*/

				fireProbility = 1 - exp((float)-1*frand());

				itsFireProbList.append(fireProbility);

			}

		}

	}

	float temp;

	float *change;

	int length = itsFireProbList.length();

	ListIterator<float> it(itsFireProbList);

	if (length < 0)

		errorSys("List length <0 \n",STOP);

	change = new float[length];	

	for (; it.more(); it.advance()) {

		change[i] = it.current();

		i++;

	}

	for (int Stop=length-1; Stop>0; Stop--) {

		for (int Check = 0; Check < Stop; Check++) {

			// make a pass compare Origin fields of array elements

			if(change[Check] > change[Check+1]) {

				temp = change[Check];				// swap if in the

				change[Check] = change[Check+1];	// wrong order

				change[Check+1] = temp;

			}

		}

	}

	itsFireProbList.reset();

	//for(i=0; i<length; i++)		itsFireProbList.append(change[i]);

	printf("Reclassfy potential fire probility category\n");

	int number = 0;

	float criterion = 0;

	for(i=0;i<5;i++) {

		float temp = fuelrule.fireProbility[i];

		if (temp<0)

			errorSys("Error! fire probility inputs are wrong. check 'fuelrule.dat' \n",STOP);

		else if (temp>1)	temp = 1;

		int num = (int)(temp*length);

		for (;number<length-1;number++) {

			criterion = change[number];

			if(number>=num && criterion<change[number+1])

				break;

		}

		fuelrule.fireProbilityClass[i] = criterion;

		printf("There are %-6d of total %-6d active sites, their potential fire probility below category %d. The criterion is %8.6f.\n\n",

			number, length, i+1, criterion);

		fprintf(fireProbilityFile,"There are %-6d of total %-6d active sites, their potential fire probility below category %d. The criterion is %8.6f.\n\n",

			number, length, i+1, criterion);		

	}

	delete [] change;

	finish = length;

	fuelrule.fireProbReclass = finish;

	fclose (fireProbilityFile);

	return finish;

}



	

/*

int AscendOrderSort (List<float> list) {

	// Ascending-order implementation of the bubble sort algorithm

	//int length = list->length();

	float temp;

	float *change;

	int length = list.length();

	ListIterator<float> it(list);

	if (list.length() < 0)

		errorSys("List length <0 \n",STOP);



	change = new float[length];	

	int i = 0;

	for (; it.more(); it.advance()) {

		change[i] = it.current();

		i++;

	}

	for (int Stop=length-1; Stop>0; Stop--) {

		for (int Check = 0; Check < Stop; Check++) {

			// make a pass compare Origin fields of array elements

			if(change[Check] > change[Check+1]) {

				temp = change[Check];				// swap if in the

				change[Check] = change[Check+1];	//wrong order

				change[Check+1] = temp;

			}

		}

	}

	list.reset();

	for(i=0; i<length; i++)

		list.append(change[i]);

	delete [] change;

	return length;

}

*/

