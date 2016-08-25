#include <stdlib.h>

#include <stdio.h>

#include "system1.h"

#include "specie.h"

#include "sites.h"

#include "landis.h"

#include "reclass3.h"



void reclassify(int timeStep, char ageMaps[MAX_SPECIES][80])

//This will reclassify sites from user defined class file and the existing age

//maps. Class file is a file containing site descriptions for a set of class.

//Age maps involved in the reclassification need to be created before.



{

int coverType, curSp, specAtNum=speciesAttrs.number();

int yDim=sites.numRows();

int xDim=sites.numColumns();

unsigned char c;

unsigned long dest[64];

char str[200],speciesName[10];

FILE	*inAgeMap, *inAgeIndex;



for (int i=0;i<specAtNum;i++)

{

	//read species name from ageIndex file

	sprintf(str,"%s.age",ageMaps[i]);

   if ((inAgeIndex=fopen(str,"r"))==NULL)

   {

		printf("%s%s\n", str," file not found.");

   	    exit(255);

   }

   else if (fscanc(inAgeIndex, "%s", speciesName) != 1)

   {

		printf("%s%s\n", "Error, reading file::", str);

   	    exit(255);

   }

   curSp=speciesAttrs.current(speciesName);

   //read age map file from output directory

   sprintf(str,"%s/%s%d.gis",parameters.outputDir,ageMaps[i],timeStep);

   if ((inAgeMap=fopen(str, "rb"))==NULL)

   {

		printf("%s%s\n", str," file not found.");

    	exit(255);

   }

   else

   {

   	fread((char*)dest,4,32,inAgeMap);

   }

   // read inAgeMap

   for (int i=yDim;i>0;i--)

   {

		for (int j=1;j<=xDim;j++)

		{

   		    fread((unsigned char*)(&c),1,1,inAgeMap);

	  		coverType=(unsigned int)c;

            if (coverType==255)          //species absence

			{

         		SPECIE *s=sites(i,j)->current(curSp);

				s->clear();

			}

			//J.Yang insepct following later

			else if (//(sites(i,j)->landUnit->active())&&

      	  		(coverType!=255)&&(coverType>=3)) //0-empty 1-water 2-nonforest

			{

         		SPECIE *s=sites(i,j)->current(curSp);

				s->clear();

				s->set((coverType-2)*sites.TimeStep);

			}

   		}

   }

   fclose(inAgeMap);

}

fclose(inAgeIndex);

}



