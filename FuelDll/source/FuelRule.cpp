// FuelRule.cpp: implementation of the FuelRule class.

//

//////////////////////////////////////////////////////////////////////

#include "FuelRule.h"

#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include "system1.h"

#include "error.h"





//////////////////////////////////////////////////////////////////////

// Construction/Destruction

//////////////////////////////////////////////////////////////////////



FuelRule::FuelRule()

{

	fireProbReclass = 0;

}



FuelRule::~FuelRule()

{

	//if(fireSeverity)	delete [] fireSeverity;

	//if(fireRisk)		delete [] fireRisk;

	//if(fireProbility)	delete [] fireProbility;



}



void FuelRule::read(FILE* infile) {

//Read a fuel rule from a file.



	int i, j, tem;



	for(i=0; i<5; i++) {

		//for (j=0; j<5; j++) 	fscanc(infile,"%d",&tem);		

		//for (j=0; j<5; j++) 	fscanc(infile,"%d",&tem);



		for (j=0; j<5; j++) {		

			if (fscanc(infile,"%d",&tem)!=1)				

				errorSys("Error reading in fuel quality classes from mattix file.",STOP);

			else fireIntensity[i][j] = tem;

			// read in the fire severity class

			//printf("%6d",fireSeverity[i][j]);

		}

		//printf("\n");

	}

	//printf("\nFire probility \n");

	/*

	if(fscanc(infile,"%d",&fireProbReclass)!=1)

		errorSys("Error reading in fire probility from mattix file.",STOP);

	*/

	fireProbReclass = 1;

	  // read in flag of the fire probability class

	//if (fireProbReclass)	printf("Use real criteria for fire probility reclassification\n");

	// if flag >0, then use the real criteria to classify the fire probability from decimal data to category data

	// if not, then calculate the criteria to calssify. See 

	for( j=0;j<5;j++) {		

		if(fscanc(infile,"%f",&fireProbility[j])!=1)

			errorSys("Error reading in fire probility from mattix file.",STOP);

		// read in the fire probability criteria

		if(fireProbReclass)	fireProbilityClass[j] = fireProbility[j];

		// if flag >0, then use the inputed fire probility criteria

		

		//printf("%6.4f    ",fireProbility[j]);

	}

	//printf("\n");



	for(i=0; i<5; i++) {

		for (j=0; j<5; j++) {		

			if (fscanc(infile,"%d",&fireRisk[i][j])!=1)

				errorSys("Error reading in fuel quality classes from mattix file.",STOP);

			// read in the fire risk cretria

			//printf("%6d",fireRisk[i][j]);

		}

		//printf("\n");



	}

}



int FuelRule::getFireIntensity (int FFLoad, int CFLoad) {

	// this function return the fire severity class

	int FireIntensity = 0;

	if (FFLoad>0 && FFLoad<=5 && CFLoad>0 && CFLoad<=5) {

		FireIntensity = fireIntensity[FFLoad-1][CFLoad-1];

		//printf("FF: %d  CF: %d  FI: %d\n",FFLoad,CFLoad, FireIntensity);

	}



	else FireIntensity = 0;



	return FireIntensity;

}



