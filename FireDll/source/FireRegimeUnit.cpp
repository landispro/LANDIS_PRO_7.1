// FireRegimeUnit.cpp: implementation of the CFireRegimeUnit class.

//

//////////////////////////////////////////////////////////////////////



#include "FireRegimeUnit.h"

#include "system1.h"

#include "error.h"



#include <string.h>



//////////////////////////////////////////////////////////////////////

// Construction/Destruction

//////////////////////////////////////////////////////////////////////



CFireRegimeUnit::CFireRegimeUnit()

{

 name=NULL;

 m_fIgPoisson=0.0;

 m_fMFS = 0.0;

 m_fFireSTD = 0.0;

 fireInterval=0; 



}



CFireRegimeUnit::~CFireRegimeUnit()

{

if(name)

	delete [] name; //Nim: changed delete to delete []



}



int CFireRegimeUnit::active()

{

if (status==ACTIVE)

	return true;

else

	return false;

}



void CFireRegimeUnit::dump()

{

	int i;

	printf("Name:          %s\n",name);

	printf("fireInterval:  %d\n",fireInterval);

	printf("IgnitionPoissonParameter:  %f\n",m_fIgPoisson);

	printf("MFS:      %f\n",m_fMFS);

	printf("FS STD deviation:      %f\n",m_fFireSTD);

	for (i=0;i<5;i++)        //Nim: changed int i to i

		printf("Class %d:  %d\n",fireClass[i],fireCurve[i]);	

}



void CFireRegimeUnit::read(FILE * infile)

{

	int i;

	char instring[255];

	if (fscanc(infile,"%s",instring)!=1)

		errorSys("Error reading in name from landtype file.",STOP);	

	

	if (name) 

		delete [] name;

	name=new char[strlen(instring)+1]; 

	strcpy(name,instring);

	if (fscanc(infile,"%d",&fireInterval)!=1)

		errorSys("Error reading in fireInterval from landtype file.",STOP);

	if (fscanc(infile,"%f",&m_fIgPoisson)!=1)

		errorSys("Error reading in fire ignition poisson parameter from landtype file.",STOP);

	if (fscanc(infile,"%f",&m_fMFS)!=1)

		errorSys("Error reading in MFS from landtype file.",STOP);

	if (fscanc(infile,"%f",&m_fFireSTD)!=1)

		errorSys("Error reading in fire size Variance from landtype file.",STOP);

	if (fscanc(infile,"%d",&initialLastFire)!=1)

		errorSys("Error reading in initialLastFire from landtype file.",STOP);

	for (i=0;i<5;i++)  

		if (fscanc(infile,"%d",&fireCurve[i])!=1)

			errorSys("Error reading in fireCurve from landtype file.",STOP);

	for (i=0;i<5;i++)  

		if (fscanc(infile,"%d",&fireClass[i])!=1)

			errorSys("Error reading in fireClass from landtype file.",STOP);

	for (i=0;i<5;i++)  

		if (fscanc(infile,"%d",&windCurve[i])!=1)

			errorSys("Error reading in fireCurve from landtype file.",STOP);

	for (i=0;i<5;i++)  

		if (fscanc(infile,"%d",&windClass[i])!=1)

			errorSys("Error reading in fireClass from landtype file.",STOP);





	if (_stricmp(name,"empty")==0)

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

	else

		status=ACTIVE;	

	

}



int CFireRegimeUnit::water()

{

	if (status==WATER)

		return true;

	else

		return false;

}



void CFireRegimeUnit::write(FILE * outfile)

{

	int i;	

	LDfprintf0(outfile,"%d \n",fireInterval);

	LDfprintf0(outfile,"%f \n",m_fIgPoisson);

	LDfprintf0(outfile,"%f \n",m_fMFS);

	LDfprintf0(outfile,"%f \n",m_fFireSTD);

	for (i=0;i<5;i++)        

		LDfprintf0(outfile,"%d ",fireCurve[i]);

	LDfprintf0(outfile,"\n");

	for (i=0;i<5;i++)        

		LDfprintf0(outfile,"%d ",fireClass[i]);

	LDfprintf0(outfile,"\n");

}



