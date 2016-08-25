#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include "system1.h"

#include "map8.h"

#include "specie.h"

#include "site.h"

#include "landis.h"

#include "reclass2.h"

#include "error.h"



///////////////////////////////////////////////////////////////////////////

//			STATIC MODULE DATA STRUCTURES			 //

///////////////////////////////////////////////////////////////////////////



static int maximum[MAX_RECLASS];   //Maximum table.

static int BOOL[MAX_RECLASS][MAX_RECLASS];  //Boolean table of class values.

static int numClasses;    //Number of output classes.



////////////////////////////////////////////////////////////////////////////

//			  INTERNAL CLASS IMPLEMENTATIONS		  //

////////////////////////////////////////////////////////////////////////////



static void reset()

//This will reset the reclassification system.



{

int specAtnum=speciesAttrs.number();

for (int i=1;i<=specAtnum;i++)

   {

    //maximum[i-1]=speciesAttrs(i)->longevity;

    maximum[i-1]=(int)((float)(speciesAttrs(i)->longevity)*(float)

                    (1.0/((float)(speciesAttrs(i)->reclassCoef)+0.00000001)));

	//J.Yang add 0.0...01 here, avoid dividing by 0

    }	 

}



void readInClassDescrip(FILE *infile)

//This will read in a class description file given the file name

//and the number of classes in the file (m).



{

int i, j, bvalue;

int specAtnum=speciesAttrs.number();

char str[200], sub[200], *p;



for (i=0;i<MAX_RECLASS;i++)     /// if this is not done the reclass maps

    for (j=0;j<MAX_RECLASS;j++) /// do not get reclassified _CSH

       BOOL[i][j]=0;



i=1;

numClasses=0;

while (!LDeof(infile))

{

	LDfgets(str,199,infile);

   p=str;

   int numChar;

   if (sscanf(p,"%s%n",sub,&numChar)==1)

   {

   	numClasses++;

      p+=numChar+1;

      while (*p!='\0' && *p!='\n' && *(p-1)!='\0' && *(p-1)!='\n')

      {

      	if (sscanf(p,"%s%n",sub,&numChar)!=1)

	         break;

         p+=numChar+1;

	      if (sub[0]=='!')

         {

		   	bvalue=-1;

		   	strcpy(sub,&sub[1]);

		  	}

         else

         {

         	bvalue=1;

		  	}

         for (int j=1;j<=specAtnum;j++)

         if (strcmp(speciesAttrs(j)->name,sub)==0)

         	BOOL[i][j]=bvalue;

      }

      	i++;

   }

}

}



int reclassificationValue(SPECIE *s)

//This will calculate the reclassification value given a specie list for a 

//site.



{



	//J.Yang the original coding is equivalent to the AGELIST::number();

	//I therefore just use the function instead

	return s->number();



}



int reclassifySite(SITE *site, int m)

//This will reclassify a singular site.  M is the number of possible output

//classes.



{

float sval[MAX_RECLASS];

int i, j=1;

SPECIE *specie;

float c;



for (i=0;i<MAX_RECLASS;i++)

    sval[i]=0.0;

specie=site->first();

while (specie!=NULL)

{

     c=(float)specie->oldest()/(float)maximum[j-1];

     if (c>1.0)

        c=1.0;

     for (i=1;i<=m;i++) 

     {

		if (BOOL[i][j]!=0)

	 	{

	  		(BOOL[i][j]>0) ? (sval[i]+=c) : (sval[i]-=c) ;

      	           if (sval[i] != 0)

	   	           {

	    		      if (sval[i]>1.0) sval[i]=1.0;

	    		      if (sval[i]<0.0) sval[i]=0.0;

	   	           }

	 	}

     }

     j++;

     specie=site->next();

}



int mx=0;

float mxVal=0.0;

for (i=1;i<=m;i++)

   if (sval[i]>mxVal)

   {

	   mxVal=sval[i];

      mx=i;

   }



if (mxVal>0.0)

    return mx;

else

    return m+1;

}



//////////////////////////////////////////////////////////////////////////////

//	    			EXTERNAL FUNCTIONS	                    //

//////////////////////////////////////////////////////////////////////////////



void fileReclass(MAP8 &m, const char *fname)

//This will reclass the Landis map and return the result m.  The map will

//be reclassified using a method defined in a an output reclassification

//text file.



{

char str[200], sub[200];

FILE *infile;

int i=3, n=0;  

int snr, snc;

//int mxNum[MAX_RECLASS]={0}; //J.Yang 04/17/2002



if ((infile=LDfopen((char*)fname, 1))==NULL){

	printf("\n%s",fname);

	 errorSys("Can not open reclassification file",STOP);

}



reset();

snr=sites.numRows();

snc=sites.numColumns();

sprintf(str,"Reclassification file: %s",fname);

m.rename(str);

m.dim(snr,snc);

/*m.assignLeg(0,"N/A");

m.assignLeg(1,"Water");

m.assignLeg(2,"NonForest");*///commented By Qia on Feb 09 2009

	m.assignLeg(MaxValueforLegend-1,"N/A");

	m.assignLeg(MaxValueforLegend-2,"Water");

	m.assignLeg(MaxValueforLegend-3,"NonForest");

i=1;//Add By Qia on Feb 09 2009

while (!LDeof(infile))

{

	sprintf(str,""); 

	LDfgets(str,199,infile);

	if (sscanf(str,"%s",sub)==1)

    {

		sub[strlen(sub)-1]='\0';

	 	m.assignLeg(i,sub);

	 	i++;

	 	n++;

	}

}

m.assignLeg(i,"Other");

for (int j=i+1;j<maxLeg-3;j++)

	m.assignLeg(j,"");

LDrewind(infile);

readInClassDescrip(infile);



for (i=snr;i>=1;i--)

{

	for (int j=1;j<=snc;j++)

	{

   		if (sites.locateLanduPt(i,j)->active())

			//Original landis4.0: sites(i,j)->landUnit->active()

			//Change By Qia on Oct 13 2008

			m(i,j)=(unsigned short)(reclassifySite(sites(i,j),n));//changed by Qia on Feb 09 2009		  			

	 	else if (sites.locateLanduPt(i,j)->lowland())

			//Original landis4.0: sites(i,j)->landUnit->lowland()

			//Change By Qia on Oct 13 2008

			m(i,j)=MaxValueforLegend-3;

	 	else if (sites.locateLanduPt(i,j)->water())

			//Original landis4.0: sites(i,j)->landUnit->water()

			//Change By Qia on Oct 13 2008

			m(i,j)=MaxValueforLegend-2;

	 	else

			m(i,j)=MaxValueforLegend-1;

   }

}

LDfclose(infile);

}

