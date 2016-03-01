#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include "defines.h"

#include "system1.h"

#include "error.h"

#include "specatt.h"

#include "specatts.h"

#include "landu.h"



LANDUNIT::LANDUNIT()

//Constructor.



{

 name=NULL;

 minShade = 0;

/* ignitionCoef=0.0;

 probCoef=0;

 fireInterval=0;

 */ //deleted by Wei, April 8, 2004



 probReproduction=NULL;

 probReproductionOriginalBackup=NULL;

 speciesAttrs=NULL;

 ltID = 0;



}



LANDUNIT::~LANDUNIT()

//Destructor.



{



if(name)

	delete [] name; //Nim: changed delete to delete []

if(probReproduction)

	delete [] probReproduction;

if(probReproductionOriginalBackup)

	delete [] probReproductionOriginalBackup;



}



void LANDUNIT::attach(SPECIESATTRS *s)



{

 speciesAttrs=s;

}



void LANDUNIT::read(FILE* infile)

//Read a land unit from a file.



{

int i; //Nim: added this line

if (speciesAttrs==NULL)

	errorSys("LANDUNIT::read(FILE*)-> No attaced species attributes.",STOP);



char instring[25];

int specAtNum=speciesAttrs->number();

if (fscanc(infile,"%s",instring)!=1)

   errorSys("Error reading in name from landtype file.",STOP);

if(name!=NULL){

	delete name;

	name=new char[strlen(instring)+1];

}

else{

name=new char[strlen(instring)+1]; //Nim: added this line

}

strcpy(name,instring);



if (fscanc(infile,"%d",&minShade)!=1)

   errorSys("Error reading in minShade from landtpye file.",STOP);



/*if (fscanc(infile,"%d",&fireInterval)!=1)

   errorSys("Error reading in fireInterval from landtype file.",STOP);



if (fscanc(infile,"%f",&ignitionCoef)!=1)

   errorSys("Error reading in fire ignition coefficient from landtype file.",STOP);



if (fscanc(infile,"%d",&probCoef)!=1)

   errorSys("Error reading in probability coefficient from landtype file.",STOP);

*/



if (fscanc(infile,"%d",&initialLastWind)!=1)

   errorSys("Error reading in initialLastWind from landtype file.",STOP);

//<Add By Qia on July 2 2009>

if (fscanc(infile,"%f",&MaxRDArray[0])!=1)

	errorSys("Error reading in maxRD from landtype file.",STOP);


//</Add By Qia on July 2 2009>

//<Add By Qia on Oct 14 2010>

if (fscanc(infile,"%f",&MaxRDArray[1])!=1)

	errorSys("Error reading in maxRD from landtype file.",STOP);


if (fscanc(infile,"%f",&MaxRDArray[2])!=1)

	errorSys("Error reading in maxRD from landtype file.",STOP);

if (fscanc(infile,"%f",&MaxRDArray[3])!=1)

	errorSys("Error reading in maxRD from landtype file.",STOP);

MaxRD= MaxRDArray[3];

//</Add By Qia on Oct 14 2010>



/*if (fscanc(infile,"%d",&initialLastFire)!=1)

   errorSys("Error reading in initialLastFire from landtype file.",STOP);

*/

if(probReproduction!=NULL){

	delete probReproduction;

	probReproduction=new float[speciesAttrs->number()];

}

else{

probReproduction=new float[speciesAttrs->number()];

}

//<Add By Qia on Jan 15 2009>

if(probReproductionOriginalBackup!=NULL){

	delete probReproductionOriginalBackup;

	probReproductionOriginalBackup= new float[speciesAttrs->number()];

}

else{

probReproductionOriginalBackup= new float[speciesAttrs->number()];

}

//</Add By Qia on Jan 15 2009>

for (i=0;i<specAtNum;i++)  {//Nim: changed int i to i

    if (fscanc(infile,"%f",&probReproduction[i])!=1)

       errorSys("Error reading in probReproduction from landtype file.",STOP);
}

/*

for (i=0;i<5;i++)  //Nim: changed int i to i

    if (fscanc(infile,"%d",&fireCurve[i])!=1)

       errorSys("Error reading in fireCurve from landtype file.",STOP);



for (i=0;i<5;i++)  //Nim: changed int i to i

    if (fscanc(infile,"%d",&fireClass[i])!=1)

       errorSys("Error reading in fireClass from landtype file.",STOP);



for (i=0;i<5;i++)  //Nim: changed int i to i

    if (fscanc(infile,"%d",&windCurve[i])!=1)

       errorSys("Error reading in windCurve from landtype file.",STOP);



for (i=0;i<5;i++)  //Nim: changed int i to i

    if (fscanc(infile,"%d",&windClass[i])!=1)

       errorSys("Error reading in windClass from landtype file.",STOP);

*/



if (_stricmp(name,"empty")==0||_stricmp(name,"road")==0)

   status=PASSIVE;

else if (_stricmp(name,"water")==0)

     status=WATER;

else if (_stricmp(name,"wetland")==0)

     status=WETLAND;

else if (_stricmp(name,"bog")==0)

     status=BOG;

else if (_stricmp(name,"lowland")==0)

     status=LOWLAND;

else if (_stricmp(name,"nonforest")==0)

     status = NONFOREST;

else if (_stricmp(name,"grassland")==0)

     status = GRASSLAND;

else

     status=ACTIVE;

}



void LANDUNIT::write(FILE* outfile)

//Write a land unit to a file.



{

int i; //Nim: added this line

int specAtNum=speciesAttrs->number();

if (speciesAttrs==NULL)

   errorSys("LANDUNIT::write(FILE*)-> No attaced species attributes.",STOP);



fprintf(outfile,"%s ",minShade, name);

/*

fprintf(outfile,"%d %d ",fireInterval);

fprintf(outfile,"%d %d ",ignitionCoef);

fprintf(outfile,"%d %d ",probCoef);

*/

for (i=0;i<specAtNum;i++) //Nim: changed int i to i

    fprintf(outfile,"%2.2f ",probReproduction[i]);

fprintf(outfile,"\n");



/*

for (i=0;i<5;i++)        //Nim: changed int i to i

    fprintf(outfile,"%d ",fireCurve[i]);

fprintf(outfile,"\n");

for (i=0;i<5;i++)        //Nim: changed int i to i

    fprintf(outfile,"%d ",fireClass[i]);

*/

fprintf(outfile,"\n");



}



void LANDUNIT::dump()

//Dump a land unit to the CRT.



{

int i; //Nim: added this line

int specAtNum=speciesAttrs->number();

if (speciesAttrs==NULL)

   errorSys("LANDUNIT::dump(FILE*)-> No attaced species attributes.",STOP);



printf("Name:          %s\n",name);

/*

printf("fireInterval:  %d\n",fireInterval);

printf("probCoef:      %d\n",probCoef);

printf("ignitionCoef:  %d\n",ignitionCoef);

*/

for (i=0;i<specAtNum;i++) //Nim: changed int i to i

    printf("%s: %2.2f\n",(*speciesAttrs)(i+1)->name,probReproduction[i]);

/*

for (i=0;i<5;i++)        //Nim: changed int i to i

    printf("Class %d:  %d\n",fireClass[i],fireCurve[i]);

	*/

}



float LANDUNIT::probRepro(int s)

//Returns the probability of reproduction of the given species on the given

//land unit.  Species is referrenced by number.



{

if (s<=speciesAttrs->number() && s>0)

    return probReproduction[s-1];



errorSys("LANDUNIT::probRepro(int)-> Array bounds error.",STOP);

return 0.0;

}



float LANDUNIT::probRepro(char *s)

//Returns the probability of reproduction of the given species on the given

//land unit.  Species is referrenced by name.



{

int specAtNum=speciesAttrs->number();

for (int i=0;i<specAtNum;i++)

{

   if (strcmp((*speciesAttrs)(i+1)->name,s)==0)

      return probReproduction[i];

}



errorSys("LANDUNIT::probRepro(char*)-> Illegal species name.",STOP);

return 0.0;

}



float LANDUNIT::probRepro(SPECIESATTR *s)

//Returns the probability of reproduction of the given species on the given

//land unit.  Species is referrenced by species record.



{

int specAtNum=speciesAttrs->number();

for (int i=0;i<specAtNum;i++)

{

    if (strcmp((*speciesAttrs)(i+1)->name,s->name)==0)

       return probReproduction[i];

}



errorSys("LANDUNIT::probRepro(SPECIESATTR*)-> Illegal spec. attr.",STOP);

return 0.0;

}

int LANDUNIT::Get_status(){
	return status;
}

int LANDUNIT::active()

//



{

if (status==ACTIVE)

	return true;

else

	return false;

}



int LANDUNIT::water()



{

if (status==WATER)

	return true;

else

	return false;

}





int LANDUNIT::lowland()

//

{

if (status==WETLAND || status==BOG || status==LOWLAND || status==NONFOREST)

	return true;

else

	return false;

}



