#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include "system1.h"

#include "map8.h"

#include "specie.h"

#include "site.h"

#include "landis.h"

#include "reclass.h"

#include "error.h"



void luReclass(MAP8 &m)

//This will perform a reclassification based on the underlying map 

//land units.  It will perform the reclassification on the global 

//object sites and place the results in m.



{
	//cout << "start luReclass" << endl;

char b[32];

int snr, snc, lun;

int i, j, k; //Nim: added this line

snr=sites.numRows();

//cout << "sites.numRows()" << sites.numRows() << endl;

snc=sites.numColumns();

//cout << "sites.numColumns()" << sites.numColumns() << endl;

m.dim(snr,snc);

sprintf(b,"Landtype");

m.rename(b);

char *tempstr;

lun=landUnits.number();

//cout << "landUnits.number()" << landUnits.number() << endl;

//<Add By Qia on Jan 22 2009>

for(k=0;k<lun;k++){

	landUnits(k)->index=k;

}

//</Add By Qia on Jan 22 2009>


for (i=snr;i>=1;i--){ //Nim: changed int i to i

	for (j = 1; j <= snc; j++) //Nim: changed int j to j

	{

		/*tempstr=sites.locateLanduPt(i,j)->name;

		//Original landis4.0: tempstr=sites(i,j)->landUnit->name

		//Changed By Qia on Oct 13 2008

		printf("(%d,%d)",i,j);

		m(i,j)= -1; // Notice the return datatype for m(i,j) is unsigned char. J.Yang 04/16/2002

		for (k=0;k<lun;k++)

		{	printf("->%d..",k);

		if (strcmp(tempstr,landUnits(k)->name)==0)

		{

		m(i,j)=(unsigned char)k;

		break;

		}

		}

		if(m(i,j)==-1) errorSys("error in reclass the land unit map",STOP);*///Commented By Qia on Jan 22 2009



		//<Add By Qia on Jan 22 2009>
		m(i, j) = sites.locateLanduPt(i, j)->index;

	//	cout << m(i, j) << " ";

		//</Add By Qia on Jan 22 2009>

	}
//	cout << endl;

    }

//cout << "finsih 1" << endl;

if (lun<maxLeg){

	for (i=0;i<lun;i++)//temporary modify by Qia jan 26 2009 original i<lun    

	    m.assignLeg(i,landUnits(i)->name);  

}

else{

	for (i=0;i<maxLeg;i++)//temporary modify by Qia jan 26 2009 original i<lun    

    m.assignLeg(i,landUnits(i)->name);  

}

//cout << "finsih 2" << endl;



}



//<Add By Qia on Jan 26 2010>

void ageReclassYoungest(MAP8 &m)

{

	char str[200];

	int i, j;

	int snr, snc;

	snr=sites.numRows();

	snc=sites.numColumns();

	m.dim(snr,snc);

	sprintf(str,"Age class representation");

	m.rename(str);

	for (j=1;j<MapmaxValue;j++)

		m.assignLeg(j,"");

	

	//J.Yang hard coding changing itr*sites.TimeStep to itr

	for (i=1;i<MaxValueforLegend-4;i++)  //J.Yang maxLeg is defined as 256 in map8.h, therefore, maximum age cohorts it can output is 254 

	{

		sprintf(str,"%3d - %3d yr",(i-1)*sites.TimeStep+1,(i-1)*sites.TimeStep+sites.TimeStep);

		m.assignLeg(i,str);

	}

	sprintf(str,"	  >%3d yr", (i-1)*sites.TimeStep);

	/*m.assignLeg(0,"N/A");

	m.assignLeg(1,"Water");

	m.assignLeg(2,"NonForest");

	

	m.assignLeg(maxLeg-2,str);

	m.assignLeg(maxLeg-1,"NoSpecies");*/

//<Add By Qia on Jan 28 2009>

	m.assignLeg(0,"NoSpecies");

	m.assignLeg(MaxValueforLegend-1,"N/A");

	m.assignLeg(MaxValueforLegend-2,"Water");

	m.assignLeg(MaxValueforLegend-3,"NonForest");

	m.assignLeg(MaxValueforLegend-4,str);

	//<Add By Qia on Jan 28 2009>

	int mycnt = 0;

	int myage;

	for (i=snr;i>=1;i--)

	{

		for (j=1;j<=snc;j++)

		{

			if (sites.locateLanduPt(i,j)->active())

				//Original landis4.0: sites(i,j)->landUnit->active()

				//changed By Qia on Oct 13 2008

			{

				m(i,j)=0; 

				myage = MapmaxValue;

				SPECIE *s=sites(i,j)->first();				

				int temp;

				while (s!=NULL)

				{

					if ( (temp = s->youngest() ) < myage&& s->youngest()>0)

						myage = temp;					

					s=sites(i,j)->next();

				}

				if(myage == MapmaxValue){

					myage = 0;

					}

				else{

					myage = (int) myage/sites.TimeStep;

					}

				/*if (myage == 0)

				{

					m(i,j) = maxLeg - 1; //No Species present

				}

				else if( (myage) < (maxLeg -4))

				{

					m(i,j) = myage + 2; //map value = oldest age + 2

				}

				else

				{

					m(i,j) = maxLeg - 2; // oldest age >= 252

				}*///Commented By Qia on Jan 28 2009

				m(i,j)=myage;//changed By Qia on Jan 28 2009

				

			} 

			else if (sites.locateLanduPt(i,j)->lowland())

				//Original landis4.0: sites(i,j)->landUnit->lowland()

				//changed By Qia on Oct 13 2008

				m(i,j)=MaxValueforLegend-3;//changed By Qia on Jan 28 2009

			else if (sites.locateLanduPt(i,j)->water())

				//Original landis4.0: sites(i,j)->landUnit->water()

				//changed By Qia on Oct 13 2008

				m(i,j)=MaxValueforLegend-2;//changed By Qia on Jan 28 2009

			else

				m(i,j)=MaxValueforLegend-1;//changed By Qia on Jan 28 2009

		}

	}	

}



//</Add By Qia on Jan 26 2010>



void ageReclass(MAP8 &m)

//This will perform a reclassification based upon the oldest cohort upon

//a landis stand.  

{

	char str[200];

	int i, j;

	int snr, snc;

	snr=sites.numRows();

	snc=sites.numColumns();

	m.dim(snr,snc);

	sprintf(str,"Age class representation");

	m.rename(str);

	for (j=1;j<MapmaxValue;j++)

		m.assignLeg(j,"");

	

	//J.Yang hard coding changing itr*sites.TimeStep to itr

	for (i=1;i<MaxValueforLegend-4;i++)  //J.Yang maxLeg is defined as 256 in map8.h, therefore, maximum age cohorts it can output is 254 

	{

		sprintf(str,"%3d - %3d yr",(i-1)*sites.TimeStep+1,(i-1)*sites.TimeStep+sites.TimeStep);

		m.assignLeg(i,str);

	}

	sprintf(str,"     >%3d yr", (i-1)*sites.TimeStep);

	/*m.assignLeg(0,"N/A");

	m.assignLeg(1,"Water");

	m.assignLeg(2,"NonForest");

	

	m.assignLeg(maxLeg-2,str);

	m.assignLeg(maxLeg-1,"NoSpecies");*/

//<Add By Qia on Jan 28 2009>

	m.assignLeg(0,"NoSpecies");

	m.assignLeg(MaxValueforLegend-1,"N/A");

	m.assignLeg(MaxValueforLegend-2,"Water");

	m.assignLeg(MaxValueforLegend-3,"NonForest");

	m.assignLeg(MaxValueforLegend-4,str);

	//<Add By Qia on Jan 28 2009>

	int mycnt = 0;

	int myage;

	for (i=snr;i>=1;i--)

	{

		for (j=1;j<=snc;j++)

        {

			if (sites.locateLanduPt(i,j)->active())

				//Original landis4.0: sites(i,j)->landUnit->active()

				//changed By Qia on Oct 13 2008

			{

				m(i,j)=0; 

				myage = 0;

				SPECIE *s=sites(i,j)->first();				

				int temp;

				while (s!=NULL)

				{

					if ( (temp = s->oldest() ) > myage)

						myage = temp;					

					s=sites(i,j)->next();

				}

				myage = (int) myage/sites.TimeStep;

				/*if (myage == 0)

				{

					m(i,j) = maxLeg - 1; //No Species present

				}

				else if( (myage) < (maxLeg -4))

				{

					m(i,j) = myage + 2; //map value = oldest age + 2

				}

				else

				{

					m(i,j) = maxLeg - 2; // oldest age >= 252

				}*///Commented By Qia on Jan 28 2009

				m(i,j)=myage;//changed By Qia on Jan 28 2009

				

			} 

			else if (sites.locateLanduPt(i,j)->lowland())

				//Original landis4.0: sites(i,j)->landUnit->lowland()

				//changed By Qia on Oct 13 2008

				m(i,j)=MaxValueforLegend-3;//changed By Qia on Jan 28 2009

	 		else if (sites.locateLanduPt(i,j)->water())

				//Original landis4.0: sites(i,j)->landUnit->water()

				//changed By Qia on Oct 13 2008

				m(i,j)=MaxValueforLegend-2;//changed By Qia on Jan 28 2009

	 		else

				m(i,j)=MaxValueforLegend-1;//changed By Qia on Jan 28 2009

        }

    }	

}





void speciesAgeMap(MAP8 &m, char *ageFile)  

//This will output age at 10 year step for each specified species.

//The cohorts can be up to 50 age classes, 0-500 years.

{

FILE *infile;

char str[200],speciesName[10];

int i, j;

int snr, snc;



/*if ((infile=LDfopen(ageFile,1))==NULL)

{

	printf("%s%s\n", ageFile," file not found.");

   exit(255);

}



if (fscanc(infile,"%s", speciesName)!=1)

{

	printf("%s%s%s%s\n", "Error... when reading species ", speciesName, " from ",ageFile);

   exit(255);

}*/

sprintf(str,"%s",ageFile);

int curSp=speciesAttrs.current(ageFile);



snr=sites.numRows();

snc=sites.numColumns();

m.dim(snr,snc);

m.rename(str);



for (i=1;i<maxLeg-4;i++)

   {

    sprintf(str,"%3d - %3d yr",(i-1)*sites.TimeStep+1,(i-1)*sites.TimeStep+sites.TimeStep);

    m.assignLeg(i,str);

   }

sprintf(str,"     >%3d yr", (i-1)*sites.TimeStep);

/*m.assignLeg(0,"N/A");

m.assignLeg(1,"Water");

m.assignLeg(2,"NonForest");

m.assignLeg(maxLeg-2,str);

m.assignLeg(maxLeg-1,"NotPresent");*///commented By Qia on Jan 28 2009

	//<Add By Qia on Jan 28 2009>

		m.assignLeg(0,"NotPresent");

		m.assignLeg(MaxValueforLegend-1,"N/A");

		m.assignLeg(MaxValueforLegend-2,"Water");

		m.assignLeg(MaxValueforLegend-3,"NonForest");

		m.assignLeg(MaxValueforLegend-4,str);

	//<Add By Qia on Jan 28 2009>

	

for (i=snr;i>=1;i--)

{

	for (j=1;j<=snc;j++)

   {

	if(sites.locateLanduPt(i,j)==NULL){

		errorSys("Invalid landunit error\n",STOP);

		}

   	if (sites.locateLanduPt(i,j)->active())//Original in Landis4.0: sites(i,j)->landUnit->active(), change by Qia on Oct 10 2008

      {	 m(i,j)=0;       //where species not presents

      	 if(sites(i,j)==NULL){

		 	errorSys("No site\n",STOP);

      	 	}

		 SPECIE *s=sites(i,j)->current(curSp);

		 if(s==NULL){

		 	printf("%d\n",curSp);

		 	errorSys("No Species\n",STOP);

		 	}

		  if(s->query())

		 {	m(i,j)=(unsigned short)(s->oldest()/sites.TimeStep); //compare ageReclass which uses +3 there???

			if (m(i,j)>MaxValueforLegend-4)   //maximum longevity is 640 years// Notice 66 means 640 years

	          m(i,j)=MaxValueforLegend-4;

		 }

		}

	

	else if (sites.locateLanduPt(i,j)->water()){ //Original in Landis4.0: sites(i,j)->landUnit, change by Qia on Oct 10 2008

      	m(i,j)=MaxValueforLegend-2;

		}

    else if (sites.locateLanduPt(i,j)->lowland()){//Original in Landis4.0: sites(i,j)->landUnit, change by Qia on Oct 10 2008

      	m(i,j)=MaxValueforLegend-3;

		}

   	else

	    m(i,j)=MaxValueforLegend-1;

   }

}

//LDfclose(infile);

}

